/*************************************************************************/
/*                      HW#1 : 3D Sierpinski Gasket					     */
/*  �ۼ��� : ������                              ��¥ : 2022�� 9�� 22��  */
/*																		 */
/* ���� ���� : 2D �þ��ɽ�Ű �ﰢ�� �����ڵ带 �����Ͽ� 3D �þ��ɽ�Ű    */
/*              �ﰢ���� �����ϱ�. ������ â ũ�⸦ �ٲ㵵 ����        */
/*				�ְ���� �ʵ��� ���ش�.                                  */		
/*�þ��ɽ�Ű �ﰢ��: ���ﰢ�� �� ������ ������ �̾ ���ο� ���ﰢ����  */ 
/*					����� ���� ��� �ݺ��Ͽ� ���� ����Ż ����           */
/* ��� : ȭ���� Ŭ���Ҷ����� �þ��ɽ�Ű �ﰢ����                        */
/*           (250, 200, 288)���� ���� 30���� ȸ���Ѵ�.                 */
/*                - - - - - - -                                          */
/*************************************************************************/
 
#include <GL/glut.h>
#include <stdlib.h>  //rand() �Լ� ��� �뵵

void MyInit()
{
	glClearColor(1.0, 1.0, 1.0, 1.0); // ���� ����(���)
	glColor3f(1.0, 0.0, 0.0); // �þ��ɽ�Ű �ﰢ�� �������� (������)

	glMatrixMode(GL_PROJECTION); //������� ����
	glLoadIdentity(); //���� ��������� �׵���ķ� �ʱ�ȭ

	glOrtho(0.0, 500.0, 0.0, 500.0, 0, -500); //3������ ���ú��� ���� ����
}

void MyDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT); //�� ���� ����
	float vertices[4][3] = { { 0.0,0.0,433.0 },{ 250.0,0.0,0.0},{ 500.0,0.0,433.0},{250.0,408.0,288.0} }; // �ʱ� ���ü ��ǥ(�����ü�� �ٻ��� ��)
	int i, j;
	float p[3] = { 500.0, 250.0, 100.0 };  // ���Ƿ� ���� ����Ʈ

	glRotatef(30.0, 250.0, 200.0, 288.0); //�𵨺�ȯ�Լ�, (250,200,288)���� ������ ���� 30���� ȸ����Ų��

	for (j = 0; j < 100000; j++) //������ ����� 1�������� �ݺ��Ѵ�
	{
		i = rand() % 4; // ���ü�� �� ������ �� �� ���� ���Ƿ� ����
		p[0] = (p[0] + vertices[i][0]) / 2.0;
		p[1] = (p[1] + vertices[i][1]) / 2.0;
		p[2] = (p[2] + vertices[i][2]) / 2.0;
		//���Ƿ� ���� ����Ʈ�� �������� ������ ����Ѵ�. 
		

		glBegin(GL_POINTS);
		glVertex3fv(p); // ������ ����� �������� ��ġ�� �����Ѵ�.
		glEnd();
	}
	
	glFlush(); 
}

void MyReshape(int NewWidth, int NewHeight) { //������ â ũ�� ��ȯ�� ���� �ְ��� �����ִ� �Լ�
	glViewport(0, 0, NewWidth, NewHeight); //���� ũ�⸦ ��ȯ �Ҷ����� �� ũ�⸦ �����̶�� �ν�

	GLfloat Widthfactor = (GLfloat)NewWidth / (GLfloat)500; //���� ������ ���α��̸� main���� ������ ������ ���α���(500)�� ������ ���� ���
	GLfloat Heightfactor = (GLfloat)NewHeight / (GLfloat)500; ////���� ������ ���α��̸� main���� ������ ������ ���α���(500)�� ������ ���� ���
	
	glMatrixMode(GL_PROJECTION); //������� ����
	glLoadIdentity(); //������� �ʱ�ȭ
	glOrtho(0.0*Widthfactor, 500.0*Widthfactor, 0.0* Heightfactor, 500.0*Heightfactor, 0.0, -500.0); //������ ���� ������ �ʱ� ���ú��� ��ǥ�� ���ؼ� ���ú��Ƕ� ������ ������ �����ش�.
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv); //window os�� ����
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //���÷��� ��� ����
	glutInitWindowSize(500, 500); //������ ũ������
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Sierpinski Gasket"); //������ ����(�̸�)

	glutDisplayFunc(MyDisplay); //�����Լ� �ۿ��� ������ �ݹ��Լ����� ���
	glutReshapeFunc(MyReshape);

	MyInit();

	glutMainLoop();
}

