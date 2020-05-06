#include "Simulation.hpp"

namespace EvelEngine
{
    Simulation::Simulation()
    {
        _state = SIM_INIT;
    }

    Simulation::~Simulation()
    {

    }

    bool Simulation::handleCommand(const std::string& command)
    {
        if (command == "quit")
        {
            _state = SIM_SHUTDOWN;
            return true;
        }
        return false;
    }

    SimulationState Simulation::getState()
    {
        return _state;
    }

    void Simulation::setState(SimulationState state)
    {
        _state = state;
    }
}
