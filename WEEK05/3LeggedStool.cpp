// kursi 3 kaki
/*
	Restu Dwi Octavriandi
	5221600013
	ComGraph

	Sumanta Guha Reference
*/

#include <GL/glew.h>
#include <GL/freeglut.h> 

static float X = 0.0;
static float Y = 0.0;
static float Z = -30.0;

// Drawing routine.
void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	glLoadIdentity();

	// kaki depan
	glPushMatrix();
	glTranslatef(X, Y-1, Z);
	glRotatef(80, 1, 0, 0);
	glColor3f(0.82, 0.4086, 0.1148);
    glutSolidCylinder(1.0, 15.0, 11.0, 2.0);
	glPopMatrix();
	
	// kaki kanan
	glPushMatrix();
	glTranslatef(X+2.5, Y-1, Z);
	glRotatef(80, -1, 0, 0);
	glRotatef(160, 0, 1, 0);
    glColor3f(0.82, 0.4086, 0.1148);
	glutSolidCylinder(1.0, 15.0, 11.0, 2.0);
	glPopMatrix();
	
	// kaki kiri
	glPushMatrix();
	glTranslatef(X-2.5, Y-1, Z);
	glRotatef(80, -1, 0, 0);
	glRotatef(160, 0, -1, 0);
	glColor3f(0.82, 0.4086, 0.1148);
    glutSolidCylinder(1.0, 15.0, 11.0, 2.0);
	glPopMatrix();

	//kepala
	glPushMatrix();
	glTranslatef(X, Y, Z);
	glRotatef(105, 1, 0, 0);
	glColor3f(0.9, 0.54, 0.036);
	glutSolidCylinder(8, 1, 40, 2);
	glPopMatrix();

	glFlush();
}

// Initialization routine.
void setup(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
		break;
	case 'a':
		X+=0.5;
		glutPostRedisplay();
		break;
	case 'd':
		X -= 0.5;
		glutPostRedisplay();
		break;
	case 's':
		Y -= 0.5;
		glutPostRedisplay();
		break;
	case 'w':
		Y += 0.5;
		glutPostRedisplay();
		break;
	case 'q':
		Z -= 0.5;
		glutPostRedisplay();
		break;
	case 'e':
		Z += 0.5;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

// Main routine.
int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("3LeggedStool.cpp");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);

	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	glutMainLoop();
}