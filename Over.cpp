#include	"DxLib.h"
#include	"Color.h"
#include	"Variable.h"

void Over(System* timer,State* state) {
	SetFontSize(120);

	DrawString(250, 300, "GAME OVER", color[RED]);

	timer->count++;

	if (timer->count >= 60 * 3) {
		timer->count = 0;
		*state = TITLE;
	}
}