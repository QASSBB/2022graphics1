#include <opencv/highgui.h>
#include <opencv/cv.h>
#include <GL/glut.h>
#include <stdio.h>
#include "glm.h"
const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };

const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };

const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };

const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };

const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };

const GLfloat high_shininess[] = { 100.0f };

GLMmodel * body = NULL;///分塊的模型
GLMmodel * head = NULL;
GLMmodel * RA1 = NULL;
GLMmodel * RA2 = NULL;
GLMmodel * LA1 = NULL;
GLMmodel * LA2 = NULL;
GLMmodel * RL = NULL;
GLMmodel * LL = NULL;
float angle[20],oldX=0;
int angleID=0;
FILE * fout = NULL, * fin = NULL;
void myWrite()
{
    if(fout == NULL)
        fout = fopen("file.txt", "w+");
    for(int i=0 ; i<20 ; i++)
    {
        printf(" %.1f ", angle[i]);
        fprintf(fout, " %.1f ",angle[i]);
    }
    printf("\n");
    fprintf(fout,"\n");
}
void myread()
{
    if(fout != NULL)
    {
        fclose(fout);
        fout=NULL;
    }
    if(fin == NULL)
        fin = fopen("file.txt", "r");
    for(int i=0 ; i<20 ; i++)
    {
        fscanf(fin, "%f",&angle[i]);
    }
    glutPostRedisplay();
}
void mouse(int Button, int state, int x, int y)
{
    oldX= x;
}
void keyboard (unsigned char key,int x,int y)
{
    if(key=='s')
        myWrite(); ///調好動作再存檔
    if(key=='r')
        myread();
    if(key=='0')
        angleID=0;
    if(key=='1')
        angleID=1;
    if(key=='2')
        angleID=2;
    if(key=='3')
        angleID=3;
    if(key=='4')
        angleID=4;
    if(key=='5')
        angleID=5;
    if(key=='6')
        angleID=6;
}
void motion(int x,int y)
{
    angle[angleID] += (x-oldX);
    ///myWrite();
    oldX = x;
    glutPostRedisplay();
}
GLMmodel * myReadOne(char * filename)
{
    GLMmodel * one=NULL;
    if(one==NULL)
    {
        one = glmReadOBJ(filename);
        glmUnitize(one);
        glmFacetNormals(one);
        glmVertexNormals(one,90);
    }
    return one;
}
int myTexture(char * filename)
{
    IplImage * img = cvLoadImage(filename);
    cvCvtColor(img,img, CV_BGR2RGB);
    glEnable(GL_TEXTURE_2D);
    GLuint id;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img->width, img->height, 0, GL_RGB, GL_UNSIGNED_BYTE, img->imageData);
    return id;
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    if(head==NULL)
        head=myReadOne("data/head.obj");
    if(body==NULL)
        body=myReadOne("data/body.obj");
    if(RA1==NULL)
        RA1=myReadOne("data/RA1.obj");
    if(RA2==NULL)
        RA2=myReadOne("data/RA2.obj");
    if(LA1==NULL)
        LA1=myReadOne("data/LA1.obj");
    if(LA2==NULL)
        LA2=myReadOne("data/LA2.obj");
    if(RL==NULL)
        RL=myReadOne("data/RL.obj");
    if(LL==NULL)
        LL=myReadOne("data/LL.obj");


    ///glColor3f(1,1,1);
    glmDraw(body, GLM_SMOOTH|GLM_MATERIAL);///身體

    glPushMatrix();///頭
    glRotatef(angle[0], 0,1,0);
    glTranslatef(0,0.35, 0);
    ///glColor3f(1,0,1);
    glmDraw(head, GLM_SMOOTH|GLM_MATERIAL);
    glPopMatrix();

    glPushMatrix();///左手
    glTranslatef( 0.15,0.2, 0);//中心點
    glRotatef(angle[1], 0,0,1);
    glTranslatef(0.05,-0.05, 0);//整根
    ///glColor3f(1,0,1);
    glmDraw(LA1,GLM_SMOOTH|GLM_MATERIAL);

    glPushMatrix();
    glTranslatef( 0.07,-0.08, 0);
    glRotatef(angle[2], 0,0,1);
    glTranslatef(0.05, -0.17, 0);
    ///glColor3f(0,1,0);
    glScalef(0.8,0.8,0.8);
    glmDraw(LA2,GLM_SMOOTH|GLM_MATERIAL);
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();///右手

    glTranslatef( -0.15,0.2, 0);//中心點
    glRotatef(angle[3], 0,0,1);
    glTranslatef(-0.05,-0.05, 0);//整根
    ///glColor3f(1,0,1);
    glmDraw(RA1,GLM_SMOOTH|GLM_MATERIAL);

    glPushMatrix();
    glTranslatef( -0.07,-0.08, 0);
    glRotatef(angle[4], 0,0,1);
    glTranslatef(-0.05, -0.17, 0);
    ///glColor3f(0,1,0);
    glScalef(0.8,0.8,0.8);
    glmDraw(RA2,GLM_SMOOTH|GLM_MATERIAL);

    glPopMatrix();

    glPopMatrix();

    glPushMatrix();//左腳
    glTranslatef( 0.1,-0.3, 0);
    glRotatef(angle[5], 0,0,1);
    glTranslatef(0,-0.2, 0);
    ///glColor3f(0,1,0);
    glScalef(0.3,0.3,0.3);
    glmDraw(LL,GLM_SMOOTH|GLM_MATERIAL);
    glPopMatrix();

    glPushMatrix();//右腳
    glTranslatef( -0.1,-0.3, 0);
    glRotatef(angle[6], 0,0,1);
    glTranslatef(0,-0.2, 0);
    ///glColor3f(0,1,0);
    glScalef(0.3,0.3,0.3);
    glmDraw(RL,GLM_SMOOTH|GLM_MATERIAL);

    glPopMatrix();
    glutSwapBuffers();
}
int main(int argc, char**argv)
{
    glutInit( &argc, argv );
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("week15_HW");
    myTexture("data/1.png");
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutIdleFunc(display);
    glutDisplayFunc(display);
    glEnable(GL_DEPTH_TEST);
    glClearColor(1,1,1,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
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
    glutMainLoop();
}
