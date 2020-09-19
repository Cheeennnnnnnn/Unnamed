#include<stdio.h>
#include<winsock2.h>
#pragma comment(lib,"WS2_32")

int main()
{
	WSADATA swadata;
	WORD sockVersion=MAKEWORD(2,0);//winsock的版本2.0
	WSAStartup(sockVersion,&swadata);//加载WInsock库，swadata返回库的信息
 
   //创建套接字
	SOCKET s=::socket(AF_INET,SOCK_STREAM,0);
	if(s==-1)
	{
		printf("Creat scoket is failed!\n");
		::WSACleanup();
		system("pause");
		return 0;
	}
	//填充socaddr_in结构
	sockaddr_in sin;
	sin.sin_family=AF_INET;
	sin.sin_port=htons(8866);//1024--65535的端口号
	sin.sin_addr.S_un.S_addr=INADDR_ANY;
	//绑定这个套接字到本地地址
	if(::bind(s,(SOCKADDR*)&sin,sizeof(sin))==SOCKET_ERROR)
	{
		printf("bind is failed!\n");
		::WSACleanup();
		system("pause");
		return 0;
	}
	//监听模式
	if(::listen(s,2)==SOCKET_ERROR)
	{
		printf("listen is failed!\n");
		::WSACleanup();
		system("pause");
		return 0;
	}
	printf("正在监听....\n");
 
	//循环接受连接请求
	sockaddr_in addrlink;
	int Len=sizeof(addrlink);
	char anser[]="\echarts\lines3d-flights.html";
	char buf[1024];
	SOCKET client;
	while(1)
	{
		client=::accept(s,(SOCKADDR*)&addrlink,&Len);
		if(client==INVALID_SOCKET)
		{
			printf("accept is failed!");
			continue;
		}
		int n;
		while((n=::recv(client,buf,1024,0))==0);
		buf[n]='\0';
		printf("客户:(%s)",inet_ntoa(addrlink.sin_addr));
		printf("\n%s\n",buf);
		::send(client,anser,strlen(anser),0);	
	}
   	::closesocket(client);
	::closesocket(s);
	::WSACleanup();
	return 0;
 
}