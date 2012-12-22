#ifndef __ThreeDimensionalBlending_H_
#define __ThreeDimensionalBlending_H_

#include <Windows.h>
#include <GL/glut.h>

#define MAXZ 8.0
#define MINZ -8.0
#define ZINC 0.4

static float solidZ = MAXZ;
static float transparentZ = MINZ;
static GLuint sphereList, cubeList;

class ThreeDimensionalBlending
{
public:
	int startup(int argc, char** argv)
	{
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
		glutInitWindowSize(500, 500);
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
		GLfloat mat_specular[] = {1.0,1.0,1.0,0.15};
		GLfloat mat_shininess[] = {100.0};
		GLfloat position[] = {0.5,0.5,1.0,0.0};//最后一个参数是0.0，表示该光源为无限远处的平行光

		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

		//平行光
		glLightfv(GL_LIGHT0, GL_POSITION, position);

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_DEPTH_TEST);

		/*Allocates range number of contiguous, previously unallocated display list
			indices. The integer returned is the index that marks the beginning of a
			contiguous block of empty display list indices. The returned indices are
			all marked as empty and used, so subsequent calls to glGenLists() don't
			return these indices until they're deleted. Zero is returned if the requested
			number of indices isn't available, or if range is zero.*/
		sphereList = glGenLists(1);

		/*Specifies the start of a display list. OpenGL routines that are called
			subsequently (until glEndList() is called to end the display list) are stored
			in a display list, except for a few restricted OpenGL routines that can't be
			stored. (Those restricted routines are executed immediately, during the
			creation of the display list.) list is a nonzero positive integer that uniquely
			identifies the display list. The possible values for mode are GL_COMPILE
			and GL_COMPILE_AND_EXECUTE. Use GL_COMPILE if you don't want
			the OpenGL commands executed as they're placed in the display list; to
			cause the commands to be both executed immediately and placed in the
			display list for later use, specify GL_COMPILE_AND_EXECUTE.*/
		glNewList(sphereList, GL_COMPILE);
		    glutSolidSphere(0.4, 16,16);
		glEndList();//Marks the end of a display list.

		cubeList = glGenLists(1);
		glNewList(cubeList,GL_COMPILE);
		    glutSolidCube(0.6);
		glEndList();
	}

	static void reshape(int w, int h)
	{
		glViewport(0,0,(GLint)w, (GLint)h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		if(w<=h)
		{
			glOrtho(-1.5, 1.5, -1.5*(GLfloat)h/(GLfloat)w,1.5*(GLfloat)h/(GLfloat)w, -10.0, 10.0);
		}
		else
		{
			glOrtho(-1.5*(GLfloat)w/(GLfloat)h,1.5*(GLfloat)w/(GLfloat)h, -1.5, 1.5, -10.0, 10.0);
		}
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}

	static void display(void)
	{
		GLfloat mat_solid[] = {0.75,0.75,0.0,1.0};
		GLfloat mat_zero[] = {0.0, 0.0, 0.0, 1.0};
		GLfloat mat_transparent[] = {0.0, 0.8, 0.8, 0.6};
		GLfloat mat_emission[] = {0.0, 0.3, 0.3, 0.6};

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glPushMatrix();
		    glTranslatef(-0.15,-0.15,solidZ);
			glMaterialfv(GL_FRONT,GL_EMISSION, mat_zero);
			glMaterialfv(GL_FRONT,GL_DIFFUSE, mat_solid);
			glCallList(sphereList);
		glPopMatrix();

		glPushMatrix();
		    glTranslatef(0.15,0.15,transparentZ);
			glRotatef(15.0,1.0,1.0,0.0);
			glRotatef(30.0,0.0,1.0,0.0);
			glMaterialfv(GL_FRONT,GL_EMISSION, mat_emission);
			glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_transparent);
			glEnable(GL_BLEND);
			glDepthMask(GL_FALSE);//调用glDepthMask(GL_FALSE);可将深度缓冲区设置为只读形式
			glBlendFunc(GL_SRC_ALPHA,GL_ONE);
			glCallList(cubeList);
			glDepthMask(GL_TRUE);//调用glDepthMask(GL_TRUE);可将深度缓冲区设置为可读可写形式
			glDisable(GL_BLEND);
		glPopMatrix();

		glutSwapBuffers();
	}

	static void animate(void)
	{
		if (solidZ <= MINZ || transparentZ >= MAXZ)
			glutIdleFunc(NULL);
		else {
			solidZ -= ZINC;
			transparentZ += ZINC;
			glutPostRedisplay();
		}
	}

	static void keyboard(unsigned char key, int x, int y)
	{
		switch (key) {
		case 'a':
		case 'A':
			solidZ = MAXZ;
			transparentZ = MINZ;
			glutIdleFunc(animate);
			break;
		case 'r':
		case 'R':
			solidZ = MAXZ;
			transparentZ = MINZ;
			glutPostRedisplay();
			break;
		case 27:
			exit(0);
			break;
		}
	}
};

#endif