#ifndef THREAD_H
#define THREAD_H

#include <thread>

class Thread {
private:
	std::thread thread;
public:
	Thread();
	Thread(const Thread& other) = delete;
	Thread& operator=(const Thread& other) = delete;
	Thread(Thread&& other);
	Thread& operator=(Thread&& other);
	void start();
	void join();
	virtual void run() = 0;
	virtual void stop() = 0;
	virtual bool finished() = 0;
	virtual ~Thread();
};

#endif
