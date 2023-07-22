/*************************************************************************/
/*                HW#3-1  Keyboard Callback 응용1	   				     */
/*  작성자 : 김준희                              날짜 : 2022년 10월 7일  */
/*																		 */
/* 문제 정의 : 키보드 콜백 함수를 이용하여								 */
/*		특정 키보드의 키를 누르면 도형을 이동하거나 색을 칠하도록 한다	 */
/*									                                     */
/* 기능: a또는A: 0.1만큼 왼쪽으로 이동/ f또는F: 0.1만큼 오른쪽으로 이동  */
/*       v또는V: 0.1만큼 위쪽으로 이동					                 */
/*       r또는R: 도형을 빨간색으로 칠한 후 0.1만큼 오른쪽으로 이동       */
/*       b또는B: 도형을 파란색으로 칠함  				                 */
/*                - - - - - - -                                          */
/*************************************************************************/
#include <GL/glut.h>

float dx, dy = 0; //사각형이 이동할 좌표 전역변수

void MyInit() {
	glClearColor(1.0, 1.0, 1.0, 1.0); //배경색상-흰색

	glClear(GL_COLOR_BUFFER_BIT); //색 버퍼 제거
	glColor3f(0.5, 0.5, 0.5); //모델 색상 지정 - 회색

	glMatrixMode(GL_PROJECTION); //투영행렬 선택
	glLoadIdentity(); //투영행렬 초기화

	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); //가시부피 영역 설정
}

void MyDisplay() {
	glBegin(GL_POLYGON); //다각형 모델링
	glVertex3f(-0.5 + dx, -0.5 + dy, 0.0); //사각형의 왼쪽아래점 좌표
	glVertex3f(0.5 + dx, -0.5 + dy, 0.0); //사각형의 오른쪽아래점 좌표
	glVertex3f(0.5 + dx, 0.5 + dy, 0.0); //사각형의 오른쪽윗점 좌표
	glVertex3f(-0.5 + dx, 0.5 + dy, 0.0); //사각형의 왼쪽윗점 좌표
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

void MyKeyboard(unsigned char key, int x, int y) { //keyboard를 누르면 발생하는 함수
	switch (key) {
	case 'a': case'A': //키보드에서 a 또는 A를 누른 경우
		glClear(GL_COLOR_BUFFER_BIT); //이전 색 버퍼를 제거하여 이동된 사각형을 화면에 보이도록 한다
		dx += -0.1; //사각형의 모든 좌표를 0.1만큼 왼쪽으로 이동
		break;
	case 'f': case'F': //키보드에서 f 또는 F를 누른 경우
		glClear(GL_COLOR_BUFFER_BIT);
		dx += 0.1; //사각형의 모든 좌표를 0.1만큼 오른쪽으로 이동
		break;
	case 'r': case'R': //키보드에서 r 또는 R을 누른 경우
		glClear(GL_COLOR_BUFFER_BIT);
		dy += -0.1; //사각형의 모든 좌표를 0.1만큼 아래로 이동
		glColor3f(1.0, 0.0, 0.0); //사각형의 색깔을 빨간색으로 칠한다
		break;
	case 'v': case'V': //키보드에서 v 또는 V를 누른 경우
		glClear(GL_COLOR_BUFFER_BIT);
		dy += 0.1; //사각형의 모든 좌표를 0.1만큼 위로 이동
		break;
	case 'b': case'B': //키보드에서 b 또는 B를 누른 경우
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(0.0, 0.0, 1.0); //사각형의 색깔을 파란색으로 칠한다
		break;
	}

	glutPostRedisplay(); //디스플레이 함수 강제 호출 함수
}

int main(int argc, char** argv) {
	glutInit(&argc, argv); //window랑 os연결
	glutInitDisplayMode(GLUT_RGB); //디스플레이 모드 설정
	glutInitWindowSize(300, 300); //윈도우크기 설정
	glutInitWindowPosition(0, 0); //시작 지점 설정
	glutCreateWindow("Keyboard Callback 1"); //윈도우 생성(이름)


	MyInit(); //윈도우 화면 초기화
	glutDisplayFunc(MyDisplay); //콜백함수 등록
	glutReshapeFunc(MyReshape); //왜곡방지 함수
	glutKeyboardFunc(MyKeyboard); //ascii문자를 입력받는 키보드 기능 콜백 함수 등록

	glutMainLoop();
	return 0;
}
