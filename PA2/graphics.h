#pragma once
#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <string>
using namespace std;
#include "logic.h"


class graphics {
public:
	graphics();
	graphics(int displayheight, int displaywidth, board* newgameboard);

	void drawBoard() const;
	void drawCards();
	void printShape(int x, int y, int shape);
	void drawScore(int score, ALLEGRO_FONT* font) const;

	// helpers
	int getCoord(int click, string type) const;
private:
	int height;
	int width;
	board* gameboard;
};

#endif
