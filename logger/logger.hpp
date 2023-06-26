/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: logger.hpp
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 使用 spdlog 进行日志记录日志
时间	   	: 2023-05-30 20:44
***************************************************************/
#ifndef __WKANGK_LOGGER_HPP__ 
#define __WKANGK_LOGGER_HPP__ 
#include <memory>
#include <string>

#include <spdlog/spdlog.h>
#include <spdlog/async.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>

#include "common.hpp"


WKANGK_TOOLS_BEGIN_NAMESPACE


enum LogLevel
{
    LOG_LEVEL_DEBUG = 0,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARN,
    LOG_LEVEL_ERROR
};

/* 
    debug | info | warn | error 四个值中的一种转换为 LogLevel
当输入值不再其中四个时, 返回 info
 */
LogLevel string_to_log_level(const std::string& log_level);

class MyLogger : public INoCopy
{
public:
    static spdlog::logger* get_instance()
    {   
        static std::unique_ptr<MyLogger> envs(new MyLogger);    /* 为了能够调到 ~MyLogger */
        return logger_.get();
    }

    static void setup(const std::string& log_fn, LogLevel log_level);
    static void set_level(LogLevel log_level);

    ~MyLogger()
    {   
        spdlog::drop_all();     
        spdlog::shutdown();
    }

private:
    MyLogger() = default;

private:
    static std::shared_ptr<spdlog::logger> logger_;
};

#define DEBUG(...) SPDLOG_LOGGER_CALL(MyLogger::get_instance(), spdlog::level::debug, __VA_ARGS__)
#define INFO(...) SPDLOG_LOGGER_CALL(MyLogger::get_instance(), spdlog::level::info, __VA_ARGS__)
#define WARN(...) SPDLOG_LOGGER_CALL(MyLogger::get_instance(), spdlog::level::warn, __VA_ARGS__)
#define ERROR(...) SPDLOG_LOGGER_CALL(MyLogger::get_instance(), spdlog::level::err, __VA_ARGS__)



/**
 *     该函数可以直接将 spdlog 的格式化形式转为 string
 * 并且当定义了自定义类型时, 也可以直接使用该 format 进行输出
 * 我真的太强了, 这都被我摘出来了, 强强强
 *
 * @param [in]  fmt     格式字符串
 * @param [in]  args    格式字符串中的参数 
 * @return     格式化后字符串
 */
template<typename... Args>
std::string format(spdlog::format_string_t<Args...> fmt, Args &&... args)
{
    spdlog::memory_buf_t buf;
    fmt::vformat_to(fmt::appender(buf), spdlog::details::to_string_view(fmt), fmt::make_format_args(args...));
    return std::string(buf.begin(), buf.end());
}

WKANGK_TOOLS_END_NAMESPACE
#endif	/* !__WKANGK_LOGGER_HPP__ */