#include	"DxLib.h"
#include	"math.h"
#include	"time.h"
#include	"Color.h"
#include	"Variable.h"

static int hit = 0;

static int instanceCount = 1;
static int instanceSave = instanceCount;
static int circleCount = 0, boxCount = 0;
static int circleSave = 0;
static int boxSave = 0;

static int combo = 0;
static int saveCombo = combo;

static bool playFlag = true;

static bool instanceFlag = true;

static Player player = { MIDLE,{MIDLE,20,color[WHITE],0,true},{MIDLE,40,40,color[WHITE],0,true},false };


const Circle CIRCLE = { WIDTH / 2,-30,20,color[RED],10,true };
const Box BOX = { WIDTH / 2 + 30,-15,50,50,color[BLUE],10,true };

const Box REDLINE = { WIDTH / 2,HEIGHT - 12,WIDTH,24,color[RED],0,true };
const Box UI = { WIDTH - 140,HEIGHT - 70,280,140,color[WHITE],0,true };

static void RandomShaep() {
	int random = rand() % 100;
	random < 50 ? circleCount++ : boxCount++;
}

static void Initialization(Circle* fallCircle,Box* fallBox,bool choice,const Circle* SC = nullptr,const Box* SB = nullptr,bool r = false) {
	if (r) {
		if (choice) {
			for (int i = 0; i < circleCount - 1; i++) {
				fallCircle[i].pos = SC[i].pos;
				fallCircle[i].radius = SC[i].radius;
				fallCircle[i].speed = SC[i].speed;
				fallCircle[i].color = SC[i].color;
				fallCircle[i].displayFlag = SC[i].displayFlag;
			}
		}
		else {
			for (int i = 0; i < boxCount - 1; i++) {
				fallBox[i].pos = SB[i].pos;
				fallBox[i].length = SB[i].length;
				fallBox[i].speed = SB[i].speed;
				fallBox[i].color = SB[i].color;
				fallBox[i].displayFlag = SB[i].displayFlag;
			}
		}
	}

	if (instanceCount == 1) {
		if (choice) {
			fallCircle->radius = rand() % (CIRCLE.radius - 5) + 5;
			fallCircle->pos.x = rand() % (WIDTH - fallCircle->radius * 2) + fallCircle->radius;
			fallCircle->pos.y = -fallCircle->radius;
			fallCircle->speed = rand() % 15 + 5;
			fallCircle->color = color[rand() % (COLORSIZE - 1)];
			fallCircle->displayFlag = CIRCLE.displayFlag;
		}
		else {
			fallBox->length.x = rand() % (BOX.length.x - 10) + 10;
			fallBox->length.y = fallBox->length.x;
			fallBox->pos.x = rand() % (WIDTH - (fallBox->length.x / 2) * 2) + fallBox->length.x / 2;
			fallBox->pos.y = -fallBox->length.y / 2;
			fallBox->speed = rand() % 15 + 5;
			fallBox->color = color[rand() % (COLORSIZE - 1)];
			fallBox->displayFlag = BOX.displayFlag;
		}
	}
	else {
		if (choice) {
			for (int i = circleSave; i < circleCount; i++) {
				fallCircle[i].radius = rand() % (CIRCLE.radius - 5) + 5;
				fallCircle[i].pos.x = rand() % (WIDTH - fallCircle[i].radius * 2) + fallCircle[i].radius;
				fallCircle[i].pos.y = -fallCircle[i].radius;
				fallCircle[i].speed = rand() % 15 + 5;
				fallCircle[i].color = color[rand() % (COLORSIZE - 1)];
				fallCircle[i].displayFlag = CIRCLE.displayFlag;
			}
		}
		else {
			for (int i = boxSave; i < boxCount; i++) {
				fallBox[i].length.x = rand() % (BOX.length.x - 10) + 10;
				fallBox[i].length.y = fallBox[i].length.x;
				fallBox[i].pos.x = rand() % (WIDTH - (fallBox[i].length.x / 2) * 2) + fallBox[i].length.x / 2;
				fallBox[i].pos.y = -fallBox[i].length.y / 2;
				fallBox[i].speed = rand() % 15 + 5;
				fallBox[i].color = color[rand() % (COLORSIZE - 1)];
				fallBox[i].displayFlag = BOX.displayFlag;
			}
		}
	}
}

static void ScreenAdjustment() {
	GetMousePoint(&player.pos.x, &player.pos.y);

	if (!player.flag && player.pos.x < 0) player.pos.x = player.P_circle.radius;
	else if (player.flag && player.pos.x < 0) player.pos.x = player.P_box.length.x / 2;

	if (!player.flag && player.pos.x > WIDTH - player.P_circle.radius) player.pos.x = WIDTH - player.P_circle.radius;
	else if(player.flag && player.pos.x > WIDTH - player.P_box.length.x / 2) player.pos.x = WIDTH - player.P_box.length.x / 2;

	if (!player.flag && player.pos.y < player.P_circle.radius) player.pos.y = player.P_circle.radius;
	else if (player.flag && player.pos.y < player.P_box.length.y / 2) player.pos.y = player.P_box.length.y / 2;

	if (player.pos.y > HEIGHT) player.pos.y = HEIGHT;

	if (pow(player.pos.y - REDLINE.pos.y, 2) < pow(player.P_box.length.y / 2 + REDLINE.length.y / 2, 2))
		player.pos.y = REDLINE.pos.y - REDLINE.length.y / 2 - player.P_box.length.y / 2;

	if (pow(player.pos.y - REDLINE.pos.y, 2) < pow(player.P_circle.radius + REDLINE.length.y / 2, 2))
		player.pos.y = REDLINE.pos.y - REDLINE.length.y / 2 - player.P_circle.radius;
}

static void Move(Circle* fallCircle, Box* fallBox) {
	for (int i = 0; i < boxCount; i++) fallBox[i].pos.y += fallBox[i].speed;

	for (int i = 0; i < circleCount; i++) fallCircle[i].pos.y += fallCircle[i].speed;
}

static void CircleJudge(Circle* fallCircle,int circle_Se,int fault_Se) {
	for (int i = 0; i < circleCount; i++) {
		if (!player.flag && pow(fallCircle[i].pos.x - player.pos.x, 2) + pow(fallCircle[i].pos.y - player.pos.y, 2)
			<= pow(fallCircle[i].radius + player.P_circle.radius, 2)) {
			if (fallCircle[i].displayFlag) combo++;
			if (combo > saveCombo) saveCombo = combo;

			if(fallCircle[i].displayFlag) PlaySoundMem(circle_Se, DX_PLAYTYPE_BACK);

			fallCircle[i].displayFlag = false;
		}
		else if ((player.flag && fallCircle[i].displayFlag && 
			pow(fallCircle[i].pos.x - player.pos.x, 2) + pow(fallCircle[i].pos.y - player.pos.y, 2)
			<= pow(fallCircle[i].radius + player.P_circle.radius, 2)) 
			|| fallCircle[i].displayFlag
			&& pow(fallCircle[i].pos.x - REDLINE.pos.x, 2) <= pow(fallCircle[i].radius + REDLINE.length.x / 2, 2)
			&& pow(fallCircle[i].pos.y - REDLINE.pos.y, 2) <= pow(fallCircle[i].radius + REDLINE.length.y / 2, 2)) {
			combo = 0;

			if(fallCircle[i].displayFlag) PlaySoundMem(fault_Se, DX_PLAYTYPE_BACK);

			fallCircle[i].displayFlag = false;
		}
	}
}

static void BoxJudge(Box* fallBox,int box_Se,int fault_Se) {
	for (int i = 0; i < boxCount; i++) {
		if (player.flag && pow(fallBox[i].pos.x - player.pos.x, 2) <= pow(fallBox[i].length.x / 2 + player.P_box.length.x / 2, 2)
			&& pow(fallBox[i].pos.y - player.pos.y, 2) <= pow(fallBox[i].length.y / 2 + player.P_box.length.y / 2, 2)) {
			if(fallBox[i].displayFlag) combo++;
			if (combo > saveCombo) saveCombo = combo;

			if(fallBox[i].displayFlag) PlaySoundMem(box_Se,DX_PLAYTYPE_BACK);

			fallBox[i].displayFlag = false;
		}
		else if ((!player.flag && fallBox[i].displayFlag &&
			pow(fallBox[i].pos.x - player.pos.x, 2) <= pow(fallBox[i].length.x / 2 + player.P_box.length.x / 2, 2)
			&& pow(fallBox[i].pos.y - player.pos.y, 2) <= pow(fallBox[i].length.y / 2 + player.P_box.length.y / 2, 2))
			|| fallBox[i].displayFlag
			&& pow(fallBox[i].pos.x - REDLINE.pos.x, 2) <= pow(fallBox[i].length.x / 2 + REDLINE.length.x / 2, 2)
			&& pow(fallBox[i].pos.y - REDLINE.pos.y, 2) <= pow(fallBox[i].length.y / 2 + REDLINE.length.y / 2, 2)) {
			combo = 0;

			if(fallBox[i].displayFlag) PlaySoundMem(fault_Se, DX_PLAYTYPE_BACK);

			fallBox[i].displayFlag = false;
		}
	}
}

static void DrawShapes(Circle* fallCircle,Box* fallBox, int circle_Se, int box_Se, int fault_Se) {
	Move(fallCircle, fallBox);

	CircleJudge(fallCircle,circle_Se,fault_Se);

	BoxJudge(fallBox,box_Se,fault_Se);

	DrawBox(REDLINE.pos.x - REDLINE.length.x / 2, REDLINE.pos.y - REDLINE.length.y / 2,
		REDLINE.pos.x + REDLINE.length.x / 2, REDLINE.pos.y + REDLINE.length.y / 2, REDLINE.color, TRUE);

	!player.flag ? DrawCircle(player.P_circle.pos.x, player.P_circle.pos.y, player.P_circle.radius, player.P_circle.color, TRUE) :
		DrawBox(player.P_box.pos.x - player.P_box.length.x / 2, player.P_box.pos.y - player.P_box.length.y / 2,
			player.P_box.pos.x + player.P_box.length.x / 2, player.P_box.pos.y + player.P_box.length.y / 2,
			player.P_box.color, TRUE);

	for (int i = 0; i < circleCount; i++) {
		if (fallCircle[i].displayFlag)
			DrawCircle(fallCircle[i].pos.x, fallCircle[i].pos.y, fallCircle[i].radius, fallCircle[i].color, TRUE);
	}
	for (int i = 0; i < boxCount; i++) {
		if (fallBox[i].displayFlag)
			DrawBox(fallBox[i].pos.x - fallBox[i].length.x / 2, fallBox[i].pos.y - fallBox[i].length.y / 2,
				fallBox[i].pos.x + fallBox[i].length.x / 2, fallBox[i].pos.y + fallBox[i].length.y / 2, fallBox[i].color, TRUE);
	}
}

static void Reset(Circle* fallCircle, Box* fallBox,Circle* saveCircle,Box* saveBox) {
	hit = 0;

	instanceCount = 1;
	instanceSave = instanceCount;
	circleCount = 0, boxCount = 0;
	circleSave = 0;
	boxSave = 0;

	combo = 0;

	playFlag = true;

	RandomShaep();

	if (instanceFlag) circleSave = circleCount;
	if (instanceFlag) boxSave = boxCount;

	fallCircle = new Circle[circleCount];
	saveCircle = fallCircle;

	fallBox = new Box[boxCount];
	saveBox = fallBox;

	if (circleCount != 0) Initialization(fallCircle, fallBox, true);
	if (boxCount != 0) Initialization(fallCircle, fallBox, false);

	player = { MIDLE,{MIDLE,20,color[WHITE],0,true},{MIDLE,40,40,color[WHITE],0,true},false };
}

void Game(System* timer,State* state,int bgm,int circle_Se,int box_Se,int fault_Se) {
	if (instanceFlag || instanceSave != instanceCount) {
		RandomShaep();

		if(instanceFlag) circleSave = circleCount;
		if (instanceFlag) boxSave = boxCount;

		instanceSave = instanceCount;
	}

	if (playFlag) {
		ChangeVolumeSoundMem(150, bgm);
		PlaySoundMem(bgm, DX_PLAYTYPE_LOOP);
		playFlag = false;
	}

	static Circle* fallCircle = new Circle[circleCount];
	static Circle* saveFallCircle = fallCircle;

	static Box* fallBox = new Box[boxCount];
	static Box* saveFallBox = fallBox;

	if (instanceFlag) {
		if(circleCount != 0) Initialization(fallCircle, fallBox,true);
		if(boxCount != 0) Initialization(fallCircle, fallBox,false);
		instanceFlag = false;
	}

	if (circleCount != circleSave) {
		fallCircle = new Circle[circleCount];

		if(circleSave == 0) Initialization(fallCircle, fallBox, true);
		else Initialization(fallCircle, fallBox,true,saveFallCircle,nullptr,true);

		circleSave = circleCount;
		saveFallCircle = fallCircle;
	}

	if (boxCount != boxSave) {
		fallBox = new Box[boxCount];

		if(boxSave == 0) Initialization(fallCircle, fallBox, false);
		else Initialization(fallCircle, fallBox,false,nullptr,saveFallBox,true);

		boxSave = boxCount;
		saveFallBox = fallBox;
	}

	ScreenAdjustment();

	CheckHitKey(KEY_INPUT_SPACE) ? hit++ : hit = 0;
	if (hit == 1) !player.flag ? player.flag = true : player.flag = false;

	player.flag ? player.P_box.pos = player.pos : player.P_circle.pos = player.pos;

	SetFontSize(30);
	DrawFormatString(timer->pos.x, timer->pos.y, color[WHITE], "%d秒", timer->count / 60);

	DrawShapes(fallCircle,fallBox,circle_Se,box_Se,fault_Se);

	DrawBox(UI.pos.x - UI.length.x / 2, UI.pos.y - UI.length.y / 2,
		UI.pos.x + UI.length.x / 2, UI.pos.y + UI.length.y / 2, UI.color, TRUE);

	DrawFormatString(WIDTH - 270, HEIGHT - 120, color[BLACK], "コンボ数:%d", combo);
	DrawFormatString(WIDTH - 270, HEIGHT - 50, color[BLACK], "最大コンボ数:%d", saveCombo);

	timer->count--;

	if (timer->count > 0 && timer->count % 15 == 0) instanceCount++;

	if (timer->count <= 0 || CheckHitKey(KEY_INPUT_ESCAPE)) {
		StopSoundMem(bgm);

		timer->count = 0;
		*state = OVER;

		delete[] fallCircle;
		delete[] fallBox;

		Reset(fallCircle,fallBox,saveFallCircle,saveFallBox);
	}
}
