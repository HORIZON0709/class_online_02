//=================================================
//
//�I�����C�����p�Z�p�`�N���C�A���g���`[main.cpp]
//Author:KishimotoEiji
//
//=================================================

//*******************************
//�C���N���[�h
//*******************************
#include "tcp_client.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//*******************************
//�萔�̒�`
//*******************************
namespace
{
const int MAX_DATA = 256;	//�f�[�^�̍ő吔
const char* MY_ADDRESS = "127.0.0.1";	//������PC�ɃA�N�Z�X����A�h���X
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
	/* Winsock�̏������֐������s���� */

	WSADATA wsaData;
	int nErr = WSAStartup(WINSOCK_VERSION, &wsaData);	//winsock�̏���������

	if (nErr != 0)
	{//�������Ɏ��s�����ꍇ(���G���[���b�Z�[�W��\�����ďI��)
		printf("\n ���������s");
	}

	CTcpClient* pTcpClient = nullptr;	//TCP�N���C�A���g

	if (pTcpClient != nullptr)
	{//NULL�`�F�b�N
		delete pTcpClient;		//�������̉��
		pTcpClient = nullptr;	//nullptr�ɂ���
	}

	if (pTcpClient == nullptr)
	{//NULL�`�F�b�N
		pTcpClient = new CTcpClient;	//�������̓��I�m��
	}

	//������
	pTcpClient->Init(MY_ADDRESS,22333);

	while (1)
	{
		char aSendQuestion[MAX_DATA] = {};	//���⑗�M�p

		//���M
		pTcpClient->Send(&aSendQuestion[0], strlen(&aSendQuestion[0]) + 1);

		if (strcmp(&aSendQuestion[0], "exit") == 0)
		{//�I���̍��}��������
			break;
		}

		char aRecvAnswer[MAX_DATA] = {};	//�𓚎�M�p

		//��M
		int nRecvByte = pTcpClient->Recv(&aRecvAnswer[0], sizeof(aRecvAnswer));

		if (nRecvByte <= 0)
		{//�ڑ����ؒf���ꂽ��
			break;
		}

		//Enter���͑҂�
		PressEnter();

		//��ʂ��N���A
		system("cls");
	}

	//���b�Z�[�W & Enter���͑҂�
	printf("\n �v���O�������I�����܂��B����ꂳ�܂ł����B");
	PressEnter();

	//�I��
	pTcpClient->Uninit();
	
	//winsock�̏I������
	WSACleanup();
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