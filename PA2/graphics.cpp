#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "logic.h"
#include <string>
using namespace std;


class graphics {
public:
	graphics();
	graphics(int displayheight, int displaywidth, board* newgameboard);

	void drawBoard() const;
	void drawCards();
	void printShape(int x, int y, int shape);
	void drawScore(int score, ALLEGRO_FONT* font);

	// helpers
	int getCoord(int click, string type);
private:
	int height;
	int width;
	board* gameboard;
};

// constructors
graphics::graphics() {
	height = 0;
	width = 0;
	gameboard = NULL;
}
graphics::graphics(int displayheight, int displaywidth, board* newgameboard) {
	height = displayheight;
	width = displaywidth;
	gameboard = newgameboard;
}
// draw the game board
void graphics::drawBoard() const {
	// card grid
	for (int i = 0; i < 4; i++) {
		al_draw_line((width / 5 + ((width / 5) * i)), 0, (width / 5 + ((width / 5) * i)), height-20, al_map_rgb(255, 255, 255), 2);
		al_draw_line(0, ((height - 20) / 5 + (((height - 20) / 5) * 0)), width, ((height - 20) / 5 + (((height-20) / 5) * 0)), al_map_rgb(255, 255, 255), 2);
	}
	// bottom banner
	al_draw_line(0, height - 20, width, height, al_map_rgb(255, 255, 255), 2);
	al_draw_filled_rectangle(0, height - 20, width, height, al_map_rgb(148, 192, 212));
}
// draw all flipped cards to the board
void graphics::drawCards() {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; i++) {
			// if the card is flipped over, draw its shape on the screen
			if (gameboard->getCard(i, j).getFlipped() == true) {
				printShape((width / 10 + ((width / 5) * i)), ((height - 20) / 10 + (((height - 20) / 5) * i)), gameboard->getCard(i, j).getShape());
			}
		}
	}
}
// print the specific shape that corresponds with the card
void graphics::printShape(int x, int y, int shape) {
	switch (shape) {
	case 0:			// circle
		al_draw_circle(x, y, 5, al_map_rgb(255, 255, 255), 2);
		break;
	case 1:			// filled circle
		al_draw_filled_circle(x, y, 5, al_map_rgb(255, 255, 255));
		break;
	case 2:			// triangle (right side up)
		al_draw_triangle(x - 5, y - 3, x, y + 3, x + 5, y - 2, al_map_rgb(255, 255, 255), 2);
		break;
	case 3:			// filled triangle
		al_draw_filled_triangle(x - 5, y - 3, x, y + 2, x + 5, y - 2, al_map_rgb(255, 255, 255));
		break;
	case 4:			// square
		al_draw_rectangle(x - 5, y - 5, x + 5, y + 5, al_map_rgb(255, 255, 255), 2);
		break;
	case 5:			// filled square
		al_draw_filled_rectangle(x - 5, y - 5, x + 5, y + 5, al_map_rgb(255, 255, 255));
		break;
	case 6:			// x mark
		al_draw_line(x - 5, y - 5, x + 5, y + 5, al_map_rgb(255, 255, 255), 4);
		al_draw_line(x + 5, y + 5, x - 5, y - 5, al_map_rgb(255, 255, 255), 4);
		break;
	case 7:			// house
		al_draw_filled_triangle(x - 6, y, x, y + 5, x - 6, y, al_map_rgb(255, 255, 255));
		al_draw_rectangle(x - 5, y, x + 5, y + 5, al_map_rgb(255, 255, 255), 2);
		break;
	case 8:			// smiley
		al_draw_circle(x, y, 5, al_map_rgb(255, 255, 255), 2);
		al_draw_filled_ellipse(x, y + 3, 2, 8, al_map_rgb(0, 0, 0));
		al_draw_filled_ellipse(x, y + 4, 2, 8, al_map_rgb(255, 255, 255));
		al_draw_filled_circle(x - 2, y - 3, 5, al_map_rgb(255, 255, 255));
		al_draw_filled_circle(x + 2, y - 3, 5, al_map_rgb(255, 255, 255));
		break;
	case 9:			// heart
		al_draw_filled_circle(x + 3, y - 2, 3, al_map_rgb(255, 255, 255));
		al_draw_filled_circle(x - 3, y - 2, 3, al_map_rgb(255, 255, 255));
		al_draw_filled_triangle(x - 6, y - 2 , x + 5, y + 5, x - 6, y - 2, al_map_rgb(255, 255, 255));
	case 10:		// diamond
		al_draw_filled_triangle(x - 5, y, x, y - 5, x + 5, y, al_map_rgb(255, 255, 255));
		al_draw_filled_triangle(x - 5, y, x, y + 5, x + 5, y, al_map_rgb(255, 255, 255));
		break;
	case 11:		// triangle (upside down)
		al_draw_triangle(x - 5, y + 3, x, y - 3, x + 5, y + 2, al_map_rgb(255, 255, 255), 2);
		break;
	case 12:		// single slash
		al_draw_line(x - 5, y - 5, x + 5, y + 5, al_map_rgb(255, 255, 255), 4);
		break;
	}

}
// draws the score to the board
void graphics::drawScore(int score, ALLEGRO_FONT* font) {
	// clear old score
	al_draw_filled_rectangle(0, height - 20, width, height, al_map_rgb(0, 0, 0));
	al_draw_textf(font, al_map_rgb(255, 255, 255), 0, height - 18, 0, "Score: %i", score);
}
// returns the card coordinate that correspond with the mouse click
int graphics::getCoord(int click, string type) {
	int spacerX = width / 5;
	int spacerY = height / 5;
	if (type == "x") {
		return click / spacerX;
	}
	else if (type == "y") {
		return click / spacerY;
	}
	else {
		// not a valid type
		return -1;
	}
}
