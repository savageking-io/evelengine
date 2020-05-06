#ifndef __EVEL_ENGINE_SIMULATION_HPP__
#define __EVEL_ENGINE_SIMULATION_HPP__

#include "Command.hpp"

namespace EvelEngine
{
    typedef enum {
        SIM_INIT,
        SIM_RUNNING,
        SIM_SHUTDOWN
    } SimulationState;

    class Simulation : public Command
    {
        public:
            Simulation();
            ~Simulation();
            bool handleCommand(const std::string& command);
            SimulationState getState();
            void setState(SimulationState state);
        private:
            SimulationState _state;
    };
}

#endif
