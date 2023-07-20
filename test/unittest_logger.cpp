/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: unittest_learning.cpp
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 测试 threadobject
时间	   	: 2023-05-30 21:45
***************************************************************/
#include <chrono>
#include <iostream>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "common.hpp"
#include "logger/logger.hpp"
#include "logger/custom_format.hpp"
#include "command_flags.h"


USEING_TOOLS_NAMESPACE


using std::cout;
using std::endl;
using std::string;
using namespace testing;


class MyEnvironment : public testing::Environment
{
public:
    virtual void SetUp()
    {   
        MyLogger::setup(FLAGS_log_fn, string_to_log_level(FLAGS_log_level));
        INFO("测试开始");
    }

    virtual void TearDown()
    {
        INFO( "测试结束." );
    }
};




TEST(MyLogger, format)
{   
    std::string str = format("你好 {}", "format");
    EXPECT_THAT("你好 format", StrEq(str));
}

template <typename T>
struct Point_t
{   
    Point_t(T x, T y) : x(x), y(y) {}
    T x, y;
};

template<>
struct fmt::formatter<Point_t<int>> : fmt::formatter<std::string>
{
    auto format(Point_t<int> my, format_context &ctx) -> decltype(ctx.out())
    {
        return format_to(ctx.out(), "x = {}, y = {}", my.x, my.y);
    }
};

TEST(MyLogger, custom_type)
{   
    Point_t<int> pt(1, 23);

    std::string str = format("{}", pt);
    EXPECT_THAT("x = 1, y = 23", StrEq(str));
}

int main(int argc, char* argv[])
{   
    gflags::ParseCommandLineFlags(&argc, &argv, true); 
    testing::AddGlobalTestEnvironment(new MyEnvironment);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}