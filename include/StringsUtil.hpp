#ifndef __EVEL_ENGINE_STRINGS_UTIL_HPP__
#define __EVEL_ENGINE_STRINGS_UTIL_HPP__

#include <vector>
#include <string>

namespace EvelEngine 
{
    class StringsUtil
    {
        public:
        enum Options 
        {
            SPLIT_IGNORE_EMPTY = 1,
            SPLIT_TRIM = 2
        };
        
        // split string into parts using specified separator
        static std::vector<std::string> Split(const std::string& str, const std::string& separator, int options = 0);
        static void Trim(std::string& str);
    };
}

#endif
