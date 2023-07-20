/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: logger.cpp
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 
时间	   	: 2023-05-30 20:59
***************************************************************/
#include "logger/logger.hpp"

TOOLS_BEGIN_NAMESPACE

std::shared_ptr<spdlog::logger> MyLogger::logger_ = nullptr;

LogLevel string_to_log_level(const std::string& log_level)
{
    if (log_level == "debug") {  return LogLevel::LOG_LEVEL_DEBUG;   }
    if (log_level == "info") {  return LogLevel::LOG_LEVEL_INFO;   }
    if (log_level == "warn") {  return LogLevel::LOG_LEVEL_WARN;   }
    if (log_level == "error") {  return LogLevel::LOG_LEVEL_ERROR;   }
    return LogLevel::LOG_LEVEL_INFO;
}

void MyLogger::setup(const std::string& log_fn, LogLevel log_level)
{   
    /* 控制台输出 */
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_pattern("[%m/%d %R][%s %!:%#]%^[%L] %v%$");

    /* 输出到日志文件 */
    auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
                        log_fn, 1024 * 1024 * 5, 3);
    file_sink->set_pattern("[%m/%d %R][%s %!:%#]%^[%L] %v%$");

    logger_ = std::shared_ptr<spdlog::logger>(new spdlog::logger("mylogger_multi_sink",
                                                        {console_sink, file_sink}));
    logger_->flush_on(spdlog::level::warn); /* 打印 warn 时, 强制同步日志到文件 */
    spdlog::register_logger(logger_);

    spdlog::flush_every(3_s);
    set_level(log_level);
}

void MyLogger::set_level(LogLevel log_level)
{
    spdlog::level::level_enum level = spdlog::level::info;
    switch (log_level) {
        case LogLevel::LOG_LEVEL_DEBUG:
            level = spdlog::level::debug;
            break;
        
        case LogLevel::LOG_LEVEL_INFO:
            break;
        
        case LogLevel::LOG_LEVEL_WARN:
            level = spdlog::level::warn;
            break;

        case LogLevel::LOG_LEVEL_ERROR:
            level = spdlog::level::err;
            break;
        
        default:
            break;
    }

    logger_->set_level(level);
}

TOOLS_END_NAMESPACE