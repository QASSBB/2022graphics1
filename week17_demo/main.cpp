#include <GL/glut.h>
#include <stdio.h>
#include "glm.h"
#include <opencv/highgui.h> ///使用 OpenCV 2.1 比較簡單, 只要用 High GUI 即可
#include <opencv/cv.h>
#include <GL/glut.h>
float dx=0,dy=0,dz=0,oldX=0,oldY=0;
GLuint tex1,tex2;
int myTexture(char * filename)
{
    IplImage * img = cvLoadImage(filename); ///OpenCV讀圖
    cvCvtColor(img,img, CV_BGR2RGB); ///OpenCV轉色彩 (需要cv.h)
    glEnable(GL_TEXTURE_2D); ///1. 開啟貼圖功能
    GLuint id; ///準備一個 unsigned int 整數, 叫 貼圖ID
    glGenTextures(1, &id); /// 產生Generate 貼圖ID
    glBindTexture(GL_TEXTURE_2D, id); ///綁定bind 貼圖ID
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); /// 貼圖參數, 超過包裝的範圖T, 就重覆貼圖
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); /// 貼圖參數, 超過包裝的範圖S, 就重覆貼圖
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); /// 貼圖參數, 放大時的內插, 用最近點
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); /// 貼圖參數, 縮小時的內插, 用最近點
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img->width, img->height, 0, GL_RGB, GL_UNSIGNED_BYTE, img->imageData);
    return id;
}
GLMmodel * head = NULL;
GLMmodel * body = NULL;
GLMmodel * RA1 = NULL;
GLMmodel * RA2 = NULL;
GLMmodel * LA1 = NULL;
GLMmodel * LA2 = NULL;
GLMmodel * RL1 = NULL;
GLMmodel * RL2 = NULL;
GLMmodel * LL1 = NULL;
GLMmodel * LL2 = NULL;
GLMmodel * Gundam = NULL;
GLMmodel * myReadOne(char * filename){
    GLMmodel * one = NULL;
     if(one == NULL){
        one = glmReadOBJ(filename);
        //glmUnitize(mantis);
        glmScale(one,1/26.0);
        glmFacetNormals(one);
        glmVertexNormals(one,90);
    }
    return one;
}
void myReadAll(){
    Gundam = myReadOne("data/Gundam.obj");
    head = myReadOne("data/head.obj");
    body = myReadOne("data/body1.obj");
    RA1 = myReadOne("data/RA1.obj");
    RA2 = myReadOne("data/RA2.obj");
    LA1 = myReadOne("data/LA1.obj");
    LA2 = myReadOne("data/LA2.obj");
    RL1 = myReadOne("data/RL1.obj");
    RL2 = myReadOne("data/RL2.obj");
    LL1 = myReadOne("data/LL1.obj");
    LL2 = myReadOne("data/LL2.obj");
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };
void mylight(){
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
}
void reshape(int w,int h){
    float ar = (float)w/(float)h;
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60,ar,0.1,100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,0,-0.5, 0,0,0, 0,1,0);
}
float angleX[20], angleY[20];

int angleID=0;
FILE * fout = NULL, * fin = NULL;
void myWrite(){
    if(fout == NULL) fout = fopen("file.txt", "w+");
    for(int i=0 ; i<20 ; i++){
        printf(" %.1f ", angleX[i]);
        fprintf(fout, " %.1f ",angleX[i]);
        printf(" %.1f ", angleY[i]);
        fprintf(fout, " %.1f ",angleY[i]);
    }
    printf("\n");
    fprintf(fout,"\n");
}
float NewAngleX[20], OldAngleX[20];
float NewAngleY[20], OldAngleY[20];
void myread(){
    if(fout != NULL){   fclose(fout); fout=NULL;  }
    if(fin == NULL) fin = fopen("file.txt", "r");
    for(int i=0 ; i<20 ; i++){
        OldAngleX[i] = NewAngleX[i];
        fscanf(fin, "%f",&NewAngleX[i]);
        OldAngleY[i] = NewAngleY[i];
        fscanf(fin, "%f",&NewAngleY[i]);
    }
    glutPostRedisplay();
}
void myInterpolate(float alpha){
    for(int i=0 ; i<20 ; i++){
        angleX[i] = alpha * NewAngleX[i]+(1-alpha)*OldAngleX[i];
        angleY[i] = alpha * NewAngleY[i]+(1-alpha)*OldAngleY[i];
    }
}
void timer(int t){
    if(t%50==0) myread();
    myInterpolate((t%50)/50.0);
    glutPostRedisplay();
    glutTimerFunc(20,timer,t+1);
}
void keyboard (unsigned char key,int x,int y){
    if(key=='p'){
        myread();
        glutTimerFunc(0,timer,0);
        //myIntperpolate((t%30)/30.0); ///介於0.0~1.0
        //glutPostRedisplay();
        //t++;
    }
    if(key=='s') myWrite(); ///調好動作再存檔
    if(key=='r') myread();
    if(key=='0') angleID=0;
    if(key=='1') angleID=1;
    if(key=='2') angleID=2;
    if(key=='3') angleID=3;
    if(key=='4') angleID=4;
    if(key=='5') angleID=5;
    if(key=='6') angleID=6;
    if(key=='7') angleID=7;
    if(key=='8') angleID=8;
    if(key=='9') angleID=9;
}
void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glBindTexture(GL_TEXTURE_2D, tex1);
    ///glmDraw(Gundam, GLM_TEXTURE | GLM_SMOOTH);

    glmDraw(body, GLM_TEXTURE | GLM_SMOOTH);///身體
    glPushMatrix();
        glTranslatef( 0.00 , 0.06 , 0.00 );
        glRotatef(angleX[0],0,1,0);
        glRotatef(angleY[0],1,0,0);
       glTranslatef( 0.00 , -0.06 , 0.00 );//glTranslatef(dx,dy,dz);
    glmDraw(head, GLM_TEXTURE | GLM_SMOOTH);///頭
    glPopMatrix();

    glPushMatrix();///左手
        glTranslatef( 0.05 , 0.05 , 0.00 );
        glRotatef(angleY[1],1,0,0);
        glRotatef(angleX[1],0,0,1);
        glTranslatef( -0.05 , -0.05 , 0.00 );//glTranslatef(dx,dy,dz);
        glmDraw(RA1, GLM_TEXTURE | GLM_SMOOTH);///上臂

        glPushMatrix();
            glTranslatef( 0.09 , -0.035 , 0.00 );
            glRotatef(angleY[2],1,0,0);
            glRotatef(angleX[2],0,1,0);
            glTranslatef( -0.09 , 0.035 , 0.00 );//glTranslatef(dx,dy,dz);
            glmDraw(RA2, GLM_TEXTURE | GLM_SMOOTH);///手肘
        glPopMatrix();

    glPopMatrix();

    glPushMatrix();///右手
        glTranslatef( -0.05 , 0.05 , 0.00 );
        glRotatef(angleY[3],1,0,0);
        glRotatef(angleX[3],0,0,1);
        glTranslatef( 0.05 , -0.05 , 0.00 );//glTranslatef(dx,dy,dz);
        glmDraw(LA1, GLM_TEXTURE | GLM_SMOOTH);///上臂

        glPushMatrix();
            glTranslatef( -0.09 , -0.035 , 0.00 );
            glRotatef(angleY[4],1,0,0);
            glRotatef(angleX[4],0,1,0);
            glTranslatef( 0.09 , 0.035 , 0.00 );//glTranslatef(dx,dy,dz);
            glmDraw(LA2, GLM_TEXTURE | GLM_SMOOTH);///手肘
        glPopMatrix();

    glPopMatrix();

    glPushMatrix();///右腳
            glTranslatef( 0.03 , -0.045 , 0.00 );
            glRotatef(angleY[5],1,0,0);
            glRotatef(angleX[5],0,1,0);
            glTranslatef( -0.03 , 0.045 , 0.00 );//glTranslatef(dx,dy,dz);
            glmDraw(RL1, GLM_TEXTURE | GLM_SMOOTH);///大腿

            glPushMatrix();
                glTranslatef( 0.04 , -0.13 , 0.00 );
                glRotatef(angleY[6],1,0,0);
                glRotatef(angleX[6],0,1,0);
                glTranslatef( -0.04 , 0.13 , 0.00 );//glTranslatef(dx,dy,dz);
                glmDraw(RL2, GLM_TEXTURE | GLM_SMOOTH);///小腿
            glPopMatrix();
    glPopMatrix();

    glPushMatrix();///左腳
            glTranslatef( -0.03 , -0.045 , 0.00 );
            glRotatef(angleX[7],0,1,0);
            glRotatef(angleY[7],1,0,0);
            glTranslatef( 0.03 , 0.045 , 0.00 );//glTranslatef(dx,dy,dz);
            glmDraw(LL1, GLM_TEXTURE | GLM_SMOOTH);///大腿

            glPushMatrix();
                glTranslatef( -0.04 , -0.13 , 0.00 );
                glRotatef(angleX[8],0,1,0);
                glRotatef(angleY[8],1,0,0);
                glTranslatef( 0.04 , 0.13 , 0.00 );//glTranslatef(dx,dy,dz);
                glmDraw(LL2, GLM_TEXTURE | GLM_SMOOTH);///小腿
            glPopMatrix();
    glPopMatrix();


    /*glBindTexture(GL_TEXTURE_2D , tex2);
    glutSolidTeapot( 0.03 );*/

    glutSwapBuffers();
}

void mouse(int Button, int state, int x, int y)
{
    oldX= x; oldY=y;
}
void motion(int x,int y)
{
    dx+=(oldX-x)/150.0; dy-=(y-oldY)/150.0;
    angleX[angleID] += (x-oldX);
    angleY[angleID] += (oldY-y);
    //printf("glTranslatef( %.2f , %.2f , %.2f );\n",dx,dy,dz);
    oldX = x;     oldY = y;
    glutPostRedisplay();
}
int main(int argc, char**argv){
    glutInit( &argc, argv );
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Final_Demo");

    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    mylight();
    tex1= myTexture("data/bastion.jpg");
    //tex2 = myTexture("data/Diffuse.jpg");

    ///glClearColor(1,1,0,0);
    myReadAll();

    glutMainLoop();
}
