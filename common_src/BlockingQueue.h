//
// Created by ezezbogar on 16/12/20.
//

#ifndef WOLFENSTEIN3D_BLOCKINGQUEUE_H_
#define WOLFENSTEIN3D_BLOCKINGQUEUE_H_

#include "../common_src/Exceptions/WolfensteinException.h"
#include <mutex>
#include <condition_variable>
#include <queue>

template <class T>
class BlockingQueue {
private:
    std::queue<T> queue;
    std::mutex mtx;
    std::condition_variable cv;
    bool finishedAdding{false};

public:
    void push(T element);
    T pop();
    bool isWorking();
    void doneAdding();
};

template <typename T> void BlockingQueue<T>::push(T element) {
    std::unique_lock<std::mutex> lock(mtx);
    queue.push(std::move(element));
    cv.notify_all();
}

template <typename T> T BlockingQueue<T>::pop() {
    std::unique_lock<std::mutex> lock(mtx);
    while (queue.empty() && !finishedAdding) {
        cv.wait(lock);
    }
    if (!queue.empty()) {
        T element = std::move(queue.front());
        queue.pop();
        return element;
    }
    throw WolfensteinException("Blocking queue doesn't accept new elements anymore!\n");
}

template <typename T>bool BlockingQueue<T>::isWorking() {
    return (finishedAdding && queue.empty());
}

template <typename T> void BlockingQueue<T>::doneAdding() {
    std::unique_lock<std::mutex> lock(mtx);
    finishedAdding = true;
    cv.notify_all();
}

#endif  // WOLFENSTEIN3D_BLOCKINGQUEUE_H_
