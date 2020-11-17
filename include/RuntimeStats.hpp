#ifndef __RUNTIME_STATS_HPP__
#define __RUNTIME_STATS_HPP__

#include <string>

#include "Engine.hpp"

namespace EvelEngine 
{
    class RuntimeStats 
    {
        public:
            RuntimeStats();
            ~RuntimeStats();
            void initialize();
            const std::string& videoDriver() const;
            const std::string& displayName() const;
        private:
            void requestVideoDriver();
            void requestDisplayName();
            void requestWindowSize();
            void requestViewport();
            Log* _log;
            std::string _videoDriver;
            std::string _displayName;
    };
}

#endif
