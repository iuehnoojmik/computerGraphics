/*************************************************************************/
/*                      HW#1 : 3D Sierpinski Gasket					     */
/*  작성자 : 김준희                              날짜 : 2022년 9월 22일  */
/*																		 */
/* 문제 정의 : 2D 시어핀스키 삼각형 구현코드를 참고하여 3D 시어핀스키    */
/*              삼각형을 구현하기. 윈도우 창 크기를 바꿔도 모델이        */
/*				왜곡되지 않도록 해준다.                                  */		
/*시어핀스키 삼각형: 정삼각형 각 변들의 중점을 이어서 새로운 정삼각형을  */ 
/*					만드는 것을 계속 반복하여 만든 프랙탈 도형           */
/* 기능 : 화면을 클릭할때마다 시어핀스키 삼각형이                        */
/*           (250, 200, 288)축을 따라서 30도씩 회전한다.                 */
/*                - - - - - - -                                          */
/*************************************************************************/
 
#include <GL/glut.h>
#include <stdlib.h>  //rand() 함수 사용 용도

void MyInit()
{
	glClearColor(1.0, 1.0, 1.0, 1.0); // 배경색 지정(흰색)
	glColor3f(1.0, 0.0, 0.0); // 시어핀스키 삼각형 색깔지정 (빨간색)

	glMatrixMode(GL_PROJECTION); //투영행렬 선택
	glLoadIdentity(); //현재 투영행렬을 항등행렬로 초기화

	glOrtho(0.0, 500.0, 0.0, 500.0, 0, -500); //3차원의 가시부피 영역 설정
}

void MyDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT); //색 버퍼 제거
	float vertices[4][3] = { { 0.0,0.0,433.0 },{ 250.0,0.0,0.0},{ 500.0,0.0,433.0},{250.0,408.0,288.0} }; // 초기 사면체 좌표(정사면체에 근사한 값)
	int i, j;
	float p[3] = { 500.0, 250.0, 100.0 };  // 임의로 찍은 포인트

	glRotatef(30.0, 250.0, 200.0, 288.0); //모델변환함수, (250,200,288)으로 지정된 축을 30도로 회전시킨다

	for (j = 0; j < 100000; j++) //점들의 출력을 1만번정도 반복한다
	{
		i = rand() % 4; // 사면체의 네 꼭짓점 중 한 점을 임의로 선택
		p[0] = (p[0] + vertices[i][0]) / 2.0;
		p[1] = (p[1] + vertices[i][1]) / 2.0;
		p[2] = (p[2] + vertices[i][2]) / 2.0;
		//임의로 찍은 포인트와 꼭짓점의 중점을 계산한다. 
		

		glBegin(GL_POINTS);
		glVertex3fv(p); // 위에서 계산한 정점들의 위치를 정의한다.
		glEnd();
	}
	
	glFlush(); 
}

void MyReshape(int NewWidth, int NewHeight) { //윈도우 창 크기 변환에 따른 왜곡을 없애주는 함수
	glViewport(0, 0, NewWidth, NewHeight); //뷰폿 크기를 변환 할때마다 그 크기를 뷰폿이라고 인식

	GLfloat Widthfactor = (GLfloat)NewWidth / (GLfloat)500; //현재 뷰폿의 가로길이를 main에서 지정한 윈도우 가로길이(500)로 나눠서 비율 얻기
	GLfloat Heightfactor = (GLfloat)NewHeight / (GLfloat)500; ////현재 뷰폿의 세로길이를 main에서 지정한 윈도우 세로길이(500)로 나눠서 비율 얻기
	
	glMatrixMode(GL_PROJECTION); //투영행렬 선택
	glLoadIdentity(); //투영행렬 초기화
	glOrtho(0.0*Widthfactor, 500.0*Widthfactor, 0.0* Heightfactor, 500.0*Heightfactor, 0.0, -500.0); //위에서 얻은 비율을 초기 가시부피 좌표에 곱해서 가시부피랑 뷰폿의 비율을 맞춰준다.
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv); //window os랑 연결
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //디스플레이 모드 설정
	glutInitWindowSize(500, 500); //윈도우 크기지정
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Sierpinski Gasket"); //윈도우 생성(이름)

	glutDisplayFunc(MyDisplay); //메인함수 밖에서 정의한 콜백함수들을 등록
	glutReshapeFunc(MyReshape);

	MyInit();

	glutMainLoop();
}

