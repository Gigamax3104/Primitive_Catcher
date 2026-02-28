#pragma once
#define	COLOR_RED 0xff0000 //ê‘
#define COLOR_GREEN 0x00ff00 //óŒ
#define COLOR_BLUE 0x0000ff //ê¬
#define COLOR_YELLOW 0xffff00 //â©
#define COLOR_LIGHTBLUE 0x00ffff //êÖ
#define COLOR_MAZENTA 0xff00ff //éá
#define COLOR_WHITE 0xffffff //îí
#define COLOR_BLACK 0x000000 //çï

const int color[] = {
	COLOR_RED,COLOR_GREEN,COLOR_BLUE,COLOR_YELLOW,COLOR_LIGHTBLUE,COLOR_MAZENTA,COLOR_WHITE,COLOR_BLACK
};

const int COLORSIZE = sizeof color / sizeof color[0];

enum {
	RED,GREEN,BLUE,YELLOW,LIGHTBLUE,MAZENTA,WHITE,BLACK
};