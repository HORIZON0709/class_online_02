//=================================================
//
//オンライン利用技術〜クライアント側〜[tcp_client.h]
//Author:KishimotoEiji
//
//=================================================
#ifndef _TCP_CLIENT_H_
#define _TCP_CLIENT_H_

#include "main.h"

//*******************************
//TCPクライアントクラスの定義
//*******************************
class CTcpClient
{/* 基本クラス */
private: /* 定数の定義 */
	static const int MAX_DATA = 256;	//データの最大数

public: /* コンストラクタ・デストラクタ */
	CTcpClient();
	~CTcpClient();

public: /* メンバ関数 */
	bool Init(const char* pIPAddress, int nPortNum);	//初期化
	int Send(char* pSendData, int nSendData);			//送信
	int Recv(char* pRecvData, int nRecvData);			//受信
	void Uninit();										//終了

private: /* メンバ変数 */
	SOCKET m_sock;	//ソケット
};

#endif