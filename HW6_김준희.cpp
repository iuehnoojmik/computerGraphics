/*********************************************************************************************************/
/*                                HW#6. glViewport()�� ���� ������ȯ                                     */
/*  �ۼ��� : ������                          ��¥ : 2022�� 11�� 11��                                     */
/*                                                                                                       */
/* ���� ���� : �� �����쿡 ���� ������ �׷� ���������� ���������� ���ϵ��� �Ѵ�.                       */
/* ��� :                                                                                                */
/*      ���ϴ� ����                                                                                      */
/*      �� : Camera�� Y�� ��ǥ�� 0.1�� ���������� ����                                                    */
/*      �� : Camera�� Y�� ��ǥ�� 0.1�� ���������� ����                                                    */
/*      �� : Camera�� X�� ��ǥ�� 0.1�� ���������� ����                                                    */
/*      �� : Camera�� X�� ��ǥ�� 0.1�� ���������� ����                                                    */
/*      F3 : Camera�� Z�� ��ǥ�� 0.1�� ���������� ����                                                   */
/*      F4 : Camera�� Z�� ��ǥ�� 0.1�� ���������� ����                                                   */
/*                                                                                                       */
/*      ���� ����                                                                                      */
/*      a �Ǵ� A : Camera�� X�� ��ǥ�� 0.1�� ���������� ����                                             */                           
/*      d �Ǵ� D : Camera�� X�� ��ǥ�� 0.1�� ���������� ����                                             */
/*      W �Ǵ� w : Camera�� Y�� ��ǥ�� 0.1�� ���������� ����                                             */
/*      S �Ǵ� s : Camera�� Y�� ��ǥ�� 0.1�� ���������� ����                                             */
/*      F1 : Camera�� Z�� ��ǥ�� 0.1�� ���������� ����                                                   */
/*      F2 : Camera�� Z�� ��ǥ�� 0.1�� ���������� ����                                                   */
/*********************************************************************************************************/

#include <GL/glut.h>

GLfloat Width = 800; //�������� ���� ��������
GLfloat Height = 800; //�������� ���� ��������

//���ϴ� ����(��������)
GLfloat camera_x_ortho = 0.0; //ī�޶��� X��ǥ�� ������ �� �ִ� ��������
GLfloat camera_y_ortho = 0.0;  //ī�޶��� Y��ǥ�� ������ �� �ִ� ��������
GLfloat camera_z_ortho = 0.0;  //ī�޶��� Z��ǥ�� ������ �� �ִ� ��������

//���� ����(��������)
GLfloat camera_x_pers = 0.0; //ī�޶��� X��ǥ�� ������ �� �ִ� ��������
GLfloat camera_y_pers = 0.0;  //ī�޶��� Y��ǥ�� ������ �� �ִ� ��������
GLfloat camera_z_pers = 0.0;  //ī�޶��� Z��ǥ�� ������ �� �ִ� ��������

void DrawScene() { //���� �׸��� �Լ�

    glColor3f(1.0, 1.0, 0.0); 
    glutWireTeapot(1.0); //������ �׸���

    glPushMatrix(); 
    glColor3f(0.0, 1.0, 1.0);
    glTranslatef(0, 0, -2);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glutWireTorus(0.3, 0.5, 20, 20); //Torus �׸���
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0, 0.0, 0.5);
    glTranslatef(2, 0, -2);
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    glutWireCone(0.5, 1.0, 10, 15); //Wire Cone �׸���
    glPopMatrix();

     glColor3f(1.0, 1.0, 1.0);
     glBegin(GL_LINES); //x,y,z�� �� �׸���
     glVertex3f(-5, 0, 0);
     glVertex3f(5, 0, 0);
     glVertex3f(0, -5, 0);
     glVertex3f(0, 5, 0);
     glVertex3f(0, 0, -5);
     glVertex3f(0, 0, 5);
     glEnd();
}

void MyDisplay( ) {
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     glColor3f(1.0, 1.0, 1.0);

     glPushMatrix();
     glViewport(0, 0, Width / 2, Height / 2); //���ϴ� ����
     glOrtho(-5.0 * ((GLfloat)Height / Width), 5.0 * ((GLfloat)Height / Width), -5.0 * ((GLfloat)Height / Width), 5.0 * ((GLfloat)Height / Width), -5.0, 5.0); //��������, ȭ�鿡�� ���̴� ����� ��Ⱦ�� ���� �����ش�
     gluLookAt(2.5 + camera_x_ortho, 2.5 + camera_y_ortho, 2.5 + camera_z_ortho, 0.0, 0.0, 0.0, 0.0, 0.3, 0.0); //ī�޶��� �ʱ����
     DrawScene();  //�����׸��� �Լ�
     glPopMatrix();

     glPushMatrix();
     glViewport(Width / 2, Height / 2, Width / 2, Height / 2); //���� ����
     gluPerspective(45.0, (GLsizei)Width / (GLsizei)Height, 0.0, 100); //��������, ��Ⱦ�� ���� �����ش�
     gluLookAt(5.0 + camera_x_pers, 5.0 + camera_y_pers, 5.0 + camera_z_pers, 0.0, 0.0, 0.0, 0.0, 0.3, 0.0); //ī�޶��� �ʱ����
     DrawScene(); //�����׸��� �Լ�
     glPopMatrix();

     glFlush();
}

void MyReshape(int w, int h) { //������ ũ�⸦ ������ �� ���� ũ�⸦ ���޹ް� ���������� �־��ش�
    Width = w;
    Height = h;
}

void MySpecialKeyboard(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_LEFT: //���� ����Ű�� ������ ��
        camera_x_ortho -= 0.1; //������������(���ϴ�)�� ī�޶� x��ǥ�� 0.1�� ����
        glutPostRedisplay(); 
        break;

    case GLUT_KEY_RIGHT: //������ ����Ű�� ������ ��
        camera_x_ortho += 0.1; //������������(���ϴ�)�� ī�޶� x��ǥ�� 0.1�� ����
        glutPostRedisplay(); 
        break;

    case GLUT_KEY_DOWN: //�Ʒ��� ����Ű�� ������ ��
        camera_y_ortho -= 0.1; //������������(���ϴ�)�� ī�޶� y��ǥ�� 0.1�� ����
        glutPostRedisplay(); 
        break;

    case GLUT_KEY_UP: //���� ����Ű�� ������ ��
        camera_y_ortho += 0.1;  //������������(���ϴ�)�� ī�޶� y��ǥ�� 0.1�� ����
        glutPostRedisplay(); 
        break;

    case GLUT_KEY_F3: //F3 ������ ��
        camera_z_ortho -= 0.1; //������������(���ϴ�)�� ī�޶� Z��ǥ�� 0.1�� ����
        glutPostRedisplay();
        break;

    case GLUT_KEY_F4: //F4 ������ ��
        camera_z_ortho += 0.1; //������������(���ϴ�)�� ī�޶� Z��ǥ�� 0.1�� ����
        glutPostRedisplay();
        break;

    case GLUT_KEY_F1: //F1 ������ ��
        camera_z_pers -= 0.1; //������������(����)�� ī�޶� Z��ǥ�� 0.1�� ����
        glutPostRedisplay();
        break;

    case GLUT_KEY_F2: //F2 ������ ��
        camera_z_pers += 0.1; //������������(����)�� ī�޶� Z��ǥ�� 0.1�� ����
        glutPostRedisplay();
        break;
    }
}

void MyKeyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'A': case 'a':
        camera_x_pers -= 0.1;  //������������(����)�� ī�޶� x��ǥ�� 0.1�� ����
        glutPostRedisplay();
        break;

    case 'D': case 'd':
        camera_x_pers += 0.1;  //������������(����)�� ī�޶� x��ǥ�� 0.1�� ����
        glutPostRedisplay();
        break;

    case 'W': case 'w':
        camera_y_pers += 0.1;  //������������(����)�� ī�޶� y��ǥ�� 0.1�� ����
        glutPostRedisplay();
        break;

    case 'S': case 's':
        camera_y_pers -= 0.1;  //������������(����)�� ī�޶� y��ǥ�� 0.1�� ����
        glutPostRedisplay();
        break;
    }
}

int main(int argc, char** argv) {
     glutInit(&argc, argv);
     glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
     glutInitWindowSize(Width, Height); //������ ���������� ������ ũ�� ����
     glutInitWindowPosition(100, 100);
     glutCreateWindow("glViewPort"); 
     glClearColor(0.0, 0.0, 0.0, 0.0);

     glutDisplayFunc(MyDisplay);
     glutReshapeFunc(MyReshape);
     glutKeyboardFunc(MyKeyboard);
     glutSpecialFunc(MySpecialKeyboard); 

     glutMainLoop( );
     return 0;
}