#ifndef __EVEL_ENGINE_LOG_HPP__
#define __EVEL_ENGINE_LOG_HPP__

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

namespace EvelEngine {
    class Log
    {
        public:
            Log();
            ~Log();
            void initialize();
            void setLevel(spdlog::level::level_enum level);
            std::shared_ptr<spdlog::logger> sget();
            template<typename... Args>
                void trace(const char* fmt, const Args&... args)
                {
                    if (_log == nullptr) return;
                    _log->trace(fmt, args...);
                }

            template<typename... Args>
                void debug(const char* fmt, const Args&... args)
                {
                    if (_log == nullptr) return;
                    _log->debug(fmt, args...);
                }

            template<typename... Args>
                void info(const char* fmt, const Args&... args)
                {
                    if (_log == nullptr) return;
                    _log->info(fmt, args...);
                }

            template<typename... Args>
                void warn(const char* fmt, const Args&... args)
                {
                    if (_log == nullptr) return;
                    _log->warn(fmt, args...);
                }

            template<typename... Args>
                void error(const char* fmt, const Args&... args)
                {
                    if (_log == nullptr) return;
                    _log->error(fmt, args...);
                }


            template<typename... Args>
                void critical(const char* fmt, const Args&... args)
                {
                    if (_log == nullptr) return;
                    _log->critical(fmt, args...);
                }
        private:
            std::shared_ptr<spdlog::logger> _log; ///< Logging subsystem
    };
}

#endif
