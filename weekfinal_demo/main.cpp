#include <GL/glut.h>
#include <stdio.h>
#include "glm.h"
#include <opencv/highgui.h>
#include <opencv/cv.h>
#include <GL/glut.h>
#include "CMP3_MCI.h"
CMP3_MCI mp3;
float dx=0,dy=0,dz=0,oldX=0,oldY=0;
GLuint tex1,tex2,bg;
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
        glmScale(one,1/26.0);
        glmFacetNormals(one);
        glmVertexNormals(one,90);
    }
    return one;
}
void myReadAll(){
    head = myReadOne("data/head.obj");
    body = myReadOne("data/body.obj");
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
    }
    if(key=='s') myWrite();
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
void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindTexture(GL_TEXTURE_2D,bg);
    glBegin(GL_POLYGON);
        glTexCoord2f(0, 0); glVertex3f(-1, +1, 0.5);
        glTexCoord2f(0, 1); glVertex3f(-1, -1, 0.5);
        glTexCoord2f(1, 1); glVertex3f(+1, -1, 0.5);
        glTexCoord2f(1, 0); glVertex3f(+1, +1, 0.5);
    glEnd();

    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, tex1);
        glTranslatef( 0.00 , 0 , 0.00 );
        glRotatef(angleY[9],1,0,0);
        glRotatef(angleX[9],0,1,0);

       glTranslatef( 0.00 , 0 , 0.00 );
        glmDraw(body, GLM_TEXTURE | GLM_SMOOTH);
    glPopMatrix();
    glPushMatrix();
        glTranslatef( 0.00 , 0.06 , 0.00 );
        glRotatef(angleX[0],0,1,0);
        glRotatef(angleY[0],1,0,0);
       glTranslatef( 0.00 , -0.06 , 0.00 );
    glmDraw(head, GLM_TEXTURE | GLM_SMOOTH);
    glPopMatrix();

    glPushMatrix();
        glTranslatef( 0.05 , 0.05 , 0.00 );

        glRotatef(angleX[1],0,1,0);
        glRotatef(angleY[1],1,0,0);
        glTranslatef( -0.05 , -0.05 , 0.00 );
        glmDraw(RA1, GLM_TEXTURE | GLM_SMOOTH);

        glPushMatrix();
            glTranslatef( 0.09 , -0.035 , 0.00 );
        glRotatef(angleX[2],0,1,0);
        glRotatef(angleY[2],1,0,0);
            glTranslatef( -0.09 , 0.035 , 0.00 );
            glmDraw(RA2, GLM_TEXTURE | GLM_SMOOTH);
        glPopMatrix();

    glPopMatrix();

    glPushMatrix();
        glTranslatef( -0.05 , 0.05 , 0.00 );

        glRotatef(angleX[3],0,1,0);
        glRotatef(angleY[3],1,0,0);
        glTranslatef( 0.05 , -0.05 , 0.00 );//glTranslatef(dx,dy,dz);
        glmDraw(LA1, GLM_TEXTURE | GLM_SMOOTH);

        glPushMatrix();
            glTranslatef( -0.09 , -0.035 , 0.00 );
            glRotatef(angleX[4],0,1,0);
            glRotatef(angleY[4],1,0,0);
            glTranslatef( 0.09 , 0.035 , 0.00 );//glTranslatef(dx,dy,dz);
            glmDraw(LA2, GLM_TEXTURE | GLM_SMOOTH);
        glPopMatrix();

    glPopMatrix();

    glPushMatrix();
            glTranslatef( 0.03 , -0.045 , 0.00 );
            glRotatef(angleX[5],0,1,0);
            glRotatef(angleY[5],1,0,0);
            glTranslatef( -0.03 , 0.045 , 0.00 );//glTranslatef(dx,dy,dz);
            glmDraw(RL1, GLM_TEXTURE | GLM_SMOOTH);

            glPushMatrix();
                glTranslatef( 0.04 , -0.13 , 0.00 );
            glRotatef(angleX[6],0,1,0);
            glRotatef(angleY[6],1,0,0);
                glTranslatef( -0.04 , 0.13 , 0.00 );//glTranslatef(dx,dy,dz);
                glmDraw(RL2, GLM_TEXTURE | GLM_SMOOTH);
            glPopMatrix();
    glPopMatrix();

    glPushMatrix();
            glTranslatef( -0.03 , -0.045 , 0.00 );
            glRotatef(angleX[7],0,1,0);
            glRotatef(angleY[7],1,0,0);
            glTranslatef( 0.03 , 0.045 , 0.00 );//glTranslatef(dx,dy,dz);
            glmDraw(LL1, GLM_TEXTURE | GLM_SMOOTH);

            glPushMatrix();
                glTranslatef( -0.04 , -0.13 , 0.00 );
            glRotatef(angleX[8],0,1,0);
            glRotatef(angleY[8],1,0,0);
                glTranslatef( 0.04 , 0.13 , 0.00 );//glTranslatef(dx,dy,dz);
                glmDraw(LL2, GLM_TEXTURE | GLM_SMOOTH);
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
    bg = myTexture("data/background1.jpg");
    glClearColor(0.7,0.8,0.85,0);
    myReadAll();

    mp3.Load("music.wav");
    mp3.Play();
    glutMainLoop();
}
