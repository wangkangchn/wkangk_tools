/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: custom_format.hpp
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 自定义格式输出
时间	   	: 2023-06-18 15:32
***************************************************************/
#ifndef __WKANGK_TOOLS_CUSTOM_FORMAT_HPP__ 
#define __WKANGK_TOOLS_CUSTOM_FORMAT_HPP__ 
#include <chrono>

#include <spdlog/fmt/fmt.h>

#include "config.hpp"


WKANGK_TOOLS_BEGIN_NAMESPACE

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

WKANGK_TOOLS_END_NAMESPACE

#endif	/* !__WKANGK_TOOLS_CUSTOM_FORMAT_HPP__ */