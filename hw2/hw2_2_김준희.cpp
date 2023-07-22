/*************************************************************************/
/*              HW#2 : GLU Modeling – 3D Primitives					     */
/*  작성자 : 김준희                              날짜 : 2022년 9월 30일  */
/*																		 */
/* 문제 정의 : 3D Primitives 구현해보기-구, 실린더, 디스크, 부분디스크   */
/*															             */
/*									                                     */
/* 기능 :  MyCreateList와 MyDisplay에 있는 주석들을 각 도형별로 해제     */
/*         해서 네가지 도형을 모두 확인할 수 있습니다                    */
/*                - - - - - - -                                          */
/*************************************************************************/
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>


GLUquadricObj* qobj = gluNewQuadric(); // 새로운 Quadric 생성
int list[4]; //도형 4가지를 넣을 리스트

void MyInit()
{
	glClearColor(0.0, 0.0, 0.0, 1.0); // 배경 색상 설정 (검정)
	glOrtho(-5.0, 5.0, -5.0, 5.0, -5.0, 5.0); // 가시부피 설정

	//조명함수
	GLfloat mat_ambient[] = { 0.5, 0.4, 0.3, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	GLfloat model_ambient[] = { 0.5, 0.4, 0.3, 1.0 };

	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);

	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
}
 
// Display List 생성
void MyCreateList() {

	//1. Sphere
	list[0] = glGenLists(1); // DisplayList 선언, 0번째 리스트에 도형 생성
	glNewList(list[0], GL_COMPILE); //도형 리스트 1개를 컴파일 완료버전으로 생성
	gluQuadricDrawStyle(qobj, GLU_SILHOUETTE); // Draw Style 지정-실루엣
	gluQuadricNormals(qobj, GLU_SMOOTH); // 법선벡터 제어
	gluQuadricOrientation(qobj, GLU_OUTSIDE); // 법선벡터 내부 및 외부 등과 같은 방향 지정
	gluQuadricTexture(qobj, GL_FALSE); // Texture 좌표 사용할 것인지에 대한 여부
	gluSphere(qobj, 5.0, 150, 150); // Sphere 모델 생성


	//2. Cylinder
	//list[1] = list[0] + 1; //1번 리스트에 도형 생성
	//glNewList(list[1], GL_COMPILE); //도형 리스트 1개를 컴파일 완료버전으로 생성
	//gluQuadricDrawStyle(qobj, GLU_LINE); //  Draw Style 지정-라인
	//gluQuadricNormals(qobj, GLU_SMOOTH); // 법선벡터 제어
	//gluQuadricOrientation(qobj, GLU_OUTSIDE); // 법선벡터 내부 및 외부 등과 같은 방향 지정
	//gluQuadricTexture(qobj, GL_FALSE); // Texture 좌표 사용할 것인지에 대한 여부
	//gluCylinder(qobj, 2.0, 0.0, 5.0, 30, 8); //cylinder-원뿔모양으로 조정


	//3. Disk
	//list[2] = list[1] + 1; //2번 리스트에 도형 생성
	//glNewList(list[1], GL_COMPILE); //도형 리스트 1개를 컴파일 완료버전으로 생성
	//gluQuadricDrawStyle(qobj, GLU_FILL); // Draw Style 지정-fill
	//gluQuadricNormals(qobj, GLU_SMOOTH); // 법선벡터 제어
	//gluQuadricOrientation(qobj, GLU_OUTSIDE); // 법선벡터 내부 및 외부 등과 같은 방향 지정
	//gluQuadricTexture(qobj, GL_FALSE); // Texture 좌표 사용할 것인지에 대한 여부
	//gluDisk(qobj, 0.5, 1.0, 30, 5); //Disk 모델 생성


	//4. Partial Disk
	//list[3] = list[2] + 1; //3번 리스트에 도형 생성
	//glNewList(list[1], GL_COMPILE); //도형 리스트 1개를 컴파일 완료버전으로 생성
	//gluQuadricDrawStyle(qobj, GLU_POINT); // Draw Style 지정-점
	//gluQuadricNormals(qobj, GLU_SMOOTH); // 법선벡터 제어
	//gluQuadricOrientation(qobj, GLU_OUTSIDE); // 법선벡터 내부 및 외부 등과 같은 방향 지정
	//gluQuadricTexture(qobj, GL_FALSE); // Texture 좌표 사용할 것인지에 대한 여부
	//gluPartialDisk(qobj, 0.5, 1.0, 60, 15, 0.0, 230.0); //Partial Disk 모델 생성-중심각이 230도

	glEndList();
}

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0); //모델링 하는 도형의 색깔을 흰색으로 지정
	
    glMatrixMode(GL_MODELVIEW); //모델뷰행렬 선택
	glLoadIdentity();

	glEnable(GL_LIGHTING); //조명모드 활성화
	glShadeModel(GL_SMOOTH); //상태변수 설정-그림자 색칠

	glutSwapBuffers();

	
	//1. Sphere - 리스트 0번에 저장된 sphere 호출
	glCallList(list[0]); 

	//2. Cylinder - 리스트 1번에 저장된 cylinder 호출
	//glRotatef(-40.0, 1.0, 0.0, 0.0);
	//glCallList(list[1]); 


	//3. Disk - 리스트 2번에 저장된 disk 호출
	//glCallList(list[2]); 


	//4.Partial Disk - 리스트 3번에 저장된 partial disk 호출
	//glCallList(list[3]); 

	glFlush();
}

void MyReshape(int NewWidth, int NewHeight) { //윈도우 창 크기 변환에 따른 왜곡을 없애주는 함수
	glViewport(0, 0, NewWidth, NewHeight); //뷰폿 크기를 변환 할때마다 그 크기를 뷰폿이라고 인식

	GLfloat Widthfactor = (GLfloat)NewWidth / (GLfloat)700; //현재 뷰폿의 가로길이를 main에서 지정한 윈도우 가로길이(500)로 나눠서 비율 얻기
	GLfloat Heightfactor = (GLfloat)NewHeight / (GLfloat)700; ////현재 뷰폿의 세로길이를 main에서 지정한 윈도우 세로길이(500)로 나눠서 비율 얻기

	glMatrixMode(GL_PROJECTION); //투영행렬 선택
	glLoadIdentity(); //투영행렬 초기화
	glOrtho(-5.0 * Widthfactor, 5.0 * Widthfactor, -5.0 * Heightfactor, 5.0 * Heightfactor, -5.0, 5.0); //위에서 얻은 비율을 초기 가시부피 좌표에 곱해서 가시부피랑 뷰폿의 비율을 맞춰준다.
}

int main(int argc, char** argv) {
		
	glutInit(&argc, argv); //window os랑 연결
	glutInitDisplayMode(GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowSize(700, 700); // 윈도우 크기 설정
	glutInitWindowPosition(0, 0); // 시작 지점 지정
	glutCreateWindow("Graphics Primitives"); // 윈도우 생성

	glutDisplayFunc(MyDisplay); //콜백함수 등록
	glutReshapeFunc(MyReshape); //왜곡 조정함수 등록
	MyCreateList(); // Display List 생성

	MyInit();

	glutMainLoop();
	return 0;
}