#include "network.h"
#include <iostream>

namespace pnm
{
    /* private static */ bool Network::open_out_file(
                                                      Configuration& configuration
                                                    , std::ofstream& out
                                                    )
    {
        time_t t;
        std::time(&t);
        char out_filename[1024];
        std::tm now; localtime_s(&now,&t);
        // open matlab readable output file
        sprintf (
                  out_filename
                , "%s/%s_%d%02d%02d_%02d%02d%02d.csv"
                , configuration.output_directory.c_str()
                , configuration.run_label.c_str()
                , now.tm_year+1900,now.tm_mon+1,now.tm_mday,now.tm_hour,now.tm_min,now.tm_sec
                );
        out.open(out_filename);
        out << "day"
            << " eternity:" << configuration.eternity
            << " replacement_initial_a:" << configuration.replacement_initial_a
            << " replacement_final_a:" << configuration.replacement_final_a
            << " number_of_contact_events_per_day_a:" << configuration.number_of_contact_events_per_day_a
            << " pre_active_state_duration_1:" << configuration.pre_active_state_duration_1
            << " pre_active_state_duration_2:" << configuration.pre_active_state_duration_2
            << " active_state_duration_1:" << configuration.active_state_duration_1
            << " active_state_duration_2:" << configuration.active_state_duration_2
            << " transmission_probability_1_a:" << configuration.transmission_probability_1_a
            << " transmission_probability_2_a:" << configuration.transmission_probability_2_a
            << " days before configuration switch: " << configuration.days_before_switch
            << " number_of_contact_events_per_day_b:" << configuration.number_of_contact_events_per_day_b
            << " replacement_initial_b:" << configuration.replacement_initial_b
            << " replacement_final_b:" << configuration.replacement_final_b
            << " transmission_probability_1_b:" << configuration.transmission_probability_1_b
            << " transmission_probability_2_b:" << configuration.transmission_probability_2_b
            << " transformation_period:" << configuration.transformation_period
            << ";"
            << "\n"
            << " day"              << ";"
            << " p_triggered"      << ";"
            << " p_initial"        << ";"
            << " p_active_1"       << ";"
            << " p_triggered_1"    << ";"
            << " p_active_2"       << ";"
            << " p_triggered_2"    << ";"
            << " strain2%"         << ";"
            << " max_triggered"    << ";"
            << " max_triggered_1"  << ";"
            << " max_triggered_2"  << ";"
            << "\n";

        return out.is_open();
    }
    long double value_at_1m = 0;
    /* public static */ long double Network::run(
                                                  Configuration& configuration
                                                )
    {
        std::ofstream out;
        std::vector<long double> triggered_states_1;
        std::vector<long double> triggered_states_2;
        long double p_non_initial   = configuration.replacement_initial_a == 1
                                    ? 0
                                    :configuration.replacement_final_a / (configuration.replacement_final_a + configuration.replacement_initial_a)
                                    ;
        long double max_triggered   = 0;
        long double max_triggered_1 = 0;
        long double max_triggered_2 = 0;
        //
        bool is_open = open_out_file(configuration, out);
        double new_triggerings = 0.0;
        {
            for (int i = 0; i < configuration.pre_active_state_duration_1 + configuration.active_state_duration_1 + 1; i++)
            {
                triggered_states_1.insert(triggered_states_1.begin(),0);
            }
            triggered_states_1.insert(triggered_states_1.begin(),0.0001);
            triggered_states_1.insert(triggered_states_1.begin(),0.0001);
            triggered_states_1.insert(triggered_states_1.begin(),0.0001);
        }

        {
            for (int i = 0; i < configuration.pre_active_state_duration_2 + configuration.active_state_duration_2 + 1; i++)
            {
                triggered_states_2.insert(triggered_states_2.begin(),0);
            }
            triggered_states_2.insert(triggered_states_2.begin(),0);
        }
        int today = 0;
        while (today++ < configuration.eternity)
        {
            new_triggerings = day(configuration,out,&p_non_initial,&max_triggered,&max_triggered_1,&max_triggered_2,triggered_states_1,triggered_states_2,today);


            if ((today == configuration.eternity/4)
                && configuration.active_state_duration_2 != 0
                )
            {
                triggered_states_2.insert(triggered_states_2.begin(),new_triggerings/200);
                triggered_states_2.insert(triggered_states_2.begin(),new_triggerings/200);
                p_non_initial += new_triggerings/100;
            }

        }

        //
        out.flush();
        out.close();
        return new_triggerings;
    }

    /* private static */ long double Network::day   (
                                                      Configuration&            configuration
                                                    , std::ostream&             out
                                                    , long double*              p_non_initial
                                                    , long double*              max_triggerings
                                                    , long double*              max_triggerings_1
                                                    , long double*              max_triggerings_2
                                                    , std::vector<long double>& triggered_states_1
                                                    , std::vector<long double>& triggered_states_2
                                                    , int                       today
                                                    )
    {        
        double switch_factor    = (configuration.days_before_switch == 0 || today<configuration.days_before_switch)
                                ? 0
                                :   (today < configuration.days_before_switch + configuration.transformation_period)
                                    ? (double)(today - configuration.days_before_switch) / configuration.transformation_period
                                    : 1
                                    ;
        long double replacement_initial = configuration.replacement_initial_a * (1.0-switch_factor)
                                        + configuration.replacement_initial_b * switch_factor
                                        ;
        long double replacement_final   = configuration.replacement_final_a * (1.0-switch_factor)
                                        + configuration.replacement_final_b * switch_factor
                                        ;
        long double transmission_probability_1  = configuration.transmission_probability_1_a * (1.0-switch_factor)
                                                + configuration.transmission_probability_1_b * switch_factor
                                                ;
        long double transmission_probability_2  = configuration.transmission_probability_2_a * (1.0-switch_factor)
                                                + configuration.transmission_probability_2_b * switch_factor
                                                ;
        int number_of_contact_events_per_day    = configuration.number_of_contact_events_per_day_a * (1.0-switch_factor)
                                                + configuration.number_of_contact_events_per_day_b * switch_factor
                                                ;
        long double p_initial = 1.0 - *p_non_initial;
        long double active_nodes_1 = 0;
        long double active_nodes_2 = 0;
        long double complement_triggering_probability = 1;
        long double exchange_rate = replacement_final + replacement_initial;
        {
            std::vector<long double>::iterator it = triggered_states_1.begin()+configuration.pre_active_state_duration_1;
            double x_inc;
            for (int i = 0; i < configuration.active_state_duration_1; i++)
            {                
                active_nodes_1 += *it++ * pow(1.0-exchange_rate,configuration.pre_active_state_duration_1+1+i);
                x_inc = *(it+1) * pow(1.0-exchange_rate,configuration.pre_active_state_duration_1+2+i);
            }
            active_nodes_1 += x_inc * configuration.additional_active_state_factor;
            complement_triggering_probability -= active_nodes_1 * transmission_probability_1;
        }
        {
            std::vector<long double>::iterator it = triggered_states_2.begin()+configuration.pre_active_state_duration_2;
            for (int i = 0; i < configuration.active_state_duration_2; i++)
            {
                active_nodes_2 += *it++ * pow(1.0-exchange_rate,configuration.pre_active_state_duration_2+1+i);
            }
            complement_triggering_probability -= active_nodes_2 * transmission_probability_2;
        }
        long double new_triggerings = ((long double)1-pow(complement_triggering_probability, number_of_contact_events_per_day)) * p_initial;
        if (new_triggerings > *max_triggerings) { *max_triggerings = new_triggerings; }
        *p_non_initial += new_triggerings;
        long double new_triggerings_1   = (active_nodes_1 < 0.0000001)
                                        ? 0
                                        : new_triggerings
                                              * ( (active_nodes_1*transmission_probability_1)
                                                 /(active_nodes_1*transmission_probability_1+active_nodes_2*transmission_probability_2)
                                                )
                                        ;
        triggered_states_1.insert(triggered_states_1.begin(),new_triggerings_1);
        if (new_triggerings_1 > *max_triggerings_1) { *max_triggerings_1 = new_triggerings_1; }
        long double new_triggerings_2   = (active_nodes_2 < 0.0000001)
                                            ? 0
                                            : new_triggerings
                                                  * ( (active_nodes_2*transmission_probability_2)
                                                     /(active_nodes_1*transmission_probability_1+active_nodes_2*transmission_probability_2)
                                                     )
            ;
        triggered_states_2.insert(triggered_states_2.begin(),new_triggerings_2);
        if (new_triggerings_2 > *max_triggerings_2) { *max_triggerings_2 = new_triggerings_2; }
        if (new_triggerings == value_at_1m)
        {
            std::cout << today << ": " << new_triggerings << "\n";
        }
        if (today==pow(10,6)*8) { value_at_1m = new_triggerings; }
        if (configuration.eternity<pow(10,6)||(today % (int)pow(10,6))<1000)
        {
            out
                << today                << ";"
                << new_triggerings      << ";"
                << 1-*p_non_initial     << ";"
                << active_nodes_1       << ";"
                << new_triggerings_1    << ";"
                << active_nodes_2       << ";"
                << new_triggerings_2    << ";"
                << ( new_triggerings  < 0.00001?0:new_triggerings_2 / (new_triggerings_1 + new_triggerings_2)) << ";"
                << *max_triggerings     << ";"
                << *max_triggerings_1   << ";"
                << *max_triggerings_2   << ";"
                << "\n";
            std::cout
                << today                << " "
                << new_triggerings      << " "
                << 1-*p_non_initial     << " "
                << active_nodes_1       << " "
                << new_triggerings_1    << " "
                << active_nodes_2       << " "
                << new_triggerings_2    << " "
                << ( new_triggerings  < 0.00001?0:new_triggerings_2 / (new_triggerings_1 + new_triggerings_2)) << " "
                << *max_triggerings     << " "
                << *max_triggerings_1   << " "
                << *max_triggerings_2   << " "
                << "\n";
        }
        *p_non_initial = *p_non_initial * (1.0-(replacement_initial+replacement_final)) + replacement_final;
        return new_triggerings;
    }
} // namespace pnm
