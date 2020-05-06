#include "Assert.hpp"

namespace EvelEngine
{
    void Assert::do_assert(const char* condition, const char* file, int linenum, const char* text)
    {
#if defined(EVEL_DEBUG)
        std::stringstream output;
        output << "Assertion Violation: " << condition;
        if (text)
        {
            output << " [" << text << "]";
        }
        output << " in " << file << " at " << linenum << std::endl;
        std::fputs(output.str().c_str(), stderr);
        abort();
#endif
    }

}
