//=================================================
//
//オンライン利用技術その2[main.cpp]
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
const int MAX_DATA = 4;		//データの最大数
}//namespaceはここまで

//*******************************
//プロトタイプ宣言
//*******************************
namespace
{
void Title();
}//namespaceはここまで

//=================================================
//メイン関数
//=================================================
void main(void)
{
	/* 2.Winsockの初期化関数を実行する */

	WSADATA wsaData;
	int nErr = WSAStartup(WINSOCK_VERSION, &wsaData);	//WSAStartup関数：winsockの初期化処理

	if (nErr != 0)
	{//初期化に失敗した場合(※エラーメッセージを表示して終了)
		printf("\n 初期化失敗");
	}

	/* 3.ソケット作成 */

	SOCKET sock;
	sock = socket(AF_INET, SOCK_STREAM, 0);	//socket関数：ソケットを作成する。接続受付用のソケット作成

	if (sock == INVALID_SOCKET)
	{//エラーメッセージを表示して終了
		printf("\n error");
	}

	/* 4.接続先の準備 */

	const char* pIPAddress = "127.0.0.1";
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(22333);
	addr.sin_addr.S_un.S_addr = inet_addr(pIPAddress);

	/* 5.接続する */

	//connect関数：サーバーに接続する
	if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) != 0)
	{//エラーメッセージを表示して終了
		printf("\n error");
	}

	/* 解答を受け取る */

	char aRecvAnswer[MAX_DATA] = {};
	int nRecvByte = recv(sock, &aRecvAnswer[0], sizeof(aRecvAnswer), 0);	//recv関数：データを受信する
	int nAnswer = 0;
	memcpy(&nAnswer, &aRecvAnswer[0], sizeof(int));

	Title();	//見出し表示

	/* 入力 */

	//変数
	int nData = 0;
	
	while (1)
	{
		//入力を促す
		printf("\n 値を入力 > ");
		scanf("%d", &nData);

		if (nData == nAnswer)
		{//正解と一致
			printf("\n\n 正解!!!");
			break;
		}

		/* 不正解の場合 */

		if (nData >= (nAnswer - 20))
		{//正解から[20以上小さい]
			printf("\n もっと小さいぞぉ～");
		}
		else if (nData <= (nAnswer + 20))
		{//正解から[20以上大きい]
			printf("\n もっと大きいぞぉ～");
		}
		else if (nData >= (nAnswer - 10))
		{//正解から[10以上小さい]
			printf("\n もう少し小さいぞぉ～");
		}
		else if (nData <= (nAnswer + 10))
		{//正解から[10以上大きい]
			printf("\n もう少し大きいぞぉ～");
		}
		
	}

	//Enter入力待ち
	printf("\n\n Press Enter");
	rewind(stdin);
	getchar();

	/* 7.接続を切断する */

	//サーバーとの接続を閉じる
	closesocket(sock);

	/* 8.Winsock終了処理 */

	WSACleanup();	//WSACleanup関数：winsockの終了処理
}

namespace
{
//-------------------------------------------------
//見出し
//-------------------------------------------------
void Title()
{
	printf("\n [ ☆ オンライン数字当てゲーム ☆ ]");
	printf("\n 1～100の数字を入力してね！");
}
}