#include <WinSock2.h>
#include <stdio.h>

void main()
{
	WORD wVersionRequested;//����ʹ�õ����winsock�汾��
	WSADATA	wsaData;//�ṹ�壬����socket����ϸ��Ϣ
	int err;

	wVersionRequested = MAKEWORD(1, 1);

	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
	{
		return;
	}

	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1)
	{
		WSACleanup();
	}

	SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);//ָ����ַ�أ�socket���ͣ�Э��

	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);

	bind(sockSrv, (SOCKADDR*)(&addrSrv), sizeof(SOCKADDR));

	listen(sockSrv, 5);

	SOCKADDR_IN addrClient;
	int len = sizeof(SOCKADDR);

	while (1)
	{
		SOCKET sockConn = accept(sockSrv, (SOCKADDR*)&addrClient, &len);
		char sendBuf[100];
		sprintf(sendBuf, "Welcome %s to hpec", inet_ntoa(addrClient.sin_addr));
		send(sockConn, sendBuf, strlen(sendBuf) + 1, 0);
		char recvBuf[100];
		recv(sockConn, recvBuf, 100, 0);
		printf("%s\n", recvBuf);
		closesocket(sockConn);
	}

}