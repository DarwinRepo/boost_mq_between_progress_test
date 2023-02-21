// boost_mq_bet_pro.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <thread>
#include <boost/interprocess/ipc/message_queue.hpp> 
#include <boost/timer/timer.hpp>

using namespace boost::interprocess;
using namespace boost::timer;

cpu_timer SysTimer;

int main()
{
    std::cout << "Hello Boost MQ Server!\n";    
	message_queue::remove("req");
	message_queue::remove("rep");
    message_queue mq_req(open_or_create, "req", 1024, 1024, permissions());
	message_queue mq_rep(open_or_create, "rep", 1024, 1024, permissions());
    auto buffer = new char[1024];

    boost::ulong_long_type recvd_size;
    unsigned int priority;

	while (1)
	{
		int times = 1000 * 1000;
		for (int i = 0; i < times; i++)
		{
			mq_req.receive(buffer, 1024, recvd_size, priority);
			mq_rep.send(buffer, 1024, 0);
		}
		Sleep(50);
	}
    
   
}


