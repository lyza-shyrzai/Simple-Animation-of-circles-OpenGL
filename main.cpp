#include<gl\glut.h>
#include<math.h>
#include<vector>
using namespace std;

class Circle
{
public:
	float x, y, r, alpha;
	Circle(float _x = 0.0, float _y = 0.0, float _r = 10.0) :x(_x), y(_y), r(_r), alpha(1.0) {};
	void draw();
};

void Circle::draw()
{
	glColor4f(0.0, 0.0, 0.8, this->alpha);
	glBegin(GL_LINE_LOOP);
	for (float i = 0.0; i<2 * 3.14; i += 3.14 / 18)
	{
		glVertex2f(this->x + this->r*sin(i), this->y + this->r*cos(i));
	}
	glEnd();
}

vector<Circle> circ;

float WinWid = 400.0;
float WinHei = 400.0;
float X = 0.0, Y = 0.0;
bool down = false;

void Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_ALPHA);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	vector<Circle>::iterator i = circ.begin();
	while (i != circ.end())
	{
		i->draw();
		if (i->alpha <= 0.05f)
			i = circ.erase(i);
		else
			++i;
	}
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA);
	glutSwapBuffers();
}

void Timer(int value)
{
	for (vector<Circle>::iterator i = circ.begin(); i != circ.end(); i++)
	{
		i->r++;
		i->alpha /= 1.05;
	}
	glutPostRedisplay();
	glutTimerFunc(40, Timer, 0);
}

void Timer2(int)
{
	if (down)
	{
		Circle c(X, Y, 10);
		circ.push_back(c);
	}
	
	glutPostRedisplay();
	glutTimerFunc(80, Timer2, 0);
}

void MousePressed(int button, int state, int ax, int ay)
{
	down = button == GLUT_LEFT_BUTTON && state == GLUT_LEFT;
	if (down)
	{
		X = ax - WinWid / 2;
		Y = ay - WinHei / 2;
	}
}

void MouseMovePressed(int ax, int ay)
{
	if (down)
	{
		X = ax - WinWid / 2;
		Y = ay - WinHei / 2;
	}
}

void Initialize()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-WinWid / 2, WinWid / 2, WinHei / 2, -WinHei / 2, -200.0, 200.0);
	glMatrixMode(GL_MODELVIEW);
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(WinWid, WinHei);
	glutInitWindowPosition(100, 200);
	glutCreateWindow("Simple animation");
	glutDisplayFunc(Draw);
	glutTimerFunc(40, Timer, 0);
	glutTimerFunc(80, Timer2, 0);
	glutMotionFunc(MouseMovePressed);
	glutMouseFunc(MousePressed);
	Initialize();
	glutMainLoop();
	return 0;
}