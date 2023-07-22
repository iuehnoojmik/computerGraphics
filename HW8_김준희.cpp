/***************************************************************************************************/
/*										hw#8 :  종합                                               */
/*  작성자 : 김준희                          날짜 : 2022년 12월 18일                               */
/*																								   */
/* 문제 정의 :   트리와 전구를 모델링하고 트리의 전구색이 변하는 효과를 준다.     	    		   */
/*  콜백프로그래밍: Display(화면출력), Reshape(윈도우크기조절,위치이동), Keyboard(시점변환에 사용) */
/*                  Menu(전구효과를 끄고키는메뉴콜백), Idle(조명효과타이머 함수 부를때 사용)       */
/*                  Timer(조명 색깔을 변환시킬때 사용)                                             */
/*  모델변환: 나무모델링과 별 모델링에 Translatef, Rotatef를 사용하여 원하는 모양이 나오게 함      */
/*  시점변환: 변수와 키보드콜백을 변환하여 시점변환이 가능하도록 함                                */
/*  투영변환: Reshape함수에 원근투영변환을 사용하여 물체에 원근감 부여                             */
/*  뷰폿변환: Reshape함수에 뷰폿변환을 사용하여 윈도우 크기조절시에도 객체들의 왜곡을 방지         */
/*  가시성검사: 모델링한 트리에 후면제거 사용                                                      */
/*  조명: 트리에 발광체 조명을 삽입                                                                */
/*  텍스처: 트리에 나무와 잎 텍스쳐 맵핑                                                           */
/***************************************************************************************************/
/* 기능:																					       */
/*       <키보드>                                                                                  */
/*       Q or q : 시점의 y좌표 증가 (최대 제한 있음)			 							       */
/*       A or a : 시점의 y좌표 감소 (최소 제한 있음)										       */
/*       up or down : 시점의 z좌표 증가 또는 감소 (최대,최소 제한 있음)		                       */
/*       left or right : 시점의 x좌표 증가 또는 감소 (최대,최소 제한 있음)		                   */
/*       <메뉴>                                                                                    */
/*       마우스 오른쪽버튼으로 메뉴 표시                                                           */
/*       Light Effect : 트리 전구의 색깔들을 그라데이션처럼 바꾸고, 상단의 별을 깜빡이게 한다.     */
/*       Effect Stop : 트리 전구의 색깔변환을 멈추고, 상단의 별을 노란색으로 유지시킨다.           */
/***************************************************************************************************/
#include <windows.h>
#include <stdlib.h>
#include <gl/glut.h>
#include <gl/glaux.h>

#pragma comment(lib, "glaux.lib")
#pragma comment (lib,"legacy_stdio_definitions.lib")

int check = 0;
int st = 0;
float rA = 0.7, rB = 0.7, gB = 0.7, gC = 0.7, bD = 0.7;
float gA = 0.0, bA = 0.0, bB = 0.0, rC = 0.0, bC = 0.0, rD = 0.0, gD = 0.0;
float rS = 0.8, gS = 0.8;

GLfloat camera_x = 0.0;
GLfloat camera_y = 0.0;
GLfloat camera_z = 0.0;
GLUquadricObj* qobj = gluNewQuadric();
GLuint tex[2]; //텍스처맵핑 식별자

int LoadGLTextures() {  //파일을 로드하고 텍스쳐로 변환
    AUX_RGBImageRec* pTextureImage[2];  //2개의 이미지 텍스처
    memset(pTextureImage, 0, sizeof(void*) * 2);

    if ((pTextureImage[0] = auxDIBImageLoad(L"wood.bmp")) && //트리의 나무이미지를 메모리로
        (pTextureImage[1] = auxDIBImageLoad(L"leaves.bmp"))) { //트리의 잎 이미지를 메모리로
        glGenTextures(2, &tex[0]); 
        for (int i = 0; i < 2; i++) { 
            glBindTexture(GL_TEXTURE_2D, tex[i]); 
            //텍스쳐 맵핑에 보간법
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
            glTexImage2D(GL_TEXTURE_2D, 0, 3, 
                pTextureImage[i]->sizeX, pTextureImage[i]->sizeY, 0,
                GL_RGB, GL_UNSIGNED_BYTE, pTextureImage[i]->data); 
        }
    }
    else 
        return FALSE;

    for (int i = 0; i < 2; i++) { 
        if (pTextureImage[i]) {
            if (pTextureImage[i]->data) {
                free(pTextureImage[i]->data);
            }
            free(pTextureImage[i]);
        }
        else 
            return FALSE;
    }
}

//나무기둥
void Wood() { 
    gluQuadricDrawStyle(qobj, GLU_FILL);
    gluQuadricTexture(qobj, GL_TRUE);
    gluQuadricNormals(qobj, GLU_SMOOTH);

    LoadGLTextures();
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(0.0, 2.0, 0.0);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glBindTexture(GL_TEXTURE_2D, tex[0]); //나무기둥에 나무텍스쳐를 맵핑
    gluCylinder(qobj, 0.5, 0.5, 2.0, 30, 1); //원기둥 모양으로 나무 모델링
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}

//나무 밑단
void leaf1() { 
    gluQuadricDrawStyle(qobj, GLU_FILL);
    gluQuadricTexture(qobj, GL_TRUE);
    gluQuadricNormals(qobj, GLU_SMOOTH);

    LoadGLTextures(); //텍스쳐함수를 불러온다. 
    glEnable(GL_TEXTURE_2D); //텍스쳐모드 켜기

    glPushMatrix();
    glTranslatef(0.0, 1.5, 0.0); //위치 조정
    glRotatef(-90.0, 1.0, 0.0, 0.0); //정면에서 볼 수 있도록 rotate
    glBindTexture(GL_TEXTURE_2D, tex[1]); //나무잎 텍스처 맵핑
    gluCylinder(qobj, 3.0, 0.0, 3.0, 30, 1); //제일 밑단 잎 모델링
    glPopMatrix();

    glDisable(GL_TEXTURE_2D); //맵핑이 끝났으니 텍스쳐모드 끈다.
}

//나무 중간단
void leaf2() { 
    gluQuadricDrawStyle(qobj, GLU_FILL);
    gluQuadricTexture(qobj, GL_TRUE);
    gluQuadricNormals(qobj, GLU_SMOOTH);

    LoadGLTextures();
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(0.0, 3.2, 0.0);
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    glBindTexture(GL_TEXTURE_2D, tex[1]);
    gluCylinder(qobj, 2.5, 0.0, 3.0, 30, 1); //중간단 잎 모델링
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}

//나무 상단
void leaf3() { 
    gluQuadricDrawStyle(qobj, GLU_FILL);
    gluQuadricTexture(qobj, GL_TRUE);
    gluQuadricNormals(qobj, GLU_SMOOTH);

    LoadGLTextures();
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(0.0, 4.9, 0.0);
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    glBindTexture(GL_TEXTURE_2D, tex[1]);
    gluCylinder(qobj, 1.8, 0.0, 3.5, 30, 1); 
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}

//땅
void DrawGround() {
    glDisable(GL_LIGHTING); //땅은 조명효과를 받지 않도록 한다.
    glColor3f(0.6, 0.6, 0.6); //회색으로 모델링
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, 0, -10.0);
    glVertex3f(-10.0, 0, 10.0);
    glVertex3f(10.0, 0, 10.0);
    glVertex3f(10.0, 0, -10.0);
    glEnd();
}

//전구A
void LightA(GLfloat x, GLfloat y, GLfloat z) { //x,y,z위치를 인자로 받음
    glEnable(GL_LIGHTING); //조명계산
    GLfloat emission[] = { rA , gA , bA , 0.0 }; //발광색깔특성
    GLfloat shininess[] = { 100.0 }; //반짝임특성

    GLUquadricObj* qobj = gluNewQuadric();
    
    glPushMatrix();
    glTranslatef(x, y, z); //인자로 받은 위치로 전구를 translate한다.
    glMaterialfv(GL_FRONT, GL_EMISSION, emission);  //특성 부여
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
    glutSolidSphere(0.1, 30, 30);
    glPopMatrix();
}

//전구B
void LightB(GLfloat x, GLfloat y, GLfloat z) {
    glEnable(GL_LIGHTING);
    GLfloat emission[] = { rB , gB , bB , 0.0 }; 
    GLfloat shininess[] = { 100.0 };

    GLUquadricObj* qobj = gluNewQuadric();

    glPushMatrix();
    glTranslatef(x, y, z);
    glMaterialfv(GL_FRONT, GL_EMISSION, emission); 
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
    glutSolidSphere(0.1, 30, 30);
    glPopMatrix(); 
}

//전구C
void LightC(GLfloat x, GLfloat y, GLfloat z) {
    glEnable(GL_LIGHTING);
    GLfloat emission[] = { rC , gC , bC , 0.0 }; 
    GLfloat shininess[] = { 100.0 };

    GLUquadricObj* qobj = gluNewQuadric();

    glPushMatrix();
    glTranslatef(x, y, z);
    glMaterialfv(GL_FRONT, GL_EMISSION, emission); 
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
    glutSolidSphere(0.1, 30, 30);
    glPopMatrix();
}

//전구D
void LightD(GLfloat x, GLfloat y, GLfloat z) {
    glEnable(GL_LIGHTING);
    GLfloat emission[] = { rD , gD , bD , 0.0 }; 
    GLfloat shininess[] = { 100.0 };

    GLUquadricObj* qobj = gluNewQuadric();

    glPushMatrix();
    glTranslatef(x, y, z);
    glMaterialfv(GL_FRONT, GL_EMISSION, emission); 
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
    glutSolidSphere(0.1, 30, 30);
    glPopMatrix();
}

//별
void star() { 
    glEnable(GL_LIGHTING);
    GLfloat emission[] = { rS , gS , 0.0 , 0.0 }; 
    GLfloat shininess[] = { 100.0 };

    GLUquadricObj* qobj = gluNewQuadric();

    glPushMatrix();
    glTranslatef(0, 8.5, 0); //1번뿔 모델링
    glRotatef(-90.0, 1.0, 0.0, 0.0); //정면에서 볼 수 있도록 rotate
    glMaterialfv(GL_FRONT, GL_EMISSION, emission); 
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
    gluCylinder(qobj, 0.1, 0.0, 0.3, 30, 1);
    glPopMatrix();

    for (int i = 1; i < 5; i++) { //2번뿔부터 일정한 각도로 회전하면서 모델링하여 별 완성
        glPushMatrix();
        glTranslatef(0, 8.5, 0);
        glRotatef(72 * i, 0.0, 0.0, 1.0);
        glRotatef(-90.0, 1.0, 0.0, 0.0);
        gluCylinder(qobj, 0.1, 0.0, 0.3, 30, 1);
        glPopMatrix();
    }
}

//전구 타이머 함수, st상태에 따라서 전구 색이 점차 변하는데, st는 0,1,2,3을 계속 순서대로 루프.
//별은 st가 0일때와 2일때 발광색을 검정으로 만들어서 깜빡이는 것처럼 보이도록 했다.
//전구 A~D를 모델링 할 때 사용한 발광색 변수 사용
void MyTimer1(int Value) { 
    if (check == 1) {

        if (st == 0) {
            rS = 0.0;
            gS = 0.0;

            gA += 0.1;

            rB -= 0.1;

            gC -= 0.1;
            bC += 0.1;

            rD += 0.1;
            bD -= 0.1;

            if (gA > 0.7) {
                rA = 0.8;
                gA = 0.7;

                rB = 0.0;
                gB = 0.8;
                bB = -0.1; 

                rC = -0.1;
                gC = 0.0;
                bC = 0.8;

                rD = 0.7;
                gD = -0.1;
                bD = 0.0;

                st = 1;
            }
        }

        if (st == 1) {

            rS = 0.8;
            gS = 0.8;

            rA -= 0.1;

            gB -= 0.1;
            bB += 0.1;

            rC += 0.1;
            bC -= 0.1;

            gD += 0.1;

            if (rA < 0.0) {
                rA = 0.0;
                gA = 0.8;
                bA = -0.1;

                rB = -0.1;
                gB = 0.0;
                bB = 0.8;

                rC = 0.7;
                gC = -0.1;
                bC = 0.0;

                rD = 0.8;
                gD = 0.7;

                st = 2;
            }
        }

        if (st == 2) {

            rS = 0.0;
            gS = 0.0;

            gA -= 0.1;
            bA += 0.1;

            rB += 0.1;
            bB -= 0.1;

            gC += 0.1;

            rD -= 0.1;

            if (bA > 0.7) {
                rA = -0.1;
                gA = 0.0;
                bA = 0.8; 

                rB = 0.7;
                gB = -0.1;
                bB = 0.0;

                rC = 0.8;
                gC = 0.7;

                rD = 0.0;
                gD = 0.8;
                bD = -0.1;

                st = 3;
            }
        }

        if (st == 3) {

            rS = 0.8;
            gS = 0.8;

            rA += 0.1;
            bA -= 0.1;

            gB += 0.1;

            rC -= 0.1;

            gD -= 0.1;
            bD += 0.1;

            if (rA > 0.7) {
                rA = 0.7;
                gA = -0.1; 
                bA = 0.0;

                rB = 0.8;
                gB = 0.7;


                rC = 0.0;
                gC = 0.8;
                bC = -0.1;

                rD = -0.1;
                gD = 0.0;
                bD = 0.8;

                st = 0;
            }
        }
    }
    else //check가 0
        return;

    glutPostRedisplay(); //디스플레이 함수 강제 호출 함수
}

void MyTimer6(int Value) { //EffectStop을 선택했을 때
    if (check == 0) {
        rS = 0.8;
        gS = 0.8; //별의 발광색을 원래대로 초기화시킨다.
    }
    glutPostRedisplay();
    glutTimerFunc(40, MyTimer6, 1);
}

void MyIdle() {  //LightEffect를 선택했을 때
    Sleep(200); //일정 시간을 두고 타이머 함수가 계속 시행되도록 하여 변하는 색깔을 확인할 수 있도록.
    glutTimerFunc(40, MyTimer1, 1); //타이머 함수 실행
}

//메뉴를 생성한다.
void MyMainMenu(int entryID) {
    if (entryID == 1) {
        check = 1;
        glutIdleFunc(MyIdle); //LightEffect를 선택하면 실행된다.
    }
    if (entryID == 2) {
        check = 0;
        glutTimerFunc(50, MyTimer6, 1); //EffectStop을 선택하면 실행된다.
    }

    glutPostRedisplay();
}

//시점x축과 z축을 변환하도록 키보드의 방향키 사용
//최대 최소 제한을 두어 일정 위치를 벗어나지 못하게 하였다.
void MySpecialKeyboard(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_LEFT:
        if (camera_x > -2.5) {
            camera_x -= 0.1;
        }
        glutPostRedisplay();
        break;

    case GLUT_KEY_RIGHT:
        if (camera_x < 2.5) {
            camera_x += 0.1;
        }

        glutPostRedisplay();
        break;

    case GLUT_KEY_DOWN:
        if (camera_z < 4.0) {
            camera_z += 0.1;
        }
        glutPostRedisplay();
        break;

    case GLUT_KEY_UP:
        if (camera_z > -3.0) {
            camera_z -= 0.1;
        }
        glutPostRedisplay();
        break;
    }
}

//시점y축을 변환하도록 키보드의 q와 a키 사용
void MyKeyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'Q': case 'q': 
        if (camera_y < 1.3) {
            camera_y += 0.1;
        }
        glutPostRedisplay();
        break;

    case 'A': case 'a':
        if (camera_y > -1.6) {
            camera_y -= 0.1;
        }
        glutPostRedisplay();
        break;

    default:
        break;
    }
}

void InitLight() { //조명효과
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 }; //조명의 지역반사
    GLfloat light_diffuse[] = { 0.8, 0.8, 0.8, 1.0 }; //조명의 난반사
    GLfloat light_ambient[] = { 0.3, 0.3, 0.3, 1.0 }; //조명의 정반사
    GLfloat light_position[] = { -3, 2, 3.0, 0.0 }; //조명의 위치

    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING); //조명계산과 조명을 활상화한다.
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position); //조명 특성 적용
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
}

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //초기에는 (0,3,15)위치에서 (0,5,0)을 바라본다. 카메라는 y축으로 1만큼 기울어져있음
    gluLookAt(camera_x, camera_y + 3.0, 15.0 + camera_z, 0.0, 5.0, 0.0, 0.0, 1.0, 0.0);

    DrawGround(); //땅 그리기
    Wood(); //나무 그리기
    leaf1(); //잎 밑단 그리기
    leaf2(); //잎 중간단 그리기
    leaf3(); //잎 상단 그리기
    
    //전구들은 x,y,z값을 인자로 받아 각 객체의 translatef함수에서 사용된다.
    //잎 밑단 전구들 그리기
    LightA(-2.6, 1.7, 1.3); 
    LightB(-1.8, 2.0, 1.8);
    LightC(-1.0, 2.3, 2.1);
    LightD(0.0, 2.6, 2.0);
    LightC(0.6, 2.9, 1.6);
    LightB(1.4, 3.1, 0.0);
    LightD(2.6, 1.7, 1.3); 
    LightC(1.8, 2.0, 1.8);
    LightA(1.0, 2.3, 2.1);
    LightA(-0.6, 2.9, 1.6); 
    LightC(-1.4, 3.1, 0.0);
    LightD(-2.0, 2.5, -0.2); 
    LightB(-0.1, 2.1, 2.5); 
    LightC(0.7, 1.9, 2.7); 
    LightA(-1.1, 1.6, 2.8); 
    LightC(1.8, 2.5, 1.2); 
    LightD(0.1, 1.6, 3.1); 
    LightB(1.6, 1.6, 2.3); 
    
    //잎 중간단 전구들 그리기
    LightB(-2.0, 3.4, 1.2);
    LightC(-1.1, 3.8, 1.8);
    LightD(-0.1, 4.1, 1.9);
    LightB(0.7, 4.4, 1.4);
    LightA(-1.5, 4.4, 0.1);
    LightB(-0.6, 4.6, 1.4);
    LightB(-0.4, 3.4, 2.4); 
    LightA(0.6, 3.7, 2.1);
    LightD(1.5, 3.6, 1.7);
    LightA(2.4, 3.4, 0.2); 
    LightC(1.6, 4.3, 0.1);
    
    //잎 상단 전구들 그리기
    LightD(1.6, 5.1, 0.7);
    LightA(1.1, 5.7, 1.0);
    LightC(0.6, 6.4, 0.9);
    LightB(-0.1, 5.8, 1.4);
    LightC(0.5, 5.3, 1.6);
    LightA(-0.3, 5.1, 1.8);
    LightC(-1.5, 5.0, 1.1);
    LightD(-1.0, 5.6, 1.1);
    LightB(-1.0, 6.5, 0.1);
    LightA(-0.3, 6.6, 0.9);
    LightB(0.1, 7.1, 0.7);

    star(); //별 그리기

    glFlush();
}

void MyInit() {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    //후면제거 사용
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW); 
    glPolygonMode(GL_FRONT, GL_LINE);
    glPolygonMode(GL_BACK, GL_FILL);
    glCullFace(GL_FRONT);

    GLint MyMainID = glutCreateMenu(MyMainMenu);  //메인 메뉴 생성
    glutAddMenuEntry("Light Effect", 1); 
    glutAddMenuEntry("Stop Light", 2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);  //마우스 오른쪽 버튼 클릭시 메뉴창 생성
}

void MyReshape(int width, int height) {
    glViewport(0, 0, (GLsizei)width, (GLsizei)height); //뷰폿은 그때그때 윈도우 크기로 입력을 받는다.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0, (GLfloat)width / (GLfloat)height, 0.0, 100); //변환되는 윈도우크기마다 종횡비를 새로 구해서 원근투영을 사용한다.
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Merry Christmas");

    InitLight();
    MyInit();
    glutDisplayFunc(MyDisplay);
    glutReshapeFunc(MyReshape);
    glutKeyboardFunc(MyKeyboard);
    glutSpecialFunc(MySpecialKeyboard);

    glutMainLoop();
    return 0;
}