/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: common.hpp
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 
时间	   	: 2023-05-30 20:49
***************************************************************/
#ifndef __WKANGK_TOOLS_COMMON_HPP__ 
#define __WKANGK_TOOLS_COMMON_HPP__ 
#include "config.hpp"

WKANGK_TOOLS_BEGIN_NAMESPACE

class INoCopy
{
protected:
    INoCopy() = default;
    virtual ~INoCopy() = default;
    INoCopy(const INoCopy&) = delete;
    INoCopy& operator=(const INoCopy&) = delete;
    INoCopy(INoCopy&&) = delete;
    INoCopy& operator=(INoCopy&&) = delete;
};


#if RPCLIB_CXX_STANDARD >= 14
    using std::make_unique;
#else
    #include <memory>
    template <class T, class... Args>
    typename std::enable_if<!std::is_array<T>::value, std::unique_ptr<T>>::type
    make_unique(Args &&...args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
    }
#endif


#include <chrono>
constexpr std::chrono::seconds operator ""_s(unsigned long long s)
{
    return std::chrono::seconds(s);
}
constexpr std::chrono::duration<long double> operator ""_s(long double s)
{
    return std::chrono::duration<long double>(s);
}

constexpr std::chrono::microseconds operator ""_us(unsigned long long us)
{
    return std::chrono::microseconds(us);
}
constexpr std::chrono::duration<long double> operator ""_us(long double us)
{
    return std::chrono::duration<long double>(us);
}

constexpr std::chrono::milliseconds operator ""_ms(unsigned long long ms)
{
    return std::chrono::milliseconds(ms);
}
constexpr std::chrono::duration<long double> operator ""_ms(long double ms)
{
    return std::chrono::duration<long double>(ms);
}

WKANGK_TOOLS_END_NAMESPACE
#endif	/* !__WKANGK_TOOLS_COMMON_HPP__ */
