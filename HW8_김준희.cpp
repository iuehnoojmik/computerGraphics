/***************************************************************************************************/
/*										hw#8 :  ����                                               */
/*  �ۼ��� : ������                          ��¥ : 2022�� 12�� 18��                               */
/*																								   */
/* ���� ���� :   Ʈ���� ������ �𵨸��ϰ� Ʈ���� �������� ���ϴ� ȿ���� �ش�.     	    		   */
/*  �ݹ����α׷���: Display(ȭ�����), Reshape(������ũ������,��ġ�̵�), Keyboard(������ȯ�� ���) */
/*                  Menu(����ȿ���� ����Ű�¸޴��ݹ�), Idle(����ȿ��Ÿ�̸� �Լ� �θ��� ���)       */
/*                  Timer(���� ������ ��ȯ��ų�� ���)                                             */
/*  �𵨺�ȯ: �����𵨸��� �� �𵨸��� Translatef, Rotatef�� ����Ͽ� ���ϴ� ����� ������ ��      */
/*  ������ȯ: ������ Ű�����ݹ��� ��ȯ�Ͽ� ������ȯ�� �����ϵ��� ��                                */
/*  ������ȯ: Reshape�Լ��� ����������ȯ�� ����Ͽ� ��ü�� ���ٰ� �ο�                             */
/*  ������ȯ: Reshape�Լ��� ������ȯ�� ����Ͽ� ������ ũ�������ÿ��� ��ü���� �ְ��� ����         */
/*  ���ü��˻�: �𵨸��� Ʈ���� �ĸ����� ���                                                      */
/*  ����: Ʈ���� �߱�ü ������ ����                                                                */
/*  �ؽ�ó: Ʈ���� ������ �� �ؽ��� ����                                                           */
/***************************************************************************************************/
/* ���:																					       */
/*       <Ű����>                                                                                  */
/*       Q or q : ������ y��ǥ ���� (�ִ� ���� ����)			 							       */
/*       A or a : ������ y��ǥ ���� (�ּ� ���� ����)										       */
/*       up or down : ������ z��ǥ ���� �Ǵ� ���� (�ִ�,�ּ� ���� ����)		                       */
/*       left or right : ������ x��ǥ ���� �Ǵ� ���� (�ִ�,�ּ� ���� ����)		                   */
/*       <�޴�>                                                                                    */
/*       ���콺 �����ʹ�ư���� �޴� ǥ��                                                           */
/*       Light Effect : Ʈ�� ������ ������� �׶��̼�ó�� �ٲٰ�, ����� ���� �����̰� �Ѵ�.     */
/*       Effect Stop : Ʈ�� ������ ����ȯ�� ���߰�, ����� ���� ��������� ������Ų��.           */
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
GLuint tex[2]; //�ؽ�ó���� �ĺ���

int LoadGLTextures() {  //������ �ε��ϰ� �ؽ��ķ� ��ȯ
    AUX_RGBImageRec* pTextureImage[2];  //2���� �̹��� �ؽ�ó
    memset(pTextureImage, 0, sizeof(void*) * 2);

    if ((pTextureImage[0] = auxDIBImageLoad(L"wood.bmp")) && //Ʈ���� �����̹����� �޸𸮷�
        (pTextureImage[1] = auxDIBImageLoad(L"leaves.bmp"))) { //Ʈ���� �� �̹����� �޸𸮷�
        glGenTextures(2, &tex[0]); 
        for (int i = 0; i < 2; i++) { 
            glBindTexture(GL_TEXTURE_2D, tex[i]); 
            //�ؽ��� ���ο� ������
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

//�������
void Wood() { 
    gluQuadricDrawStyle(qobj, GLU_FILL);
    gluQuadricTexture(qobj, GL_TRUE);
    gluQuadricNormals(qobj, GLU_SMOOTH);

    LoadGLTextures();
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(0.0, 2.0, 0.0);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glBindTexture(GL_TEXTURE_2D, tex[0]); //������տ� �����ؽ��ĸ� ����
    gluCylinder(qobj, 0.5, 0.5, 2.0, 30, 1); //����� ������� ���� �𵨸�
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}

//���� �ش�
void leaf1() { 
    gluQuadricDrawStyle(qobj, GLU_FILL);
    gluQuadricTexture(qobj, GL_TRUE);
    gluQuadricNormals(qobj, GLU_SMOOTH);

    LoadGLTextures(); //�ؽ����Լ��� �ҷ��´�. 
    glEnable(GL_TEXTURE_2D); //�ؽ��ĸ�� �ѱ�

    glPushMatrix();
    glTranslatef(0.0, 1.5, 0.0); //��ġ ����
    glRotatef(-90.0, 1.0, 0.0, 0.0); //���鿡�� �� �� �ֵ��� rotate
    glBindTexture(GL_TEXTURE_2D, tex[1]); //������ �ؽ�ó ����
    gluCylinder(qobj, 3.0, 0.0, 3.0, 30, 1); //���� �ش� �� �𵨸�
    glPopMatrix();

    glDisable(GL_TEXTURE_2D); //������ �������� �ؽ��ĸ�� ����.
}

//���� �߰���
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
    gluCylinder(qobj, 2.5, 0.0, 3.0, 30, 1); //�߰��� �� �𵨸�
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}

//���� ���
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

//��
void DrawGround() {
    glDisable(GL_LIGHTING); //���� ����ȿ���� ���� �ʵ��� �Ѵ�.
    glColor3f(0.6, 0.6, 0.6); //ȸ������ �𵨸�
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, 0, -10.0);
    glVertex3f(-10.0, 0, 10.0);
    glVertex3f(10.0, 0, 10.0);
    glVertex3f(10.0, 0, -10.0);
    glEnd();
}

//����A
void LightA(GLfloat x, GLfloat y, GLfloat z) { //x,y,z��ġ�� ���ڷ� ����
    glEnable(GL_LIGHTING); //������
    GLfloat emission[] = { rA , gA , bA , 0.0 }; //�߱�����Ư��
    GLfloat shininess[] = { 100.0 }; //��¦��Ư��

    GLUquadricObj* qobj = gluNewQuadric();
    
    glPushMatrix();
    glTranslatef(x, y, z); //���ڷ� ���� ��ġ�� ������ translate�Ѵ�.
    glMaterialfv(GL_FRONT, GL_EMISSION, emission);  //Ư�� �ο�
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
    glutSolidSphere(0.1, 30, 30);
    glPopMatrix();
}

//����B
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

//����C
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

//����D
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

//��
void star() { 
    glEnable(GL_LIGHTING);
    GLfloat emission[] = { rS , gS , 0.0 , 0.0 }; 
    GLfloat shininess[] = { 100.0 };

    GLUquadricObj* qobj = gluNewQuadric();

    glPushMatrix();
    glTranslatef(0, 8.5, 0); //1���� �𵨸�
    glRotatef(-90.0, 1.0, 0.0, 0.0); //���鿡�� �� �� �ֵ��� rotate
    glMaterialfv(GL_FRONT, GL_EMISSION, emission); 
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
    gluCylinder(qobj, 0.1, 0.0, 0.3, 30, 1);
    glPopMatrix();

    for (int i = 1; i < 5; i++) { //2���Ժ��� ������ ������ ȸ���ϸ鼭 �𵨸��Ͽ� �� �ϼ�
        glPushMatrix();
        glTranslatef(0, 8.5, 0);
        glRotatef(72 * i, 0.0, 0.0, 1.0);
        glRotatef(-90.0, 1.0, 0.0, 0.0);
        gluCylinder(qobj, 0.1, 0.0, 0.3, 30, 1);
        glPopMatrix();
    }
}

//���� Ÿ�̸� �Լ�, st���¿� ���� ���� ���� ���� ���ϴµ�, st�� 0,1,2,3�� ��� ������� ����.
//���� st�� 0�϶��� 2�϶� �߱����� �������� ���� �����̴� ��ó�� ���̵��� �ߴ�.
//���� A~D�� �𵨸� �� �� ����� �߱��� ���� ���
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
    else //check�� 0
        return;

    glutPostRedisplay(); //���÷��� �Լ� ���� ȣ�� �Լ�
}

void MyTimer6(int Value) { //EffectStop�� �������� ��
    if (check == 0) {
        rS = 0.8;
        gS = 0.8; //���� �߱����� ������� �ʱ�ȭ��Ų��.
    }
    glutPostRedisplay();
    glutTimerFunc(40, MyTimer6, 1);
}

void MyIdle() {  //LightEffect�� �������� ��
    Sleep(200); //���� �ð��� �ΰ� Ÿ�̸� �Լ��� ��� ����ǵ��� �Ͽ� ���ϴ� ������ Ȯ���� �� �ֵ���.
    glutTimerFunc(40, MyTimer1, 1); //Ÿ�̸� �Լ� ����
}

//�޴��� �����Ѵ�.
void MyMainMenu(int entryID) {
    if (entryID == 1) {
        check = 1;
        glutIdleFunc(MyIdle); //LightEffect�� �����ϸ� ����ȴ�.
    }
    if (entryID == 2) {
        check = 0;
        glutTimerFunc(50, MyTimer6, 1); //EffectStop�� �����ϸ� ����ȴ�.
    }

    glutPostRedisplay();
}

//����x��� z���� ��ȯ�ϵ��� Ű������ ����Ű ���
//�ִ� �ּ� ������ �ξ� ���� ��ġ�� ����� ���ϰ� �Ͽ���.
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

//����y���� ��ȯ�ϵ��� Ű������ q�� aŰ ���
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

void InitLight() { //����ȿ��
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 }; //������ �����ݻ�
    GLfloat light_diffuse[] = { 0.8, 0.8, 0.8, 1.0 }; //������ ���ݻ�
    GLfloat light_ambient[] = { 0.3, 0.3, 0.3, 1.0 }; //������ ���ݻ�
    GLfloat light_position[] = { -3, 2, 3.0, 0.0 }; //������ ��ġ

    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING); //������� ������ Ȱ��ȭ�Ѵ�.
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position); //���� Ư�� ����
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
}

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //�ʱ⿡�� (0,3,15)��ġ���� (0,5,0)�� �ٶ󺻴�. ī�޶�� y������ 1��ŭ ����������
    gluLookAt(camera_x, camera_y + 3.0, 15.0 + camera_z, 0.0, 5.0, 0.0, 0.0, 1.0, 0.0);

    DrawGround(); //�� �׸���
    Wood(); //���� �׸���
    leaf1(); //�� �ش� �׸���
    leaf2(); //�� �߰��� �׸���
    leaf3(); //�� ��� �׸���
    
    //�������� x,y,z���� ���ڷ� �޾� �� ��ü�� translatef�Լ����� ���ȴ�.
    //�� �ش� ������ �׸���
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
    
    //�� �߰��� ������ �׸���
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
    
    //�� ��� ������ �׸���
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

    star(); //�� �׸���

    glFlush();
}

void MyInit() {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    //�ĸ����� ���
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW); 
    glPolygonMode(GL_FRONT, GL_LINE);
    glPolygonMode(GL_BACK, GL_FILL);
    glCullFace(GL_FRONT);

    GLint MyMainID = glutCreateMenu(MyMainMenu);  //���� �޴� ����
    glutAddMenuEntry("Light Effect", 1); 
    glutAddMenuEntry("Stop Light", 2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);  //���콺 ������ ��ư Ŭ���� �޴�â ����
}

void MyReshape(int width, int height) {
    glViewport(0, 0, (GLsizei)width, (GLsizei)height); //������ �׶��׶� ������ ũ��� �Է��� �޴´�.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0, (GLfloat)width / (GLfloat)height, 0.0, 100); //��ȯ�Ǵ� ������ũ�⸶�� ��Ⱦ�� ���� ���ؼ� ���������� ����Ѵ�.
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