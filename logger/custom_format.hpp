/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: custom_format.hpp
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 自定义格式输出
时间	   	: 2023-06-18 15:32
***************************************************************/
#ifndef __TOOLS_CUSTOM_FORMAT_HPP__ 
#define __TOOLS_CUSTOM_FORMAT_HPP__ 
#include <chrono>

#include <spdlog/spdlog.h>
#include <spdlog/fmt/fmt.h>

#include "config.hpp"

template<>
struct fmt::formatter<std::chrono::system_clock::time_point> : fmt::formatter<std::string>
{
    auto format(std::chrono::system_clock::time_point tp, 
                format_context &ctx) -> decltype(ctx.out())
    {
        auto tt = std::chrono::system_clock::to_time_t ( tp );
        return format_to(ctx.out(), "{}", ctime(&tt));
    }
};


TOOLS_BEGIN_NAMESPACE

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


TOOLS_END_NAMESPACE

#endif	/* !__TOOLS_CUSTOM_FORMAT_HPP__ */