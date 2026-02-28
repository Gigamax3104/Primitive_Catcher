#pragma once

const int WIDTH = 1080; //ウインドウ幅
const int HEIGHT = 720; //ウインドウ高

struct Vector2 { //位置
	int x;
	int y;
};

const Vector2 MIDLE = { WIDTH / 2,HEIGHT / 2 }; //中央

struct Circle { //円
	Vector2 pos;
	int radius;
	int color;
	int speed;
	bool displayFlag;
};

struct Box { //矩形
	Vector2 pos;
	Vector2 length;
	int color;
	int speed;
	bool displayFlag;
};

struct Player { //プレイヤー
	Vector2 pos;
	Circle P_circle;
	Box P_box;
	bool flag;
};

struct System { //システム
	Vector2 pos;
	int count;
};

enum State { //状態
	TITLE, GAME, OVER,E
};

enum { //SE
	SE_CIRCLE = 3,
	SE_BOX = 4,
	SE_FAULT = 5
};