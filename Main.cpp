#include	"DxLib.h"
#include	"Function.h"
#include	"Variable.h"

System timer = { 0,HEIGHT / 2,0 };

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	SetWindowText("プリミティブキャッチャー");
	SetGraphMode(WIDTH, HEIGHT, 32);
	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1) return -1;
	SetBackgroundColor(0, 0, 0);
	SetDrawScreen(DX_SCREEN_BACK);

	State state = TITLE;

	while (1) {
		ClearDrawScreen();

		switch (state) {
		case TITLE:
			Title(&timer, &state);
			break;
		case GAME:
			Game(&timer, &state);
			break;
		case OVER:
			Over(&timer, &state);
			break;
		}

		ScreenFlip();
		WaitTimer(33);
		if (ProcessMessage() == -1) break;
		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;
	}
	DxLib_End();
	return 0;
}