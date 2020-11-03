#pragma once
#include "Condition.h"
#include "MutexLock.h"
#include "noncopyable.h"
//����count��countDown()�� �㲥��������wait���߳� עwait��������++count ֻ�ڳ�ʼ��ʱ��ֵ
// CountDownLatch����Ҫ������ȷ��Thread�д���ȥ��func����������Ժ�
// ����start�ŷ���
class CountDownLatch : noncopyable {
public:
	explicit CountDownLatch(int count);
	void wait();
	void countDown();

private:
	mutable MutexLock mutex_;
	Condition condition_;
	int count_;
};