/*********************************************************************************************************/
/*                                HW#5-1 : gluLookAt()의 실시간 제어                                     */
/*  작성자 : 김준희                          날짜 : 2022년 11월 4일                                      */
/*                                                                                                       */
/* 문제 정의 : 시점 좌표계를 Keyboard Callback 함수로 실시간 제어가 가능하도록 구현                      */
/* 기능 :                                                                                                */
/*      ↑ : Camera의 Y축 좌표가 0.1씩 연속적으로 증가                                                    */
/*      ↓ : Camera의 Y축 좌표가 0.1씩 연속적으로 감소                                                    */
/*      ← : Camera의 X축 좌표가 0.1씩 연속적으로 감소                                                    */
/*      → : Camera의 X축 좌표가 0.1씩 연속적으로 증가                                                    */
/*      a 또는 A : 초점(Focus)의 X축 좌표가 0.1씩 연속적으로 증가                                        */                           
/*      f 또는 F : 초점(Focus)의 X축 좌표가 0.1씩 연속적으로 감소                                        */
/*      r 또는 R : 초점(Focus)의 Y축 좌표가 0.1씩 연속적으로 증가                                        */
/*      v 또는 V : 초점(Focus)의 Y축 좌표가 0.1씩 연속적으로 감소                                        */
/*      z 또는 Z : 초점(Focus)의 Z축 좌표가 0.1씩 연속적으로 증가                                        */
/*      t 또는 T : 초점(Focus)의 Z축 좌표가 0.1씩 연속적으로 감소                                        */
/*********************************************************************************************************/

#include <GL/glut.h>

GLfloat camera_x = 0.0; //카메라의 X좌표를 조정할 수 있는 전역변수
GLfloat camera_y = 0.0;  //카메라의 Y좌표를 조정할 수 있는 전역변수

GLfloat focus_x = 0.0; //초점의 X좌표를 조정할 수 있는 전역변수
GLfloat focus_y = 0.0;  //초점의 Y좌표를 조정할 수 있는 전역변수
GLfloat focus_z = 0.0; //초점의 Z좌표를 조정할 수 있는 전역변수

void DrawGround() { //땅을 그리는 함수
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

     //초기에는 y,z축으로 3.5씩 이동시킨 곳에 카메라를 위치시킨다. (0, 3.5, 3.5)
     //초기 초점은 (0 ,0 ,0)이다.
     //카메라를 y축으로 1.0만큼 기울여서 주전자를 응시할 수 있도록 한다.
     gluLookAt(camera_x, camera_y + 3.5, 3.5, focus_x, focus_y, focus_z, 0.0, 1.0, 0.0);

     DrawGround(); //땅을 그리는 함수

     glColor3f(1.0, 1.0, 0.0); //주전자 색깔 지정
     glutWireTeapot(1.0); //주전자 그리기

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
    case GLUT_KEY_LEFT: //왼쪽 방향키를 눌렀을 때
        camera_x -= 0.1; //카메라의 x좌표를 0.1씩 감소시켜서 카메라를 왼쪽으로 이동시킨다
        glutPostRedisplay(); 
        break;

    case GLUT_KEY_RIGHT: //오른쪽 방향키를 눌렀을 때
        camera_x += 0.1; //카메라의 x좌표를 0.1씩 증가시켜서 카메라를 오른쪽으로 이동시킨다
        glutPostRedisplay(); 
        break;

    case GLUT_KEY_DOWN: //아래쪽 방향키를 눌렀을 때
        camera_y -= 0.1; //카메라의 y좌표를 0.1씩 감소시켜서 카메라를 아래쪽으로 이동시킨다
        glutPostRedisplay(); 
        break;

    case GLUT_KEY_UP: //위쪽 방향키를 눌렀을 때
        camera_y += 0.1;  //카메라의 y좌표를 0.1씩 증가시켜서 카메라를 위쪽으로 이동시킨다
        glutPostRedisplay(); 
        break;
    }
}

void MyKeyboard(unsigned char key, int x, int y) { 
    switch (key) {
        case 'A': case 'a':
            focus_x += 0.1; //초점의 x좌표를 0.1씩 증가시켜서 0.1만큼 오른쪽을 응시하게 한다.
            glutPostRedisplay(); 
            break;

        case 'F': case 'f':
            focus_x -= 0.1; //초점의 x좌표를 0.1씩 감소시켜서 0.1만큼 왼쪽을 응시하게 한다.
            glutPostRedisplay();
            break;

        case 'R': case 'r':
            focus_y += 0.1; //초점의 y좌표를 0.1씩 증가시켜서 0.1만큼 위쪽을 응시하게 한다.
            glutPostRedisplay(); 
            break;

        case 'V': case 'v':
            focus_y -= 0.1;  //초점의 y좌표를 0.1씩 감소시켜서 0.1만큼 아래쪽을 응시하게 한다.
            glutPostRedisplay();
            break;

        case 'Z': case 'z':
            focus_z += 0.1;  //초점의 z좌표를 0.1씩 증가시켜서 앞구르기하듯이 초점을 응시하게 한다.
            glutPostRedisplay(); 
            break;

        case 'T': case 't':
            focus_z -= 0.1;  //초점의 z좌표를 0.1씩 감소시켜서 뒷구르기하듯이 초점을 응시하게 한다.
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