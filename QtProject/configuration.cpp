#include "configuration.h"

namespace pnm
{

    Configuration::Configuration    (
                                      std::string output_directory
                                    , std::string run_label
                                    , int eternity
                                    , long double replacement_initial_a
                                    , long double replacement_final_a
                                    , int number_of_contact_events_per_day_a
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
                                    , long double additional_active_state_factor
                                    , int transformation_period
                                    )
                                    :
                                      run_label(run_label)
                                    , output_directory(output_directory)
                                    , eternity(eternity)
                                    , replacement_initial_a(replacement_initial_a)
                                    , replacement_final_a(replacement_final_a)
                                    , number_of_contact_events_per_day_a(number_of_contact_events_per_day_a)
                                    , pre_active_state_duration_1(pre_active_state_duration_1)
                                    , pre_active_state_duration_2(pre_active_state_duration_2)
                                    , active_state_duration_1(active_state_duration_1)
                                    , active_state_duration_2(active_state_duration_2)
                                    , transmission_probability_1_a(transmission_probability_1_a)
                                    , transmission_probability_2_a(transmission_probability_2_a)
                                    , days_before_switch(days_before_switch)
                                    , number_of_contact_events_per_day_b(number_of_contact_events_per_day_b)
                                    , replacement_initial_b(replacement_initial_b)
                                    , replacement_final_b(replacement_final_b)
                                    , transmission_probability_1_b(transmission_probability_1_b)
                                    , transmission_probability_2_b(transmission_probability_2_b)
                                    , additional_active_state_factor(additional_active_state_factor)
                                    , transformation_period(transformation_period)
                                    {}
} // namespace pnm
