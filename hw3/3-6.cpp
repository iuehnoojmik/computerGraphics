/*************************************************************************/
/*                HW#3-6  Time Callback 응용	     				     */
/*  작성자 : 김준희                              날짜 : 2022년 10월 7일  */
/*																		 */
/* 문제 정의 : Time 콜백 함수를 이용하여								 */
/*		     좌우로 움직이는 도형이 경계에 닿으면 색깔을 바꾸게 한다.	 */
/*									                                     */
/* 기능: 도형이 좌우로 각 경계에 닿을 때까지 0.1씩 연속으로 이동한다.	 */
/*     오른쪽 경계에 닿으면 빨간색, 왼쪽 경계에 닿으면 파란색으로 변한다.*/
/*      마우스의 왼쪽 키를 누르면 움직이는 도형이 멈춘다.			     */
/*      마우스의 오른쪽 키를 누르면 멈춰있던 도형이 움직인다.			 */
/*      도형 이동 중에 마우스 오른쪽 키를 눌러도 아무런 변화가 없다.     */
/*                - - - - - - -                                          */
/*************************************************************************/
#include <GL/glut.h>
float dx = 0.0; //도형이 이동할 x좌표 전역변수
GLboolean dir = true; //도형의 이동 방향변수, true-오른쪽, false-왼쪽
GLboolean click = false; //마우스 왼쪽키가 눌렸는지 확인하는 변수, true-왼쪽키 눌림, false-안눌림

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT); //색버퍼 제거

	glBegin(GL_POLYGON); //사각형 모델링, 초기 사각형은 왼쪽 중앙에 생성
	glVertex3f(-1.0 + dx, -0.5, 0.0); //왼쪽 아래점
	glVertex3f(0.0 + dx, -0.5, 0.0); //오른쪽 아래점
	glVertex3f(0.0 + dx, 0.5, 0.0); //오른쪽 윗점
	glVertex3f(-1.0 + dx, 0.5, 0.0); //왼쪽 윗점

	glEnd();
	glutSwapBuffers(); //버퍼를 스왑하여 유령현상 방지
}

void MyTimer(int value) {
	if (click == false) { //마우스 왼쪽키가 눌리지 않은 초기상태 or 마우스 오른쪽 키를 눌러서 도형이동을 재진행 시킨 경우
		if (dir == true) { //도형 진행방향이 오른쪽인 경우 (이동변수가 true)
			dx += 0.1; //x좌표를 증가시켜 도형을 오른쪽으로 0.1씩 이동시킨다.
			if (dx > 1.1) { //도형이 오른쪽 경계에 닿으면
				glClear(GL_COLOR_BUFFER_BIT); //색버퍼 초기화
				glColor3f(1.0, 0.0, 0.0); //도형을 빨간색으로 바꾼다
				dx -= 0.1; //x좌표를 0.1만큼 감소시켜 오른쪽 경계를 넘어가지 않도록 한다.
				dir = false; //이동변수를 false로 바꿔서 이동방향을 왼쪽으로 바꿔준다.
			}
		}

		else { //도형 진행방향이 왼쪽인 경우 (이동변수가 false)
			dx -= 0.1; //x좌표를 감소시켜 도형을 왼쪽으로 0.1씩 이동시킨다.
			if (dx < 0) { //도형이 왼쪽 경계에 닿으면
				glClear(GL_COLOR_BUFFER_BIT); //색버퍼 초기화
				glColor3f(0.0, 0.0, 1.0); //도형을 파란색으로 바꾼다
				dx += 0.1; //x좌표를 0.1만큼 증가시켜 왼쪽 경계를 넘어가지 않도록 한다.
				dir = true; //이동변수를 true로 바꿔서 이동방향을 왼쪽으로 바꿔준다.
			}
		}
	}

	//마우스 왼쪽키를 누르면 click==true가 되어 아무일도 발생하지 않는다. - 도형 이동 정지
	
	glutPostRedisplay(); //디스플레이 함수 강제 호출 함수
	glutTimerFunc(100, MyTimer, 1); //100msec 후에 호출, 인위적으로 발생시킨다
}void MyInit() {
	glClearColor(1.0, 1.0, 1.0, 1.0); //배경색상-흰색

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-1.0, 1.0, -1.0, 1.0, 1.0, -1.0); //가시부피 영역
}

void Left() { //마우스 왼쪽버튼을 누를 시 호출됨
	click = true; //왼쪽 키가 눌렸으므로 click 변수를 true로 설정
}

void RIGHT() { //마우스 오른쪽버튼을 누를 시 호출됨
	click = false; //오른쪽 키가 눌렸으므로 click 변수를 false로 설정
} 

void mouseCallback(int Button, int State, int x, int y) {
	if ((Button == GLUT_LEFT_BUTTON) && (State == GLUT_DOWN)) { //마우스 왼쪽 버튼 푸시
		glutIdleFunc(Left); //왼쪽버튼을 눌렀을때 작용하는 idle콜백함수 등록
	}
	if ((Button == GLUT_RIGHT_BUTTON) && (State == GLUT_DOWN)) { //마우스 오른쪽 버튼 푸시
		glutIdleFunc(RIGHT); //오른쪽버튼을 눌렀을때 작용하는 idle콜백함수 등록
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv); //window랑 os연결
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); //디스플레이 모드 설정
	glutInitWindowSize(300, 300); //윈도우크기 설정
	glutInitWindowPosition(0, 0); //시작 지점 설정
	glutCreateWindow("Timer Callback"); //윈도우 생성(이름)

	MyInit(); //윈도우 초기화
	glutDisplayFunc(MyDisplay); //디스플레이 콜백함수 등록
	glutTimerFunc(100, MyTimer, 1); //타이머 콜백함수 등록
	glutMouseFunc(mouseCallback); //마우스 버튼을 입력받는 콜백 함수 등록

	glutMainLoop();
	return 0;
}