
#pragma once

#include "CurrentThread.h"
#include "Thread.h"

namespace muduo
{

class EventLoop : noncopyable
{
 public:

  EventLoop();
  ~EventLoop();

  void loop();
  //���һ��assertInLoopThread����������⵱ǰ�߳��Ƿ���ڸ�eventloop�����threadid
  void assertInLoopThread()
  {
    if (!isInLoopThread())
    {
      abortNotInLoopThread();
    }
  }

  bool isInLoopThread() const { return threadId_ == CurrentThread::tid(); }

 private:

  void abortNotInLoopThread();

  bool looping_; /* atomic */
  const pid_t threadId_;
};

}

