/*************************************************************************/
/*                   HW#3-3  Mouse Callback ����	   				     */
/*  �ۼ��� : ������                              ��¥ : 2022�� 10�� 7��  */
/*																		 */
/* ���� ���� : ���콺 �ݹ� �Լ��� �̿��Ͽ�								 */
/*	        ���콺�� Ư�� ��ư�� ������ ������ �̵� �Ǵ� �����ϵ��� �Ѵ� */
/*									                                     */
/* ���: ���콺���ʹ�ư: ������ ���������� 0.1�� �������� �̵�	         */
/*       ���콺���ʹ�ư: ���������� �̵� ���� ������ ����			     */
/*   ���̵� ���� ������ ������ ������ â�� ������ ���̻� �̵����� ����   */
/*   �������� ��ǥ�� ������ â �� ���� �־ ���콺��ư ������        */
/*      �۵��Ѵٴ� ���� Ȯ���ϱ� ���� #3-2�� Ű���� �ݹ� �Լ� �籸��     */
/*                - - - - - - -                                          */
/*************************************************************************/
#include <GL/glut.h>
#include <stdlib.h> //���� �̵��� �ð����� �ֱ� ���� sleep�Լ��� ����ϴµ�, sleep�� ���Ե� ���̺귯��

float px, py = 0.0; //y��ǥ ��������
float mx, my = 0.0; //x��ǥ ��������

void MyInit() {
	glClearColor(1.0, 1.0, 1.0, 1.0); ////������-���

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); //���ú��ǿ�������
}

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.5, 0.5, 0.5); //�� ���� - ȸ��

	glBegin(GL_POLYGON);
	glVertex3f(-0.5 + mx, -0.5 + my, 0.0); //���� �Ʒ�
	glVertex3f(0.5 + px, -0.5 + my, 0.0); //������ �Ʒ�
	glVertex3f(0.5 + px, 0.5 + py, 0.0); //������ ��
	glVertex3f(-0.5 + mx, 0.5 + py, 0.0); //���� ��
	glEnd();
	glFlush();
}

void MySpecial(int key, int x, int y) { //#3-2���� ������ Ű���� ���� �Լ�
	switch (key) {
	case GLUT_KEY_UP:
		py += 0.1;
		my += 0.1;
		if (py > 0.5) {
			py -= 0.1;
			my -= 0.1;
		}
		break;
	case GLUT_KEY_DOWN:
		py -= 0.1;
		my -= 0.1;
		if (my < -0.5) {
			py += 0.1;
			my += 0.1;
		}
		break;
	case GLUT_KEY_LEFT:
		px -= 0.1;
		mx -= 0.1;
		if (mx < -0.5) {
			mx += 0.1;
			px += 0.1;
		}
		break;
	case GLUT_KEY_RIGHT:
		px += 0.1;
		mx += 0.1;
		if (px > 0.5) {
			mx -= 0.1;
			px -= 0.1;
		}
		break;
	case GLUT_KEY_PAGE_UP:
		mx -= 0.1;
		px += 0.1;
		my -= 0.1;
		py += 0.1;
		if (mx < -0.5 || px > 0.5 || my < -0.5 || py > 0.5) {
			mx += 0.1;
			px -= 0.1;
			my += 0.1;
			py -= 0.1;
			break;
		}
		break;
	case GLUT_KEY_PAGE_DOWN:
		if (mx - px > 0.8)
			break;
		mx += 0.1;
		px -= 0.1;
		my += 0.1;
		py -= 0.1;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void Left() { //���콺 ���ʹ�ư�� ���� �� ȣ��Ǵ� �Լ� (sleep�Լ��� ����ϱ� ���� ���̵� �Լ� ���)
	mx += 0.1; //x��ǥ ������������ 0.1�� �������Ѽ� ������ ���������� �̵���Ų��
	px += 0.1;
	if (mx > 0.5) { //x������������ 0.5���� Ŀ���� ������ â �����ʿ� ������)
		mx -= 0.1; //��ǥ���������� 0.1��ŭ �ٽ� �������Ѽ� ������ â�� ����� �ʵ��� �Ѵ�
		px -= 0.1;
	}
	Sleep(1000); //sleep�Լ��� �̿��Ͽ� ������ ���������� �̵��ϴ� �Ϳ� �ð����� �ش�
	glutPostRedisplay(); //���÷��� �Լ� ���� ȣ�� �Լ�
}

void Right() { // ���콺 �����ʹ�ư�� ���� �� ȣ��Ǵ� �Լ�
	Sleep(1000);
	return; //�ƹ��͵� �������� �ʴ´�>>������ ���ߵ��� �Ѵ�
}

void mouseCallback(int Button, int State, int x, int y) {
	if ((Button == GLUT_LEFT_BUTTON) && (State == GLUT_DOWN)) { //���콺 ���� ��ư Ǫ��
		glutIdleFunc(Left); //���ʹ�ư�� �������� �ۿ��ϴ� idle�ݹ��Լ� ���
	}

	if ((Button == GLUT_RIGHT_BUTTON) && (State == GLUT_DOWN)) { //���콺 ������ ��ư Ǫ��
		glutIdleFunc(Right); //�����ʹ�ư�� �������� �ۿ��ϴ� idle�ݹ��Լ� ���
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv); //window�� os����
	glutInitDisplayMode(GLUT_RGB); //���÷��� ��� ����
	glutInitWindowSize(300, 300); //������ũ�� ����
	glutInitWindowPosition(0, 0); //���� ���� ����
	glutCreateWindow("Mouse Callback"); //������ ����(�̸�)

	MyInit(); //������ �ʱ�ȭ
	glutDisplayFunc(MyDisplay); //���÷��� �ݹ��Լ� ���
	glutSpecialFunc(MySpecial);
	glutMouseFunc(mouseCallback); //���콺 ��ư�� �Է¹޴� �ݹ� �Լ� ���

	glutMainLoop();
	return 0;
}