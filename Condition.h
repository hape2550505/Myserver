#pragma once
#pragma once
#include <errno.h>
#include <pthread.h>
#include <pthread.h>
#include <time.h>
#include <cstdint>
#include "MutexLock.h"
#include "noncopyable.h"
/*
��Ҫ�����ڶ�������ߵ����

notify������໽��һ���߳�

���߳�����һ��mutex��ʼ��condition

Ȼ���ڲ�ͬ���߳�wait

�����߳�notify

��װ��api��ֱ�ۣ��������Լ�ȥ����pthread_cond_wait pthread_cond_signal�����Ѽǵ�api*/

class Condition : noncopyable {
public:
	explicit Condition(MutexLock &_mutex) : mutex(_mutex) {
		pthread_cond_init(&cond, NULL);
	}
	~Condition() { pthread_cond_destroy(&cond); }
	void wait() { pthread_cond_wait(&cond, mutex.get()); }
	void notify() { pthread_cond_signal(&cond); }
	void notifyAll() { pthread_cond_broadcast(&cond); }
	bool waitForSeconds(int seconds) {//��ӵ�
		struct timespec abstime;
		clock_gettime(CLOCK_REALTIME, &abstime);
		abstime.tv_sec += static_cast<time_t>(seconds);
		return ETIMEDOUT == pthread_cond_timedwait(&cond, mutex.get(), &abstime);
	}

private:
	MutexLock &mutex;
	pthread_cond_t cond;
};