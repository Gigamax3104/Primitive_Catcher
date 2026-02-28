#include	"DxLib.h"
#include	"Color.h"
#include	"Variable.h"

static bool playFlag = true;

void Title(System* timer, State* state,int music) {
	if (playFlag) { //起動時のみ
		PlaySoundMem(music, DX_PLAYTYPE_LOOP);
		playFlag = false;
	}

	timer->count++;

	SetFontSize(100);
	DrawString(110, 120, "Primitive Catcher", color[YELLOW]);

	SetFontSize(70);
	if (timer->count % 60 <= 30)DrawString(270, HEIGHT - 180, "SPACE to Start", color[GREEN]); //0.5秒ごと表示

	if(CheckHitKey(KEY_INPUT_SPACE)) { //スペースキーを押されたらゲーム開始
		StopSoundMem(music);
		playFlag = true;

		timer->count = 600;
		*state = GAME;
	}
}