#include "ProtectedQueue.h"

ProtectedQueue::ProtectedQueue() {}

void ProtectedQueue::push(const uint8_t element) {
	std::lock_guard<std::mutex> lock(m);
	queue.push(element);
}

bool ProtectedQueue::isEmpty() const {
	return queue.empty();
}

uint8_t ProtectedQueue::pop() {
	std::lock_guard<std::mutex> lock(m);
	uint8_t element = queue.front();
	queue.pop();

	return element;
}

ProtectedQueue::~ProtectedQueue() {}