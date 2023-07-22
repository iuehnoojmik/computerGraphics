/*************************************************************************/
/*                HW#3-4  Menu Callback ����	     				     */
/*  �ۼ��� : ������                              ��¥ : 2022�� 10�� 7��  */
/*																		 */
/* ���� ���� : �޴� �ݹ� �Լ��� �̿��Ͽ�								 */
/*	           �� �޴��� ���� ���ο� ������ �׸���						 */
/*									                                     */
/* ���: Draw@@@: �޴��� ���� �� �Ϻ� �޴��� Small@@@�� Large@@@ ��	     */
/*       �ϳ��� �����ϸ� �޴� ũ�⿡ �´� @@@���� ����			         */
/*       Change Color: �Ϻθ޴��� Red, Green, Blue�� �ϳ��� �����ϸ�	 */
/*                     ������ ���� �µ��� ���� ���� ����			     */
/*       Exit: ������ â ����										     */
/*                - - - - - - -                                          */
/*************************************************************************/
#include <GL/glut.h>
#include <stdlib.h>

int shape = 1; //�����޴��� �ݹ��Լ� ���ڰ�. ����Ʈ�� 1���� Sphere
int color = 1; //Change color�޴��� �ݹ��Լ� ���ڰ�. ����Ʈ�� 1���� Red
int size = 1; //Size�� �ݹ��Լ� ���ڰ�. ����Ʈ�� 1���� small

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT); //������ �ʱ�ȭ
	if (color == 1) //Change color���� Red ���ý� color������ 1
		glColor3f(1.0, 0.0, 0.0); //������ ���������� �ٲ۴�
	else if (color == 2) //Change color���� Green ���ý� color������ 2
		glColor3f(0.0, 1.0, 0.0); //������ �ʷϻ����� �ٲ۴�
	else if (color == 3)  //Change color���� Blue ���ý� color������ 3
		glColor3f(0.0, 0.0, 1.0); //������ �Ķ������� �ٲ۴�

	if (shape == 1) { //DrawSphere ���ý� shape ������ 1
		if(size==1) //�����޴����� SmallSphere�� �����ߴٸ� size ������ 1
			glutWireSphere(0.3, 30, 30); //����sphere�� wire�� �׸���
		else //�����޴����� LargeSphere�� �����ߴٸ� size ������ 2
			glutWireSphere(0.8, 30, 30); //ūsphere�� wire�� �׸���
	}
	
	else if (shape == 2) { //DrawTorus ���ý� shape ������ 2
		if(size==1) //�����޴����� SmallTorus�� �����ߴٸ� size ������ 1
			glutWireTorus(0.1, 0.3, 40, 30); //����Torus�� wire�� �׸���
		else //�����޴����� LargeTorus�� �����ߴٸ� size ������ 2
			glutWireTorus(0.2, 0.6, 40, 30); //ūTorus�� wire�� �׸���
	}

	else if (shape == 3) { //DrawTeapot ���ý� shape ������ 3
		if (size == 1) //�����޴����� SmallTeapot�� �����ߴٸ� size ������ 1
			glutWireTeapot(0.3); //����Teapot�� wire�� �׸���
		else //�����޴����� LargeTeapot�� �����ߴٸ� size ������ 2
			glutWireTeapot(0.6); //ūTeapot�� wire�� �׸���
	}

	glFlush();
}

void MyMainMenu(int entryID) { //���θ޴� �ݹ��Լ�
	if (entryID == 5) //5��° �޴� ����
		exit(0); //������ ����
	glutPostRedisplay(); //���÷��� �Լ� ���� ȣ�� �Լ�
}

void Sphere(int entryID) {
	shape = 1; //DrawSphere�޴��� �������� ��� shape�� 1�� ����

	if (entryID == 1) //�����޴��� SmallSphere�� �����Ͽ� ID���� 1�� ���޹��� ���
		size = 1; //size������ 1
	else //�����޴����� LargeSphere�� ������ ���
		size = 2; //size������ 2

	glutPostRedisplay(); //���÷��� �Լ� ���� ȣ�� �Լ�
}void Torus(int entryID) {
	shape = 2; //DrawTorus�޴��� �������� ��� shape�� 2�� ����

	if (entryID == 1) //�����޴��� SmallTorus�� �����Ͽ� ID���� 1�� ���޹��� ���
		size = 1; //size������ 1
	else //�����޴����� LargeTorus�� ������ ���
		size = 2; //size������ 2

	glutPostRedisplay(); //���÷��� �Լ� ���� ȣ�� �Լ�
}void Teapot(int entryID) {
	shape = 3; //DrawTeapot�޴��� �������� ��� shape�� 3���� ����

	if (entryID == 1) //�����޴��� SmallTeapot�� �����Ͽ� ID���� 1�� ���޹��� ���
		size = 1; //size������ 1
	else  //�����޴����� LargetTeapot�� ������ ���
		size = 2; //size������ 2

	glutPostRedisplay();  //���÷��� �Լ� ���� ȣ�� �Լ�
}void ChangeColor(int entryID) {
	if (entryID == 1) //ChangeColor�޴����� Red�� �����Ͽ� 1�� ���޹��� ���
		color = 1; //color ������ 1
	else if (entryID == 2)  //ChangeColor�޴����� Green�� �����Ͽ� 2�� ���޹��� ���
		color = 2; //color ������ 2
	else if (entryID == 3)  //ChangeColor�޴����� Blue�� �����Ͽ� 3�� ���޹��� ���
		color = 3; //color ������ 3

	glutPostRedisplay();  //Display�̺�Ʈ ������ �߻���Ŵ
}void MyInit() {
	glClearColor(1.0, 1.0, 1.0, 1.0); //������-���
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); //���ú��� ����

	GLint SphereID = glutCreateMenu(Sphere); //DrawSphere�޴� �ݹ��Լ� ���
	glutAddMenuEntry("Smalll Sphere", 1);
	glutAddMenuEntry("Large Sphere", 2); //DrawSphere�޴��� �����޴� ����, Sphere�Լ��� �� �������� �����Ѵ� 

	GLint TorusID = glutCreateMenu(Torus); //DrawTorus�޴� �ݹ��Լ� ���
	glutAddMenuEntry("Small Torus", 1);
	glutAddMenuEntry("Large Torus", 2); //DrawTorus�޴��� �����޴� ����, Torus�Լ��� �� �������� �����Ѵ� 


	GLint TeapotID = glutCreateMenu(Teapot); //DrawTeapot�޴� �ݹ��Լ� ���
	glutAddMenuEntry("Small Teapot", 1);
	glutAddMenuEntry("Large Teapot", 2); //DrawTeapot�޴��� �����޴� ����, Teapot�Լ��� �� �������� �����Ѵ� 

	GLint ChangeColorID = glutCreateMenu(ChangeColor); //ChangeColor�޴� �ݹ��Լ� ���
	glutAddMenuEntry("Red", 1);
	glutAddMenuEntry("Green", 2);
	glutAddMenuEntry("Blue", 3); //ChangeColor�޴��� �����޴� ����, ChangeColor�Լ��� �� �������� �����Ѵ� 

	GLint MyMainID = glutCreateMenu(MyMainMenu);  //���θ޴� �ݹ��Լ� ���, ����ID�� ����
	glutAddSubMenu("Draw Sphere", SphereID); //�����޴��� �ִ� Draw Sphere �޴�, Sphere�޴��� ���鶧 �޴� ���̵��� SphereID�� ���ϵǾ���
	glutAddSubMenu("Draw Torus", TorusID); //�����޴��� �ִ� Draw Torus �޴�, Sphere�޴��� ���鶧 �޴� ���̵��� TorusID�� ���ϵǾ���
	glutAddSubMenu("Draw Teapot", TeapotID); //�����޴��� �ִ� Draw Teapot �޴�, Sphere�޴��� ���鶧 �޴� ���̵��� TeapotID�� ���ϵǾ���
	glutAddSubMenu("Change Color", ChangeColorID); //�����޴��� �ִ� Change Color �޴�, Sphere�޴��� ���鶧 �޴� ���̵��� ChangeColorID�� ���ϵǾ���
	glutAddMenuEntry("EXIT", 5); //���� �޴��� ���� EXIT, ���ý� ���θ޴� �ݹ��Լ��� 5�� ����

	glutAttachMenu(GLUT_RIGHT_BUTTON); //���콺 ������ ��ư�� ������ �޴��� ��Ÿ��
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);  //window�� os����
	glutInitDisplayMode(GLUT_RGB); //���÷��� ��� ����
	glutInitWindowSize(300, 300); //������ũ�� ����
	glutInitWindowPosition(0, 0); //������ ���� ���� ����
	glutCreateWindow("Menu Callback"); //������ ����(�̸�)

	MyInit(); //������ �ʱ�ȭ
	glutDisplayFunc(MyDisplay); //���÷��� �ݹ��Լ� ���

	glutMainLoop(); 
	return 0;
}