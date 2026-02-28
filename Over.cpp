#include	"DxLib.h"
#include	"Color.h"
#include	"Variable.h"

static bool playFlag = true;

void Over(System* timer,State* state,int music) {
	if (playFlag) { //ゲームオーバーになった時のみ
		PlaySoundMem(music, DX_PLAYTYPE_BACK);
		playFlag = false;
	}

	SetFontSize(120);

	DrawString(250, 300, "GAME OVER", color[RED]);

	timer->count++;

	if (timer->count >= 60 * 3) { //3秒後にタイトルへ戻る
		playFlag = true;

		timer->count = 0;
		*state = TITLE;
	}
}