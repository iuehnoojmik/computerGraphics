/*************************************************************************/
/*                    HW#4-1  로봇 손-팔 모델링     	   			     */
/*  작성자 : 김준희                              날짜 : 2022년 10월 7일  */
/*																		 */
/* 문제 정의 : 행렬스택과 타이머함수를 이용하여 손가락과 팔관절을 가진 	 */
/*			   로봇 손-팔을 모델링			                             */
/* 기능:															     */
/*      키보드 1: 가운데 손가락 접었다 펼치기 반복                       */
/*      키보드 2: 왼쪽 손가락 접었다 펼치기 반복                         */
/*      키보드 3: 오른쪽 손가락 접었다 펼치기 반복                       */
/*      키보드 S또는 s: 움직이는 손가락 멈추기		                     */
/*      왼쪽 마우스: 어깨,팔꿈치,손가락을 전부 움직여서 집는 모양 만들기 */
/*      오른쪽 마우스: 어깨,팔꿈치,손가락을 원래대로 되돌리기            */
/*************************************************************************/
#include<iostream>
using namespace std;

#include <GL/glut.h>
static int shoulder, elbow = 0;
static int fin1_1, fin1_2, fin1_3 = 0;
static int fin2_1, fin2_2, fin2_3 = 0;
static int fin3_1, fin3_2, fin3_3 = 0;
GLboolean work = false;

void MyInit() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 0.0); // 배경 색상 설정 (검정)
	glOrtho(-5.0, 5.0, -5.0, 5.0, -5.0, 5.0);
}

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	gluLookAt(0.7, 0.5, 1.5, 1.0, 0.0, 0.0, 0.0, 2.0, 0.0); //로봇팔을 보는 시점 설정

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix(); //원점 푸시
	//팔 상완
	glTranslatef(-1.0, 0.0, 0.0);
	glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0); //팔이 이동한 상태에서 회전하도록 조정
	glTranslatef(1.0, 0.0, 0.0); //팔을 원점으로 돌린다
	glPushMatrix(); 
	glScalef(2.0, 0.4, 1.0); //팔의 크기를 x축으로 2배, y축으로 0.4배 확대한다.
	glutWireCube(1.0); //팔을 와이어큐브로 모델링
	glPopMatrix(); //scale한 스택을 pop
	
	//팔 하완
	glTranslatef(1.0, 0.0, 0.0); 
	glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0); //팔꿈치가 회전할 수 있도록 축 조정
	glTranslatef(1.0, 0.0, 0.0); //상완에서 위치를 조정
	glPushMatrix();
	glScalef(2.0, 0.4, 1.0);
	glutWireCube(1.0);
	glPopMatrix();

	//1번 손가락
	glPushMatrix();
	glTranslatef(1.0, 0.0, 0.0); //손가락 중 팔에 붙어있는 마디
	glRotatef((GLfloat)fin1_1, 0.0, 0.0, 1.0);
	glTranslatef(0.2, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.5, 0.2, 0.2);
	glutWireCube(1.0);

	glRotatef((GLfloat)fin1_2, 0.0, 0.0, 1.0); //손가락 중 가운데 마디
	glTranslatef(1.0, 0.0, 0.0);
	glutWireCube(1.0);

	glRotatef((GLfloat)fin1_3, 0.0, 0.0, 1.0); //손가락 중 가장 끝 마디
	glTranslatef(1.0, 0.0, 0.0);
	glutWireCube(1.0);
	glPopMatrix();
	glPopMatrix();

	//2번 손가락
	glPushMatrix();
	glTranslatef(1.0, 0.0, 0.0); //손가락 중 팔에 붙어있는 마디
	glRotatef(50, 0.0, 1.0, 0.0);
	glRotatef((GLfloat)fin2_1, 0.0, 0.0, 1.0);
	glTranslatef(0.2, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.5, 0.2, 0.2);
	glutWireCube(1.0);

	glRotatef((GLfloat)fin2_2, 0.0, 0.0, 1.0); //손가락 중 가운데 마디
	glTranslatef(1.0, 0.0, 0.0);
	glutWireCube(1.0);

	glRotatef((GLfloat)fin2_3, 0.0, 0.0, 1.0); //손가락 가장 끝 마디
	glTranslatef(1.0, 0.0, 0.0);
	glutWireCube(1.0);
	glPopMatrix();
	glPopMatrix();

	//3번 손가락
	glPushMatrix();
	glTranslatef(1.0, 0.0, 0.0); //손가락 중 팔에 붙어있는 마디
	glRotatef(-50, 0.0, 1.0, 0.0);
	glRotatef((GLfloat)fin3_1, 0.0, 0.0, 1.0);
	glTranslatef(0.2, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.5, 0.2, 0.2);
	glutWireCube(1.0);

	glRotatef((GLfloat)fin3_2, 0.0, 0.0, 1.0); //손가락 중 가운데 마디
	glTranslatef(1.0, 0.0, 0.0);
	glutWireCube(1.0);

	glRotatef((GLfloat)fin3_3, 0.0, 0.0, 1.0); //손가락 가장 끝 마디
	glTranslatef(1.0, 0.0, 0.0);
	glutWireCube(1.0);
	glPopMatrix();
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();
	glutSwapBuffers();
}

void timer1(int value) { //1번키보드를 누르면 실행되는 타이머함수 (가운데 손가락)
	if (work == true && shoulder == 0) {
		if (fin1_1 < 100) { //손에 붙어있는 마디가 100도가 될때까지 움직인다
			if (fin1_2 < 10) { //먼저 첫번째와 두번째 마디를 움직이도록 조정
				fin1_1 += 5;
				fin1_2 += 1;
			}
			else if (fin1_2 >= 10) { //일정 각도 후에는 세번째 마디도 움직이도록 조정
				fin1_1 += 5;
				fin1_2 += 1;
				fin1_3 += 2;
			}
			glutPostRedisplay();
		}

		else if (fin1_1 == 100) { //붙어있는 마디가 100도가 된다면
			fin1_1 = 460; //조정을 위해 360도를 더한 460도로 설정해준다
			glutPostRedisplay();
		}

		else if (fin1_1 > 360) { //460도인 상태에서 순차적으로 다시 손가락을 되돌린다
			if (fin1_2 <= 10) {
				fin1_1 -= 5;
				fin1_2 -= 1;
			}
			else if (fin1_2 > 10) {
				fin1_1 -= 5;
				fin1_2 -= 1;
				fin1_3 -= 2;
			}
			glutPostRedisplay();
		}

		else if (fin1_1 == 360) { //마디가 다시 0(+360)도가 된다면 마디들의 각도를 리셋해준다
			fin1_1 = 0;
			fin1_2 = 0;
			fin1_3 = 0;
			glutPostRedisplay();
		}

		glutTimerFunc(50, timer1, 0);
	}
}

void timer2(int value) {
	if (work == true && shoulder == 0) {
		if (fin2_1 < 100) {
			if (fin2_2 < 10) {
				fin2_1 += 5;
				fin2_2 += 1;
			}
			else if (fin2_2 >= 10) {
				fin2_1 += 5;
				fin2_2 += 1;
				fin2_3 += 2;
			}
			glutPostRedisplay();
		}

		else if (fin2_1 == 100) {
			fin2_1 = 460;
			glutPostRedisplay();
		}

		else if (fin2_1 > 360) {
			if (fin2_2 <= 10) {
				fin2_1 -= 5;
				fin2_2 -= 1;
			}
			else if (fin2_2 > 10) {
				fin2_1 -= 5;
				fin2_2 -= 1;
				fin2_3 -= 2;
			}
			glutPostRedisplay();
		}

		else if (fin2_1 == 360) {
			fin2_1 = 0;
			fin2_2 = 0;
			fin2_3 = 0;
			glutPostRedisplay();
		}

		glutTimerFunc(50, timer2, 0);
	}
}

void timer3(int value) {
	if (work == true && shoulder == 0) {
		if (fin3_1 < 100) {
			if (fin3_2 < 10) {
				fin3_1 += 5;
				fin3_2 += 1;
			}
			else if (fin3_2 >= 10) {
				fin3_1 += 5;
				fin3_2 += 1;
				fin3_3 += 2;
			}
			glutPostRedisplay();
		}

		else if (fin3_1 == 100) {
			fin3_1 = 460;
			glutPostRedisplay();
		}

		else if (fin3_1 > 360) {
			if (fin3_2 <= 10) {
				fin3_1 -= 5;
				fin3_2 -= 1;
			}
			else if (fin3_2 > 10) {
				fin3_1 -= 5;
				fin3_2 -= 1;
				fin3_3 -= 2;
			}
			glutPostRedisplay();
		}

		else if (fin3_1 == 360) {
			fin3_1 = 0;
			fin3_2 = 0;
			fin3_3 = 0;
			glutPostRedisplay();
		}

		glutTimerFunc(50, timer3, 0);
	}
}

void timer4(int value) { //S나 s를 실행했을때 실행되는 타이머 함수, 움직임을 멈춘다.
	if (work == false) {}

	glutPostRedisplay();
	glutTimerFunc(50, timer4, 0);
}

void timer5(int value) { //마우스 왼쪽을 클릭하면 실행되는 타이머 함수
	if (work == true) { 
		if (fin1_1 >= 120) //손가락 첫번째 마디가 120도가 되면 함수를 중단시킨다
			work = false;
		else {
			if (elbow >= 25) { //팔꿈치 각도가 25도가 넘으면 손가락들도 굽혀준다.
				if (fin1_2 > 10) { //두번째 마디들이 12도 이상 구부려지면 세번째 마디들도 구부려준다
					fin1_1 += 3;
					fin2_1 += 3;
					fin3_1 += 3;

					fin1_2 += 2;
					fin2_2 += 2;
					fin3_2 += 2;

					fin1_3 += 1;
					fin2_3 += 1;
					fin3_3 += 1;
				}
				else if(fin1_1 > 40) { //첫번째 마디들이 40도 이상 구부려지면 두번째 마디들도 구부려준다
					fin1_1 += 3;
					fin2_1 += 3;
					fin3_1 += 3;

					fin1_2 += 3;
					fin2_2 += 3;
					fin3_2 += 3;
				}
				else { //손가락들의 첫번째 마디를 먼저 구부려준다
					fin1_1 += 3;
					fin2_1 += 3;
					fin3_1 += 3;
				}
			}
			else if (shoulder >= 10) { //어깨 각도가 10도가 넘어가면 팔꿈치 각도도 증가시킨다.
				elbow += 1;
			}
			else //제일 처음 실행되는 반복문, 어깨 각도를 증가시킨다.
				shoulder += 1;
		}
		glutPostRedisplay();
		glutTimerFunc(50, timer5, 0);
	}
}

void timer6(int value) {  //마우스 오른쪽을 클릭하면 실행되는 타이머 함수
	if (work == true) {
		if (shoulder == 0)
			work = false;

		else {
			if (elbow == 0) { //팔꿈치가 다 펴지면 어깨도 원래대로 펴준다
				shoulder -= 5;
			}
			else if (fin1_1 == 0) { //손가락 마디들이 원상태가 된다면 팔꿈치도 다시 펴준다
				elbow -= 5;
			}
			else {
				if (fin1_1 <= 40) { //두번째 마디들도 원상복구 된 상태, 첫번째 마디들도 마저 펴준다
					fin1_1 -= 3;
					fin2_1 -= 3;
					fin3_1 -= 3;
				}
				else if (fin1_2 <= 10) { //세번째 마디들이 다 원상복구 된 상태, 첫번째와 두번째 마디들을 마저 펴준다
					fin1_1 -= 3;
					fin2_1 -= 3;
					fin3_1 -= 3;

					fin1_2 -= 3;
					fin2_2 -= 3;
					fin3_2 -= 3;
				}
				else { //손가락 마디들을 다시 펴준다
					fin1_1 -= 3;
					fin2_1 -= 3;
					fin3_1 -= 3;

					fin1_2 -= 2;
					fin2_2 -= 2;
					fin3_2 -= 2;

					fin1_3 -= 1;
					fin2_3 -= 1;
					fin3_3 -= 1;
				}
			}
		}
		glutPostRedisplay();
		glutTimerFunc(50, timer6, 0);
	}
}

void MyKeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case '1':
		work = true;
		glutTimerFunc(50, timer1, 0);
		break;
	case '2':
		work = true;
		glutTimerFunc(50, timer2, 0);
		break;
	case '3':
		work = true;
		glutTimerFunc(50, timer3, 0);
		break;
	case '4':
		work = true; //4번을 클릭하면 손가락 타이머 함수를 전부 실행시켜서 모든 손가락이 움직일 수 있도록 해준다
		glutTimerFunc(50, timer1, 0);
		glutTimerFunc(50, timer2, 0);
		glutTimerFunc(50, timer3, 0);
	case 'S': case 's':
		work = false; //실행중인 함수들을 중단시키고, 4번 타이머 함수를 실행시켜 중단을 유지한다.
		glutTimerFunc(50, timer4, 0);
		break;
	default:
		break;
	}

	glutPostRedisplay();
}

void mouseCallback(int Button, int State, int x, int y) {
	if ((Button == GLUT_LEFT_BUTTON) && (State == GLUT_DOWN)) { //마우스 왼쪽 버튼
		if (shoulder == 0) {
			work = false; //일이 실행중이라는 상태를 false로 중단시킨다
			//모든 손가락 관절들을 제자리로 리셋시킨다
			fin1_1 = 0; 
			fin1_2 = 0; 
			fin1_3 = 0; 
			fin2_1 = 0;
			fin2_2 = 0; 
			fin2_3 = 0; 
			fin3_1 = 0; 
			fin3_2 = 0; 
			fin3_3 = 0;
			glutPostRedisplay();
			work = true; //일을 다시 진행중 상태로 만든다.
			glutTimerFunc(50, timer5, 0); 
		}
	}
	if ((Button == GLUT_RIGHT_BUTTON) && (State == GLUT_DOWN)) { //마우스 오른쪽 버튼
		if (fin1_1 >= 120) { //왼쪽을 클릭했을 때 최종 fin1_1은 120도인 상태
			work = true;
			glutTimerFunc(50, timer6, 0);
		}
	}
}

void MyReshape(int NewWidth, int NewHeight) {
	glViewport(0, 0, NewWidth, NewHeight);
	GLfloat WidthFactor = (GLfloat)NewWidth / (GLfloat)1000;
	GLfloat HeightFactor = (GLfloat)NewHeight / (GLfloat)500;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-5.0 * WidthFactor, 5.0 * WidthFactor, -5.0 * HeightFactor, 5.0 * HeightFactor, -5.0, 5.0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv); //window랑 os연결
	glutInitDisplayMode(GLUT_RGB); //디스플레이 모드 설정
	glutInitWindowSize(1000, 500); //윈도우크기 설정
	glutInitWindowPosition(0, 0); //시작 지점 설정
	glutCreateWindow("Robot Hand"); //윈도우 생성(이름)

	MyInit();
	glutDisplayFunc(MyDisplay); //디스플레이 콜백함수 등록
	glutReshapeFunc(MyReshape);
	glutKeyboardFunc(MyKeyboard);
	glutMouseFunc(mouseCallback);

	glutMainLoop();
	return 0;
}
