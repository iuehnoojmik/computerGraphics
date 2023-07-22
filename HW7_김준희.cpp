/***************************************************************************************************/
/*										hw#7 : ���� ����                                           */
/*  �ۼ��� : ������                          ��¥ : 2022�� 12�� 2��                                */
/*																								   */
/* ���� ���� : ���ű���κ��� �޸����� �𵨸��ϰ� ������ ������.								   */
/* ���:																					       */
/*       R or r : �κ��� �޸��� ����� �ǵ��� ���ش�.			 							       */
/*       S or s : �����̴� ���� ��ü�� �Ͻ������Ѵ�.										       */
/***************************************************************************************************/

#include <GL/glut.h>
#include <gl/glu.h>
#include <GL/gl.h>

float head, body, neck, left_arm, right_arm, left_sh, right_sh, left_leg, right_leg, left_knee, right_knee, st = 0.0;
GLboolean check2 = false;


void myinit() {
	GLfloat global_ambient[] = { 0.1, 0.1, 0.1, 1.0 }; //���� �ֺ��ݻ�(�� ���� ȿ�� x)
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient); //�����ֺ��ݻ�
 
	//0�� ���� ---------------------------------------------------------------
	GLfloat light0_ambient[] = { 0.5, 0.4, 0.3, 1.0 }; //0�� ���� �ֺ��ݻ� RGBA
	GLfloat light0_diffuse[] = { 0.5, 0.4, 0.3, 1.0 }; //0�� ���� ���ݻ� RGBA
	GLfloat light0_specular[] = { 1.0, 1.0, 1.0, 1.0 }; //0�� ���� ���ݻ� RGBA
	
	GLfloat Light0_Position[] = { 0.0, 0.0, 5.0, 1.0 }; //0�� ������ġ
	GLfloat Light0_Direction[] = { 0.0, 0.7, -5.0 }; //0�� ���� ����
	GLfloat Light0_Cutoff[] = { 40.0 }; //0�� ���� ����

	//0�� ���� Ư���Ҵ�
	glEnable(GL_LIGHT0); //0�� ���� Ȱ��ȭ
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient); //0�� ���� �ֺ��ݻ� ����
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse); //0�� ���� ���ݻ� ����
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular); //0�� ���� ���ݻ� ����

	glLightfv(GL_LIGHT0, GL_POSITION, Light0_Position); //����Ʈ����Ʈ
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, Light0_Direction); //����
	glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, Light0_Cutoff); //����
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 1.0); //�ڻ��� �¼�


	//1�� ���� ---------------------------------------------------------------
	GLfloat light1_ambient[] = { 0.0, 0.0, 0.3, 1.0 }; //1�� ���� �ֺ��ݻ� RGBA
	GLfloat light1_diffuse[] = { 0.5, 0.2, 0.3, 1.0 }; //1�� ���� ���ݻ� RGBA
	GLfloat light1_specular[] = { 0.0, 0.0, 0.0, 1.0 }; //1�� ���� ���ݻ� RGBA

	GLfloat Light1_Position[] = { 0.0, 0.0, 5.0, 1.0 }; //1�� ������ġ
	GLfloat Light1_Direction[] = { 0.0, 0.3, -1.0 }; //1�� ���� ����
	GLfloat Light1_Cutoff[] = { 15.0 }; //1�� ���� ����

	glEnable(GL_LIGHT1); //1�� ���� Ȱ��ȭ
	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient); //1�� ���� �ֺ��ݻ� ����
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse); //1�� ���� ���ݻ� ����
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular); //1�� ���� ���ݻ� ����

	glLightfv(GL_LIGHT1, GL_POSITION, Light1_Position); //����Ʈ����Ʈ
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, Light1_Direction); //����
	glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, Light1_Cutoff); //����
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 1.0); //�ڻ��� �¼�

	glShadeModel(GL_SMOOTH); //���� ���̵�
	glEnable(GL_DEPTH_TEST); //���� ����
	glEnable(GL_LIGHTING); //���� Ȱ��ȭ

	//��ü Ư��
	GLfloat my_material_ambient[] = { 0.3, 0.3, 0.3, 1.0 }; //��ü�� �ֺ��ݻ� RGBA
	GLfloat my_material_diffuse[] = { 0.8, 0.8, 0.8, 1.0 }; //��ü�� ���ݻ� RGBA
	GLfloat my_material_specular[] = { 0.0, 0.0, 1.0, 1.0 }; //��ü�� ���ݻ� RGBA
	GLfloat my_material_shininess[] = { 90.0 }; //���ð��
	
	//��ü Ư���Ҵ�
	glMaterialfv(GL_FRONT, GL_AMBIENT, my_material_ambient); 
	glMaterialfv(GL_FRONT, GL_DIFFUSE, my_material_diffuse);   
	glMaterialfv(GL_FRONT, GL_SPECULAR, my_material_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, my_material_shininess);

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE); //�������� ���x (������ġ ���Ѵ�)
}

void mydisplay(void) {

	gluLookAt(5.0, 1.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); //����

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	GLUquadricObj* qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, GLU_FILL); //Draw Style ����-Solid

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	/////////////////// �Ӹ� //////////////////////////
	glPushMatrix();//����Ǫ��
	glTranslatef(0.0, 1.8, 0.0);//�Ӹ� ��ġ ����
	glPushMatrix();//�Ӹ���ġǪ��
	glColor3f(0.9, 0.5, 0.0); //�Ӹ���������
	glRotatef(-90.0, 1.0, 0.0, 0.0);//�Ӹ������� �� �� �ֵ��� ȸ��
	glRotatef((GLfloat)head, 1.0, 0.0, 0.0); //�Ӹ��� ������ �� �ֵ��� �������� �̿�
	gluCylinder(qobj, 0.8, 0.6, 1.0, 50, 1); //�Ӹ��� �Ǹ��� Ÿ������ �𵨸�
	glPopMatrix();//�Ӹ���

	/////////////////// �� //////////////////////////
	glPushMatrix();//����ġ Ǫ��
	glColor3f(0.0, 0.0, 0.7); //����� ����
	glRotatef(90.0, 1.0, 0.0, 0.0);//���� ���鿡�� �� �� �ֵ��� ȸ��
	glRotatef((GLfloat)neck, 1.0, 0.0, 0.0); //���� ������ �� �ֵ��� �������� �̿�
	gluCylinder(qobj, 0.2, 0.2, 0.3, 30, 1); //���� �Ǹ��� Ÿ������ �𵨸�
	glPopMatrix();//�� ��

	/////////////////// ���� //////////////////////////
	glTranslatef(0.0, -0.3, 0.0);//������ġ ġ��
	glPushMatrix(); //���� ��ġ Ǫ��
	glColor3f(0.0, 0.0, 0.8); //�����������
	glRotatef(90.0, 1.0, 0.0, 0.0); //������ ���鿡�� �� �� �ֵ��� ȸ��
	glRotatef((GLfloat)body, 1.0, 0.0, 0.0); //������ ������ �� �ֵ��� �������� �̿�
	gluCylinder(qobj, 1.0, 1.0, 1.5, 70, 1);//������ �Ǹ��� Ÿ������ �𵨸�
	glPopMatrix();//���� ��, �ֻ��� ������ ������ġ�� ����

	/////////////////// ���� �ٸ� //////////////////////////
	glPushMatrix();//���� ���� ��ġ Ǫ��
	glRotatef((GLfloat)left_leg, -0.1, 0.0, 0.0); //�ٸ��� ȸ���� �� �ֵ��� �������� �̿�
	glTranslatef(-0.3, -2.1, 0.0); //��������� ��ġ ����
	glPushMatrix();//���� ����� ��ġ Ǫ��
	glColor3f(1.0, 0.4, 0.7); //���� ����� ���� ����
	glRotatef(90.0, -1.0, 0.0, 0.0); //�ٸ��� ���鿡�� �� �� �ֵ��� ȸ��
	gluCylinder(qobj, 0.2, 0.2, 0.6, 20, 1);//�ٸ��� �Ǹ��� Ÿ������ �𵨸�
	glPopMatrix();//���� ����� ��

	glPushMatrix();
	glRotatef((GLfloat)left_knee, 1.0, 0.0, 0.0); //������ ������ �� �ֵ��� �������� �̿�
	glTranslatef(0.0, -0.6, 0.0); //���� ������ ��ġ ����
	glPushMatrix();//���������� ��ġ Ǫ��
	glColor3f(1.0, 0.6, 0.0); //���� ������ ���� ����
	glRotatef(90.0, -1.0, 0.0, 0.0); //�ٸ��� ���鿡�� �� �� �ֵ��� ȸ��
	gluCylinder(qobj, 0.2, 0.2, 0.6, 20, 1); //�ٸ��� �Ǹ��� Ÿ������ �𵨸�
	glPopMatrix();//���������� ��

	glTranslatef(-0.1, -0.15, 0.1); //���� �� ��ġ ����
	glColor3f(0.0, 0.0, 1.0); //���� �� ���� ����
	glRotatef(90.0, -1.0, 0.0, 0.0); //���� ���鿡�� �� �� �ֵ��� ȸ��
	gluCylinder(qobj, 0.3, 0.3, 0.15, 30, 1);//���� �Ǹ��� Ÿ������ �𵨸�

	glPopMatrix();
	glPopMatrix();//������ ��, ���� ������ ���� ��ġ�� ����

	/////////////////// ������ �ٸ� //////////////////////////
	glPushMatrix();//������ġ����	
	glRotatef((GLfloat)right_leg, -0.1, 0.0, 0.0); //������ �����
	glTranslatef(0.3, -2.1, 0.0);
	glPushMatrix();
	glColor3f(1.0, 0.4, 0.7);
	glRotatef(90.0, -1.0, 0.0, 0.0);
	gluCylinder(qobj, 0.2, 0.2, 0.6, 20, 1);
	glPopMatrix();

	glPushMatrix();
	glRotatef((GLfloat)right_knee, 1.0, 0.0, 0.0); //������ ������ �� �ֵ��� �������� �̿�
	glTranslatef(0.0, -0.6, 0.0); //������ ������
	glPushMatrix();
	glColor3f(1.0, 0.6, 0.0);
	glRotatef(90.0, -1.0, 0.0, 0.0);
	gluCylinder(qobj, 0.2, 0.2, 0.6, 20, 1);
	glPopMatrix();

	glTranslatef(0.1, -0.15, 0.1); //������ ��
	glColor3f(0.0, 0.0, 1.0);
	glRotatef(90.0, -1.0, 0.0, 0.0);
	gluCylinder(qobj, 0.3, 0.3, 0.15, 30, 1);

	glPopMatrix(); 
	glPopMatrix(); 
	glPopMatrix();

	/////////////////// ���� �� //////////////////////////
	glPushMatrix(); //���� Ǫ��
	glTranslatef(-1.1, 0.7, 0.1); //���� ��� ��ġ
	glRotatef((GLfloat)left_sh, 1.0, 0.0, 0.0);
	glRotatef(90, -1.0, 0.0, 0.0);
	glRotatef(5, 0.0, 1.0, 0.0); //��ü�� ����ϵ��� ����� ȸ����Ŵ
	glPushMatrix();//���� ��� Ǫ��
	glColor3f(0.0, 1.0, 0.0); //���� ��� ���� ����
	gluCylinder(qobj, 0.2, 0.2, 0.8, 20, 1); //���� �Ǹ��� Ÿ������ �𵨸�
	glPopMatrix();//���� �� ��

	glPushMatrix(); //���� Ǫ��
	glRotatef((GLfloat)left_arm, -0.7, -0.2, 0.0); //���� ȸ���� �� �ֵ��� �������� �̿�
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
	glPopMatrix();
	//���� �� pop���� �������� ���ư���

	/////////////////// ������ �� //////////////////////////
	glPushMatrix();
	glTranslatef(1.1, 0.7, 0.1); //������ ���
	glRotatef((GLfloat)right_sh, 1.0, 0.0, 0.0);
	glRotatef(90, -1.0, 0.0, 0.0);
	glRotatef(5, 0.0, -1.0, 0.0);
	glPushMatrix();
	glColor3f(0.0, 1.0, 0.0);
	gluCylinder(qobj, 0.2, 0.2, 0.8, 20, 1);
	glPopMatrix();

	glPushMatrix();//�������
	glRotatef((GLfloat)right_arm, -0.7, 0.2, 0.0); //������ �� �Ͽ� 
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
	glPopMatrix();
	//���� �� ��

	glutSwapBuffers();
}

void mytimer2(int value) { //R �Ǵ� r�� ������ �� ����Ǵ� Ÿ�̸� �Լ�
	if (st == 0) { //�������°� �ƴ� ��
		if (check2) {

			//�����Ȱ� �޴ٸ��� ������ ���� ��
			if (right_arm < 150.0) //�������� 150������ ������
			{
				right_sh += 0.3; //��������� �� ������ ����
				right_arm += 5.0;
				if (left_knee < 90.0) { //������ ������ 90������ ���� �� 
					left_leg += 1.0; //������ �ٸ��� ���� ����
					left_knee += 3.0;

					//���Ȱ� �����ٸ��� ���ڸ���
					if (left_arm > 0.0) { //������ ������ 0���� Ŭ ��
						left_sh -= 0.3; //���Ȱ� �޾���� ������ ����
						left_arm -= 5.0;
						if (right_knee > 0.0) { //�����ٸ��� ������ 0���� Ŭ ��
							right_leg -= 1.0; //�����ٸ��� ���������� ������ ����
							right_knee -= 3.0;

							head += 0.2; //�Ӹ�, ��, ��� ������ �������Ѽ� ������ �ο�
							neck += 0.2;
							body -= 0.2;
						}
					}

				}
				else {
				}
			}
			else
				check2 = false;
		}
		else {
			//�����Ȱ� �޴ٸ��� ���ڸ��� �� ��
			if (right_arm > 0.0)
			{
				right_sh -= 0.3;
				right_arm -= 5.0;
				if (left_knee > 0.0) {
					left_leg -= 1.0;
					left_knee -= 3.0;

					//���Ȱ� �����ٸ��� ������
					if (left_arm < 150.0) {
						left_sh += 0.3;
						left_arm += 5.0;
						if (right_knee < 90) {
							right_leg += 1.0;
							right_knee += 3.0;

							head -= 0.2;
							neck -= 0.2;
							body += 0.2;
						}
					}

				}
				else {
					return;
				}
			}
			else {
				check2 = true;
				return;
			}
		}
		glutPostRedisplay();
	}

}

void mytimer6(int value) { //s�� s�� �������� ����Ǵ� Ÿ�̸� �Լ�, �ƹ��͵� ������� �ʱ� ������ �����̴� ��ü�� �����.
	if (st == 1) {

	}
	glutPostRedisplay();
	glutTimerFunc(40, mytimer6, 1);
}

void myidle() { //R �Ǵ� r�� �������� ����Ǵ� ���̵� �ݹ��Լ�
	Sleep(10);
	glutTimerFunc(40, mytimer2, 1); //mytimer2�Լ� ����
}

//R�̳� r�� ������ ���̵��ݹ��Լ� ����
//S�� s�� ������ mytimer6 ����
void mykeyboard(unsigned char key, int x, int y) { 
	switch (key) {
	case 'R': case 'r':
		st = 0;
		glutIdleFunc(myidle);
		break;
	case 'S': case 's':
		st = 1;
		glutTimerFunc(50, mytimer6, 1);
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void myreshape(int newwidth, int newheight) {
	glViewport(0, 0, (GLsizei)newwidth, (GLsizei)newheight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLfloat)newwidth / (GLfloat)newheight, 5.0, 100);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Can Robot");

	myinit();
	glutDisplayFunc(mydisplay);
	glutReshapeFunc(myreshape);
	glutKeyboardFunc(mykeyboard);

	glutMainLoop();
	return 0;
}