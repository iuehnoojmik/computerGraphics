/*************************************************************************/
/*                HW#3-5  IDLE Callback ����	     				     */
/*  �ۼ��� : ������                              ��¥ : 2022�� 10�� 7��  */
/*																		 */
/* ���� ���� : Idle �ݹ� �Լ��� �̿��Ͽ�								 */
/*	Ư�� Ű���� Ű�� ������ ������ Ư���������� ���������� �̵��ϰ� �Ѵ� */
/*									                                     */
/* ���: ���ʹ���Ű - ������ �������� 0.1�� �������� �̵�	             */
/*       �Ʒ��ʹ���Ű-������ �Ʒ������� 0.1�� �������� �̵�		         */
/*       ���ʹ���Ű-������ �������� 0.1�� �������� �̵�			         */
/*       �����ʹ���Ű-������ ���������� 0.1�� �������� �̵�		         */
/*       ���̵� �߿� �ٸ� ����Ű�� ������ �� �������� �̵�			     */
/*       ���̵� �߿� ������ â�� ����� �ʴ´�				         */
/*                - - - - - - -                                          */
/*************************************************************************/
#include <GL/glut.h>
#include <stdlib.h>

float px, py = 0.0; //�簢���� �̵��� y��ǥ ��������
float mx, my = 0.0; //�簢���� �̵��� x��ǥ ��������

void MyInit() {
	glClearColor(1.0, 1.0, 1.0, 1.0); //���-������� ����

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); //���ú��� ����
}

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT); //������ ����
	glColor3f(0.0, 0.5, 0.8); //�� ���� ����

	glBegin(GL_POLYGON);
	glVertex3f(-0.5 + mx, -0.5 + my, 0.0); //���� �Ʒ�
	glVertex3f(0.5 + px, -0.5 + my, 0.0); //������ �Ʒ�
	glVertex3f(0.5 + px, 0.5 + py, 0.0); //������ ��
	glVertex3f(-0.5 + mx, 0.5 + py, 0.0); //���� ��
	glEnd();
	glFlush();
}

void MyIdleU() { //���ʹ���Ű�� �������� ����Ǵ� �ݹ��Լ�
	Sleep(1000); //������ ���������� �̵��ϴµ��� ������ �ð����� �ش�
	py += 0.1; //������ y��ǥ�� 0.1�� �������� �̵�
	my += 0.1;
	if (py > 0.5) { //������ ����â�� ����� �ʵ��� �Ѵ�
		py -= 0.1;
		my -= 0.1;
	}
	glutPostRedisplay();
}

void MyIdleD() { //�Ʒ��ʹ���Ű�� �������� ����Ǵ� �ݹ��Լ�
	Sleep(1000); 
	py -= 0.1; //������ y��ǥ�� 0.1�� �Ʒ������� �̵�
	my -= 0.1;
	if (my < -0.5) { //������ �Ʒ���â�� ����� �ʵ��� �Ѵ�
		py += 0.1;
		my += 0.1;
	}
	glutPostRedisplay();
}

void MyIdleL() { //���ʹ���Ű�� �������� ����Ǵ� �ݹ��Լ�
	Sleep(1000);
	px -= 0.1; //������ x��ǥ�� 0.1�� �������� �̵�
	mx -= 0.1;
	if (mx < -0.5) { //������ ����â�� ����� �ʵ��� �Ѵ�
		mx += 0.1;
		px += 0.1;
	}
	glutPostRedisplay();
}

void MyIdleR() { //�����ʹ���Ű�� �������� ����Ǵ� �ݹ��Լ�
	Sleep(1000);
	px += 0.1; //������ x��ǥ�� 0.1�� ���������� �̵�
	mx += 0.1;
	if (px > 0.5) { //����������� â�� ����� �ʵ��� �Ѵ�
		mx -= 0.1;
		px -= 0.1;
	}
	glutPostRedisplay();
}


void MySpecial(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP: //���� ����Ű Ǫ��
		glutIdleFunc(MyIdleU); //MyIdleU�ݹ��Լ� ���
		break;
	case GLUT_KEY_DOWN: //�Ʒ��� ����Ű Ǫ��
		glutIdleFunc(MyIdleD); //MyIdleD�ݹ��Լ� ���
		break;
	case GLUT_KEY_LEFT: //���� ����Ű Ǫ��
		glutIdleFunc(MyIdleL); //MyIdleL�ݹ��Լ� ���
		break;
	case GLUT_KEY_RIGHT: //������ ����Ű Ǫ��
		glutIdleFunc(MyIdleR); //MyIdleR�ݹ��Լ� ���
		break;
	default:
		break;
	}
	glutPostRedisplay(); //���÷��� �Լ� ���� ȣ�� �Լ�
}

int main(int argc, char** argv) {
	glutInit(&argc, argv); //window�� os����
	glutInitDisplayMode(GLUT_RGB); //���÷��� ��� ����
	glutInitWindowSize(300, 300); //������ũ�� ����
	glutInitWindowPosition(0, 0); //���� ���� ����
	glutCreateWindow("Idle Callback");//������ ����(�̸�)

	MyInit(); //������ �ʱ�ȭ
	glutDisplayFunc(MyDisplay); //���÷��� �ݹ��Լ�
	glutSpecialFunc(MySpecial); //����Ű�� �Է¹ޱ����� Ű���� ��� �ݹ� �Լ� ���

	glutMainLoop();
	return 0;
}