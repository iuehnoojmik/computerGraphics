/*************************************************************************/
/*                HW#3-1  Keyboard Callback ����1	   				     */
/*  �ۼ��� : ������                              ��¥ : 2022�� 10�� 7��  */
/*																		 */
/* ���� ���� : Ű���� �ݹ� �Լ��� �̿��Ͽ�								 */
/*		Ư�� Ű������ Ű�� ������ ������ �̵��ϰų� ���� ĥ�ϵ��� �Ѵ�	 */
/*									                                     */
/* ���: a�Ǵ�A: 0.1��ŭ �������� �̵�/ f�Ǵ�F: 0.1��ŭ ���������� �̵�  */
/*       v�Ǵ�V: 0.1��ŭ �������� �̵�					                 */
/*       r�Ǵ�R: ������ ���������� ĥ�� �� 0.1��ŭ ���������� �̵�       */
/*       b�Ǵ�B: ������ �Ķ������� ĥ��  				                 */
/*                - - - - - - -                                          */
/*************************************************************************/
#include <GL/glut.h>

float dx, dy = 0; //�簢���� �̵��� ��ǥ ��������

void MyInit() {
	glClearColor(1.0, 1.0, 1.0, 1.0); //������-���

	glClear(GL_COLOR_BUFFER_BIT); //�� ���� ����
	glColor3f(0.5, 0.5, 0.5); //�� ���� ���� - ȸ��

	glMatrixMode(GL_PROJECTION); //������� ����
	glLoadIdentity(); //������� �ʱ�ȭ

	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); //���ú��� ���� ����
}

void MyDisplay() {
	glBegin(GL_POLYGON); //�ٰ��� �𵨸�
	glVertex3f(-0.5 + dx, -0.5 + dy, 0.0); //�簢���� ���ʾƷ��� ��ǥ
	glVertex3f(0.5 + dx, -0.5 + dy, 0.0); //�簢���� �����ʾƷ��� ��ǥ
	glVertex3f(0.5 + dx, 0.5 + dy, 0.0); //�簢���� ���������� ��ǥ
	glVertex3f(-0.5 + dx, 0.5 + dy, 0.0); //�簢���� �������� ��ǥ
	glEnd();
	glFlush();
}

void MyReshape(int NewWidth, int NewHeight) {
	glViewport(0, 0, NewWidth, NewHeight);
	GLfloat WidthFactor = (GLfloat)NewWidth / (GLfloat)300;
	GLfloat HeightFactor = (GLfloat)NewHeight / (GLfloat)300;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0 * WidthFactor, 1.0 * WidthFactor,-1.0 * HeightFactor, 1.0 * HeightFactor, -1.0, 1.0);
}

void MyKeyboard(unsigned char key, int x, int y) { //keyboard�� ������ �߻��ϴ� �Լ�
	switch (key) {
	case 'a': case'A': //Ű���忡�� a �Ǵ� A�� ���� ���
		glClear(GL_COLOR_BUFFER_BIT); //���� �� ���۸� �����Ͽ� �̵��� �簢���� ȭ�鿡 ���̵��� �Ѵ�
		dx += -0.1; //�簢���� ��� ��ǥ�� 0.1��ŭ �������� �̵�
		break;
	case 'f': case'F': //Ű���忡�� f �Ǵ� F�� ���� ���
		glClear(GL_COLOR_BUFFER_BIT);
		dx += 0.1; //�簢���� ��� ��ǥ�� 0.1��ŭ ���������� �̵�
		break;
	case 'r': case'R': //Ű���忡�� r �Ǵ� R�� ���� ���
		glClear(GL_COLOR_BUFFER_BIT);
		dy += -0.1; //�簢���� ��� ��ǥ�� 0.1��ŭ �Ʒ��� �̵�
		glColor3f(1.0, 0.0, 0.0); //�簢���� ������ ���������� ĥ�Ѵ�
		break;
	case 'v': case'V': //Ű���忡�� v �Ǵ� V�� ���� ���
		glClear(GL_COLOR_BUFFER_BIT);
		dy += 0.1; //�簢���� ��� ��ǥ�� 0.1��ŭ ���� �̵�
		break;
	case 'b': case'B': //Ű���忡�� b �Ǵ� B�� ���� ���
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(0.0, 0.0, 1.0); //�簢���� ������ �Ķ������� ĥ�Ѵ�
		break;
	}

	glutPostRedisplay(); //���÷��� �Լ� ���� ȣ�� �Լ�
}

int main(int argc, char** argv) {
	glutInit(&argc, argv); //window�� os����
	glutInitDisplayMode(GLUT_RGB); //���÷��� ��� ����
	glutInitWindowSize(300, 300); //������ũ�� ����
	glutInitWindowPosition(0, 0); //���� ���� ����
	glutCreateWindow("Keyboard Callback 1"); //������ ����(�̸�)


	MyInit(); //������ ȭ�� �ʱ�ȭ
	glutDisplayFunc(MyDisplay); //�ݹ��Լ� ���
	glutReshapeFunc(MyReshape); //�ְ���� �Լ�
	glutKeyboardFunc(MyKeyboard); //ascii���ڸ� �Է¹޴� Ű���� ��� �ݹ� �Լ� ���

	glutMainLoop();
	return 0;
}