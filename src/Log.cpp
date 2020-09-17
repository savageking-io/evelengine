#include "Log.hpp"

namespace EvelEngine
{
    Log::Log()
    {

    }

    Log::~Log()
    {

    }

    void Log::initialize()
    {
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        // console_sink->set_level(spdlog::level::debug);
        
        std::shared_ptr<spdlog::sinks::basic_file_sink_mt> file_sink = nullptr;
        try {
            file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("evel-engine.log", true);
        } catch (spdlog::spdlog_ex& e) {
            error("Failed to initialize log files: {0}", e.what());
        }

        _log = std::make_shared<spdlog::logger>("evel", console_sink );
        if (file_sink != nullptr) _log->sinks().push_back(file_sink);
        _log->set_level(spdlog::level::debug);
        info("Initializing loggin subsystem");
        spdlog::register_logger(_log);
    }

    void Log::setLevel(spdlog::level::level_enum level)
    {
        if (_log == nullptr) return;
        _log->set_level(level);
    }

    std::shared_ptr<spdlog::logger> Log::sget()
    {
        return _log;
    }

}
