/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: thread_pool.hpp
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 线程池
时间	   	: 2023-05-07 16:56
***************************************************************/
#ifndef __WKANGK_TOOLS_THREAD_POOL_HPP__ 
#define __WKANGK_TOOLS_THREAD_POOL_HPP__ 
#include <iostream>
#include <queue>
#include <mutex>
#include <atomic>
#include <future>
#include <thread>
#include <functional>
#include <type_traits>
#include <condition_variable>

#include "common.hpp"


WKANGK_TOOLS_BEGIN_NAMESPACE


/**
 *  线程池, 仅可移动, 不可复制
 */
class ThreadPool
{

public:
    /**
     * \param [in]  pool_size:  线程池数目, 线程池内部限制最大线程数目为
     *                              std::thread::hardware_concurrency() - 1
     */
    explicit ThreadPool(size_t pool_size)
    {
        create_thread_pool(pool_size);
    }

    ~ThreadPool()
    {
        clear();
    }

    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;

public:

    /**
     *      提交一个任务到任务队列
     * 
     * \param [in]  f:      可调用对象
     * \param [in]  args:   任意参数 
     * \return     以 std::future 的方式返回传入的可调用对象的返回值
     */
    template <typename Callable, typename ...Args>
    std::future<typename std::result_of<Callable(Args...)>::type>
    commit(Callable&& f, Args&&... args)
    {
        using ResultType = typename std::result_of<Callable(Args...)>::type;

        /* 1. 包装函数使其可以能够获取返回值 */
        // auto task = std::packaged_task<ResultType()>(           /* 因为 packaged_task 仅可移动, 不能复制, 所以不能按值传递到 lambda 中 */
        //     std::bind(std::forward<Callable>(f), std::forward<Args>(args)...)
        // );
        // auto reture_future = task.get_future();
        auto task = std::make_shared<std::packaged_task<ResultType()>>(           /* 这里包装一下函数值, 使其仅保留返回值 */
            std::bind(std::forward<Callable>(f), std::forward<Args>(args)...)
        );
        auto reture_future = task->get_future();

        /* 2. 将任务添加至任务队列 */
        {
            std::lock_guard<std::mutex> lck{mtx_};
            task_queue_.emplace(
                [task]
                {
                    (*task)();
                }
            );
        }
        cv_.notify_one();
        return reture_future;
    }

private:
    void create_thread_pool(size_t pool_size)
    {   
        if (pool_size > std::thread::hardware_concurrency() - 1) {
            pool_size = std::thread::hardware_concurrency() - 1;
        }
        pool_size = pool_size > 0 ? pool_size : 1;
        thread_pool_.reserve(pool_size);

        try {
            for (size_t i = 0; i < pool_size; ++i) {
                thread_pool_.emplace_back(
                    [this]
                    {   
                        /* 不断从任务队列中取出任务而后执行 */
                        while (true) {
                            TaskType task;
                            {
                                std::unique_lock<std::mutex> lck{mtx_};
                                cv_.wait(lck, [this] { return !task_queue_.empty() || stop_; });    /* 主动唤醒, 或条件成立时, 条件变量会唤醒 */

                                if (task_queue_.empty() && stop_) {     /* 只有当任务队列全空, 且设置停止标记时才退出 */
                                    break;
                                }

                                task = std::move(task_queue_.front());
                                task_queue_.pop();
                            }

                            /* 执行任务 */
                            task();
                        }
                    }
                );
            }
        } catch (std::exception& e) {
            clear();
            throw e;
        }
    }

    void clear()
    {
        stop_.store(true);
        cv_.notify_all(); // 唤醒所有线程执行, 保证当有空闲线程时, 空闲线程亦能安全退出
        for (auto& th : thread_pool_) {
            if (th.joinable()) {
                th.join();
            }
        }
    }

private:
    using TaskType = std::function<void()>;         /*!< 任务类型 */
    std::vector<std::thread>    thread_pool_;       /*!< 存放执行线程 */
    std::queue<TaskType>        task_queue_;        /*!< 任务队列 */

    std::mutex                  mtx_;               /*!< 保护任务队列 */
    std::condition_variable     cv_;

    std::atomic<bool>           stop_{false};       /*!< 标识是否停止线程池 */
};


WKANGK_TOOLS_END_NAMESPACE
#endif	/* !__WKANGK_TOOLS_THREAD_POOL_HPP__ */
