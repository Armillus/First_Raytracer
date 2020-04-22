/*
 * Created on Tue Apr 21 2020
 *
 * Copyright (c) raytracer 2020 Arthur Lang
 * ThreadPool.cpp
 */

#include "ThreadPool.hpp"

#include <future>
#include <iostream>

rt::ThreadPool::ThreadPool(const int &threadLimit) : _state(true), _threadLimit(threadLimit)
{
    for (int i = 0; i < threadLimit; i++) {
        _threads.emplace_back(std::bind(&rt::ThreadPool::work, this));
    }
}

rt::ThreadPool::~ThreadPool()
{
    {
        std::unique_lock<std::mutex> lock(_mutex);
        _state = false;
    }
    joinAll();
}

void rt::ThreadPool::addTask(const std::function<void(void)> &fct)
{
    _mutex.lock();
    _task.emplace(fct);
    _mutex.unlock();
    _condVar.notify_one();
}


void rt::ThreadPool::joinAll()
{
    _condVar.notify_all();
    for (auto &_t : _threads)
        _t.join();
}

void rt::ThreadPool::work()
{
    while(_state) {
        std::unique_lock<std::mutex> lock(_mutex);
        if (_task.empty()) {
            _condVar.wait(lock);
        } else {
            auto task = _task.front();
            _task.pop();
            lock.unlock();
            task();
            lock.lock();
        }
    }
}

void fct1(std::promise<int> &res, int a, int b)
{
    std::this_thread::sleep_for(std::chrono::seconds(3));
    res.set_value(a + b);
}

void fct2(std::promise<int> &res, int a, int b, int c)
{
    std::this_thread::sleep_for(std::chrono::seconds(3));
    res.set_value(a + b + c);
}

int main()
{
    rt::ThreadPool t(5);
    std::promise<int>p1;
    std::future f1 = p1.get_future();
    t.addTask(std::bind(fct1, std::ref(p1), 1, 2));

    std::promise<int>p2;
    std::future f2 = p2.get_future();
    t.addTask(std::bind(fct1, std::ref(p2), 3, -2));

    std::promise<int>p3;
    std::future f3 = p3.get_future();
    t.addTask(std::bind(fct2, std::ref(p3), 1, 20, 10));

    std::promise<int>p4;
    std::future f4 = p4.get_future();
    t.addTask(std::bind(fct1, std::ref(p4), -1, -2));

    std::promise<int>p5;
    std::future f5 = p5.get_future();
    t.addTask(std::bind(fct2, std::ref(p5), 14, 40, 30));
    return 0;
}
