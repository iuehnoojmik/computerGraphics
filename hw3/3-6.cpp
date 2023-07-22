/*************************************************************************/
/*                HW#3-6  Time Callback ����	     				     */
/*  �ۼ��� : ������                              ��¥ : 2022�� 10�� 7��  */
/*																		 */
/* ���� ���� : Time �ݹ� �Լ��� �̿��Ͽ�								 */
/*		     �¿�� �����̴� ������ ��迡 ������ ������ �ٲٰ� �Ѵ�.	 */
/*									                                     */
/* ���: ������ �¿�� �� ��迡 ���� ������ 0.1�� �������� �̵��Ѵ�.	 */
/*     ������ ��迡 ������ ������, ���� ��迡 ������ �Ķ������� ���Ѵ�.*/
/*      ���콺�� ���� Ű�� ������ �����̴� ������ �����.			     */
/*      ���콺�� ������ Ű�� ������ �����ִ� ������ �����δ�.			 */
/*      ���� �̵� �߿� ���콺 ������ Ű�� ������ �ƹ��� ��ȭ�� ����.     */
/*                - - - - - - -                                          */
/*************************************************************************/
#include <GL/glut.h>
float dx = 0.0; //������ �̵��� x��ǥ ��������
GLboolean dir = true; //������ �̵� ���⺯��, true-������, false-����
GLboolean click = false; //���콺 ����Ű�� ���ȴ��� Ȯ���ϴ� ����, true-����Ű ����, false-�ȴ���

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT); //������ ����

	glBegin(GL_POLYGON); //�簢�� �𵨸�, �ʱ� �簢���� ���� �߾ӿ� ����
	glVertex3f(-1.0 + dx, -0.5, 0.0); //���� �Ʒ���
	glVertex3f(0.0 + dx, -0.5, 0.0); //������ �Ʒ���
	glVertex3f(0.0 + dx, 0.5, 0.0); //������ ����
	glVertex3f(-1.0 + dx, 0.5, 0.0); //���� ����

	glEnd();
	glutSwapBuffers(); //���۸� �����Ͽ� �������� ����
}

void MyTimer(int value) {
	if (click == false) { //���콺 ����Ű�� ������ ���� �ʱ���� or ���콺 ������ Ű�� ������ �����̵��� ������ ��Ų ���
		if (dir == true) { //���� ��������� �������� ��� (�̵������� true)
			dx += 0.1; //x��ǥ�� �������� ������ ���������� 0.1�� �̵���Ų��.
			if (dx > 1.1) { //������ ������ ��迡 ������
				glClear(GL_COLOR_BUFFER_BIT); //������ �ʱ�ȭ
				glColor3f(1.0, 0.0, 0.0); //������ ���������� �ٲ۴�
				dx -= 0.1; //x��ǥ�� 0.1��ŭ ���ҽ��� ������ ��踦 �Ѿ�� �ʵ��� �Ѵ�.
				dir = false; //�̵������� false�� �ٲ㼭 �̵������� �������� �ٲ��ش�.
			}
		}

		else { //���� ��������� ������ ��� (�̵������� false)
			dx -= 0.1; //x��ǥ�� ���ҽ��� ������ �������� 0.1�� �̵���Ų��.
			if (dx < 0) { //������ ���� ��迡 ������
				glClear(GL_COLOR_BUFFER_BIT); //������ �ʱ�ȭ
				glColor3f(0.0, 0.0, 1.0); //������ �Ķ������� �ٲ۴�
				dx += 0.1; //x��ǥ�� 0.1��ŭ �������� ���� ��踦 �Ѿ�� �ʵ��� �Ѵ�.
				dir = true; //�̵������� true�� �ٲ㼭 �̵������� �������� �ٲ��ش�.
			}
		}
	}

	//���콺 ����Ű�� ������ click==true�� �Ǿ� �ƹ��ϵ� �߻����� �ʴ´�. - ���� �̵� ����
	
	glutPostRedisplay(); //���÷��� �Լ� ���� ȣ�� �Լ�
	glutTimerFunc(100, MyTimer, 1); //100msec �Ŀ� ȣ��, ���������� �߻���Ų��
}void MyInit() {
	glClearColor(1.0, 1.0, 1.0, 1.0); //������-���

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-1.0, 1.0, -1.0, 1.0, 1.0, -1.0); //���ú��� ����
}

void Left() { //���콺 ���ʹ�ư�� ���� �� ȣ���
	click = true; //���� Ű�� �������Ƿ� click ������ true�� ����
}

void RIGHT() { //���콺 �����ʹ�ư�� ���� �� ȣ���
	click = false; //������ Ű�� �������Ƿ� click ������ false�� ����
} 

void mouseCallback(int Button, int State, int x, int y) {
	if ((Button == GLUT_LEFT_BUTTON) && (State == GLUT_DOWN)) { //���콺 ���� ��ư Ǫ��
		glutIdleFunc(Left); //���ʹ�ư�� �������� �ۿ��ϴ� idle�ݹ��Լ� ���
	}
	if ((Button == GLUT_RIGHT_BUTTON) && (State == GLUT_DOWN)) { //���콺 ������ ��ư Ǫ��
		glutIdleFunc(RIGHT); //�����ʹ�ư�� �������� �ۿ��ϴ� idle�ݹ��Լ� ���
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv); //window�� os����
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); //���÷��� ��� ����
	glutInitWindowSize(300, 300); //������ũ�� ����
	glutInitWindowPosition(0, 0); //���� ���� ����
	glutCreateWindow("Timer Callback"); //������ ����(�̸�)

	MyInit(); //������ �ʱ�ȭ
	glutDisplayFunc(MyDisplay); //���÷��� �ݹ��Լ� ���
	glutTimerFunc(100, MyTimer, 1); //Ÿ�̸� �ݹ��Լ� ���
	glutMouseFunc(mouseCallback); //���콺 ��ư�� �Է¹޴� �ݹ� �Լ� ���

	glutMainLoop();
	return 0;
}