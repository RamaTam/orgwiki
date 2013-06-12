// Triangle.cpp
// OpenGL SuperBible
// Demonstrates OpenGL Triangle Fans, backface culling, and depth testing
// Program by Richard S. Wright Jr.
#include <GL/glut.h>
#include <math.h>


// Define a constant for the value of PI
#define GL_PI 3.1415f

// Rotation amounts
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

// Flags for effects
// Flags for effects
int iCull = 0;
int iOutline = 0;
int iDepth = 0;

///////////////////////////////////////////////////////////////////////////////
// Reset flags as appropriate in response to menu selections
void ProcessMenu(int value)
	{
	switch(value)
		{
		case 1:
			iDepth = !iDepth;
			break;

		case 2:
			iCull = !iCull;
			break;

		case 3:
			iOutline = !iOutline;
		default:
			break;
		}

	glutPostRedisplay();
	}


// Called to draw scene
void RenderScene(void)
	{
	GLfloat x,y,angle;  // �洢����ͽǶ�
	int iPivot = 1;		// ���ڱ�ʶ�����ɫ

	// ������ںͻ�����
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// �����־�ѱ����ã���ѡ��
	if(iCull)
		glEnable(GL_CULL_FACE);
	else
		glDisable(GL_CULL_FACE);

	// �����־�ѱ����ã�����Ȳ���
	if(iDepth)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);

	// �����־�ѱ����ã�ֻ��Ϊ�߿���Ʊ���
	if(iOutline)
		glPolygonMode(GL_BACK,GL_LINE);
	else
		glPolygonMode(GL_BACK,GL_FILL);
		

	// �������״̬��������ת
	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);


	// ��ʼ������������
	glBegin(GL_TRIANGLE_FAN);

	// Բ׶��׶�����������ȵĹ�����
    // ��z���ƶ�������һ��Բ׶������Բ
	glVertex3f(0.0f, 0.0f, 75.0f);
	
	// ��һ��Բѭ�����������Բ��ż����ָ��Ϊ�������ȵĶ���
	for(angle = 0.0f; angle < (2.0f*GL_PI); angle += (GL_PI/8.0f))
		{
		// ������һ�������x��yλ��
		x = 50.0f*sin(angle);
		y = 50.0f*cos(angle);
	
		// ����ʹ�ú�ɫ����ɫ
		if((iPivot %2) == 0)
			glColor3f(0.0f, 1.0f, 0.0f);
		else
			glColor3f(1.0f, 0.0f, 0.0f);
			
		// ���ӻ�׼ֵ���´θı���ɫ
		iPivot++;

		// Ϊ��������ָ����һ������
		glVertex2f(x, y);
		}

	// ���ΪԲ׶������������
	glEnd();


	// ��ʼ����һ���µ��������ȣ����ڸ���Բ׶�ĵ�
	glBegin(GL_TRIANGLE_FAN);

	// �������ȵ�����λ��ԭ��
	glVertex2f(0.0f, 0.0f);
	for(angle = 0.0f; angle < (2.0f*GL_PI); angle += (GL_PI/8.0f))
		{
		// ������һ�������x��yλ��
		x = 50.0f*sin(angle);
		y = 50.0f*cos(angle);
	
		// ����ʹ�ú�ɫ����ɫ
		if((iPivot %2) == 0)
			glColor3f(0.0f, 1.0f, 0.0f);
		else
			glColor3f(1.0f, 0.0f, 0.0f);
			
		// ���ӻ�׼ֵ���´θı���ɫ
		iPivot++;

		// ָ�������ε���һ������
		glVertex2f(x, y);
		}

	// ��ɻ��Ƹ��ǵ������������
	glEnd();

	// �ָ��任
	glPopMatrix();


    glutSwapBuffers();
	}

// This function does any needed initialization on the rendering
// context. 
void SetupRC()
	{
	// Black background
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f );

	// Set drawing color to green
	glColor3f(0.0f, 1.0f, 0.0f);

	// ����ɫģʽ����Ϊ������ɫ
	glShadeModel(GL_FLAT);

	// ˳ʱ�뻷�ƵĶ����������
    // ���Ƿ�ת�ģ���Ϊ����ʹ�õ�����������
	glFrontFace(GL_CW);
	}

void SpecialKeys(int key, int x, int y)
	{
	if(key == GLUT_KEY_UP)
		xRot-= 5.0f;

	if(key == GLUT_KEY_DOWN)
		xRot += 5.0f;

	if(key == GLUT_KEY_LEFT)
		yRot -= 5.0f;

	if(key == GLUT_KEY_RIGHT)
		yRot += 5.0f;

	if(key > 356.0f)
		xRot = 0.0f;

	if(key < -1.0f)
		xRot = 355.0f;

	if(key > 356.0f)
		yRot = 0.0f;

	if(key < -1.0f)
		yRot = 355.0f;

	// Refresh the Window
	glutPostRedisplay();
	}


void ChangeSize(int w, int h)
	{
	GLfloat nRange = 100.0f;

	// Prevent a divide by zero
	if(h == 0)
		h = 1;

	// Set Viewport to window dimensions
    glViewport(0, 0, w, h);

	// Reset projection matrix stack
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Establish clipping volume (left, right, bottom, top, near, far)
    if (w <= h) 
		glOrtho (-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange, nRange);
    else 
		glOrtho (-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange, nRange);

	// Reset Model view matrix stack
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	}

int main(int argc, char* argv[])
	{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Triangle Culling Example");
	
	// Create the Menu
	glutCreateMenu(ProcessMenu);
	glutAddMenuEntry("Toggle depth test",1);
	glutAddMenuEntry("Toggle cull backface",2);
	glutAddMenuEntry("Toggle outline back",3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(SpecialKeys);
	glutDisplayFunc(RenderScene);
	SetupRC();
	glutMainLoop();

	return 0;
	}
