/*
 * Created on Mon Apr 20 2020
 *
 * Copyright (c) YEP_project1_2019 2020 Arthur Lang
 * ThreadPool.hpp
 */

#pragma once

#include <queue>
#include <vector>
#include <thread>
#include <mutex>
#include <functional>
#include <condition_variable>

namespace rt
{
    class ThreadPool {

        public:
            ThreadPool(const int &threadLimit);
            ~ThreadPool();
            
            void addTask(const std::function<void(void)> &fct);

        private:
            void joinAll();
            void work();

            std::mutex _mutex;
            std::condition_variable _condVar;
            bool _state;
            int _threadLimit;
            std::vector<std::thread> _threads;

            std::queue<std::function<void(void)>> _task;
    };
}
