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
	pTcpClient->Init(CTcpClient::MY_ADDRESS,22333);

	while (1)
	{
		char aSendQuestion[CTcpClient::MAX_DATA] = {};	//���⑗�M�p

		//���͂𑣂�
		printf("\n ��������( �I������ꍇ�� [exit] �Ɠ��� ) > ");
		scanf("%s", &aSendQuestion[0]);

		if (strcmp(&aSendQuestion[0], "exit") == 0)
		{//�I���̍��}��������
			break;
		}

		//���M
		pTcpClient->Send(&aSendQuestion[0], strlen(&aSendQuestion[0]) + 1);

		char aRecvAnswer[CTcpClient::MAX_DATA] = {};	//�𓚎�M�p

		//��M
		int nRecvByte = pTcpClient->Recv(&aRecvAnswer[0], sizeof(aRecvAnswer));

		//�\��
		printf("\n [ %s ]", &aRecvAnswer[0]);

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

	if (pTcpClient != nullptr)
	{//NULL�`�F�b�N
		pTcpClient->Uninit();	//�I��
		delete pTcpClient;		//�������̉��
		pTcpClient = nullptr;	//nullptr�ɂ���
	}

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