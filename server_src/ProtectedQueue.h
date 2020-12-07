#ifndef PROTECTEDQUEUE_H
#define PROTECTEDQUEUE_H

#include <queue>
#include <mutex>

class ProtectedQueue {
private:
	std::mutex m;
	std::queue<uint8_t> queue;
public:
	ProtectedQueue();
	void push(const uint8_t element);
	bool isEmpty() const;
	uint8_t pop();
	~ProtectedQueue();
};

#endif
