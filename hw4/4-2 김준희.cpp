/***************************************************************************************************/
/*                            HW#4-2 : 전신 Can Robot 모델링                                       */
/*  작성자 : 김준희                          날짜 : 2021년 11월 4일                                */
/*																								   */
/* 문제 정의 : 전신깡통로봇을 모델링하고 메뉴를 선택하면 해당 신체를 움직였다가 돌아오도록 만든다. */
/* 기능: Head: 머리를 우->좌로 까딱하고 제자리로 돌아온다.									       */
/*       Left Arm : 왼쪽 하단 팔을 가슴쪽으로 올렸다가 다시 내린다.							       */
/*       Right Arm : 왼쪽 하단 팔을 가슴쪽으로 올렸다가 다시 내린다.						       */
/*       Left Leg : 왼쪽 다리를 앞으로 찼다가 다시 내린다.									       */
/*       Right Leg : 오른쪽 다리를 앞으로 찼다가 다시 내린다.								       */
/*       S or s : 움직이는 중인 신체를 일시정지한다.										       */
/***************************************************************************************************/
#include <GL/glut.h>
#include <stdlib.h>

int head, left_arm, right_arm, left_leg, right_leg, st = 0;
int check1 = 0;
GLboolean check2 = false, check3 = false, check4 = false, check5 = false;

void MyDisplay(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	GLUquadricObj* qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, GLU_LINE); //Draw Style 지정-라인
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	///////////////////// 머리 //////////////////////////
	glPushMatrix();//원점푸시
	glTranslatef(0.0, 1.8, 0.0);//머리 위치 지정
	glPushMatrix();//머리위치푸시
	glColor3f(0.9, 0.5, 0.0); //머리색깔지정
	glRotatef(-90.0, 1.0, 0.0, 0.0);//머리를에서 볼 수 있도록 회전
	glRotatef((GLfloat)head, 0.0, 1.0, 0.0); //머리 회전할 수 있도록 전역변수 이용
	gluCylinder(qobj, 0.8, 0.6, 1.0, 50, 1); //머리를 실린더 타입으로 모델링
	glPopMatrix();//머리팝

	///////////////////// 목 //////////////////////////
	glPushMatrix();//목위치 푸시
	glColor3f(0.0, 0.0, 0.7); //목색깔 지정
	glRotatef(90.0, 1.0, 0.0, 0.0);//목을 정면에서 볼 수 있도록 회전
	gluCylinder(qobj, 0.2, 0.2, 0.3, 30, 1); //목을 실린더 타입으로 모델링
	glPopMatrix();//목 팝
	
	///////////////////// 몸통 //////////////////////////
	glTranslatef(0.0, -0.3, 0.0);//몸통위치 치정
	glPushMatrix(); //몸통 위치 푸시
	glColor3f(0.0, 0.0, 0.8); //몸통색깔지정
	glRotatef(90.0, 1.0, 0.0, 0.0); //몸통을 정면에서 볼 수 있도록 회전
	gluCylinder(qobj, 1.0, 1.0, 1.5, 70, 1);//몸통을 실린더 타입으로 모델링
	glPopMatrix();//몸통 팝, 최상위 스택은 몸통위치인 상태

	///////////////////// 왼쪽 다리 //////////////////////////
	glPushMatrix();//현재 몸통 위치 푸시
	glRotatef((GLfloat)left_leg, -0.1, 0.0, 0.0); //다리를 회전할 수 있도록 전역변수 이용
	glTranslatef(-0.3, -2.1, 0.0); //왼쪽허벅지 위치 지정
	glPushMatrix();//왼쪽 허벅지 위치 푸시
	glColor3f(1.0, 0.4, 0.7); //왼쪽 허벅지 색깔 지정
	glRotatef(90.0, -1.0, 0.0, 0.0); //다리를 정면에서 볼 수 있도록 회전
	gluCylinder(qobj, 0.2, 0.2, 0.6, 20, 1);//다리를 실린더 타입으로 모델링
	glPopMatrix();//왼쪽 허벅지 팝

	glTranslatef(0.0, -0.6, 0.0); //왼쪽 정강이 위치 지정
	glPushMatrix();//왼쪽정강이 위치 푸시
	glColor3f(1.0, 0.6, 0.0); //왼쪽 정강이 색깔 지정
	glRotatef(90.0, -1.0, 0.0, 0.0); //다리를 정면에서 볼 수 있도록 회전
	gluCylinder(qobj, 0.2, 0.2, 0.6, 20, 1); //다리를 실린더 타입으로 모델링
	glPopMatrix();//왼쪽정강이 팝

	glTranslatef(-0.1, -0.15, 0.0); //왼쪽 발 위치 지정
	glColor3f(0.0, 0.0, 1.0); //왼쪽 발 색깔 지정
	glRotatef(90.0, -1.0, 0.0, 0.0); //발을 정면에서 볼 수 있도록 회전
	gluCylinder(qobj, 0.3, 0.3, 0.15, 30, 1);//발을 실린더 타입으로 모델링

	glPopMatrix(); //정강이 팝, 최종 스택은 몸통 위치인 상태

	///////////////////// 오른쪽 다리 //////////////////////////
	glPushMatrix();//몸통위치저장	
	glRotatef((GLfloat)right_leg, 0.1, 0.0, 0.0); //오른쪽 허벅지
	glTranslatef(0.3, -2.1, 0.0);
	glPushMatrix();
	glColor3f(1.0, 0.4, 0.7);
	glRotatef(90.0, -1.0, 0.0, 0.0);
	gluCylinder(qobj, 0.2, 0.2, 0.6, 20, 1); 
	glPopMatrix();

	glTranslatef(0.0, -0.6, 0.0); //오른쪽 정강이
	glPushMatrix();
	glColor3f(1.0, 0.6, 0.0);
	glRotatef(90.0, -1.0, 0.0, 0.0);
	gluCylinder(qobj, 0.2, 0.2, 0.6, 20, 1);
	glPopMatrix();

	glTranslatef(0.1, -0.15, 0.0); //오른쪽 발
	glColor3f(0.0, 0.0, 1.0);
	glRotatef(90.0, -1.0, 0.0, 0.0);
	gluCylinder(qobj, 0.3, 0.3, 0.15, 30, 1);

	glPopMatrix();
	glPopMatrix(); 

	///////////////////// 왼쪽 팔 //////////////////////////
	glPushMatrix(); //원점 푸시
	glTranslatef(-1.1, 0.7, 0.3); //왼쪽 어깨 위치
	glRotatef(90, -1.0, 0.0, 0.0); 
	glRotatef(5, 0.0, 1.0, 0.0); //신체와 비슷하도록 어깨를 회전시킴
	glPushMatrix();//왼쪽 어깨 푸시
	glColor3f(0.0, 1.0, 0.0); //왼쪽 어깨 색깔 지정
	gluCylinder(qobj, 0.2, 0.2, 0.8, 20, 1); //팔을 실린더 타입으로 모델링
	glPopMatrix(); //왼쪽 팔 팝

	glPushMatrix(); //원점 푸시
	glRotatef((GLfloat)left_arm, 0.0, -1.0, 0.0); //팔을 회전할 수 있도록 전역변수 이용
	glTranslatef(0.0, 0.0, -0.8); //왼쪽 팔 하완 위치 지정
	glPushMatrix(); //팔 하완 위치 푸시
	glColor3f(1.0, 0.6, 0.0); //팔 색깔 지정
	gluCylinder(qobj, 0.2, 0.2, 0.8, 20, 1); //팔을 실린더 타입으로 모델링
	glPopMatrix(); //팔 하완 팝

	glTranslatef(0.0, 0.0, -0.1); //왼손 위치 지정
	glPushMatrix(); //손 위치 푸시
	glColor3f(1.0, 0.6, 0.0); //손 색깔 지정
	gluSphere(qobj, 0.2, 10, 10); //손을 구 타입으로 모델링

	glPopMatrix();
	glPopMatrix();
	glPopMatrix(); //전부 다 pop시켜 원점으로 돌아간다

	///////////////////// 오른쪽 팔 //////////////////////////
	glPushMatrix(); 
	glTranslatef(1.1, 0.7, 0.3); //오른쪽 어깨
	glRotatef(90, -1.0, 0.0, 0.0);
	glRotatef(5, 0.0, -1.0, 0.0);
	glPushMatrix();
	glColor3f(0.0, 1.0, 0.0);
	gluCylinder(qobj, 0.2, 0.2, 0.8, 20, 1);
	glPopMatrix();

	glPushMatrix();//오른어깨
	glRotatef((GLfloat)right_arm, 0.0, 1.0, 0.0); //오른쪽 팔 하완 
	glTranslatef(0.0, 0.0, -0.8);
	glPushMatrix();
	glColor3f(1.0, 0.6, 0.0);
	gluCylinder(qobj, 0.2, 0.2, 0.8, 20, 1);
	glPopMatrix();

	glTranslatef(0.0, 0.0, -0.1); //오른손
	glPushMatrix();
	glColor3f(1.0, 0.6, 0.0);
	gluSphere(qobj, 0.2, 10, 10);


	glPopMatrix();
	glPopMatrix();
	glPopMatrix(); //전부 다 팝

	glutSwapBuffers();
}

void MyTimer1(int Value) { //Head를 눌렀을 때 실행되는 타이머 함수
	if (st == 0) {
		if (check1 == 0) { //머리를 왼쪽으로 30도 기울이게 한다.
			if (head < 30.0) {
				head += 3.0;
			}
			else //머리가 30도가 되면 다음으로 넘어가도록 check1을 1로 바꾼다.
				check1 = 1;
		}
		if (check1 == 1) { //머리를 오른쪽으로 30도 기울이게 한다.
			if (head > -30.0) {
				head -= 3.0;
			}
			else //머리가 30도가 되면 다음으로 넘어가도록 check1을 1로 바꾼다.
				check1 = 2;
		}
		if (check1 == 2) { //머리를 제자리로 돌아가도록 한다.
			if (head < 0) {
				head += 3.0;
			}
			else
				return;
		}

		glutPostRedisplay();
		glutTimerFunc(40, MyTimer1, 1);
	}
}

void MyTimer2(int Value) { //Right Arm을 눌렀을 때 실행되는 타이머 함수
	if (st == 0) {
		if (check2) { //오른쪽 팔을 상체쪽으로 50도 올리게 한다.
			if (right_arm < 50.0)
			{
				right_arm += 3.0;
			}

			else
				check2 = false;

		}
		else { //오른쪽 팔이 50도가 되면 다시 제자리로 돌아오도록 한다.
			if (right_arm > 0.0)
			{
				right_arm -= 3.0;
			}
		}

		glutPostRedisplay();
		glutTimerFunc(40, MyTimer2, 1);
	}

}

void MyTimer3(int Value) { //Left Arm을 눌렀을 때 실행되는 타이머 함수
	if (st == 0) {
		if (check3) { //왼쪽 팔을 상체쪽으로 50도 올리게 한다.
			if (left_arm < 50.0)
			{
				left_arm += 3.0;
			}

			else
				check3 = false;

		}
		else { //왼쪽 팔이 50도가 되면 다시 제자리로 돌아오도록 한다.
			if (left_arm > 0.0)
			{
				left_arm -= 3.0;
			}
		}

		glutPostRedisplay();
		glutTimerFunc(40, MyTimer3, 1);
	}
}

void MyTimer4(int Value) { //Right Leg를 눌렀을 때 실행되는 타이머 함수
	if (st == 0) {
		if (check4) { //오른쪽 다리를 30도 앞으로 차게 한다.
			if (right_leg < 30.0)
			{
				right_leg += 3.0;
			}

			else
				check4 = false;

		}
		else { //오른쪽 다리가 30도가 되면 다시 제자리로 돌아오도록 한다.
			if (right_leg > 0.0)
			{
				right_leg -= 3.0;
			}
		}

		glutPostRedisplay();
		glutTimerFunc(40, MyTimer4, 1);
	}

}

void MyTimer5(int Value) { //Left Leg를 눌렀을 때 실행되는 타이머 함수
	if (st == 0) {
		if (check5) { //왼쪽 다리를 30도 앞으로 차게 한다.
			if (left_leg < 30.0)
			{
				left_leg += 3.0;
			}
			else
				check5 = false;

		}
		else { //왼쪽 다리가 30도가 되면 다시 제자리로 돌아오도록 한다.
			if (left_leg > 0.0)
			{
				left_leg -= 3.0;
			}
		}

		glutPostRedisplay();
		glutTimerFunc(40, MyTimer5, 1);
	}

}

void MyTimer6(int Value) { //S나 s를 눌렀을때 실행되는 타이머 함수, 아무것도 실행되지 않기 때문에 움직이는 신체를 멈춘다.
	if (st == 1) {

	}
	glutPostRedisplay();
	glutTimerFunc(40, MyTimer6, 1);
	
	st = 0;
}

void MyKeyboard(unsigned char key, int x, int y) { //S나 s를 누르면 MyTimer 6 실행
	switch (key) {
	case 'S': case 's':
		st = 1;
		glutTimerFunc(50, MyTimer6, 1);
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void MyMainMenu(int entryID) {  //메인메뉴 콜백함수
	if (entryID == 1) { 
		check1 = 0;
		glutTimerFunc(40, MyTimer1, 1); //Head를 누르면 MyTimer1을 실행
	}
	else if (entryID == 2) {
		check2 = true;
		glutTimerFunc(40, MyTimer2, 1); //Right Arm을 누르면 MyTimer2를 실행
	}
	else if (entryID == 3) {
		check3 = true;
		glutTimerFunc(40, MyTimer3, 1); //Left Arm을 누르면 MyTimer3을 실행
	}
	else if (entryID == 4) {
		check4 = true;
		glutTimerFunc(40, MyTimer4, 1); //Right Leg를 누르면 MyTimer4를 실행
	}
	else if (entryID == 5) {
		check5 = true;
		glutTimerFunc(40, MyTimer5, 1); //Left Leg를 누르면 MyTimer5를 실행
	}

	glutPostRedisplay();
}

void MyInit() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 0.0); // 배경 색상 설정 (검정)
	GLint MyMainID = glutCreateMenu(MyMainMenu);  //메인 메뉴 만들기
	glutAddMenuEntry("Head", 1);
	glutAddMenuEntry("Right Arm", 2);
	glutAddMenuEntry("Left Arm", 3);
	glutAddMenuEntry("Right Leg", 4);
	glutAddMenuEntry("Left Leg", 5); //해당 신체 부위에 맞는 메뉴 생성
	glutAttachMenu(GLUT_RIGHT_BUTTON);  //마우스 오른쪽 버튼 클릭하면 메뉴 창 뜸
}

void MyReshape(int NewWidth, int NewHeight) { 
	glViewport(0, 0, NewWidth, NewHeight);
	GLfloat WidthFactor = (GLfloat)NewWidth / (GLfloat)600;
	GLfloat HeightFactor = (GLfloat)NewHeight / (GLfloat)800;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-5.0 * WidthFactor, 5.0 * WidthFactor, -5.0 * HeightFactor, 5.0 * HeightFactor, -5.0, 5.0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(600, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Can Robot");

	MyInit();
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	glutKeyboardFunc(MyKeyboard);

	glutMainLoop();
	return 0;
}