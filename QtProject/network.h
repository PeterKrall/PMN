#ifndef NETWORK_H
#define NETWORK_H
#include "configuration.h"
#include <ostream>
#include <fstream>
#include <vector>
namespace pnm
{

    class Network
    {
    public:
        static long double run  (
                                  Configuration&            configuration
                                );
    private:
        static bool open_out_file(
                                   Configuration&           configuration
                                 , std::ofstream&           out
                                 );

        static long double day  (
                                  Configuration&            configuration
                                , std::ostream&             out
                                , long double*              p_non_initial
                                , long double*              max_triggerings
                                , long double*              max_triggerings_1
                                , long double*              max_triggerings_2
                                , std::vector<long double>& triggered_states_1
                                , std::vector<long double>& triggered_states_2
                                , int                       today
                                );
    };

} // namespace pnm

#endif // NETWORK_H
