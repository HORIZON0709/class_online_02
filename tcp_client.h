//=================================================
//
//�I�����C�����p�Z�p�`�N���C�A���g���`[tcp_client.h]
//Author:KishimotoEiji
//
//=================================================
#ifndef _TCP_CLIENT_H_
#define _TCP_CLIENT_H_

#include "main.h"

//*******************************
//TCP�N���C�A���g�N���X�̒�`
//*******************************
class CTcpClient
{/* ��{�N���X */
public: /* �萔�̒�` */
	static const int MAX_DATA = 256;	//�f�[�^�̍ő吔
	static const char* MY_ADDRESS;		//������PC�ɃA�N�Z�X����A�h���X

public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CTcpClient();
	~CTcpClient();

public: /* �����o�֐� */
	bool Init(const char* pIPAddress, int nPortNum);	//������
	int Send(char* pSendData, int nSendData);			//���M
	int Recv(char* pRecvData, int nRecvData);			//��M
	void Uninit();										//�I��

private: /* �����o�ϐ� */
	SOCKET m_sock;	//�\�P�b�g
};

#endif