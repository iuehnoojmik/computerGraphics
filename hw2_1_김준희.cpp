/*************************************************************************/
/*                  HW#2 : GLU Modeling – 2D Primitives	     	       */
/*  작성자 : 김준희                              날짜 : 2022년 9월 30일  */
/*																	   */
/* 문제 정의 : 2D Primitive들 구현해보기							       */
/*															           */
/* 기능 : Primitive들마다 주석처리 해제해주세요		                   */
/*		  Reshape 함수도 넣었습니다						               */
/*                - - - - - - -                                          */
/*************************************************************************/
#include <GL/glut.h>

void MyInit()
{
	glClearColor(1.0, 1.0, 1.0, 1.0); // 배경 색상 설정 (흰색)
	glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0); // 가시부피 설정
}

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT); //색 버퍼 제거
	glColor3f(0.0, 0.3, 0.6); //모델의 색깔 지정 (파란색)

	////1.Points
	//glPointSize(5); //점들의 상태변수 크기 설정
	//glBegin(GL_POINTS); 
	//glVertex3f(-0.5, -0.86, 0.0); //V0
	//glVertex3f(0.5, -0.86, 0.0); //V1
	//glVertex3f(1.0, 0.0, 0.0); //V2
	//glVertex3f(0.5, 0.86, 0.0); //V3
	//glVertex3f(-0.5, 0.86, 0.0); //V4
	//glVertex3f(-1.0, 0.0, 0.0); //V5
	//glEnd();
	//glFlush();

	////2. Lines
	//glBegin(GL_LINES); //V0와 V1, V2와 V3, V4와 V5를 연결해서 line으로 모델링
	//glVertex3f(-0.5, -0.86, 0.0); //V0
	//glVertex3f(0.5, -0.86, 0.0); //V1
	//glVertex3f(1.0, 0.0, 0.0); //V2
	//glVertex3f(0.5, 0.86, 0.0); //V3
	//glVertex3f(-0.5, 0.86, 0.0); //V4
	//glVertex3f(-1.0, 0.0, 0.0); //V5
	//glEnd();
	//glFlush();

	////3. LineStrip
	//glBegin(GL_LINE_STRIP); //제일 처음 지정한 좌표V0부터 마지막으로 지정한 좌표 V5까지 line으로 연결해서 모델링
	//glVertex3f(-0.5, -0.86, 0.0); //V0
	//glVertex3f(0.5, -0.86, 0.0); //V1
	//glVertex3f(1.0, 0.0, 0.0); //V2
	//glVertex3f(0.5, 0.86, 0.0); //V3
	//glVertex3f(-0.5, 0.86, 0.0); //V4
	//glVertex3f(-1.0, 0.0, 0.0); //V5
	//glEnd();
	//glFlush();

	////4. LineLoop
	//glBegin(GL_LINE_LOOP); //제일 처음 지정한 좌표V0부터 마지막으로 지정한 좌표 V5까지 line으로 연결+V0와 V5도 연결해서 모델링
	//glVertex3f(-0.5, -0.86, 0.0); //V0
	//glVertex3f(0.5, -0.86, 0.0); //V1
	//glVertex3f(1.0, 0.0, 0.0); //V2
	//glVertex3f(0.5, 0.86, 0.0); //V3
	//glVertex3f(-0.5, 0.86, 0.0); //V4
	//glVertex3f(-1.0, 0.0, 0.0); //V5
	//glEnd();
	//glFlush();

	////5. TriangleFan
	//glBegin(GL_TRIANGLE_FAN); //제일 처음 지정한 좌표V0와 나머지 좌표들 중 2개를 선택해서 삼각형들을 모델링
	//glVertex3f(-0.5, -0.86, 0.0); //V0
	//glVertex3f(2.0, -0.8, 0.0); //V1
	//glVertex3f(1.8, 0.0, 0.0); //V2
	//glVertex3f(1.7, 0.7, 0.0); //V3
	//glVertex3f(0.8, 1.0, 0.0); //V4
	//glVertex3f(0.0, 1.0, 0.0); //V5
	//glEnd();
	//glFlush();

	////6. Triangles
	//glBegin(GL_TRIANGLES); //좌표들을 앞에서부터 각각 3개씩 묶어서 삼각형을 모델링
	//glVertex3f(-0.5, -0.86, 0.0); //V0
	//glVertex3f(0.5, -0.86, 0.0); //V1
	//glVertex3f(1.0, 0.0, 0.0); //V2
	//glVertex3f(0.5, 0.86, 0.0); //V3
	//glVertex3f(-0.5, 0.86, 0.0); //V4
	//glVertex3f(-1.0, 0.0, 0.0); //V5
	//glEnd();
	//glFlush();

	////7. TriangleStrip
	//glBegin(GL_TRIANGLE_STRIP); //삼각형들을 길게 연결하여 모델링
	//glVertex3f(2.0, 0.0, 0.0); //V0
	//glVertex3f(1.5, 1.5, 0.0); //V1
	//glVertex3f(1.0, 0.2, 0.0); //V2
	//glVertex3f(0.0, 1.6, 0.0); //V3
	//glVertex3f(-0.5, 0.1, 0.0); //V4
	//glVertex3f(-1.5, 1.5, 0.0); //V5
	//glVertex3f(-2.0, 0.0, 0.0); //V5
	//glEnd();
	//glFlush();

	////9. Quads
	//glBegin(GL_QUADS); //좌표를 앞에서부터 각각4개씩 묶어서 사각형을 모델링
	//glVertex3f(1.5,-1.0, 0.0); //V0
	//glVertex3f(2.0, 0.0, 0.0); //V1
	//glVertex3f(1.0, 0.5, 0.0); //V2
	//glVertex3f(0.0, -1.0, 0.0); //V3 -사각형 1

	//glVertex3f(0.0, 0.0, 0.0); //V4
	//glVertex3f(0.0, 1.2, 0.0); //V5
	//glVertex3f(-1.2, 1.1, 0.0); //V6
	//glVertex3f(-1.7, 0.5, 0.0); //V7 -사각형 2
	//glEnd();
	//glFlush();

	////10. QuadStrip
	//glBegin(GL_QUAD_STRIP); //사각형들을 길게 연결하여 모델링
	//glVertex3f(1.5, -1.0, 0.0); //V0
	//glVertex3f(2.0, 0.0, 0.0); //V1
	//glVertex3f(0.0, -1.0, 0.0); //V2
	//glVertex3f(1.0, 0.5, 0.0); //V3
	//glVertex3f(0.0, 0.0, 0.0); //V4
	//glVertex3f(0.0, 1.2, 0.0); //V5
	//glVertex3f(-1.7, 0.5, 0.0); //V6
	//glVertex3f(-1.2, 1.1, 0.0); //V7
	//glEnd();
	//glFlush();
}

void MyReshape(int NewWidth, int NewHeight) { //윈도우 창 크기 변환에 따른 왜곡을 없애주는 함수
	glViewport(0, 0, NewWidth, NewHeight); //뷰폿 크기를 변환 할때마다 그 크기를 뷰폿이라고 인식

	GLfloat Widthfactor = (GLfloat)NewWidth / (GLfloat)500; //현재 뷰폿의 가로길이를 main에서 지정한 윈도우 가로길이(500)로 나눠서 비율 얻기
	GLfloat Heightfactor = (GLfloat)NewHeight / (GLfloat)500; ////현재 뷰폿의 세로길이를 main에서 지정한 윈도우 세로길이(500)로 나눠서 비율 얻기

	glMatrixMode(GL_PROJECTION); //투영행렬 선택
	glLoadIdentity(); //투영행렬 초기화
	glOrtho(-2.0 * Widthfactor, 2.0 * Widthfactor, -2.0 * Heightfactor, 2.0 * Heightfactor, -2.0, 2.0); //위에서 얻은 비율을 초기 가시부피 좌표에 곱해서 가시부피랑 뷰폿의 비율을 맞춰준다.
}

int main(int argc, char** argv) {
	glutInit(&argc, argv); //window os랑 연결
	glutInitDisplayMode(GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowSize(500, 500); // 윈도우 크기 설정
	glutInitWindowPosition(0, 0); // 시작 지점 지정
	glutCreateWindow("Graphics Primitives"); // 윈도우 생성

	glutDisplayFunc(MyDisplay); //콜백함수 등록
	glutReshapeFunc(MyReshape);

	MyInit();

	glutMainLoop();
	return 0;
}