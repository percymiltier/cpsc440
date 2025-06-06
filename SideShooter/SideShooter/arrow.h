#include "player.h"
#include "ghost.h"

class Arrow
{
public:
	Arrow();
	~Arrow();
	void DrawArrow();
	void FireArrow(player &Player);
	void UpdateArrow(int WIDTH);
	void CollideArrow(ghost ghosts[], int cSize);
private:
	int x;
	int y;
	bool live;
	int speed;
	ALLEGRO_BITMAP *image;
};

