/*********************************************************************************************************/
/*                                HW#5-1 : gluLookAt()�� �ǽð� ����                                     */
/*  �ۼ��� : ������                          ��¥ : 2022�� 11�� 4��                                      */
/*                                                                                                       */
/* ���� ���� : ���� ��ǥ�踦 Keyboard Callback �Լ��� �ǽð� ��� �����ϵ��� ����                      */
/* ��� :                                                                                                */
/*      �� : Camera�� Y�� ��ǥ�� 0.1�� ���������� ����                                                    */
/*      �� : Camera�� Y�� ��ǥ�� 0.1�� ���������� ����                                                    */
/*      �� : Camera�� X�� ��ǥ�� 0.1�� ���������� ����                                                    */
/*      �� : Camera�� X�� ��ǥ�� 0.1�� ���������� ����                                                    */
/*      a �Ǵ� A : ����(Focus)�� X�� ��ǥ�� 0.1�� ���������� ����                                        */                           
/*      f �Ǵ� F : ����(Focus)�� X�� ��ǥ�� 0.1�� ���������� ����                                        */
/*      r �Ǵ� R : ����(Focus)�� Y�� ��ǥ�� 0.1�� ���������� ����                                        */
/*      v �Ǵ� V : ����(Focus)�� Y�� ��ǥ�� 0.1�� ���������� ����                                        */
/*      z �Ǵ� Z : ����(Focus)�� Z�� ��ǥ�� 0.1�� ���������� ����                                        */
/*      t �Ǵ� T : ����(Focus)�� Z�� ��ǥ�� 0.1�� ���������� ����                                        */
/*********************************************************************************************************/

#include <GL/glut.h>

GLfloat camera_x = 0.0; //ī�޶��� X��ǥ�� ������ �� �ִ� ��������
GLfloat camera_y = 0.0;  //ī�޶��� Y��ǥ�� ������ �� �ִ� ��������

GLfloat focus_x = 0.0; //������ X��ǥ�� ������ �� �ִ� ��������
GLfloat focus_y = 0.0;  //������ Y��ǥ�� ������ �� �ִ� ��������
GLfloat focus_z = 0.0; //������ Z��ǥ�� ������ �� �ִ� ��������

void DrawGround() { //���� �׸��� �Լ�
     glColor3f(0.5, 0.5, 0.5); 
     glBegin(GL_POLYGON);
          glVertex3f(-2.0,-0.71, 2.0);
          glVertex3f( 2.0,-0.71, 2.0);
          glVertex3f( 2.0,-0.71,-2.0);
          glVertex3f(-2.0,-0.71,-2.0);
     glEnd();

     glColor3f(0.3, 0.3, 0.3);
     glBegin(GL_LINES);
          for (float x = -2.0; x <= 2.2; x += 0.2) {
               glVertex3f(x,-0.7,-2.0);
               glVertex3f(x,-0.7, 2.0);
          }

          for (float z = -2.0; z <= 2.2; z += 0.2) {
               glVertex3f(-2.0,-0.7, z);
               glVertex3f( 2.0,-0.7, z);
          }
     glEnd();
}

void MyDisplay( ) {
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity( );

     //�ʱ⿡�� y,z������ 3.5�� �̵���Ų ���� ī�޶� ��ġ��Ų��. (0, 3.5, 3.5)
     //�ʱ� ������ (0 ,0 ,0)�̴�.
     //ī�޶� y������ 1.0��ŭ ��￩�� �����ڸ� ������ �� �ֵ��� �Ѵ�.
     gluLookAt(camera_x, camera_y + 3.5, 3.5, focus_x, focus_y, focus_z, 0.0, 1.0, 0.0);

     DrawGround(); //���� �׸��� �Լ�

     glColor3f(1.0, 1.0, 0.0); //������ ���� ����
     glutWireTeapot(1.0); //������ �׸���

     glFlush();
}

void MyReshape (int w, int h) {
     glViewport (0, 0, (GLsizei) w, (GLsizei) h);
     glMatrixMode (GL_PROJECTION);
     glLoadIdentity( );

     gluPerspective(45.0, (GLsizei)w/(GLsizei)h, 0.0, 100);
}

void MySpecialKeyboard(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_LEFT: //���� ����Ű�� ������ ��
        camera_x -= 0.1; //ī�޶��� x��ǥ�� 0.1�� ���ҽ��Ѽ� ī�޶� �������� �̵���Ų��
        glutPostRedisplay(); 
        break;

    case GLUT_KEY_RIGHT: //������ ����Ű�� ������ ��
        camera_x += 0.1; //ī�޶��� x��ǥ�� 0.1�� �������Ѽ� ī�޶� ���������� �̵���Ų��
        glutPostRedisplay(); 
        break;

    case GLUT_KEY_DOWN: //�Ʒ��� ����Ű�� ������ ��
        camera_y -= 0.1; //ī�޶��� y��ǥ�� 0.1�� ���ҽ��Ѽ� ī�޶� �Ʒ������� �̵���Ų��
        glutPostRedisplay(); 
        break;

    case GLUT_KEY_UP: //���� ����Ű�� ������ ��
        camera_y += 0.1;  //ī�޶��� y��ǥ�� 0.1�� �������Ѽ� ī�޶� �������� �̵���Ų��
        glutPostRedisplay(); 
        break;
    }
}

void MyKeyboard(unsigned char key, int x, int y) { 
    switch (key) {
        case 'A': case 'a':
            focus_x += 0.1; //������ x��ǥ�� 0.1�� �������Ѽ� 0.1��ŭ �������� �����ϰ� �Ѵ�.
            glutPostRedisplay(); 
            break;

        case 'F': case 'f':
            focus_x -= 0.1; //������ x��ǥ�� 0.1�� ���ҽ��Ѽ� 0.1��ŭ ������ �����ϰ� �Ѵ�.
            glutPostRedisplay();
            break;

        case 'R': case 'r':
            focus_y += 0.1; //������ y��ǥ�� 0.1�� �������Ѽ� 0.1��ŭ ������ �����ϰ� �Ѵ�.
            glutPostRedisplay(); 
            break;

        case 'V': case 'v':
            focus_y -= 0.1;  //������ y��ǥ�� 0.1�� ���ҽ��Ѽ� 0.1��ŭ �Ʒ����� �����ϰ� �Ѵ�.
            glutPostRedisplay();
            break;

        case 'Z': case 'z':
            focus_z += 0.1;  //������ z��ǥ�� 0.1�� �������Ѽ� �ձ������ϵ��� ������ �����ϰ� �Ѵ�.
            glutPostRedisplay(); 
            break;

        case 'T': case 't':
            focus_z -= 0.1;  //������ z��ǥ�� 0.1�� ���ҽ��Ѽ� �ޱ������ϵ��� ������ �����ϰ� �Ѵ�.
            glutPostRedisplay(); 
            break;
	}
}

int main(int argc, char** argv) {
     glutInit(&argc, argv);
     glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
     glutInitWindowSize(500, 500);
     glutInitWindowPosition(0, 0);
     glutCreateWindow("gluLookAt"); 
     glClearColor(0.0, 0.0, 0.0, 0.0);

     glutDisplayFunc(MyDisplay);
     glutReshapeFunc(MyReshape);
     glutKeyboardFunc(MyKeyboard); 
     glutSpecialFunc(MySpecialKeyboard); 

     glutMainLoop( );
     return 0;
}