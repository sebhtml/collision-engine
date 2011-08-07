
#include "Object.h"

class Wall: public Object{
	int m_x;
	int m_y;
	int m_width;
	int m_height;
	int m_angle;
	int m_red;
	int m_green;
	int m_blue;
public:
	void update();
	void display(Screen*screen);
	Wall(int centerX,int centerY,int width,int height,int angle,int red,int green,int blue);
};
