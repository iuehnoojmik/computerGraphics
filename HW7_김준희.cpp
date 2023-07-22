/***************************************************************************************************/
/*										hw#7 : 조명 종합                                           */
/*  작성자 : 김준희                          날짜 : 2022년 12월 2일                                */
/*																								   */
/* 문제 정의 : 전신깡통로봇을 달리도록 모델링하고 조명을 입힌다.								   */
/* 기능:																					       */
/*       R or r : 로봇이 달리는 모습이 되도록 해준다.			 							       */
/*       S or s : 움직이는 중인 신체를 일시정지한다.										       */
/***************************************************************************************************/

#include <GL/glut.h>
#include <gl/glu.h>
#include <GL/gl.h>

float head, body, neck, left_arm, right_arm, left_sh, right_sh, left_leg, right_leg, left_knee, right_knee, st = 0.0;
GLboolean check2 = false;


void myinit() {
	GLfloat global_ambient[] = { 0.1, 0.1, 0.1, 1.0 }; //전역 주변반사(빛 감쇠 효과 x)
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient); //전역주변반사
 
	//0번 광원 ---------------------------------------------------------------
	GLfloat light0_ambient[] = { 0.5, 0.4, 0.3, 1.0 }; //0번 광원 주변반사 RGBA
	GLfloat light0_diffuse[] = { 0.5, 0.4, 0.3, 1.0 }; //0번 광원 난반사 RGBA
	GLfloat light0_specular[] = { 1.0, 1.0, 1.0, 1.0 }; //0번 광원 정반사 RGBA
	
	GLfloat Light0_Position[] = { 0.0, 0.0, 5.0, 1.0 }; //0번 광원위치
	GLfloat Light0_Direction[] = { 0.0, 0.7, -5.0 }; //0번 광원 방향
	GLfloat Light0_Cutoff[] = { 40.0 }; //0번 광원 각도

	//0번 광원 특성할당
	glEnable(GL_LIGHT0); //0번 광원 활성화
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient); //0번 광원 주변반사 설정
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse); //0번 광원 난반사 설정
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular); //0번 광원 정반사 설정

	glLightfv(GL_LIGHT0, GL_POSITION, Light0_Position); //스포트라이트
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, Light0_Direction); //방향
	glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, Light0_Cutoff); //각도
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 1.0); //코사인 승수


	//1번 광원 ---------------------------------------------------------------
	GLfloat light1_ambient[] = { 0.0, 0.0, 0.3, 1.0 }; //1번 광원 주변반사 RGBA
	GLfloat light1_diffuse[] = { 0.5, 0.2, 0.3, 1.0 }; //1번 광원 난반사 RGBA
	GLfloat light1_specular[] = { 0.0, 0.0, 0.0, 1.0 }; //1번 광원 정반사 RGBA

	GLfloat Light1_Position[] = { 0.0, 0.0, 5.0, 1.0 }; //1번 광원위치
	GLfloat Light1_Direction[] = { 0.0, 0.3, -1.0 }; //1번 광원 방향
	GLfloat Light1_Cutoff[] = { 15.0 }; //1번 광원 각도

	glEnable(GL_LIGHT1); //1번 광원 활성화
	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient); //1번 광원 주변반사 설정
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse); //1번 광원 난반사 설정
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular); //1번 광원 정반사 설정

	glLightfv(GL_LIGHT1, GL_POSITION, Light1_Position); //스포트라이트
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, Light1_Direction); //방향
	glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, Light1_Cutoff); //각도
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 1.0); //코사인 승수

	glShadeModel(GL_SMOOTH); //고러드 셰이딩
	glEnable(GL_DEPTH_TEST); //깊이 버퍼
	glEnable(GL_LIGHTING); //조명 활성화

	//물체 특성
	GLfloat my_material_ambient[] = { 0.3, 0.3, 0.3, 1.0 }; //물체의 주변반사 RGBA
	GLfloat my_material_diffuse[] = { 0.8, 0.8, 0.8, 1.0 }; //물체의 난반사 RGBA
	GLfloat my_material_specular[] = { 0.0, 0.0, 1.0, 1.0 }; //물체의 정반사 RGBA
	GLfloat my_material_shininess[] = { 90.0 }; //광택계수
	
	//물체 특성할당
	glMaterialfv(GL_FRONT, GL_AMBIENT, my_material_ambient); 
	glMaterialfv(GL_FRONT, GL_DIFFUSE, my_material_diffuse);   
	glMaterialfv(GL_FRONT, GL_SPECULAR, my_material_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, my_material_shininess);

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE); //시점벡터 계산x (시점위치 무한대)
}

void mydisplay(void) {

	gluLookAt(5.0, 1.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); //정면

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	GLUquadricObj* qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, GLU_FILL); //Draw Style 지정-Solid

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	/////////////////// 머리 //////////////////////////
	glPushMatrix();//원점푸시
	glTranslatef(0.0, 1.8, 0.0);//머리 위치 지정
	glPushMatrix();//머리위치푸시
	glColor3f(0.9, 0.5, 0.0); //머리색깔지정
	glRotatef(-90.0, 1.0, 0.0, 0.0);//머리를에서 볼 수 있도록 회전
	glRotatef((GLfloat)head, 1.0, 0.0, 0.0); //머리를 움직일 수 있도록 전역변수 이용
	gluCylinder(qobj, 0.8, 0.6, 1.0, 50, 1); //머리를 실린더 타입으로 모델링
	glPopMatrix();//머리팝

	/////////////////// 목 //////////////////////////
	glPushMatrix();//목위치 푸시
	glColor3f(0.0, 0.0, 0.7); //목색깔 지정
	glRotatef(90.0, 1.0, 0.0, 0.0);//목을 정면에서 볼 수 있도록 회전
	glRotatef((GLfloat)neck, 1.0, 0.0, 0.0); //목을 움직일 수 있도록 전역변수 이용
	gluCylinder(qobj, 0.2, 0.2, 0.3, 30, 1); //목을 실린더 타입으로 모델링
	glPopMatrix();//목 팝

	/////////////////// 몸통 //////////////////////////
	glTranslatef(0.0, -0.3, 0.0);//몸통위치 치정
	glPushMatrix(); //몸통 위치 푸시
	glColor3f(0.0, 0.0, 0.8); //몸통색깔지정
	glRotatef(90.0, 1.0, 0.0, 0.0); //몸통을 정면에서 볼 수 있도록 회전
	glRotatef((GLfloat)body, 1.0, 0.0, 0.0); //몸통을 움직일 수 있도록 전역변수 이용
	gluCylinder(qobj, 1.0, 1.0, 1.5, 70, 1);//몸통을 실린더 타입으로 모델링
	glPopMatrix();//몸통 팝, 최상위 스택은 몸통위치인 상태

	/////////////////// 왼쪽 다리 //////////////////////////
	glPushMatrix();//현재 몸통 위치 푸시
	glRotatef((GLfloat)left_leg, -0.1, 0.0, 0.0); //다리를 회전할 수 있도록 전역변수 이용
	glTranslatef(-0.3, -2.1, 0.0); //왼쪽허벅지 위치 지정
	glPushMatrix();//왼쪽 허벅지 위치 푸시
	glColor3f(1.0, 0.4, 0.7); //왼쪽 허벅지 색깔 지정
	glRotatef(90.0, -1.0, 0.0, 0.0); //다리를 정면에서 볼 수 있도록 회전
	gluCylinder(qobj, 0.2, 0.2, 0.6, 20, 1);//다리를 실린더 타입으로 모델링
	glPopMatrix();//왼쪽 허벅지 팝

	glPushMatrix();
	glRotatef((GLfloat)left_knee, 1.0, 0.0, 0.0); //무릎을 움직일 수 있도록 전역변수 이용
	glTranslatef(0.0, -0.6, 0.0); //왼쪽 정강이 위치 지정
	glPushMatrix();//왼쪽정강이 위치 푸시
	glColor3f(1.0, 0.6, 0.0); //왼쪽 정강이 색깔 지정
	glRotatef(90.0, -1.0, 0.0, 0.0); //다리를 정면에서 볼 수 있도록 회전
	gluCylinder(qobj, 0.2, 0.2, 0.6, 20, 1); //다리를 실린더 타입으로 모델링
	glPopMatrix();//왼쪽정강이 팝

	glTranslatef(-0.1, -0.15, 0.1); //왼쪽 발 위치 지정
	glColor3f(0.0, 0.0, 1.0); //왼쪽 발 색깔 지정
	glRotatef(90.0, -1.0, 0.0, 0.0); //발을 정면에서 볼 수 있도록 회전
	gluCylinder(qobj, 0.3, 0.3, 0.15, 30, 1);//발을 실린더 타입으로 모델링

	glPopMatrix();
	glPopMatrix();//정강이 팝, 최종 스택은 몸통 위치인 상태

	/////////////////// 오른쪽 다리 //////////////////////////
	glPushMatrix();//몸통위치저장	
	glRotatef((GLfloat)right_leg, -0.1, 0.0, 0.0); //오른쪽 허벅지
	glTranslatef(0.3, -2.1, 0.0);
	glPushMatrix();
	glColor3f(1.0, 0.4, 0.7);
	glRotatef(90.0, -1.0, 0.0, 0.0);
	gluCylinder(qobj, 0.2, 0.2, 0.6, 20, 1);
	glPopMatrix();

	glPushMatrix();
	glRotatef((GLfloat)right_knee, 1.0, 0.0, 0.0); //무릎을 움직일 수 있도록 전역변수 이용
	glTranslatef(0.0, -0.6, 0.0); //오른쪽 정강이
	glPushMatrix();
	glColor3f(1.0, 0.6, 0.0);
	glRotatef(90.0, -1.0, 0.0, 0.0);
	gluCylinder(qobj, 0.2, 0.2, 0.6, 20, 1);
	glPopMatrix();

	glTranslatef(0.1, -0.15, 0.1); //오른쪽 발
	glColor3f(0.0, 0.0, 1.0);
	glRotatef(90.0, -1.0, 0.0, 0.0);
	gluCylinder(qobj, 0.3, 0.3, 0.15, 30, 1);

	glPopMatrix(); 
	glPopMatrix(); 
	glPopMatrix();

	/////////////////// 왼쪽 팔 //////////////////////////
	glPushMatrix(); //원점 푸시
	glTranslatef(-1.1, 0.7, 0.1); //왼쪽 어깨 위치
	glRotatef((GLfloat)left_sh, 1.0, 0.0, 0.0);
	glRotatef(90, -1.0, 0.0, 0.0);
	glRotatef(5, 0.0, 1.0, 0.0); //신체와 비슷하도록 어깨를 회전시킴
	glPushMatrix();//왼쪽 어깨 푸시
	glColor3f(0.0, 1.0, 0.0); //왼쪽 어깨 색깔 지정
	gluCylinder(qobj, 0.2, 0.2, 0.8, 20, 1); //팔을 실린더 타입으로 모델링
	glPopMatrix();//왼쪽 팔 팝

	glPushMatrix(); //원점 푸시
	glRotatef((GLfloat)left_arm, -0.7, -0.2, 0.0); //팔을 회전할 수 있도록 전역변수 이용
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
	glPopMatrix();
	//전부 다 pop시켜 원점으로 돌아간다

	/////////////////// 오른쪽 팔 //////////////////////////
	glPushMatrix();
	glTranslatef(1.1, 0.7, 0.1); //오른쪽 어깨
	glRotatef((GLfloat)right_sh, 1.0, 0.0, 0.0);
	glRotatef(90, -1.0, 0.0, 0.0);
	glRotatef(5, 0.0, -1.0, 0.0);
	glPushMatrix();
	glColor3f(0.0, 1.0, 0.0);
	gluCylinder(qobj, 0.2, 0.2, 0.8, 20, 1);
	glPopMatrix();

	glPushMatrix();//오른어깨
	glRotatef((GLfloat)right_arm, -0.7, 0.2, 0.0); //오른쪽 팔 하완 
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
	glPopMatrix();
	//전부 다 팝

	glutSwapBuffers();
}

void mytimer2(int value) { //R 또는 r을 눌렀을 때 실행되는 타이머 함수
	if (st == 0) { //정지상태가 아닐 때
		if (check2) {

			//오른팔과 왼다리가 앞으로 나갈 때
			if (right_arm < 150.0) //오른팔이 150도보다 작으면
			{
				right_sh += 0.3; //어깨각도와 팔 각도를 증가
				right_arm += 5.0;
				if (left_knee < 90.0) { //오른쪽 무릎이 90도보다 작을 때 
					left_leg += 1.0; //무릎과 다리의 각도 증가
					left_knee += 3.0;

					//왼팔과 오른다리는 제자리로
					if (left_arm > 0.0) { //왼팔의 각도가 0보다 클 때
						left_sh -= 0.3; //왼팔과 왼어깨의 각도를 감소
						left_arm -= 5.0;
						if (right_knee > 0.0) { //오른다리의 각도가 0보다 클 때
							right_leg -= 1.0; //오른다리와 오른무릎의 각도를 감소
							right_knee -= 3.0;

							head += 0.2; //머리, 목, 어깨 각도를 증가시켜서 역동성 부여
							neck += 0.2;
							body -= 0.2;
						}
					}

				}
				else {
				}
			}
			else
				check2 = false;
		}
		else {
			//오른팔과 왼다리가 제자리로 갈 때
			if (right_arm > 0.0)
			{
				right_sh -= 0.3;
				right_arm -= 5.0;
				if (left_knee > 0.0) {
					left_leg -= 1.0;
					left_knee -= 3.0;

					//왼팔과 오른다리는 앞으로
					if (left_arm < 150.0) {
						left_sh += 0.3;
						left_arm += 5.0;
						if (right_knee < 90) {
							right_leg += 1.0;
							right_knee += 3.0;

							head -= 0.2;
							neck -= 0.2;
							body += 0.2;
						}
					}

				}
				else {
					return;
				}
			}
			else {
				check2 = true;
				return;
			}
		}
		glutPostRedisplay();
	}

}

void mytimer6(int value) { //s나 s를 눌렀을때 실행되는 타이머 함수, 아무것도 실행되지 않기 때문에 움직이는 신체를 멈춘다.
	if (st == 1) {

	}
	glutPostRedisplay();
	glutTimerFunc(40, mytimer6, 1);
}

void myidle() { //R 또는 r을 눌렀을때 실행되는 아이들 콜백함수
	Sleep(10);
	glutTimerFunc(40, mytimer2, 1); //mytimer2함수 실행
}

//R이나 r을 누르면 아이들콜백함수 실행
//S나 s를 누르면 mytimer6 실행
void mykeyboard(unsigned char key, int x, int y) { 
	switch (key) {
	case 'R': case 'r':
		st = 0;
		glutIdleFunc(myidle);
		break;
	case 'S': case 's':
		st = 1;
		glutTimerFunc(50, mytimer6, 1);
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void myreshape(int newwidth, int newheight) {
	glViewport(0, 0, (GLsizei)newwidth, (GLsizei)newheight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLfloat)newwidth / (GLfloat)newheight, 5.0, 100);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Can Robot");

	myinit();
	glutDisplayFunc(mydisplay);
	glutReshapeFunc(myreshape);
	glutKeyboardFunc(mykeyboard);

	glutMainLoop();
	return 0;
}