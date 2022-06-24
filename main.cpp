//=================================================
//
//オンライン利用技術～クライアント側～[main.cpp]
//Author:KishimotoEiji
//
//=================================================

//*******************************
//インクルード
//*******************************
#include "tcp_client.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//*******************************
//プロトタイプ宣言
//*******************************
namespace
{
void PressEnter();
}//namespaceはここまで

//=================================================
//メイン関数
//=================================================
void main(void)
{
	/* Winsockの初期化関数を実行する */

	WSADATA wsaData;
	int nErr = WSAStartup(WINSOCK_VERSION, &wsaData);	//winsockの初期化処理

	if (nErr != 0)
	{//初期化に失敗した場合(※エラーメッセージを表示して終了)
		printf("\n 初期化失敗");
	}

	CTcpClient* pTcpClient = nullptr;	//TCPクライアント

	if (pTcpClient != nullptr)
	{//NULLチェック
		delete pTcpClient;		//メモリの解放
		pTcpClient = nullptr;	//nullptrにする
	}

	if (pTcpClient == nullptr)
	{//NULLチェック
		pTcpClient = new CTcpClient;	//メモリの動的確保
	}

	//初期化
	pTcpClient->Init(CTcpClient::MY_ADDRESS,22333);

	while (1)
	{
		char aSendQuestion[CTcpClient::MAX_DATA] = {};	//質問送信用

		//入力を促す
		printf("\n 質問を入力( 終了する場合は [exit] と入力 ) > ");
		scanf("%s", &aSendQuestion[0]);

		if (strcmp(&aSendQuestion[0], "exit") == 0)
		{//終了の合図が来たら
			break;
		}

		//送信
		pTcpClient->Send(&aSendQuestion[0], strlen(&aSendQuestion[0]) + 1);

		char aRecvAnswer[CTcpClient::MAX_DATA] = {};	//解答受信用

		//受信
		int nRecvByte = pTcpClient->Recv(&aRecvAnswer[0], sizeof(aRecvAnswer));

		//表示
		printf("\n [ %s ]", &aRecvAnswer[0]);

		if (nRecvByte <= 0)
		{//接続が切断されたら
			break;
		}

		//Enter入力待ち
		PressEnter();

		//画面をクリア
		system("cls");
	}

	//メッセージ & Enter入力待ち
	printf("\n プログラムを終了します。お疲れさまでした。");
	PressEnter();

	if (pTcpClient != nullptr)
	{//NULLチェック
		pTcpClient->Uninit();	//終了
		delete pTcpClient;		//メモリの解放
		pTcpClient = nullptr;	//nullptrにする
	}

	//winsockの終了処理
	WSACleanup();
}

namespace
{
//-------------------------------------------------
//Enter入力待ち
//-------------------------------------------------
void PressEnter()
{
	printf("\n\n Press Enter");
	rewind(stdin);
	getchar();
}
}