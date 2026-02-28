#pragma once
#include	"Variable.h"

bool ErrorCheck(const char** musicFile,int fileSize);
void Error(const char** musicFile, int fileSize);
void Title(System* timer, State* state, int music);
void Game(System* timer, State* state, int music, int circle_Se, int box_Se, int fault_Se);
void Over(System* timer, State* state, int music);