#include	"DxLib.h"
#include	"Color.h"
#include	"Variable.h"

bool ErrorCheck(const char** musicFile,int fileSize) {
	bool flag = false;

	for (int i = 0; i < fileSize; i++) if (LoadSoundMem(musicFile[i]) == -1) flag = true;

	return flag;
}

void Error(const char** musicFile,int fileSize) {
	int font_Pos_y = 100;

	SetFontSize(80);
	DrawString(0, 0, "File defind.", color[RED]);

	SetFontSize(40);

	for (int i = 0; i < fileSize; i++) {
		if (LoadSoundMem(musicFile[i]) == -1) {
			DrawFormatString(0, font_Pos_y, color[WHITE], musicFile[i]);

			font_Pos_y += 40;
		}
	}
}