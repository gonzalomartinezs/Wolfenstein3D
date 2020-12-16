#ifndef WOLFENSTEIN3D_PROTECTEDQUEUE_H
#define WOLFENSTEIN3D_PROTECTEDQUEUE_H

#include <queue>
#include <mutex>

template <class T>
class ProtectedQueue {
private:
	std::mutex m;
	std::queue<T> queue;
public:
    /* Constructor */
	ProtectedQueue();
	void push(const T element);
	bool isEmpty() const;
	T pop();
	/* Destructor */
	~ProtectedQueue();
};

template<class T> ProtectedQueue<T>::ProtectedQueue() {}

template<class T> void ProtectedQueue<T>::push(const T element) {
    std::lock_guard<std::mutex> lock(m);
    queue.push(element);
}

template<class T> bool ProtectedQueue<T>::isEmpty() const {
    return queue.empty();
}

template<class T> T ProtectedQueue<T>::pop() {
    std::lock_guard<std::mutex> lock(m);
    T element = queue.front();
    queue.pop();
    return element;
}

template<class T> ProtectedQueue<T>::~ProtectedQueue() {}

#endif  // WOLFENSTEIN3D_PROTECTEDQUEUE_H
