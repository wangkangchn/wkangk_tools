/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: thread_object.hpp
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 支持暂停运行的线程
时间	   	: 2023-06-23 13:38
***************************************************************/
#ifndef __WKANGK_TOOLS_THREADOBJECT_HPP__ 
#define __WKANGK_TOOLS_THREADOBJECT_HPP__ 
#include <memory>
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>

#include "common.hpp"


WKANGK_TOOLS_BEGIN_NAMESPACE


class ThreadObject
{
public:
    /**
     * @param [in]  detach:     是否创建守护线程
     */
    ThreadObject(bool detach=false) :
        detach_(detach),
        stop_(true),
        pause_(true),
        th_(nullptr)
    {
    }

    virtual ~ThreadObject()
    {   
        stop();
        pause_.store(true);
        if (th_ && th_->joinable()) {
            th_->join();
        }
        pause_.store(true);
        th_ = nullptr;
    }

public:
    void start()
    {
        stop_.store(false);
        pause_.store(false);

        th_ = make_unique<std::thread>(&ThreadObject::run, this);

        if (detach_) {
            th_->detach();  
        }
    }

    void stop()
    {
        stop_.store(true);
    }

    void pause()
    {
        pause_.store(true);
    }

    void resume()
    {
        pause_.store(false);
        cv_.notify_one();
    }


protected:
    /**
     *     当前线程一轮循环所要做到工作
     *
     * @return     true 工作未结束, false 工作结束
     */
    virtual bool work() = 0;

private:
    void run()
    {
        while (!stop_.load()) {
            
            if (pause_) {
                std::unique_lock<std::mutex> lck{mtx_};
                cv_.wait(lck, [this] { return !pause_ || stop_; });
            }

            /* 没有停止才可以继续 */
            if (!stop_ && !work()) {  /* 返回 false 说明工作结束 */
                stop_.store(true);
            }
        }
    }

private:
    bool detach_;
    std::mutex                  mtx_;               /*!< 保护任务队列 */
    std::condition_variable     cv_;
    std::atomic<bool> stop_;
    std::atomic<bool> pause_;
    std::unique_ptr<std::thread> th_;
};

WKANGK_TOOLS_END_NAMESPACE
#endif	/* !__WKANGK_TOOLS_THREADOBJECT_HPP__ */