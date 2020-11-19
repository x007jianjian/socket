#include "socketudp.h"
#include "sockettcp.h"

#include <iostream>
#include <stdio.h>
#include <cstring>
using namespace std;

#include <opencv/cv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;



int main()
{
	string inImageDir = "C:\\Users\\Administrator\\Desktop\\slambook-master\\ch5\\joinMap\\mytestData\\color\\1.png";
	string inImageDir2 = "C:\\Users\\Administrator\\Desktop\\slambook-master\\ch5\\joinMap\\mytestData\\color\\dd1.png";

	cv::Mat img_ori = cv::imread(inImageDir.c_str(), -1);
	cv::Mat img_ori2 = cv::imread(inImageDir2.c_str(), -1);

	char * data = (char*)img_ori.data;
	char* data2 = (char*)img_ori2.data;



	othka::comm::SocketTCP sender;
	sender.Connect("127.0.0.1", 1234);
	sender.Blocking(false);
	system("pause");

	int counter = 0;

	while (1)
	{
		//发送字符串测试
		//counter++;
		//sender.Send(to_string(counter));
		//cout << counter << endl;
		//Sleep(1000);

		//发送图片
		counter++;
		//dataa.ifGot = counter;
		//cout << dataa.ifGot << endl;
		//sender.Send((char*) & dataa, sizeof(struct Dataa));
		if(counter%2)
			sender.Send(data, 1080*1920*3);//一定要写上要发送的大小，不然char*遇到\0就会被截断
		else
			sender.Send(data2, 1080 * 1920 * 3);
		Sleep(30);
		//cout << "sended" << endl;
		//cout << "sizeof Data:" << sizeof(struct Dataa) << endl;
	}



}

//接收
//int main()
//{
//	cv::Mat receive_img;
//
//	othka::comm::SocketTCP receiver;
//	othka::comm::SocketTCP socket_accept;
//
//	receiver.Listen(1234, "127.0.0.1");
//	receiver.Blocking(false);
//	receiver.WaitRecv(10000);
//	system("pause");
//
//	receiver.MakeConnect(&socket_accept);
//	socket_accept.Blocking(false);
//
//	string receivedStr;
//
//	while (1)
//	{
//		////接收字符串测试
//		//if (socket_accept.Recv(receivedStr))
//		//{
//		//	cout << receivedStr << endl;
//		//}
//		if (socket_accept.Recv(receivedStr) && receivedStr.size() == 1080 * 1920 * 3)
//		{
//			cout << receivedStr.size() << endl;
//			void* receivedData = (void*)receivedStr.c_str();
//			//char* receivedData = (char*)receivedStr.c_str();
//			cv::Mat receivedImg = cv::Mat(1080, 1920, CV_8UC3, receivedData);
//			cv::imshow("", receivedImg);
//			cv::waitKey(30);
//			//cv::waitKey(0);
//		}
//	}
//}


//TCP单元测试代码

//void TCPTest()
//{
//	std::string receive_buffer = "test";
//	std::string client_receive;
//	othka::comm::SocketTCP socket_client;
//	othka::comm::SocketTCP socket_server;
//	othka::comm::SocketTCP socket_accept;
//
//
//	try
//	{
//		socket_server.Listen(6008);
//		socket_server.Blocking(false);
//
//		socket_client.Connect("127.0.0.1", 6008);
//		socket_client.Blocking(false);
//	}
//	catch (const char* e)
//	{
//		std::cout << "Unable to create TCP socket : " << e << std::endl;
//		return;
//	}
//
//	std::cout << "client sent message.\n";
//	socket_client.Send("client test message.");
//
//	std::cout << "Server wait for receiving" << std::endl;
//	if (!socket_server.WaitRecv(10000))
//	{
//		std::cout << "No reception on server." << std::endl;
//		return;
//	}
//
//	std::cout << "Server accept connection" << std::endl;
//	if (!socket_server.MakeConnect(&socket_accept))
//	{
//		std::cout << "Fail to accept reception." << std::endl;
//		return;
//	}
//	std::cout << "Server receiving" << std::endl;
//	socket_accept.Blocking(false);
//
//	bool is_rece = socket_accept.Recv(receive_buffer);
//
//	if (is_rece)
//	{
//		std::cout << "Server receive : " << receive_buffer << std::endl;
//		bool is_send = socket_accept.Send("server send message.");
//		std::cout << "Server sending message" << std::endl;
//	}
//
//
//	if (!socket_client.WaitRecv(10000))
//	{
//		std::cout << "Argh ! No reception on client." << std::endl;
//		return;
//	}
//
//	try
//	{
//		socket_client.Recv(client_receive);
//	}
//	catch (const char* e)
//	{
//		std::cout << "Argh ! Unable to receive data : " << e << std::endl;
//		return;
//	}
//
//	std::cout << "Client receive : " << client_receive << std::endl;
//
//	socket_server.Close();
//	socket_client.Close();
//	socket_accept.Close();
//	std::cout << "All sockets are closed" << std::endl;
//}
