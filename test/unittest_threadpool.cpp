/***************************************************************
Copyright © wkangk <wangkangchn@163.com>
文件名		: unittest_threadpool.cpp
作者	  	: wkangk <wangkangchn@163.com>
版本	   	: v1.0
描述	   	: 测试线程池
时间	   	: 2023-06-23 13:38
***************************************************************/
#include <iostream>

#include <gmock/gmock.h>

#include "thread/thread_pool.hpp"


USEING_TOOLS_NAMESPACE


void fun1(int slp)
{
    std::cout << "  hello, fun1 !  " << std::this_thread::get_id() << "\n";
    if (slp>0) {
        std::cout << "  hello, fun1 !  " << std::this_thread::get_id() << "\n";
        printf(" ======= fun1 sleep %d  =========  ", slp);
        std::cout << std::this_thread::get_id() << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(slp));
    }
}

struct gfun 
{
    int operator()(int n) {
        std::cout << n <<  "  hello, gfun !  " << std::this_thread::get_id() << "\n";
        return 42;
    }
};

class A 
{
public:
    static int Afun(int n = 0) {   //函数必须是 static 的才能直接使用线程池
        std::cout << n << "  hello, Afun !  " << std::this_thread::get_id() << std::endl;
        return n;
    }

    static std::string Bfun(int n, std::string str, char c) {
        std::cout << n << "  hello, Bfun !  "<< str.c_str() <<"  " << (int)c <<"  " << std::this_thread::get_id() << std::endl;
        return str;
    }
};


TEST(ThreadPool, work) 
{
    ThreadPool executor{ 50 };
    A a;
    std::future<void> ff = executor.commit(fun1, 0);
    std::future<int> fg = executor.commit(gfun{},0);
    std::future<int> gg = executor.commit(a.Afun, 9999); //IDE提示错误,但可以编译运行
    std::future<std::string> gh = executor.commit(A::Bfun, 9998,"mult args", 123);
    std::future<std::string> fh = executor.commit([]()->std::string { std::cout << "hello, fh !  " << std::this_thread::get_id() << std::endl; return "hello,fh ret !"; });

    std::cout << " =======  sleep ========= " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(std::chrono::microseconds(900));

    for (int i = 0; i < 50; i++) {
        executor.commit(fun1,i*100 );
    }

    std::cout << " =======  sleep ========= " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));

    ff.get(); //调用.get()获取返回值会等待线程执行完,获取返回值
    std::cout << fg.get() << "  " << fh.get().c_str()<< "  " << std::this_thread::get_id() << std::endl;

    std::cout << " =======  sleep ========= " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));

    std::cout << " =======  fun1,55 ========= " << std::this_thread::get_id() << std::endl;
    executor.commit(fun1,55).get();    //调用.get()获取返回值会等待线程执行完

    std::cout << "end... " << std::this_thread::get_id() << std::endl;


    ThreadPool pool(4);
    std::vector< std::future<int> > results;

    for (int i = 0; i < 2; ++i) {
        results.emplace_back(
            pool.commit([i] {
                std::cout << "hello " << i << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                std::cout << "world " << i << std::endl;
                return i*i;
            })
        );
    }
    std::cout << " =======  commit all2 ========= " << std::this_thread::get_id() << std::endl;

    for (auto && result : results)
        std::cout << result.get() << ' ';
    std::cout << std::endl;

    std::cout << "main end" << std::endl;
}


int main(int argc, char* argv[])
{   
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}