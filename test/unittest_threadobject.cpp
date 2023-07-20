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
#include "command_flags.h"
#include "thread/thread_object.hpp"


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



class MyTask : public ThreadObject
{
protected:
    virtual bool work() override
    {   
        static size_t count = 0;
        if (count++ >= 5) {
            std::cout << std::this_thread::get_id() << " 退出\n";
            return false;
        }
        std::cout << std::this_thread::get_id() << " 运行\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        return true;
    }
};

TEST(ThreadObject, work)
{   
    MyTask task;

    std::cout << std::this_thread::get_id() << " task 开始运行\n";
    task.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(4000));

    std::cout << std::this_thread::get_id() << " 要求 task 暂停\n";
    task.pause();
    std::this_thread::sleep_for(std::chrono::milliseconds(4000));

    std::cout << std::this_thread::get_id() << " 要求 task 恢复运行\n";
    task.resume();
    std::this_thread::sleep_for(std::chrono::milliseconds(4000));

    std::cout << std::this_thread::get_id() << " 要求 task 停止\n";
    task.stop();
}

int main(int argc, char* argv[])
{   
    gflags::ParseCommandLineFlags(&argc, &argv, true); 
    testing::AddGlobalTestEnvironment(new MyEnvironment);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}