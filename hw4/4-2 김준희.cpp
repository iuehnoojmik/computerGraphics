/***************************************************************************************************/
/*                            HW#4-2 : ���� Can Robot �𵨸�                                       */
/*  �ۼ��� : ������                          ��¥ : 2021�� 11�� 4��                                */
/*																								   */
/* ���� ���� : ���ű���κ��� �𵨸��ϰ� �޴��� �����ϸ� �ش� ��ü�� �������ٰ� ���ƿ����� �����. */
/* ���: Head: �Ӹ��� ��->�·� ����ϰ� ���ڸ��� ���ƿ´�.									       */
/*       Left Arm : ���� �ϴ� ���� ���������� �÷ȴٰ� �ٽ� ������.							       */
/*       Right Arm : ���� �ϴ� ���� ���������� �÷ȴٰ� �ٽ� ������.						       */
/*       Left Leg : ���� �ٸ��� ������ á�ٰ� �ٽ� ������.									       */
/*       Right Leg : ������ �ٸ��� ������ á�ٰ� �ٽ� ������.								       */
/*       S or s : �����̴� ���� ��ü�� �Ͻ������Ѵ�.										       */
/***************************************************************************************************/
#include <GL/glut.h>
#include <stdlib.h>

int head, left_arm, right_arm, left_leg, right_leg, st = 0;
int check1 = 0;
GLboolean check2 = false, check3 = false, check4 = false, check5 = false;

void MyDisplay(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	GLUquadricObj* qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, GLU_LINE); //Draw Style ����-����
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	///////////////////// �Ӹ� //////////////////////////
	glPushMatrix();//����Ǫ��
	glTranslatef(0.0, 1.8, 0.0);//�Ӹ� ��ġ ����
	glPushMatrix();//�Ӹ���ġǪ��
	glColor3f(0.9, 0.5, 0.0); //�Ӹ���������
	glRotatef(-90.0, 1.0, 0.0, 0.0);//�Ӹ������� �� �� �ֵ��� ȸ��
	glRotatef((GLfloat)head, 0.0, 1.0, 0.0); //�Ӹ� ȸ���� �� �ֵ��� �������� �̿�
	gluCylinder(qobj, 0.8, 0.6, 1.0, 50, 1); //�Ӹ��� �Ǹ��� Ÿ������ �𵨸�
	glPopMatrix();//�Ӹ���

	///////////////////// �� //////////////////////////
	glPushMatrix();//����ġ Ǫ��
	glColor3f(0.0, 0.0, 0.7); //����� ����
	glRotatef(90.0, 1.0, 0.0, 0.0);//���� ���鿡�� �� �� �ֵ��� ȸ��
	gluCylinder(qobj, 0.2, 0.2, 0.3, 30, 1); //���� �Ǹ��� Ÿ������ �𵨸�
	glPopMatrix();//�� ��
	
	///////////////////// ���� //////////////////////////
	glTranslatef(0.0, -0.3, 0.0);//������ġ ġ��
	glPushMatrix(); //���� ��ġ Ǫ��
	glColor3f(0.0, 0.0, 0.8); //�����������
	glRotatef(90.0, 1.0, 0.0, 0.0); //������ ���鿡�� �� �� �ֵ��� ȸ��
	gluCylinder(qobj, 1.0, 1.0, 1.5, 70, 1);//������ �Ǹ��� Ÿ������ �𵨸�
	glPopMatrix();//���� ��, �ֻ��� ������ ������ġ�� ����

	///////////////////// ���� �ٸ� //////////////////////////
	glPushMatrix();//���� ���� ��ġ Ǫ��
	glRotatef((GLfloat)left_leg, -0.1, 0.0, 0.0); //�ٸ��� ȸ���� �� �ֵ��� �������� �̿�
	glTranslatef(-0.3, -2.1, 0.0); //��������� ��ġ ����
	glPushMatrix();//���� ����� ��ġ Ǫ��
	glColor3f(1.0, 0.4, 0.7); //���� ����� ���� ����
	glRotatef(90.0, -1.0, 0.0, 0.0); //�ٸ��� ���鿡�� �� �� �ֵ��� ȸ��
	gluCylinder(qobj, 0.2, 0.2, 0.6, 20, 1);//�ٸ��� �Ǹ��� Ÿ������ �𵨸�
	glPopMatrix();//���� ����� ��

	glTranslatef(0.0, -0.6, 0.0); //���� ������ ��ġ ����
	glPushMatrix();//���������� ��ġ Ǫ��
	glColor3f(1.0, 0.6, 0.0); //���� ������ ���� ����
	glRotatef(90.0, -1.0, 0.0, 0.0); //�ٸ��� ���鿡�� �� �� �ֵ��� ȸ��
	gluCylinder(qobj, 0.2, 0.2, 0.6, 20, 1); //�ٸ��� �Ǹ��� Ÿ������ �𵨸�
	glPopMatrix();//���������� ��

	glTranslatef(-0.1, -0.15, 0.0); //���� �� ��ġ ����
	glColor3f(0.0, 0.0, 1.0); //���� �� ���� ����
	glRotatef(90.0, -1.0, 0.0, 0.0); //���� ���鿡�� �� �� �ֵ��� ȸ��
	gluCylinder(qobj, 0.3, 0.3, 0.15, 30, 1);//���� �Ǹ��� Ÿ������ �𵨸�

	glPopMatrix(); //������ ��, ���� ������ ���� ��ġ�� ����

	///////////////////// ������ �ٸ� //////////////////////////
	glPushMatrix();//������ġ����	
	glRotatef((GLfloat)right_leg, 0.1, 0.0, 0.0); //������ �����
	glTranslatef(0.3, -2.1, 0.0);
	glPushMatrix();
	glColor3f(1.0, 0.4, 0.7);
	glRotatef(90.0, -1.0, 0.0, 0.0);
	gluCylinder(qobj, 0.2, 0.2, 0.6, 20, 1); 
	glPopMatrix();

	glTranslatef(0.0, -0.6, 0.0); //������ ������
	glPushMatrix();
	glColor3f(1.0, 0.6, 0.0);
	glRotatef(90.0, -1.0, 0.0, 0.0);
	gluCylinder(qobj, 0.2, 0.2, 0.6, 20, 1);
	glPopMatrix();

	glTranslatef(0.1, -0.15, 0.0); //������ ��
	glColor3f(0.0, 0.0, 1.0);
	glRotatef(90.0, -1.0, 0.0, 0.0);
	gluCylinder(qobj, 0.3, 0.3, 0.15, 30, 1);

	glPopMatrix();
	glPopMatrix(); 

	///////////////////// ���� �� //////////////////////////
	glPushMatrix(); //���� Ǫ��
	glTranslatef(-1.1, 0.7, 0.3); //���� ��� ��ġ
	glRotatef(90, -1.0, 0.0, 0.0); 
	glRotatef(5, 0.0, 1.0, 0.0); //��ü�� ����ϵ��� ����� ȸ����Ŵ
	glPushMatrix();//���� ��� Ǫ��
	glColor3f(0.0, 1.0, 0.0); //���� ��� ���� ����
	gluCylinder(qobj, 0.2, 0.2, 0.8, 20, 1); //���� �Ǹ��� Ÿ������ �𵨸�
	glPopMatrix(); //���� �� ��

	glPushMatrix(); //���� Ǫ��
	glRotatef((GLfloat)left_arm, 0.0, -1.0, 0.0); //���� ȸ���� �� �ֵ��� �������� �̿�
	glTranslatef(0.0, 0.0, -0.8); //���� �� �Ͽ� ��ġ ����
	glPushMatrix(); //�� �Ͽ� ��ġ Ǫ��
	glColor3f(1.0, 0.6, 0.0); //�� ���� ����
	gluCylinder(qobj, 0.2, 0.2, 0.8, 20, 1); //���� �Ǹ��� Ÿ������ �𵨸�
	glPopMatrix(); //�� �Ͽ� ��

	glTranslatef(0.0, 0.0, -0.1); //�޼� ��ġ ����
	glPushMatrix(); //�� ��ġ Ǫ��
	glColor3f(1.0, 0.6, 0.0); //�� ���� ����
	gluSphere(qobj, 0.2, 10, 10); //���� �� Ÿ������ �𵨸�

	glPopMatrix();
	glPopMatrix();
	glPopMatrix(); //���� �� pop���� �������� ���ư���

	///////////////////// ������ �� //////////////////////////
	glPushMatrix(); 
	glTranslatef(1.1, 0.7, 0.3); //������ ���
	glRotatef(90, -1.0, 0.0, 0.0);
	glRotatef(5, 0.0, -1.0, 0.0);
	glPushMatrix();
	glColor3f(0.0, 1.0, 0.0);
	gluCylinder(qobj, 0.2, 0.2, 0.8, 20, 1);
	glPopMatrix();

	glPushMatrix();//�������
	glRotatef((GLfloat)right_arm, 0.0, 1.0, 0.0); //������ �� �Ͽ� 
	glTranslatef(0.0, 0.0, -0.8);
	glPushMatrix();
	glColor3f(1.0, 0.6, 0.0);
	gluCylinder(qobj, 0.2, 0.2, 0.8, 20, 1);
	glPopMatrix();

	glTranslatef(0.0, 0.0, -0.1); //������
	glPushMatrix();
	glColor3f(1.0, 0.6, 0.0);
	gluSphere(qobj, 0.2, 10, 10);


	glPopMatrix();
	glPopMatrix();
	glPopMatrix(); //���� �� ��

	glutSwapBuffers();
}

void MyTimer1(int Value) { //Head�� ������ �� ����Ǵ� Ÿ�̸� �Լ�
	if (st == 0) {
		if (check1 == 0) { //�Ӹ��� �������� 30�� ����̰� �Ѵ�.
			if (head < 30.0) {
				head += 3.0;
			}
			else //�Ӹ��� 30���� �Ǹ� �������� �Ѿ���� check1�� 1�� �ٲ۴�.
				check1 = 1;
		}
		if (check1 == 1) { //�Ӹ��� ���������� 30�� ����̰� �Ѵ�.
			if (head > -30.0) {
				head -= 3.0;
			}
			else //�Ӹ��� 30���� �Ǹ� �������� �Ѿ���� check1�� 1�� �ٲ۴�.
				check1 = 2;
		}
		if (check1 == 2) { //�Ӹ��� ���ڸ��� ���ư����� �Ѵ�.
			if (head < 0) {
				head += 3.0;
			}
			else
				return;
		}

		glutPostRedisplay();
		glutTimerFunc(40, MyTimer1, 1);
	}
}

void MyTimer2(int Value) { //Right Arm�� ������ �� ����Ǵ� Ÿ�̸� �Լ�
	if (st == 0) {
		if (check2) { //������ ���� ��ü������ 50�� �ø��� �Ѵ�.
			if (right_arm < 50.0)
			{
				right_arm += 3.0;
			}

			else
				check2 = false;

		}
		else { //������ ���� 50���� �Ǹ� �ٽ� ���ڸ��� ���ƿ����� �Ѵ�.
			if (right_arm > 0.0)
			{
				right_arm -= 3.0;
			}
		}

		glutPostRedisplay();
		glutTimerFunc(40, MyTimer2, 1);
	}

}

void MyTimer3(int Value) { //Left Arm�� ������ �� ����Ǵ� Ÿ�̸� �Լ�
	if (st == 0) {
		if (check3) { //���� ���� ��ü������ 50�� �ø��� �Ѵ�.
			if (left_arm < 50.0)
			{
				left_arm += 3.0;
			}

			else
				check3 = false;

		}
		else { //���� ���� 50���� �Ǹ� �ٽ� ���ڸ��� ���ƿ����� �Ѵ�.
			if (left_arm > 0.0)
			{
				left_arm -= 3.0;
			}
		}

		glutPostRedisplay();
		glutTimerFunc(40, MyTimer3, 1);
	}
}

void MyTimer4(int Value) { //Right Leg�� ������ �� ����Ǵ� Ÿ�̸� �Լ�
	if (st == 0) {
		if (check4) { //������ �ٸ��� 30�� ������ ���� �Ѵ�.
			if (right_leg < 30.0)
			{
				right_leg += 3.0;
			}

			else
				check4 = false;

		}
		else { //������ �ٸ��� 30���� �Ǹ� �ٽ� ���ڸ��� ���ƿ����� �Ѵ�.
			if (right_leg > 0.0)
			{
				right_leg -= 3.0;
			}
		}

		glutPostRedisplay();
		glutTimerFunc(40, MyTimer4, 1);
	}

}

void MyTimer5(int Value) { //Left Leg�� ������ �� ����Ǵ� Ÿ�̸� �Լ�
	if (st == 0) {
		if (check5) { //���� �ٸ��� 30�� ������ ���� �Ѵ�.
			if (left_leg < 30.0)
			{
				left_leg += 3.0;
			}
			else
				check5 = false;

		}
		else { //���� �ٸ��� 30���� �Ǹ� �ٽ� ���ڸ��� ���ƿ����� �Ѵ�.
			if (left_leg > 0.0)
			{
				left_leg -= 3.0;
			}
		}

		glutPostRedisplay();
		glutTimerFunc(40, MyTimer5, 1);
	}

}

void MyTimer6(int Value) { //S�� s�� �������� ����Ǵ� Ÿ�̸� �Լ�, �ƹ��͵� ������� �ʱ� ������ �����̴� ��ü�� �����.
	if (st == 1) {

	}
	glutPostRedisplay();
	glutTimerFunc(40, MyTimer6, 1);
	
	st = 0;
}

void MyKeyboard(unsigned char key, int x, int y) { //S�� s�� ������ MyTimer 6 ����
	switch (key) {
	case 'S': case 's':
		st = 1;
		glutTimerFunc(50, MyTimer6, 1);
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void MyMainMenu(int entryID) {  //���θ޴� �ݹ��Լ�
	if (entryID == 1) { 
		check1 = 0;
		glutTimerFunc(40, MyTimer1, 1); //Head�� ������ MyTimer1�� ����
	}
	else if (entryID == 2) {
		check2 = true;
		glutTimerFunc(40, MyTimer2, 1); //Right Arm�� ������ MyTimer2�� ����
	}
	else if (entryID == 3) {
		check3 = true;
		glutTimerFunc(40, MyTimer3, 1); //Left Arm�� ������ MyTimer3�� ����
	}
	else if (entryID == 4) {
		check4 = true;
		glutTimerFunc(40, MyTimer4, 1); //Right Leg�� ������ MyTimer4�� ����
	}
	else if (entryID == 5) {
		check5 = true;
		glutTimerFunc(40, MyTimer5, 1); //Left Leg�� ������ MyTimer5�� ����
	}

	glutPostRedisplay();
}

void MyInit() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 0.0); // ��� ���� ���� (����)
	GLint MyMainID = glutCreateMenu(MyMainMenu);  //���� �޴� �����
	glutAddMenuEntry("Head", 1);
	glutAddMenuEntry("Right Arm", 2);
	glutAddMenuEntry("Left Arm", 3);
	glutAddMenuEntry("Right Leg", 4);
	glutAddMenuEntry("Left Leg", 5); //�ش� ��ü ������ �´� �޴� ����
	glutAttachMenu(GLUT_RIGHT_BUTTON);  //���콺 ������ ��ư Ŭ���ϸ� �޴� â ��
}

void MyReshape(int NewWidth, int NewHeight) { 
	glViewport(0, 0, NewWidth, NewHeight);
	GLfloat WidthFactor = (GLfloat)NewWidth / (GLfloat)600;
	GLfloat HeightFactor = (GLfloat)NewHeight / (GLfloat)800;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-5.0 * WidthFactor, 5.0 * WidthFactor, -5.0 * HeightFactor, 5.0 * HeightFactor, -5.0, 5.0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(600, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Can Robot");

	MyInit();
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	glutKeyboardFunc(MyKeyboard);

	glutMainLoop();
	return 0;
}