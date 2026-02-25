#pragma once

const int WIDTH = 1080;
const int HEIGHT = 720;

struct Vector2 {
	int x;
	int y;
};

const Vector2 MIDLE = { WIDTH / 2,HEIGHT / 2 };

struct Circle {
	Vector2 pos;
	int radius;
	int color;
	int speed;
	bool displayFlag;
};

struct Box {
	Vector2 pos;
	Vector2 length;
	int color;
	int speed;
	bool displayFlag;
};

struct Player {
	Vector2 pos;
	Circle P_circle;
	Box P_box;
	bool flag;
};

struct System {
	Vector2 pos;
	int count;
};

enum State {
	TITLE, GAME, OVER
};