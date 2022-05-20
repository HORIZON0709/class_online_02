//=================================================
//
//�I�����C�����p�Z�p[main.cpp]
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

	}

	/* 3.�\�P�b�g�쐬 */

	SOCKET sockServer;
	sockServer = socket(AF_INET, SOCK_STREAM, 0);	//socket�֐��F�\�P�b�g���쐬����B�ڑ���t�p�̃\�P�b�g�쐬

	if (sockServer == INVALID_SOCKET)
	{//�G���[���b�Z�[�W��\�����ďI��

	}

	/* 4.�ڑ����󂯕t���邽�߂̏��� */

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(22333);	/* �|�[�g�ԍ� */
	addr.sin_addr.S_un.S_addr = INADDR_ANY;
	bind(sockServer, (struct sockaddr*)&addr, sizeof(addr));	//bind�֐��F�\�P�b�g�Ƀ|�[�g�����蓖��
	listen(sockServer, 10);		/* �ۗ����̐ڑ��ő吔 */		//listen�֐��F�ڑ���t�̏���

	/* 5.�ڑ���҂� */

	struct sockaddr_in clientAddr;
	int nLength = sizeof(clientAddr);
	SOCKET sock = accept(sockServer, (struct sockaddr*)&clientAddr, &nLength);	//accept�֐��F�ڑ����󂯕t����

	/* 6.�f�[�^�̑��M */

	int nData = 12345;
	char aData[MAX_DATA];
	memcpy(&aData[0], &nData, sizeof(int));
	send(sock, &aData[0], sizeof(int), 0);	//send�֐��F�f�[�^�𑗐M����

	/* 7.�ڑ���ؒf���� */

	//�N���C�A���g�Ƃ̐ڑ������
	closesocket(sock);

	//�ڑ���t�p�\�P�b�g�����
	closesocket(sockServer);		//closesocket�֐��F�\�P�b�g�����

	/* 8.Winsock�I������ */

	WSACleanup();	//WSACleanup�֐��Fwinsock�̏I������
}