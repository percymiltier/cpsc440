class sprite
{
public: 
	~sprite();
	void updatesprite();
	void bouncesprite(int SCREEN_W, int SCREEN_H);
	void load_animated_sprite(int size);
	void drawSprite();
	void detectCollision(sprite sprites[], int count, int width, int height);

	// setters
	void setcollision(bool col);
	void setSpin(bool spinning);
	void setScared(bool scary);
	void setBaby(bool babymode);
	void setFreeze(bool frozen);
	void setTime(int newtime);

	// getters
	int getX() { return x; }
	int getY() { return y; }
	int getWidth() { return width; }
	int getHeight() { return height; }
	int getXDelay() { return xdelay; }
	int getYDelay() { return ydelay; }
	int getXCount() { return xcount; }
	int getYCount() { return ycount; }
	int getCurframe() { return curframe; }
	int getMaxframe() { return maxframe; }
	int getAnimDir() { return animdir; }
	int getFramecount() { return framecount; }
	int getFramedelay() { return framedelay; }

	bool getCol() { return collision; }
	bool getSpin() { return spin; }
	bool getScared() { return scared; }
	bool getBaby() { return baby; }
	bool getFreeze() { return freeze; }

	double getTime() { return timer; }
	double getScale() { return scale; }

private:
	int x,y;
	int width = 128;
	int height = 128;
	int xspeed,yspeed;
	int xdelay,ydelay;
	int xcount,ycount;
	int curframe,maxframe,animdir;
	int framecount,framedelay;
	ALLEGRO_BITMAP *image[20];

	// additional variables
	bool collision = false;
	bool spin = false;
	bool scared = false;
	bool baby = false;
	bool freeze = false;

	// timer
	double timer = 0;
	double angle = 0;
	int scale = 1;
};