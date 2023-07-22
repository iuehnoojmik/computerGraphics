/*************************************************************************/
/*                HW#3-5  IDLE Callback 응용	     				     */
/*  작성자 : 김준희                              날짜 : 2022년 10월 7일  */
/*																		 */
/* 문제 정의 : Idle 콜백 함수를 이용하여								 */
/*	특정 키보드 키를 누르면 도형이 특정방향으로 연속적으로 이동하게 한다 */
/*									                                     */
/* 기능: 위쪽방향키 - 도형이 위쪽으로 0.1씩 연속으로 이동	             */
/*       아래쪽방향키-도형이 아래쪽으로 0.1씩 연속으로 이동		         */
/*       왼쪽방향키-도형이 왼쪽으로 0.1씩 연속으로 이동			         */
/*       오른쪽방향키-도형이 오른쪽으로 0.1씩 연속으로 이동		         */
/*       ㄴ이동 중에 다른 방향키를 누르면 그 방향으로 이동			     */
/*       ㄴ이동 중에 윈도우 창을 벗어나지 않는다				         */
/*                - - - - - - -                                          */
/*************************************************************************/
#include <GL/glut.h>
#include <stdlib.h>

float px, py = 0.0; //사각형이 이동할 y좌표 전역변수
float mx, my = 0.0; //사각형이 이동할 x좌표 전역변수

void MyInit() {
	glClearColor(1.0, 1.0, 1.0, 1.0); //배경-흰색으로 지정

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); //가시부피 영역
}

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT); //색버퍼 제거
	glColor3f(0.0, 0.5, 0.8); //모델 색깔 지정

	glBegin(GL_POLYGON);
	glVertex3f(-0.5 + mx, -0.5 + my, 0.0); //왼쪽 아래
	glVertex3f(0.5 + px, -0.5 + my, 0.0); //오른쪽 아래
	glVertex3f(0.5 + px, 0.5 + py, 0.0); //오른쪽 위
	glVertex3f(-0.5 + mx, 0.5 + py, 0.0); //왼쪽 위
	glEnd();
	glFlush();
}

void MyIdleU() { //위쪽방향키를 눌렀을때 실행되는 콜백함수
	Sleep(1000); //도형이 연속적으로 이동하는데에 일정한 시간차를 준다
	py += 0.1; //도형의 y좌표를 0.1씩 위쪽으로 이동
	my += 0.1;
	if (py > 0.5) { //윈도우 위쪽창을 벗어나지 않도록 한다
		py -= 0.1;
		my -= 0.1;
	}
	glutPostRedisplay();
}

void MyIdleD() { //아래쪽방향키를 눌렀을때 실행되는 콜백함수
	Sleep(1000); 
	py -= 0.1; //도형의 y좌표를 0.1씩 아래쪽으로 이동
	my -= 0.1;
	if (my < -0.5) { //윈도우 아래쪽창을 벗어나지 않도록 한다
		py += 0.1;
		my += 0.1;
	}
	glutPostRedisplay();
}

void MyIdleL() { //왼쪽방향키를 눌렀을때 실행되는 콜백함수
	Sleep(1000);
	px -= 0.1; //도형의 x좌표를 0.1씩 왼쪽으로 이동
	mx -= 0.1;
	if (mx < -0.5) { //윈도우 왼쪽창을 벗어나지 않도록 한다
		mx += 0.1;
		px += 0.1;
	}
	glutPostRedisplay();
}

void MyIdleR() { //오른쪽방향키를 눌렀을때 실행되는 콜백함수
	Sleep(1000);
	px += 0.1; //도형의 x좌표를 0.1씩 오른쪽으로 이동
	mx += 0.1;
	if (px > 0.5) { //윈도우오른쪽 창을 벗어나지 않도록 한다
		mx -= 0.1;
		px -= 0.1;
	}
	glutPostRedisplay();
}


void MySpecial(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP: //위쪽 방향키 푸시
		glutIdleFunc(MyIdleU); //MyIdleU콜백함수 등록
		break;
	case GLUT_KEY_DOWN: //아래쪽 방향키 푸시
		glutIdleFunc(MyIdleD); //MyIdleD콜백함수 등록
		break;
	case GLUT_KEY_LEFT: //왼쪽 방향키 푸시
		glutIdleFunc(MyIdleL); //MyIdleL콜백함수 등록
		break;
	case GLUT_KEY_RIGHT: //오른쪽 방향키 푸시
		glutIdleFunc(MyIdleR); //MyIdleR콜백함수 등록
		break;
	default:
		break;
	}
	glutPostRedisplay(); //디스플레이 함수 강제 호출 함수
}

int main(int argc, char** argv) {
	glutInit(&argc, argv); //window랑 os연결
	glutInitDisplayMode(GLUT_RGB); //디스플레이 모드 설정
	glutInitWindowSize(300, 300); //윈도우크기 설정
	glutInitWindowPosition(0, 0); //시작 지점 설정
	glutCreateWindow("Idle Callback");//윈도우 생성(이름)

	MyInit(); //윈도우 초기화
	glutDisplayFunc(MyDisplay); //디스플레이 콜백함수
	glutSpecialFunc(MySpecial); //방향키를 입력받기위해 키보드 기능 콜백 함수 등록

	glutMainLoop();
	return 0;
}