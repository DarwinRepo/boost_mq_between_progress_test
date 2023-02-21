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

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
