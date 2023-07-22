/*************************************************************************/
/*                   HW#3-3  Mouse Callback 응용	   				     */
/*  작성자 : 김준희                              날짜 : 2022년 10월 7일  */
/*																		 */
/* 문제 정의 : 마우스 콜백 함수를 이용하여								 */
/*	        마우스의 특정 버튼을 누르면 도형을 이동 또는 정지하도록 한다 */
/*									                                     */
/* 기능: 마우스왼쪽버튼: 도형이 오른쪽으로 0.1씩 연속으로 이동	         */
/*       마우스왼쪽버튼: 오른쪽으로 이동 중인 도형을 정지			     */
/*   ㄴ이동 중인 도형은 오른쪽 윈도우 창에 닿으면 더이상 이동하지 않음   */
/*   ㄴ도형의 좌표가 윈도우 창 내 어디든 있어도 마우스버튼 동작이        */
/*      작동한다는 것을 확인하기 위해 #3-2의 키보드 콜백 함수 재구현     */
/*                - - - - - - -                                          */
/*************************************************************************/
#include <GL/glut.h>
#include <stdlib.h> //도형 이동에 시간차를 주기 위해 sleep함수를 사용하는데, sleep이 포함된 라이브러리

float px, py = 0.0; //y좌표 전역변수
float mx, my = 0.0; //x좌표 전역변수

void MyInit() {
	glClearColor(1.0, 1.0, 1.0, 1.0); ////배경색상-흰색

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); //가시부피영역설정
}

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.5, 0.5, 0.5); //모델 색상 - 회색

	glBegin(GL_POLYGON);
	glVertex3f(-0.5 + mx, -0.5 + my, 0.0); //왼쪽 아래
	glVertex3f(0.5 + px, -0.5 + my, 0.0); //오른쪽 아래
	glVertex3f(0.5 + px, 0.5 + py, 0.0); //오른쪽 위
	glVertex3f(-0.5 + mx, 0.5 + py, 0.0); //왼쪽 위
	glEnd();
	glFlush();
}

void MySpecial(int key, int x, int y) { //#3-2에서 구현한 키보드 동작 함수
	switch (key) {
	case GLUT_KEY_UP:
		py += 0.1;
		my += 0.1;
		if (py > 0.5) {
			py -= 0.1;
			my -= 0.1;
		}
		break;
	case GLUT_KEY_DOWN:
		py -= 0.1;
		my -= 0.1;
		if (my < -0.5) {
			py += 0.1;
			my += 0.1;
		}
		break;
	case GLUT_KEY_LEFT:
		px -= 0.1;
		mx -= 0.1;
		if (mx < -0.5) {
			mx += 0.1;
			px += 0.1;
		}
		break;
	case GLUT_KEY_RIGHT:
		px += 0.1;
		mx += 0.1;
		if (px > 0.5) {
			mx -= 0.1;
			px -= 0.1;
		}
		break;
	case GLUT_KEY_PAGE_UP:
		mx -= 0.1;
		px += 0.1;
		my -= 0.1;
		py += 0.1;
		if (mx < -0.5 || px > 0.5 || my < -0.5 || py > 0.5) {
			mx += 0.1;
			px -= 0.1;
			my += 0.1;
			py -= 0.1;
			break;
		}
		break;
	case GLUT_KEY_PAGE_DOWN:
		if (mx - px > 0.8)
			break;
		mx += 0.1;
		px -= 0.1;
		my += 0.1;
		py -= 0.1;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void Left() { //마우스 왼쪽버튼을 누를 시 호출되는 함수 (sleep함수를 사용하기 위해 아이들 함수 사용)
	mx += 0.1; //x좌표 전역변수들을 0.1씩 증가시켜서 도형을 오른쪽으로 이동시킨다
	px += 0.1;
	if (mx > 0.5) { //x전역변수들이 0.5보다 커져서 윈도우 창 오른쪽에 닿으면)
		mx -= 0.1; //좌표전역변수를 0.1만큼 다시 증가시켜서 윈도우 창을 벗어나지 않도록 한다
		px -= 0.1;
	}
	Sleep(1000); //sleep함수를 이용하여 도형이 연속적으로 이동하는 것에 시간차를 준다
	glutPostRedisplay(); //디스플레이 함수 강제 호출 함수
}

void Right() { // 마우스 오른쪽버튼을 누를 시 호출되는 함수
	Sleep(1000);
	return; //아무것도 수행하지 않는다>>도형을 멈추도록 한다
}

void mouseCallback(int Button, int State, int x, int y) {
	if ((Button == GLUT_LEFT_BUTTON) && (State == GLUT_DOWN)) { //마우스 왼쪽 버튼 푸시
		glutIdleFunc(Left); //왼쪽버튼을 눌렀을때 작용하는 idle콜백함수 등록
	}

	if ((Button == GLUT_RIGHT_BUTTON) && (State == GLUT_DOWN)) { //마우스 오른쪽 버튼 푸시
		glutIdleFunc(Right); //오른쪽버튼을 눌렀을때 작용하는 idle콜백함수 등록
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv); //window랑 os연결
	glutInitDisplayMode(GLUT_RGB); //디스플레이 모드 설정
	glutInitWindowSize(300, 300); //윈도우크기 설정
	glutInitWindowPosition(0, 0); //시작 지점 설정
	glutCreateWindow("Mouse Callback"); //윈도우 생성(이름)

	MyInit(); //윈도우 초기화
	glutDisplayFunc(MyDisplay); //디스플레이 콜백함수 등록
	glutSpecialFunc(MySpecial);
	glutMouseFunc(mouseCallback); //마우스 버튼을 입력받는 콜백 함수 등록

	glutMainLoop();
	return 0;
}