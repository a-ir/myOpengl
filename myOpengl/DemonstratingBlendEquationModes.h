#include <Windows.h>
#include <GL/glut.h>
#include <GL/glext.h>

PFNGLBLENDEQUATIONPROC glBlendEquation = NULL;//定义函数指针

class DemonstratingBlendEquationModes{
public:
	int startup(int argc, char** argv){
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
		glutInitWindowSize(200, 200);
		glutCreateWindow(argv[0]);
		init();
		glutKeyboardFunc(keyboard);
		glutDisplayFunc(display);
		glutMainLoop();
		return 0;
	}
private:
	void init(void){
		//Sets the current clearing color for use in clearing color buffers in RGBA
		//mode
		//The default clearing color is (0, 0, 0, 0), which is black
		glClearColor(1.0,1.0,0.0,0.0);

		//Controls how color values in the fragment being processed (the source)
		//are combined with those already stored in the framebuffer (the destination)
		glBlendFunc(GL_ONE,GL_ONE);
		glEnable(GL_BLEND);
	}

	static void display(void){
		//Clears the specified buffers to their current clearing values
		glClear(GL_COLOR_BUFFER_BIT);

		glColor3f(0.0,0.0,1.0);
		glRectf(-0.5, -0.5, 0.5, 0.5);
		glFlush();
	}

	static void keyboard(unsigned char key, int x, int y){
		//glBlendEquation是OpenGL的扩展函数，以下是一种调用方法，还有其它调用方法，有待研究
		PFNGLBLENDEQUATIONPROC glBlendEquation = (PFNGLBLENDEQUATIONPROC)wglGetProcAddress("glBlendEquation");
		switch(key){
		case'a': case'A':
			glBlendEquation(GL_FUNC_ADD);
			break;
		case's':case'S':
			glBlendEquation(GL_FUNC_SUBTRACT);
			break;
		case 'r': case 'R':
			glBlendEquation(GL_FUNC_REVERSE_SUBTRACT);
			break;
		case 'm': case 'M':
				/* The minimum of each component is computed, as
				* [min(1,0),min(1,0),min(0,1)] which equates to (0,0,0).
				* This will produce a black square on the yellow
				* background. */
			glBlendEquation(GL_MIN);
			break;
		case 'x': case 'X':
				/* The minimum of each component is computed, as
				* [max(1, 0), max(1, 0), max(0, 1)] which equates to
				* (1, 1, 1). This will produce a white square on the
				* yellow background. */
			glBlendEquation(GL_MAX);
			break;
		case 27:
			exit(0);
			break;
		}

		glutPostRedisplay();
	}
};