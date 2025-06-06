#include "graphics.h"

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
	// clear the screen to change cards if needed
	al_draw_filled_rectangle(0, 0, width, height, al_map_rgb(0, 0, 0));
	// card grid
	for (int i = 0; i < 4; i++) {
		al_draw_line((width / 5 + ((width / 5) * i)), 0, (width / 5 + ((width / 5) * i)), height-30, al_map_rgb(255, 255, 255), 2);
		al_draw_line(0, ((height - 30) / 5 + (((height - 30) / 5) * i)), width, ((height - 30) / 5 + (((height-30) / 5) * i)), al_map_rgb(255, 255, 255), 2);
	}
}
// draw all flipped cards to the board
void graphics::drawCards(int flag) {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			// if the card is flipped over, draw its shape on the screen
			if (gameboard->getCard(i, j)->getFlipped() == true) {
				printShape((width / 10 + ((width / 5) * j)), ((height - 30) / 10 + (((height - 30) / 5) * i)), gameboard->getCard(i, j)->getShape(), flag);
			}
		}
	}
}
// print the specific shape that corresponds with the card
void graphics::printShape(int x, int y, int shape, int flag) {
	// pick colors 
	int color[3];
	switch (flag) {
	case 1:
		color[0] = 255;
		color[1] = 0;
		color[2] = 0;
		break;
	case 2:
		color[0] = 0;
		color[1] = 255;
		color[2] = 0;
		break;
	default:
		color[0] = 255;
		color[1] = 255;
		color[2] = 255;
		break;
	}

	switch (shape) {
	case 0:			// circle
		al_draw_circle(x, y, 10, al_map_rgb(color[0], color[1], color[2]), 2);
		break;
	case 1:			// filled circle
		al_draw_filled_circle(x, y, 10, al_map_rgb(color[0], color[1], color[2]));
		break;
	case 2:			// triangle (right side up)
		al_draw_triangle(x - 10, y - 5, x, y + 5, x + 10, y - 5, al_map_rgb(color[0], color[1], color[2]), 2);
		break;
	case 3:			// filled triangle
		al_draw_filled_triangle(x - 10, y - 5, x, y + 5, x + 10, y - 5, al_map_rgb(color[0], color[1], color[2]));
		break;
	case 4:			// square
		al_draw_rectangle(x - 10, y - 10, x + 10, y + 10, al_map_rgb(color[0], color[1], color[2]), 2);
		break;
	case 5:			// filled square
		al_draw_filled_rectangle(x - 10, y - 10, x + 10, y + 10, al_map_rgb(color[0], color[1], color[2]));
		break;
	case 6:			// x mark
		al_draw_line(x - 10, y - 10, x + 10, y + 10, al_map_rgb(color[0], color[1], color[2]), 4);
		al_draw_line(x + 10, y + 10, x - 10, y - 10, al_map_rgb(color[0], color[1], color[2]), 4);
		break;
	case 7:			// house
		al_draw_filled_triangle(x - 12, y, x, y + 10, x - 12, y, al_map_rgb(color[0], color[1], color[2]));
		al_draw_rectangle(x - 10, y, x + 10, y + 10, al_map_rgb(color[0], color[1], color[2]), 2);
		break;
	case 8:			// smiley
		al_draw_circle(x, y, 10, al_map_rgb(color[0], color[1], color[2]), 2);
		al_draw_filled_ellipse(x, y + 4, 4, 3, al_map_rgb(color[0], color[1], color[2]));
		al_draw_filled_ellipse(x, y + 3, 4, 3, al_map_rgb(0, 0, 0));
		al_draw_filled_circle(x - 5, y - 4, 1, al_map_rgb(color[0], color[1], color[2]));
		al_draw_filled_circle(x + 5, y - 4, 1, al_map_rgb(color[0], color[1], color[2]));
		break;
	case 9:			// heart
		al_draw_filled_circle(x + 5, y - 5, 7, al_map_rgb(color[0], color[1], color[2]));
		al_draw_filled_circle(x - 5, y - 5, 7, al_map_rgb(color[0], color[1], color[2]));
		al_draw_filled_triangle(x - 14, y - 2 , x + 10, y + 10, x - 14, y - 2, al_map_rgb(color[0], color[1], color[2]));
	case 10:		// diamond
		al_draw_filled_triangle(x - 10, y, x, y - 10, x + 10, y, al_map_rgb(color[0], color[1], color[2]));
		al_draw_filled_triangle(x - 10, y, x, y + 10, x + 10, y, al_map_rgb(color[0], color[1], color[2]));
		break;
	case 11:		// triangle (upside down)
		al_draw_triangle(x - 10, y + 5, x, y - 5, x + 10, y + 5, al_map_rgb(color[0], color[1], color[2]), 2);
		break;
	case 12:		// single slash
		al_draw_line(x - 10, y - 10, x + 10, y + 10, al_map_rgb(color[0], color[1], color[2]), 4);
		break;
	}

}
// draws the score to the board
void graphics::drawScore(int score, ALLEGRO_FONT* font) const {
	// clear old score
	al_draw_filled_rectangle(0, height - 30, width, height, al_map_rgb(148, 192, 212));
	al_draw_line(0, height - 30, width, height - 30, al_map_rgb(255, 255, 255), 2);
	al_draw_textf(font, al_map_rgb(255, 255, 255), 10, height - 29, 0, "Score: %i", score);
}
// returns the card coordinate that correspond with the mouse click
int graphics::getCoord(int click, string type) const {
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
