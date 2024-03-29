#include <Windows.h>
#include <GL/glut.h>

class BlendingExampleAlpha
{
public:
	int startup(int argc, char** argv)
	{
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
		glutInitWindowSize(200, 200);
		glutCreateWindow(argv[0]);
		init();
		glutReshapeFunc(reshape);
		glutKeyboardFunc(keyboard);
		glutDisplayFunc(display);
		glutMainLoop();
		return 0;
	}
private:
	void init(void){
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glShadeModel(GL_FLAT);
		glClearColor(0.0,0.0,0.0,0.0);
	}

	static void drawLeftTriangle(void){
		glBegin(GL_TRIANGLES);
		    glColor4f(1.0,1.0,0.0,0.25);
			glVertex3f(0.1,0.9,0.0);
			glVertex3f(0.1,0.1,0.0);
			glVertex3f(0.7,0.5,0.0);
		glEnd();
	}

	static void drawRightTriangle(void){
		glBegin(GL_TRIANGLES);
		    glColor4f(0.0, 1.0, 1.0, 0.75);
			glVertex3f(0.9, 0.9, 0.0);
			glVertex3f(0.3, 0.5, 0.0);
			glVertex3f(0.9, 0.1, 0.0);
		glEnd();
	}

	static void display(void){
		glClear(GL_COLOR_BUFFER_BIT);

		if(leftFirst){
			drawLeftTriangle();
			drawRightTriangle();
		}
		else
		{
			drawRightTriangle();
			drawLeftTriangle();
		}

		glFlush();
	}
	
	static void reshape(int w, int h)
	{
		glViewport(0,0,(GLsizei)w, (GLsizei)h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		if(w <=h)
		{
			gluOrtho2D(0.0,1.0,0.0,1.0*(GLsizei)h/(GLsizei)w);
		}
		else
		{
			gluOrtho2D(0.0, 1.0*(GLfloat)w/(GLfloat)h, 0.0, 1.0);
		}
	}

	static void keyboard(unsigned char key, int x, int y)
	{
		switch (key)
		{
		case 't':
		case'T':
			leftFirst = !leftFirst;
			glutPostRedisplay();
			break;
		case 27:
			exit(0);
			break;
		default:
			break;
		}
	}
public:
	static int leftFirst;
};

int BlendingExampleAlpha::leftFirst = GL_TRUE;