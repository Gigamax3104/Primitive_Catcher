#include	"DxLib.h"
#include	"time.h"
#include	"Function.h"
#include	"Variable.h"

const char* musicFile[] = { //音のファイル(追加時はここへ記入)
	"sound/Title.mp3","sound/Game.mp3","sound/GameOver.mp3","sound/Circle.mp3","sound/Box.mp3","sound/Fault.mp3"
};
const int FILESIZE = sizeof musicFile / sizeof musicFile[0];

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	SetWindowText("プリミティブキャッチャー");
	SetGraphMode(WIDTH, HEIGHT, 32);
	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1) return -1;
	SetBackgroundColor(0, 0, 0);
	SetDrawScreen(DX_SCREEN_BACK);

	srand((unsigned int)time(NULL));

	int* music = new int[FILESIZE];

	State state = TITLE;

	System timer = { 0,HEIGHT / 2,0 };

	for (int i = 0; i < FILESIZE; i++) music[i] = LoadSoundMem(musicFile[i]);

	if (ErrorCheck(musicFile, FILESIZE)) state = E; //エラーチェック(詳細は「ErrorCheck.cpp」へ)

	while (1) {
		ClearDrawScreen();

		switch (state) {
		case TITLE:
			Title(&timer, &state,music[state]); //タイトル(詳細は「Title.cpp」へ)
			break;
		case GAME:
			Game(&timer, &state,music[state],music[SE_CIRCLE],music[SE_BOX],music[SE_FAULT]); //ゲームプレイ(詳細は「Game.cpp」へ)
			break;
		case OVER:
			Over(&timer, &state,music[state]); //ゲームオーバー(詳細は「Over.cpp」へ)
			break;
		case E:
			Error(musicFile, FILESIZE); //エラー(詳細は「ErrorCheck.cpp」へ)
			break;
		}

		ScreenFlip();
		WaitTimer(33);
		if (ProcessMessage() == -1) break;
		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;
	}

	for (int i = 0; i < FILESIZE; i++) DeleteSoundMem(music[i]);
	delete[] music;

	DxLib_End();
	return 0;
}