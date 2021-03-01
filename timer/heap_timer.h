#ifndef LST_TIMER
#define LST_TIMER
#include <queue>
#include <time.h>
#include "../log/log.h"

class util_timer;
struct client_data
{
    sockaddr_in address;
    int sockfd;
    util_timer *timer;
};

class util_timer
{
public:
	util_timer() { 
		del = false;
	};

public:
    time_t expire;
    void (*cb_func)(client_data *);
    client_data *user_data;
	bool del;
};

class timer_heap
{
public:
    timer_heap() {}
    ~timer_heap()//ɾ�����нڵ�
    {
        while (!min_heap.empty())
        {
			min_heap.pop();
        }
    }
    void add_timer(util_timer *timer)
    {
        if (!timer)
        {
            return;
        }
        min_heap.push(timer);
        return;
    }
    void adjust_timer(util_timer *timer)
    {
		//��ʱ�Ѿ��޸Ĺ�ʱ���ˣ�ֻ�ǿ������ȶ���û�е���
    }
	void del_timer(util_timer *timer)//��֧������ɾ��ֻ֧�ֳ�ʱɾ��
	{
		timer->del = true;
	}

    void tick()
    {
        if (min_heap.empty())
        {
            return;
        }
        //printf( "timer tick\n" );
        LOG_INFO("%s", "timer tick");
        Log::get_instance()->flush();
        time_t cur = time(NULL);
        util_timer *tmp = min_heap.top();
        while (tmp)
        {
            if (cur < tmp->expire&&!tmp->del)//�Դ���ʱ��or�б�ʶ�Ľ���ɾ��
            {
                break;
            }
            tmp->cb_func(tmp->user_data);
			min_heap.pop();
			tmp = min_heap.top();
        }
    }

private:
	struct cmp {
		bool operator()(const util_timer* a, const util_timer* b) {
			return a->expire < b->expire;//����ÿ��pushʱ����
		}
	};
	
	priority_queue < util_timer*, vector<util_timer*>,cmp > min_heap;
};

#endif
