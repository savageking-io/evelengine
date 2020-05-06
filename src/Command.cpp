#include "Command.hpp"

namespace EvelEngine
{

    bool Command::handleCommand(const std::string& command)
    {
        return false;
    }

    const std::string& Command::output() const {
        return _output;
    }

}
