// Client.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

#include <iostream>
#include <thread>
#include <boost/interprocess/ipc/message_queue.hpp> 
#include <boost/timer/timer.hpp>

using namespace boost::interprocess;
using namespace boost::timer;

cpu_timer SysTimer;
cpu_timer SysTimerTemp;
int main()
{
	std::cout << "Hello Boost MQ Client!\n";
	
	message_queue mq_req(open_only, "req");
	message_queue mq_rep(open_only, "rep");

	boost::ulong_long_type recvd_size;
	unsigned int priority;

	auto buffer = new char[1024];

	while(1)
	{
		int times = 1000 * 1000;
		SysTimer.start();
		for (int i = 0; i < times; i++)
		{
			SysTimerTemp.start();
			mq_req.send(buffer, 1024, 0);
			mq_rep.receive(buffer, 1024, recvd_size, priority);
			//SysTimerTemp.stop();
			std::cout << "Current cost time  = " << SysTimerTemp.elapsed().wall / 1000.0 << " us." << std::endl;
			Sleep(1);
		}
		SysTimer.stop();
		auto cost_time = SysTimer.elapsed().wall;
		std::cout << "Total cost time = " << cost_time /1000.0 << " us." << std::endl;
		std::cout << "Avg cost time = " << cost_time / (double)times /1000.0  << " us." << std::endl;
		Sleep(1000);
	}
}

