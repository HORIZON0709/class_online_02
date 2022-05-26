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
#include <stdlib.h>

//*******************************
//�萔�̒�`
//*******************************
namespace
{
const int MAX_DATA = 4;		//�f�[�^�̍ő吔
}//namespace�͂����܂�

//*******************************
//�v���g�^�C�v�錾
//*******************************
namespace
{
void Title();
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

	/* �𓚂��󂯎�� */

	char aRecvAnswer[MAX_DATA] = {};
	int nRecvByte = recv(sock, &aRecvAnswer[0], sizeof(aRecvAnswer), 0);	//recv�֐��F�f�[�^����M����
	int nAnswer = 0;
	memcpy(&nAnswer, &aRecvAnswer[0], sizeof(int));

	Title();	//���o���\��

	/* ���� */

	//�ϐ�
	int nData = 0;
	
	while (1)
	{
		//���͂𑣂�
		printf("\n �l����� > ");
		scanf("%d", &nData);

		if (nData == nAnswer)
		{//�����ƈ�v
			printf("\n\n ����!!!");
			break;
		}

		/* �s�����̏ꍇ */

		if (nData >= (nAnswer - 20))
		{//��������[20�ȏ㏬����]
			printf("\n �����Ə����������`");
		}
		else if (nData <= (nAnswer + 20))
		{//��������[20�ȏ�傫��]
			printf("\n �����Ƒ傫�������`");
		}
		else if (nData >= (nAnswer - 10))
		{//��������[10�ȏ㏬����]
			printf("\n �������������������`");
		}
		else if (nData <= (nAnswer + 10))
		{//��������[10�ȏ�傫��]
			printf("\n ���������傫�������`");
		}
		
	}

	//Enter���͑҂�
	printf("\n\n Press Enter");
	rewind(stdin);
	getchar();

	/* 7.�ڑ���ؒf���� */

	//�T�[�o�[�Ƃ̐ڑ������
	closesocket(sock);

	/* 8.Winsock�I������ */

	WSACleanup();	//WSACleanup�֐��Fwinsock�̏I������
}

namespace
{
//-------------------------------------------------
//���o��
//-------------------------------------------------
void Title()
{
	printf("\n [ �� �I�����C���������ăQ�[�� �� ]");
	printf("\n 1�`100�̐�������͂��ĂˁI");
}
}