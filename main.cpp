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
const int MAX_DATA = 4;			//�f�[�^�̍ő吔
const int SMALL_ERROR = 10;		//�������덷
const int LARGE_ERROR = 30;		//�傫���덷
}//namespace�͂����܂�

//*******************************
//�v���g�^�C�v�錾
//*******************************
namespace
{
void Title();
void PressEnter();
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

	//�G���f�B�A���ϊ�(netowork to host)
	nAnswer = ntohl(nAnswer);

	/* ���� */

	//�ϐ�
	int nData = 0;
	
	while (1)
	{
		Title();	//���o���\��

		//���͂𑣂�
		printf("\n �l����� > ");
		scanf("%d", &nData);

		if (nData == nAnswer)
		{//�����ƈ�v
			printf("\n\n ����!!!");

			//Enter���͑҂�
			PressEnter();

			//��ʂ��N���A
			system("cls");
			break;
		}

		/* �s�����̏ꍇ */

		if ((nData >= (nAnswer - SMALL_ERROR)) && (nData <= (nAnswer + SMALL_ERROR)))
		{//��������[�}10]
			if ((nData >= (nAnswer - SMALL_ERROR)) && (nData <= nAnswer))
			{//[ - ]
				printf(" ���������傫�������`\n");
			}
			else if ((nData >= nAnswer) && (nData <= (nAnswer + SMALL_ERROR)))
			{//[ + ]
				printf(" �������������������`\n");
			}

			//Enter���͑҂�
			PressEnter();

			//��ʂ��N���A
			system("cls");

			continue;	//���֖͂߂�
		}

		if ((nData >= (nAnswer - LARGE_ERROR)) && (nData <= (nAnswer + LARGE_ERROR)))
		{//��������[�}30]
			if ((nData >= (nAnswer - LARGE_ERROR)) && (nData <= nAnswer))
			{//[ - ]
				printf(" �����Ƒ傫�������`\n");
			}
			else if ((nData >= nAnswer) && (nData <= (nAnswer + LARGE_ERROR)))
			{//[ + ]
				printf(" �����Ə����������`\n");
			}

			//Enter���͑҂�
			PressEnter();

			//��ʂ��N���A
			system("cls");

			continue;	//���֖͂߂�
		}

		/* ����ȏ�̌덷�̏ꍇ */

		printf(" �����[�񂶂���Ⴄ��悧�`\n");

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