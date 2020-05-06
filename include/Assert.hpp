#ifndef __EVEL_ENGINE_ASSERT_HPP__
#define __EVEL_ENGINE_ASSERT_HPP__

#include <cstdlib>
#include <string>
#include <sstream>

namespace EvelEngine
{
    class Assert
    {
        public:
            static void do_assert(const char* condition, const char* file, int linenum, const char* text = 0);
    };
}

#if defined(EVEL_DEBUG)
    #define evel_assert(cond) \
        if (!(cond)) EvelEngine::Assert::do_assert(#cond, __FILE__, __LINE__); else (void) 0

    #define evel_assert_msg(cond, text) \
        if (!(cond)) EvelEngine::Assert::do_assert(#cond, __FILE__, __LINE__, text); else (void) 0
#else
    #define evel_assert(cond) 
    #define evel_assert_msg(cond, text)
#endif

#endif
