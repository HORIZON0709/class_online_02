//=================================================
//
//オンライン利用技術～クライアント側～[main.cpp]
//Author:KishimotoEiji
//
//=================================================

//*******************************
//インクルード
//*******************************
#include "main.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//*******************************
//定数の定義
//*******************************
namespace
{
const int MAX_DATA = 256;	//データの最大数
}//namespaceはここまで

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
	/*
		2.Winsockの初期化関数を実行する
	*/

	WSADATA wsaData;
	int nErr = WSAStartup(WINSOCK_VERSION, &wsaData);	//winsockの初期化処理

	if (nErr != 0)
	{//初期化に失敗した場合(※エラーメッセージを表示して終了)
		printf("\n 初期化失敗");
	}

	/*
		3.ソケット作成
	*/

	SOCKET sock;
	sock = socket(AF_INET, SOCK_STREAM, 0);	//ソケットを作成する。接続受付用のソケット作成

	if (sock == INVALID_SOCKET)
	{//エラーメッセージを表示して終了
		printf("\n error");
	}

	/*
		4.接続先の準備
	*/

	//const char* pIPAddress = "127.0.0.1";
	const char* pIPAddress = "10.70.21.125";
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(22333);
	addr.sin_addr.S_un.S_addr = inet_addr(pIPAddress);

	/*
		5.接続する
	*/

	//サーバーに接続する
	if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) != 0)
	{//エラーメッセージを表示して終了
		printf("\n error");
	}

	while (1)
	{
		//入力用配列
		char aData[MAX_DATA] = {};

		//入力を促す
		printf("\n 質問を入力( 終了する場合は [exit] と入力 ) > ");
		scanf("%s", &aData[0]);

		if (strcmp(&aData[0], "exit") == 0)
		{//終了の合図が来たら
			break;
		}

		/* それ以外の場合 */

		//送信
		send(sock, &aData[0], strlen(&aData[0]) + 1, 0);

		//解答を受信
		char aRecvAnswer[MAX_DATA] = {};
		int nRecvByte = recv(sock, &aRecvAnswer[0], sizeof(aRecvAnswer), 0);	//データを受信する
		
		if (nRecvByte <= 0)
		{//接続が切断されたら
			break;
		}

		//表示
		printf("\n [ %s ]", &aRecvAnswer[0]);

		//Enter入力待ち
		PressEnter();

		//画面をクリア
		system("cls");
	}

	//メッセージ & Enter入力待ち
	printf("\n プログラムを終了します。お疲れさまでした。");
	PressEnter();

	/*
		7.接続を切断する
	*/

	//サーバーとの接続を閉じる
	closesocket(sock);

	/*
		8.Winsock終了処理
	*/

	WSACleanup();	//winsockの終了処理
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