#ifndef __FogCoordinates_H_
#define __FogCoordinates_H_

#include <Windows.h>
#include <GL/glut.h>
#include <GL/glext.h>

static GLfloat f1,f2,f3;
PFNGLFOGCOORDFPROC glFogCoordf = NULL;

/** Fog Coordinates
@remarks
Render a triangle and allows you to
change the fog coordinate at each vertex by pressing several numerical keys.
While in explicit fog coordinate mode, moving the viewpoint forward and
backward (pressing the 'f' and 'b' keys) does not transform the fog coordinates
and therefore does not affect the colors of the vertices. If you stop
using explicit fog coordinates (pressing the 'c' key), moving the viewpoint
once again dramatically affects colors calculated for fog
*/
class FogCoordinates
{
public:
	int startup(int argc, char** argv)
	{
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
		glutCreateWindow(argv[0]);
		init();
		glutKeyboardFunc(keyboard);
		glutDisplayFunc(display);
		glutMainLoop();
		return 0;
	}
private:
	void init(void)
	{
		GLfloat fogColor[4] = {0.0,0.25,0.25,1.0};
		f1 = 1.0f;
		f2 = 5.0f;
		f3 = 10.0f;

		glEnable(GL_FOG);
		glFogi(GL_FOG_MODE,GL_EXP);
		glFogfv(GL_FOG_COLOR,fogColor);
		glFogf(GL_FOG_DENSITY,0.25);
		glHint(GL_FOG_HINT,GL_DONT_CARE);
		glFogi(GL_FOG_COORD_SRC,GL_FOG_COORD);
		glClearColor(0.0,0.25,0.25,1.0);
	}

	static void display(void)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		PFNGLFOGCOORDFPROC glFogCoordf = (PFNGLFOGCOORDFPROC)wglGetProcAddress("glFogCoordf");
		glColor3f(1.0f,0.75f,0.0f);
		glBegin(GL_TRIANGLES);
		    glFogCoordf(f1);
			glVertex3f(2.0f,-2.0f,0.0f);
			glFogCoordf(f2);
			glVertex3f(-2.0f,0.0f,-5.0f);
			glFogCoordf(f3);
			glVertex3f(0.0f,2.0f,-10.0f);
		glEnd();
		glutSwapBuffers();
	}

	static void keyboard(unsigned char key, int x, int y)
	{
		switch (key)
		{
		case 'c':
			glFogi(GL_FOG_COORD_SRC, GL_FRAGMENT_DEPTH);
			glutPostRedisplay();
			break;
		case 'C':
			glFogi(GL_FOG_COORD_SRC, GL_FOG_COORD);
			glutPostRedisplay();
			break;
		case '1':
			f1 = f1 + 0.25;
			glutPostRedisplay();
			break;
		case '2':
			f2 = f2 + 0.25;
			glutPostRedisplay();
			break;
		case '3':
			f3 = f3 + 0.25;
			glutPostRedisplay();
			break;
		case '8':
			if (f1 > 0.25) {
				f1 = f1 - 0.25;
				glutPostRedisplay();
			}
			break;
		case '9':
			if (f2 > 0.25) {
				f2 = f2 - 0.25;
				glutPostRedisplay();
			}
			break;
		case '0':
			if (f3 > 0.25) {
				f3 = f3 - 0.25;
				glutPostRedisplay();
			}
			break;
		case 'b':
			glMatrixMode(GL_MODELVIEW);
			glTranslatef(0.0, 0.0, -0.25);
			glutPostRedisplay();
			break;
		case 'f':
			glMatrixMode(GL_MODELVIEW);
			glTranslatef(0.0, 0.0, 0.25);
			glutPostRedisplay();
			break;
		case 27:
			exit(0);
			break;
		default:
			break;
		}
	}
};


#endif