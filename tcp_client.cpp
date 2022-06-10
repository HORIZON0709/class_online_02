//=================================================
//
//オンライン利用技術～クライアント側～[tcp_client.cpp]
//Author:KishimotoEiji
//
//=================================================

//*******************************
//インクルード
//*******************************
#include "tcp_client.h"

#include <stdio.h>

//=================================================
//コンストラクタ
//=================================================
CTcpClient::CTcpClient()
{
	//メンバ変数をクリア
	m_sock = INVALID_SOCKET;
}

//=================================================
//デストラクタ
//=================================================
CTcpClient::~CTcpClient()
{
}

//=================================================
//初期化
//=================================================
bool CTcpClient::Init(const char* pIPAddress, int nPortNum)
{
	//ソケットを作成する。接続受付用のソケット作成
	m_sock = socket(AF_INET, SOCK_STREAM, 0);

	if (m_sock == INVALID_SOCKET)
	{//エラーメッセージを表示して終了
		printf("\n error");
		return false;	//失敗
	}

	/* 接続先の準備 */

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(nPortNum);
	addr.sin_addr.S_un.S_addr = inet_addr(pIPAddress);

	/* 接続先する */

	//サーバーに接続する
	if (connect(m_sock, (struct sockaddr*)&addr, sizeof(addr)) != 0)
	{//エラーメッセージを表示して終了
		printf("\n error");
		return false;	//失敗
	}

	return true;	//成功
}

//=================================================
//送信
//=================================================
int CTcpClient::Send(char* pSendData, int nSendData)
{
	//入力を促す
	printf("\n 質問を入力( 終了する場合は [exit] と入力 ) > ");
	scanf("%s", pSendData);

	//送信
	return send(m_sock, pSendData, nSendData, 0);	//送信データサイズを返す
}

//=================================================
//受信
//=================================================
int CTcpClient::Recv(char* pRecvData, int nRecvData)
{
	//データを受信する
	int nRecvByte = recv(m_sock, pRecvData, nRecvData, 0);

	//表示
	printf("\n [ %s ]", pRecvData);

	return nRecvByte;	//受信データサイズを返す
}

//=================================================
//終了
//=================================================
void CTcpClient::Uninit()
{
	//サーバーとの接続を閉じる
	closesocket(m_sock);
}