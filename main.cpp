//=================================================
//
//�I�����C�����p�Z�p�`�N���C�A���g���`[main.cpp]
//Author:KishimotoEiji
//
//=================================================

//*******************************
//�C���N���[�h
//*******************************
#include "main.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//*******************************
//�萔�̒�`
//*******************************
namespace
{
const int MAX_DATA = 256;	//�f�[�^�̍ő吔
}//namespace�͂����܂�

//*******************************
//�v���g�^�C�v�錾
//*******************************
namespace
{
void PressEnter();
}//namespace�͂����܂�

//=================================================
//���C���֐�
//=================================================
void main(void)
{
	/* 2.Winsock�̏������֐������s���� */

	WSADATA wsaData;
	int nErr = WSAStartup(WINSOCK_VERSION, &wsaData);	//winsock�̏���������

	if (nErr != 0)
	{//�������Ɏ��s�����ꍇ(���G���[���b�Z�[�W��\�����ďI��)
		printf("\n ���������s");
	}

	/* 3.�\�P�b�g�쐬 */

	SOCKET sock;
	sock = socket(AF_INET, SOCK_STREAM, 0);	//�\�P�b�g���쐬����B�ڑ���t�p�̃\�P�b�g�쐬

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

	//�T�[�o�[�ɐڑ�����
	if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) != 0)
	{//�G���[���b�Z�[�W��\�����ďI��
		printf("\n error");
	}

	while (1)
	{
		//���͗p�z��
		char aData[MAX_DATA] = {};

		//���͂𑣂�
		printf("\n �������� > ");
		scanf("%s", &aData[0]);

		//���M
		send(sock, &aData[0], strlen(&aData[0]) + 1, 0);

		//�𓚂���M
		char aRecvAnswer[MAX_DATA] = {};
		int nRecvByte = recv(sock, &aRecvAnswer[0], sizeof(aRecvAnswer), 0);	//�f�[�^����M����
		
		if (nRecvByte <= 0)
		{//�ڑ����ؒf���ꂽ��
			closesocket(sock);		//�\�P�b�g�̃N���[�Y�������s��

			/* ������ȍ~�A����M�͂ł��Ȃ� */
		}

		//�\��
		printf("\n [ %s ]", &aRecvAnswer[0]);

		//Enter���͑҂�
		PressEnter();

		//��ʂ��N���A
		system("cls");
	}

	//���b�Z�[�W & Enter���͑҂�
	printf("\n �v���O�������I�����܂��B����ꂳ�܂ł����B");
	PressEnter();

	/* 7.�ڑ���ؒf���� */

	//�T�[�o�[�Ƃ̐ڑ������
	closesocket(sock);

	/* 8.Winsock�I������ */

	WSACleanup();	//winsock�̏I������
}

namespace
{
//-------------------------------------------------
//Enter���͑҂�
//-------------------------------------------------
void PressEnter()
{
	printf("\n\n Press Enter");
	rewind(stdin);
	getchar();
}
}