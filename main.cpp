//=================================================
//
//�I�����C�����p�Z�p����2[main.cpp]
//Author:KishimotoEiji
//
//=================================================

//*******************************
//�C���N���[�h
//*******************************
#include "main.h"

#include <stdio.h>
#include <string.h>

//*******************************
//�萔�̒�`
//*******************************
namespace
{
const int MAX_DATA = 4;		//�f�[�^�̍ő吔
}//namespace�͂����܂�

//=================================================
//���C���֐�
//=================================================
void main(void)
{
	/* 2.Winsock�̏������֐������s���� */

	WSADATA wsaData;
	int nErr = WSAStartup(WINSOCK_VERSION, &wsaData);	//WSAStartup�֐��Fwinsock�̏���������

	if (nErr != 0)
	{//�������Ɏ��s�����ꍇ(���G���[���b�Z�[�W��\�����ďI��)
		printf("\n ���������s");
	}

	/* 3.�\�P�b�g�쐬 */

	SOCKET sock;
	sock = socket(AF_INET, SOCK_STREAM, 0);	//socket�֐��F�\�P�b�g���쐬����B�ڑ���t�p�̃\�P�b�g�쐬

	if (sock == INVALID_SOCKET)
	{//�G���[���b�Z�[�W��\�����ďI��
		printf("\n error");
	}

	/* 4.�ڑ���̏��� */

	const char* pIPAddress = "127.0.0.1";
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(22333);
	addr.sin_addr.S_un.S_addr = inet_addr(pIPAddress);

	/* 5.�ڑ����� */

	//connect�֐��F�T�[�o�[�ɐڑ�����
	if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) != 0)
	{//�G���[���b�Z�[�W��\�����ďI��
		printf("\n error");
	}

	/* 6.�f�[�^�̑���M */

	char aRecvData[MAX_DATA] = {};
	int nRecvByte = recv(sock, &aRecvData[0], sizeof(aRecvData), 0);	//recv�֐��F�f�[�^����M����
	int nData = 0;
	memcpy(&nData, &aRecvData[0], sizeof(int));

	/* 7.�ڑ���ؒf���� */

	//�T�[�o�[�Ƃ̐ڑ������
	closesocket(sock);

	/* 8.Winsock�I������ */

	WSACleanup();	//WSACleanup�֐��Fwinsock�̏I������

	printf("[ �󂯎�����l : %d ]",nData);

	//Enter���͑҂�
	printf("\n Press Enter");
	rewind(stdin);
	getchar();
}