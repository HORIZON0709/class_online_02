//=================================================
//
//�I�����C�����p�Z�p�`�N���C�A���g���`[tcp_client.cpp]
//Author:KishimotoEiji
//
//=================================================

//*******************************
//�C���N���[�h
//*******************************
#include "tcp_client.h"

#include <stdio.h>

//=================================================
//�R���X�g���N�^
//=================================================
CTcpClient::CTcpClient()
{
	//�����o�ϐ����N���A
	m_sock = INVALID_SOCKET;
}

//=================================================
//�f�X�g���N�^
//=================================================
CTcpClient::~CTcpClient()
{
}

//=================================================
//������
//=================================================
bool CTcpClient::Init(const char* pIPAddress, int nPortNum)
{
	//�\�P�b�g���쐬����B�ڑ���t�p�̃\�P�b�g�쐬
	m_sock = socket(AF_INET, SOCK_STREAM, 0);

	if (m_sock == INVALID_SOCKET)
	{//�G���[���b�Z�[�W��\�����ďI��
		printf("\n error");
		return false;	//���s
	}

	/* �ڑ���̏��� */

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(nPortNum);
	addr.sin_addr.S_un.S_addr = inet_addr(pIPAddress);

	/* �ڑ��悷�� */

	//�T�[�o�[�ɐڑ�����
	if (connect(m_sock, (struct sockaddr*)&addr, sizeof(addr)) != 0)
	{//�G���[���b�Z�[�W��\�����ďI��
		printf("\n error");
		return false;	//���s
	}

	return true;	//����
}

//=================================================
//���M
//=================================================
int CTcpClient::Send(char* pSendData, int nSendData)
{
	//���͂𑣂�
	printf("\n ��������( �I������ꍇ�� [exit] �Ɠ��� ) > ");
	scanf("%s", pSendData);

	//���M
	return send(m_sock, pSendData, nSendData, 0);	//���M�f�[�^�T�C�Y��Ԃ�
}

//=================================================
//��M
//=================================================
int CTcpClient::Recv(char* pRecvData, int nRecvData)
{
	//�f�[�^����M����
	int nRecvByte = recv(m_sock, pRecvData, nRecvData, 0);

	//�\��
	printf("\n [ %s ]", pRecvData);

	return nRecvByte;	//��M�f�[�^�T�C�Y��Ԃ�
}

//=================================================
//�I��
//=================================================
void CTcpClient::Uninit()
{
	//�T�[�o�[�Ƃ̐ڑ������
	closesocket(m_sock);
}