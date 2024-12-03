#ifndef CONFIGURATION_H
#define CONFIGURATION_H
#include <string>
namespace pnm
{

    class Configuration
    {
    public:
        Configuration   (
                          std::string output_directory
                        , std::string run_label
                        , int eternity
                        , long double replacement_initial_a
                        , long double replacement_final_a
                        , int number_of_contact_events_per_day
                        , int pre_active_state_duration_1
                        , int pre_active_state_duration_2
                        , int active_state_duration_1
                        , int active_state_duration_2
                        , long double transmission_probability_1_a
                        , long double transmission_probability_2_a
                        , int days_before_switch
                        , int number_of_contact_events_per_day_b
                        , long double replacement_initial_b
                        , long double replacement_final_b
                        , long double transmission_probability_1_b
                        , long double transmission_probability_2_b
                        , long double additional_active_state_factor = 0
                        , int transformation_period = 0
                        );
        const std::string run_label;
        const std::string output_directory;
        const int eternity;
        const long double replacement_initial_a;
        const long double replacement_final_a;
        const int number_of_contact_events_per_day_a;
        const int pre_active_state_duration_1;
        const int pre_active_state_duration_2;
        const int active_state_duration_1;
        const int active_state_duration_2;
        const long double transmission_probability_1_a;
        const long double transmission_probability_2_a;
        const int days_before_switch;
        const int number_of_contact_events_per_day_b;
        const long double replacement_initial_b;
        const long double replacement_final_b;
        const long double transmission_probability_1_b;
        const long double transmission_probability_2_b;
        const long double additional_active_state_factor;
        const int transformation_period;
    };

} // namespace pnm

#endif // CONFIGURATION_H
