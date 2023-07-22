/*************************************************************************/
/*                HW#3-4  Menu Callback 응용	     				     */
/*  작성자 : 김준희                              날짜 : 2022년 10월 7일  */
/*																		 */
/* 문제 정의 : 메뉴 콜백 함수를 이용하여								 */
/*	           각 메뉴에 따른 새로운 도형을 그린다						 */
/*									                                     */
/* 기능: Draw@@@: 메뉴를 선택 후 하부 메뉴인 Small@@@와 Large@@@ 중	     */
/*       하나를 선택하면 메뉴 크기에 맞는 @@@도형 생성			         */
/*       Change Color: 하부메뉴인 Red, Green, Blue중 하나를 선택하면	 */
/*                     선택한 색깔에 맞도록 도형 색깔 변경			     */
/*       Exit: 윈도우 창 종료										     */
/*                - - - - - - -                                          */
/*************************************************************************/
#include <GL/glut.h>
#include <stdlib.h>

int shape = 1; //도형메뉴의 콜백함수 인자값. 디폴트는 1번인 Sphere
int color = 1; //Change color메뉴의 콜백함수 인자값. 디폴트는 1번인 Red
int size = 1; //Size의 콜백함수 인자값. 디폴트는 1번인 small

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT); //색버퍼 초기화
	if (color == 1) //Change color에서 Red 선택시 color변수는 1
		glColor3f(1.0, 0.0, 0.0); //도형을 빨간색으로 바꾼다
	else if (color == 2) //Change color에서 Green 선택시 color변수는 2
		glColor3f(0.0, 1.0, 0.0); //도형을 초록색으로 바꾼다
	else if (color == 3)  //Change color에서 Blue 선택시 color변수는 3
		glColor3f(0.0, 0.0, 1.0); //도형을 파란색으로 바꾼다

	if (shape == 1) { //DrawSphere 선택시 shape 변수는 1
		if(size==1) //하위메뉴에서 SmallSphere를 선택했다면 size 변수는 1
			glutWireSphere(0.3, 30, 30); //작은sphere를 wire로 그린다
		else //하위메뉴에서 LargeSphere를 선택했다면 size 변수는 2
			glutWireSphere(0.8, 30, 30); //큰sphere를 wire로 그린다
	}
	
	else if (shape == 2) { //DrawTorus 선택시 shape 변수는 2
		if(size==1) //하위메뉴에서 SmallTorus를 선택했다면 size 변수는 1
			glutWireTorus(0.1, 0.3, 40, 30); //작은Torus를 wire로 그린다
		else //하위메뉴에서 LargeTorus를 선택했다면 size 변수는 2
			glutWireTorus(0.2, 0.6, 40, 30); //큰Torus를 wire로 그린다
	}

	else if (shape == 3) { //DrawTeapot 선택시 shape 변수는 3
		if (size == 1) //하위메뉴에서 SmallTeapot를 선택했다면 size 변수는 1
			glutWireTeapot(0.3); //작은Teapot을 wire로 그린다
		else //하위메뉴에서 LargeTeapot를 선택했다면 size 변수는 2
			glutWireTeapot(0.6); //큰Teapot을 wire로 그린다
	}

	glFlush();
}

void MyMainMenu(int entryID) { //메인메뉴 콜백함수
	if (entryID == 5) //5번째 메뉴 선택
		exit(0); //윈도우 종료
	glutPostRedisplay(); //디스플레이 함수 강제 호출 함수
}

void Sphere(int entryID) {
	shape = 1; //DrawSphere메뉴를 선택했을 경우 shape를 1로 지정

	if (entryID == 1) //하위메뉴인 SmallSphere를 선택하여 ID값을 1로 전달받은 경우
		size = 1; //size변수는 1
	else //하위메뉴에서 LargeSphere를 선택한 경우
		size = 2; //size변수는 2

	glutPostRedisplay(); //디스플레이 함수 강제 호출 함수
}void Torus(int entryID) {
	shape = 2; //DrawTorus메뉴를 선택했을 경우 shape를 2로 지정

	if (entryID == 1) //하위메뉴인 SmallTorus를 선택하여 ID값을 1로 전달받은 경우
		size = 1; //size변수는 1
	else //하위메뉴에서 LargeTorus를 선택한 경우
		size = 2; //size변수는 2

	glutPostRedisplay(); //디스플레이 함수 강제 호출 함수
}void Teapot(int entryID) {
	shape = 3; //DrawTeapot메뉴를 선택했을 경우 shape를 3으로 지정

	if (entryID == 1) //하위메뉴인 SmallTeapot을 선택하여 ID값을 1로 전달받은 경우
		size = 1; //size변수는 1
	else  //하위메뉴에서 LargetTeapot을 선택한 경우
		size = 2; //size변수는 2

	glutPostRedisplay();  //디스플레이 함수 강제 호출 함수
}void ChangeColor(int entryID) {
	if (entryID == 1) //ChangeColor메뉴에서 Red를 선택하여 1을 전달받은 경우
		color = 1; //color 변수는 1
	else if (entryID == 2)  //ChangeColor메뉴에서 Green을 선택하여 2를 전달받은 경우
		color = 2; //color 변수는 2
	else if (entryID == 3)  //ChangeColor메뉴에서 Blue를 선택하여 3을 전달받은 경우
		color = 3; //color 변수는 3

	glutPostRedisplay();  //Display이벤트 강제로 발생시킴
}void MyInit() {
	glClearColor(1.0, 1.0, 1.0, 1.0); //배경색상-흰색
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); //가시부피 영역

	GLint SphereID = glutCreateMenu(Sphere); //DrawSphere메뉴 콜백함수 등록
	glutAddMenuEntry("Smalll Sphere", 1);
	glutAddMenuEntry("Large Sphere", 2); //DrawSphere메뉴의 하위메뉴 생성, Sphere함수에 각 정수값을 전달한다 

	GLint TorusID = glutCreateMenu(Torus); //DrawTorus메뉴 콜백함수 등록
	glutAddMenuEntry("Small Torus", 1);
	glutAddMenuEntry("Large Torus", 2); //DrawTorus메뉴의 하위메뉴 생성, Torus함수에 각 정수값을 전달한다 


	GLint TeapotID = glutCreateMenu(Teapot); //DrawTeapot메뉴 콜백함수 등록
	glutAddMenuEntry("Small Teapot", 1);
	glutAddMenuEntry("Large Teapot", 2); //DrawTeapot메뉴의 하위메뉴 생성, Teapot함수에 각 정수값을 전달한다 

	GLint ChangeColorID = glutCreateMenu(ChangeColor); //ChangeColor메뉴 콜백함수 등록
	glutAddMenuEntry("Red", 1);
	glutAddMenuEntry("Green", 2);
	glutAddMenuEntry("Blue", 3); //ChangeColor메뉴의 하위메뉴 생성, ChangeColor함수에 각 정수값을 전달한다 

	GLint MyMainID = glutCreateMenu(MyMainMenu);  //메인메뉴 콜백함수 등록, 유일ID값 가짐
	glutAddSubMenu("Draw Sphere", SphereID); //하위메뉴가 있는 Draw Sphere 메뉴, Sphere메뉴를 만들때 메뉴 아이디값인 SphereID가 리턴되었다
	glutAddSubMenu("Draw Torus", TorusID); //하위메뉴가 있는 Draw Torus 메뉴, Sphere메뉴를 만들때 메뉴 아이디값인 TorusID가 리턴되었다
	glutAddSubMenu("Draw Teapot", TeapotID); //하위메뉴가 있는 Draw Teapot 메뉴, Sphere메뉴를 만들때 메뉴 아이디값인 TeapotID가 리턴되었다
	glutAddSubMenu("Change Color", ChangeColorID); //하위메뉴가 있는 Change Color 메뉴, Sphere메뉴를 만들때 메뉴 아이디값인 ChangeColorID가 리턴되었다
	glutAddMenuEntry("EXIT", 5); //하위 메뉴가 없는 EXIT, 선택시 메인메뉴 콜백함수에 5를 전달

	glutAttachMenu(GLUT_RIGHT_BUTTON); //마우스 오른쪽 버튼을 누르면 메뉴가 나타남
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);  //window랑 os연결
	glutInitDisplayMode(GLUT_RGB); //디스플레이 모드 설정
	glutInitWindowSize(300, 300); //윈도우크기 설정
	glutInitWindowPosition(0, 0); //윈도우 시작 지점 설정
	glutCreateWindow("Menu Callback"); //윈도우 생성(이름)

	MyInit(); //윈도우 초기화
	glutDisplayFunc(MyDisplay); //디스플레이 콜백함수 등록

	glutMainLoop(); 
	return 0;
}