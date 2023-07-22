/*********************************************************************************************************/
/*                                HW#6. glViewport()을 통한 뷰폿변환                                     */
/*  작성자 : 김준희                          날짜 : 2022년 11월 11일                                     */
/*                                                                                                       */
/* 문제 정의 : 한 윈도우에 여러 뷰폿을 그려 원근투영과 직교투영을 비교하도록 한다.                       */
/* 기능 :                                                                                                */
/*      좌하단 뷰폿                                                                                      */
/*      ↑ : Camera의 Y축 좌표가 0.1씩 연속적으로 증가                                                    */
/*      ↓ : Camera의 Y축 좌표가 0.1씩 연속적으로 감소                                                    */
/*      ← : Camera의 X축 좌표가 0.1씩 연속적으로 감소                                                    */
/*      → : Camera의 X축 좌표가 0.1씩 연속적으로 증가                                                    */
/*      F3 : Camera의 Z축 좌표가 0.1씩 연속적으로 감소                                                   */
/*      F4 : Camera의 Z축 좌표가 0.1씩 연속적으로 증가                                                   */
/*                                                                                                       */
/*      우상단 뷰폿                                                                                      */
/*      a 또는 A : Camera의 X축 좌표가 0.1씩 연속적으로 감소                                             */                           
/*      d 또는 D : Camera의 X축 좌표가 0.1씩 연속적으로 증가                                             */
/*      W 또는 w : Camera의 Y축 좌표가 0.1씩 연속적으로 증가                                             */
/*      S 또는 s : Camera의 Y축 좌표가 0.1씩 연속적으로 감소                                             */
/*      F1 : Camera의 Z축 좌표가 0.1씩 연속적으로 감소                                                   */
/*      F2 : Camera의 Z축 좌표가 0.1씩 연속적으로 증가                                                   */
/*********************************************************************************************************/

#include <GL/glut.h>

GLfloat Width = 800; //윈도우의 가로 전역변수
GLfloat Height = 800; //윈도우의 세로 전역변수

//좌하단 뷰폿(직교투영)
GLfloat camera_x_ortho = 0.0; //카메라의 X좌표를 조정할 수 있는 전역변수
GLfloat camera_y_ortho = 0.0;  //카메라의 Y좌표를 조정할 수 있는 전역변수
GLfloat camera_z_ortho = 0.0;  //카메라의 Z좌표를 조정할 수 있는 전역변수

//우상단 뷰폿(원근투영)
GLfloat camera_x_pers = 0.0; //카메라의 X좌표를 조정할 수 있는 전역변수
GLfloat camera_y_pers = 0.0;  //카메라의 Y좌표를 조정할 수 있는 전역변수
GLfloat camera_z_pers = 0.0;  //카메라의 Z좌표를 조정할 수 있는 전역변수

void DrawScene() { //땅을 그리는 함수

    glColor3f(1.0, 1.0, 0.0); 
    glutWireTeapot(1.0); //주전자 그리기

    glPushMatrix(); 
    glColor3f(0.0, 1.0, 1.0);
    glTranslatef(0, 0, -2);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glutWireTorus(0.3, 0.5, 20, 20); //Torus 그리기
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0, 0.0, 0.5);
    glTranslatef(2, 0, -2);
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    glutWireCone(0.5, 1.0, 10, 15); //Wire Cone 그리기
    glPopMatrix();

     glColor3f(1.0, 1.0, 1.0);
     glBegin(GL_LINES); //x,y,z축 선 그리기
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
     glViewport(0, 0, Width / 2, Height / 2); //좌하단 뷰폿
     glOrtho(-5.0 * ((GLfloat)Height / Width), 5.0 * ((GLfloat)Height / Width), -5.0 * ((GLfloat)Height / Width), 5.0 * ((GLfloat)Height / Width), -5.0, 5.0); //평행투영, 화면에서 보이는 면들을 종횡비를 구해 곱해준다
     gluLookAt(2.5 + camera_x_ortho, 2.5 + camera_y_ortho, 2.5 + camera_z_ortho, 0.0, 0.0, 0.0, 0.0, 0.3, 0.0); //카메라의 초기시점
     DrawScene();  //도형그리는 함수
     glPopMatrix();

     glPushMatrix();
     glViewport(Width / 2, Height / 2, Width / 2, Height / 2); //우상단 뷰폿
     gluPerspective(45.0, (GLsizei)Width / (GLsizei)Height, 0.0, 100); //원근투영, 종횡비를 구해 곱해준다
     gluLookAt(5.0 + camera_x_pers, 5.0 + camera_y_pers, 5.0 + camera_z_pers, 0.0, 0.0, 0.0, 0.0, 0.3, 0.0); //카메라의 초기시점
     DrawScene(); //도형그리는 함수
     glPopMatrix();

     glFlush();
}

void MyReshape(int w, int h) { //윈도우 크기를 변경할 때 마다 크기를 전달받고 전역변수에 넣어준다
    Width = w;
    Height = h;
}

void MySpecialKeyboard(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_LEFT: //왼쪽 방향키를 눌렀을 때
        camera_x_ortho -= 0.1; //직교투영뷰폿(좌하단)의 카메라 x좌표를 0.1씩 감소
        glutPostRedisplay(); 
        break;

    case GLUT_KEY_RIGHT: //오른쪽 방향키를 눌렀을 때
        camera_x_ortho += 0.1; //직교투영뷰폿(좌하단)의 카메라 x좌표를 0.1씩 증가
        glutPostRedisplay(); 
        break;

    case GLUT_KEY_DOWN: //아래쪽 방향키를 눌렀을 때
        camera_y_ortho -= 0.1; //직교투영뷰폿(좌하단)의 카메라 y좌표를 0.1씩 감소
        glutPostRedisplay(); 
        break;

    case GLUT_KEY_UP: //위쪽 방향키를 눌렀을 때
        camera_y_ortho += 0.1;  //직교투영뷰폿(좌하단)의 카메라 y좌표를 0.1씩 증가
        glutPostRedisplay(); 
        break;

    case GLUT_KEY_F3: //F3 눌렀을 때
        camera_z_ortho -= 0.1; //직교투영뷰폿(좌하단)의 카메라 Z좌표를 0.1씩 감소
        glutPostRedisplay();
        break;

    case GLUT_KEY_F4: //F4 눌렀을 때
        camera_z_ortho += 0.1; //직교투영뷰폿(좌하단)의 카메라 Z좌표를 0.1씩 증가
        glutPostRedisplay();
        break;

    case GLUT_KEY_F1: //F1 눌렀을 때
        camera_z_pers -= 0.1; //원근투영뷰폿(우상단)의 카메라 Z좌표를 0.1씩 감소
        glutPostRedisplay();
        break;

    case GLUT_KEY_F2: //F2 눌렀을 때
        camera_z_pers += 0.1; //원근투영뷰폿(우상단)의 카메라 Z좌표를 0.1씩 증가
        glutPostRedisplay();
        break;
    }
}

void MyKeyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'A': case 'a':
        camera_x_pers -= 0.1;  //원근투영뷰폿(우상단)의 카메라 x좌표를 0.1씩 감소
        glutPostRedisplay();
        break;

    case 'D': case 'd':
        camera_x_pers += 0.1;  //원근투영뷰폿(우상단)의 카메라 x좌표를 0.1씩 증가
        glutPostRedisplay();
        break;

    case 'W': case 'w':
        camera_y_pers += 0.1;  //원근투영뷰폿(우상단)의 카메라 y좌표를 0.1씩 증가
        glutPostRedisplay();
        break;

    case 'S': case 's':
        camera_y_pers -= 0.1;  //원근투영뷰폿(우상단)의 카메라 y좌표를 0.1씩 감소
        glutPostRedisplay();
        break;
    }
}

int main(int argc, char** argv) {
     glutInit(&argc, argv);
     glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
     glutInitWindowSize(Width, Height); //선언한 전역변수로 윈도우 크기 지정
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