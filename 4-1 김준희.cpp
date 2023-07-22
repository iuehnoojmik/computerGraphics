/*************************************************************************/
/*                    HW#4-1  �κ� ��-�� �𵨸�     	   			     */
/*  �ۼ��� : ������                              ��¥ : 2022�� 10�� 7��  */
/*																		 */
/* ���� ���� : ��Ľ��ð� Ÿ�̸��Լ��� �̿��Ͽ� �հ����� �Ȱ����� ���� 	 */
/*			   �κ� ��-���� �𵨸�			                             */
/* ���:															     */
/*      Ű���� 1: ��� �հ��� ������ ��ġ�� �ݺ�                       */
/*      Ű���� 2: ���� �հ��� ������ ��ġ�� �ݺ�                         */
/*      Ű���� 3: ������ �հ��� ������ ��ġ�� �ݺ�                       */
/*      Ű���� S�Ǵ� s: �����̴� �հ��� ���߱�		                     */
/*      ���� ���콺: ���,�Ȳ�ġ,�հ����� ���� �������� ���� ��� ����� */
/*      ������ ���콺: ���,�Ȳ�ġ,�հ����� ������� �ǵ�����            */
/*************************************************************************/
#include<iostream>
using namespace std;

#include <GL/glut.h>
static int shoulder, elbow = 0;
static int fin1_1, fin1_2, fin1_3 = 0;
static int fin2_1, fin2_2, fin2_3 = 0;
static int fin3_1, fin3_2, fin3_3 = 0;
GLboolean work = false;

void MyInit() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 0.0); // ��� ���� ���� (����)
	glOrtho(-5.0, 5.0, -5.0, 5.0, -5.0, 5.0);
}

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	gluLookAt(0.7, 0.5, 1.5, 1.0, 0.0, 0.0, 0.0, 2.0, 0.0); //�κ����� ���� ���� ����

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix(); //���� Ǫ��
	//�� ���
	glTranslatef(-1.0, 0.0, 0.0);
	glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0); //���� �̵��� ���¿��� ȸ���ϵ��� ����
	glTranslatef(1.0, 0.0, 0.0); //���� �������� ������
	glPushMatrix(); 
	glScalef(2.0, 0.4, 1.0); //���� ũ�⸦ x������ 2��, y������ 0.4�� Ȯ���Ѵ�.
	glutWireCube(1.0); //���� ���̾�ť��� �𵨸�
	glPopMatrix(); //scale�� ������ pop
	
	//�� �Ͽ�
	glTranslatef(1.0, 0.0, 0.0); 
	glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0); //�Ȳ�ġ�� ȸ���� �� �ֵ��� �� ����
	glTranslatef(1.0, 0.0, 0.0); //��Ͽ��� ��ġ�� ����
	glPushMatrix();
	glScalef(2.0, 0.4, 1.0);
	glutWireCube(1.0);
	glPopMatrix();

	//1�� �հ���
	glPushMatrix();
	glTranslatef(1.0, 0.0, 0.0); //�հ��� �� �ȿ� �پ��ִ� ����
	glRotatef((GLfloat)fin1_1, 0.0, 0.0, 1.0);
	glTranslatef(0.2, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.5, 0.2, 0.2);
	glutWireCube(1.0);

	glRotatef((GLfloat)fin1_2, 0.0, 0.0, 1.0); //�հ��� �� ��� ����
	glTranslatef(1.0, 0.0, 0.0);
	glutWireCube(1.0);

	glRotatef((GLfloat)fin1_3, 0.0, 0.0, 1.0); //�հ��� �� ���� �� ����
	glTranslatef(1.0, 0.0, 0.0);
	glutWireCube(1.0);
	glPopMatrix();
	glPopMatrix();

	//2�� �հ���
	glPushMatrix();
	glTranslatef(1.0, 0.0, 0.0); //�հ��� �� �ȿ� �پ��ִ� ����
	glRotatef(50, 0.0, 1.0, 0.0);
	glRotatef((GLfloat)fin2_1, 0.0, 0.0, 1.0);
	glTranslatef(0.2, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.5, 0.2, 0.2);
	glutWireCube(1.0);

	glRotatef((GLfloat)fin2_2, 0.0, 0.0, 1.0); //�հ��� �� ��� ����
	glTranslatef(1.0, 0.0, 0.0);
	glutWireCube(1.0);

	glRotatef((GLfloat)fin2_3, 0.0, 0.0, 1.0); //�հ��� ���� �� ����
	glTranslatef(1.0, 0.0, 0.0);
	glutWireCube(1.0);
	glPopMatrix();
	glPopMatrix();

	//3�� �հ���
	glPushMatrix();
	glTranslatef(1.0, 0.0, 0.0); //�հ��� �� �ȿ� �پ��ִ� ����
	glRotatef(-50, 0.0, 1.0, 0.0);
	glRotatef((GLfloat)fin3_1, 0.0, 0.0, 1.0);
	glTranslatef(0.2, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.5, 0.2, 0.2);
	glutWireCube(1.0);

	glRotatef((GLfloat)fin3_2, 0.0, 0.0, 1.0); //�հ��� �� ��� ����
	glTranslatef(1.0, 0.0, 0.0);
	glutWireCube(1.0);

	glRotatef((GLfloat)fin3_3, 0.0, 0.0, 1.0); //�հ��� ���� �� ����
	glTranslatef(1.0, 0.0, 0.0);
	glutWireCube(1.0);
	glPopMatrix();
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();
	glutSwapBuffers();
}

void timer1(int value) { //1��Ű���带 ������ ����Ǵ� Ÿ�̸��Լ� (��� �հ���)
	if (work == true && shoulder == 0) {
		if (fin1_1 < 100) { //�տ� �پ��ִ� ���� 100���� �ɶ����� �����δ�
			if (fin1_2 < 10) { //���� ù��°�� �ι�° ���� �����̵��� ����
				fin1_1 += 5;
				fin1_2 += 1;
			}
			else if (fin1_2 >= 10) { //���� ���� �Ŀ��� ����° ���� �����̵��� ����
				fin1_1 += 5;
				fin1_2 += 1;
				fin1_3 += 2;
			}
			glutPostRedisplay();
		}

		else if (fin1_1 == 100) { //�پ��ִ� ���� 100���� �ȴٸ�
			fin1_1 = 460; //������ ���� 360���� ���� 460���� �������ش�
			glutPostRedisplay();
		}

		else if (fin1_1 > 360) { //460���� ���¿��� ���������� �ٽ� �հ����� �ǵ�����
			if (fin1_2 <= 10) {
				fin1_1 -= 5;
				fin1_2 -= 1;
			}
			else if (fin1_2 > 10) {
				fin1_1 -= 5;
				fin1_2 -= 1;
				fin1_3 -= 2;
			}
			glutPostRedisplay();
		}

		else if (fin1_1 == 360) { //���� �ٽ� 0(+360)���� �ȴٸ� ������� ������ �������ش�
			fin1_1 = 0;
			fin1_2 = 0;
			fin1_3 = 0;
			glutPostRedisplay();
		}

		glutTimerFunc(50, timer1, 0);
	}
}

void timer2(int value) {
	if (work == true && shoulder == 0) {
		if (fin2_1 < 100) {
			if (fin2_2 < 10) {
				fin2_1 += 5;
				fin2_2 += 1;
			}
			else if (fin2_2 >= 10) {
				fin2_1 += 5;
				fin2_2 += 1;
				fin2_3 += 2;
			}
			glutPostRedisplay();
		}

		else if (fin2_1 == 100) {
			fin2_1 = 460;
			glutPostRedisplay();
		}

		else if (fin2_1 > 360) {
			if (fin2_2 <= 10) {
				fin2_1 -= 5;
				fin2_2 -= 1;
			}
			else if (fin2_2 > 10) {
				fin2_1 -= 5;
				fin2_2 -= 1;
				fin2_3 -= 2;
			}
			glutPostRedisplay();
		}

		else if (fin2_1 == 360) {
			fin2_1 = 0;
			fin2_2 = 0;
			fin2_3 = 0;
			glutPostRedisplay();
		}

		glutTimerFunc(50, timer2, 0);
	}
}

void timer3(int value) {
	if (work == true && shoulder == 0) {
		if (fin3_1 < 100) {
			if (fin3_2 < 10) {
				fin3_1 += 5;
				fin3_2 += 1;
			}
			else if (fin3_2 >= 10) {
				fin3_1 += 5;
				fin3_2 += 1;
				fin3_3 += 2;
			}
			glutPostRedisplay();
		}

		else if (fin3_1 == 100) {
			fin3_1 = 460;
			glutPostRedisplay();
		}

		else if (fin3_1 > 360) {
			if (fin3_2 <= 10) {
				fin3_1 -= 5;
				fin3_2 -= 1;
			}
			else if (fin3_2 > 10) {
				fin3_1 -= 5;
				fin3_2 -= 1;
				fin3_3 -= 2;
			}
			glutPostRedisplay();
		}

		else if (fin3_1 == 360) {
			fin3_1 = 0;
			fin3_2 = 0;
			fin3_3 = 0;
			glutPostRedisplay();
		}

		glutTimerFunc(50, timer3, 0);
	}
}

void timer4(int value) { //S�� s�� ���������� ����Ǵ� Ÿ�̸� �Լ�, �������� �����.
	if (work == false) {}

	glutPostRedisplay();
	glutTimerFunc(50, timer4, 0);
}

void timer5(int value) { //���콺 ������ Ŭ���ϸ� ����Ǵ� Ÿ�̸� �Լ�
	if (work == true) { 
		if (fin1_1 >= 120) //�հ��� ù��° ���� 120���� �Ǹ� �Լ��� �ߴܽ�Ų��
			work = false;
		else {
			if (elbow >= 25) { //�Ȳ�ġ ������ 25���� ������ �հ����鵵 �����ش�.
				if (fin1_2 > 10) { //�ι�° ������� 12�� �̻� ���η����� ����° ����鵵 ���η��ش�
					fin1_1 += 3;
					fin2_1 += 3;
					fin3_1 += 3;

					fin1_2 += 2;
					fin2_2 += 2;
					fin3_2 += 2;

					fin1_3 += 1;
					fin2_3 += 1;
					fin3_3 += 1;
				}
				else if(fin1_1 > 40) { //ù��° ������� 40�� �̻� ���η����� �ι�° ����鵵 ���η��ش�
					fin1_1 += 3;
					fin2_1 += 3;
					fin3_1 += 3;

					fin1_2 += 3;
					fin2_2 += 3;
					fin3_2 += 3;
				}
				else { //�հ������� ù��° ���� ���� ���η��ش�
					fin1_1 += 3;
					fin2_1 += 3;
					fin3_1 += 3;
				}
			}
			else if (shoulder >= 10) { //��� ������ 10���� �Ѿ�� �Ȳ�ġ ������ ������Ų��.
				elbow += 1;
			}
			else //���� ó�� ����Ǵ� �ݺ���, ��� ������ ������Ų��.
				shoulder += 1;
		}
		glutPostRedisplay();
		glutTimerFunc(50, timer5, 0);
	}
}

void timer6(int value) {  //���콺 �������� Ŭ���ϸ� ����Ǵ� Ÿ�̸� �Լ�
	if (work == true) {
		if (shoulder == 0)
			work = false;

		else {
			if (elbow == 0) { //�Ȳ�ġ�� �� ������ ����� ������� ���ش�
				shoulder -= 5;
			}
			else if (fin1_1 == 0) { //�հ��� ������� �����°� �ȴٸ� �Ȳ�ġ�� �ٽ� ���ش�
				elbow -= 5;
			}
			else {
				if (fin1_1 <= 40) { //�ι�° ����鵵 ���󺹱� �� ����, ù��° ����鵵 ���� ���ش�
					fin1_1 -= 3;
					fin2_1 -= 3;
					fin3_1 -= 3;
				}
				else if (fin1_2 <= 10) { //����° ������� �� ���󺹱� �� ����, ù��°�� �ι�° ������� ���� ���ش�
					fin1_1 -= 3;
					fin2_1 -= 3;
					fin3_1 -= 3;

					fin1_2 -= 3;
					fin2_2 -= 3;
					fin3_2 -= 3;
				}
				else { //�հ��� ������� �ٽ� ���ش�
					fin1_1 -= 3;
					fin2_1 -= 3;
					fin3_1 -= 3;

					fin1_2 -= 2;
					fin2_2 -= 2;
					fin3_2 -= 2;

					fin1_3 -= 1;
					fin2_3 -= 1;
					fin3_3 -= 1;
				}
			}
		}
		glutPostRedisplay();
		glutTimerFunc(50, timer6, 0);
	}
}

void MyKeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case '1':
		work = true;
		glutTimerFunc(50, timer1, 0);
		break;
	case '2':
		work = true;
		glutTimerFunc(50, timer2, 0);
		break;
	case '3':
		work = true;
		glutTimerFunc(50, timer3, 0);
		break;
	case '4':
		work = true; //4���� Ŭ���ϸ� �հ��� Ÿ�̸� �Լ��� ���� ������Ѽ� ��� �հ����� ������ �� �ֵ��� ���ش�
		glutTimerFunc(50, timer1, 0);
		glutTimerFunc(50, timer2, 0);
		glutTimerFunc(50, timer3, 0);
	case 'S': case 's':
		work = false; //�������� �Լ����� �ߴܽ�Ű��, 4�� Ÿ�̸� �Լ��� ������� �ߴ��� �����Ѵ�.
		glutTimerFunc(50, timer4, 0);
		break;
	default:
		break;
	}

	glutPostRedisplay();
}

void mouseCallback(int Button, int State, int x, int y) {
	if ((Button == GLUT_LEFT_BUTTON) && (State == GLUT_DOWN)) { //���콺 ���� ��ư
		if (shoulder == 0) {
			work = false; //���� �������̶�� ���¸� false�� �ߴܽ�Ų��
			//��� �հ��� �������� ���ڸ��� ���½�Ų��
			fin1_1 = 0; 
			fin1_2 = 0; 
			fin1_3 = 0; 
			fin2_1 = 0;
			fin2_2 = 0; 
			fin2_3 = 0; 
			fin3_1 = 0; 
			fin3_2 = 0; 
			fin3_3 = 0;
			glutPostRedisplay();
			work = true; //���� �ٽ� ������ ���·� �����.
			glutTimerFunc(50, timer5, 0); 
		}
	}
	if ((Button == GLUT_RIGHT_BUTTON) && (State == GLUT_DOWN)) { //���콺 ������ ��ư
		if (fin1_1 >= 120) { //������ Ŭ������ �� ���� fin1_1�� 120���� ����
			work = true;
			glutTimerFunc(50, timer6, 0);
		}
	}
}

void MyReshape(int NewWidth, int NewHeight) {
	glViewport(0, 0, NewWidth, NewHeight);
	GLfloat WidthFactor = (GLfloat)NewWidth / (GLfloat)1000;
	GLfloat HeightFactor = (GLfloat)NewHeight / (GLfloat)500;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-5.0 * WidthFactor, 5.0 * WidthFactor, -5.0 * HeightFactor, 5.0 * HeightFactor, -5.0, 5.0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv); //window�� os����
	glutInitDisplayMode(GLUT_RGB); //���÷��� ��� ����
	glutInitWindowSize(1000, 500); //������ũ�� ����
	glutInitWindowPosition(0, 0); //���� ���� ����
	glutCreateWindow("Robot Hand"); //������ ����(�̸�)

	MyInit();
	glutDisplayFunc(MyDisplay); //���÷��� �ݹ��Լ� ���
	glutReshapeFunc(MyReshape);
	glutKeyboardFunc(MyKeyboard);
	glutMouseFunc(mouseCallback);

	glutMainLoop();
	return 0;
}