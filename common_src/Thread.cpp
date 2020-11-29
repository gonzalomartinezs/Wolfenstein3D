#include "Thread.h"

#include <utility>

Thread::Thread() {}

Thread::Thread(Thread&& other) {
	thread = std::move(other.thread);
}

Thread& Thread::operator=(Thread&& other) {
	thread = std::move(other.thread);

	return *this;
}

void Thread::start() {
	thread = std::thread(&Thread::run, this);
}

void Thread::join() {
	thread.join();
}

Thread::~Thread() {}
