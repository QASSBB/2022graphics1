#include <opencv/highgui.h>
#include <opencv/cv.h>
#include <GL/glut.h>
#include "glm.h"
GLMmodel * pmodela1 = NULL;
GLMmodel * pmodela2 = NULL;
GLMmodel * pmodela3 = NULL;
GLMmodel * pmodela4 = NULL;
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
float angle=0;
float angle2=0;
float angle3=0;
float x;
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if( pmodela1 == NULL){
        pmodela1 = glmReadOBJ("data/body.obj");
        glmUnitize( pmodela1 );
        glmFacetNormals( pmodela1 );
        glmVertexNormals( pmodela1 , 90);
    }
        if( pmodela2 == NULL){
        pmodela2 = glmReadOBJ("data/hand.obj");
        glmUnitize( pmodela2 );
        glmFacetNormals( pmodela2 );
        glmVertexNormals( pmodela2 , 90);
    }
        if( pmodela3 == NULL){
        pmodela3 = glmReadOBJ("data/leg.obj");
        glmUnitize( pmodela3 );
        glmFacetNormals( pmodela3 );
        glmVertexNormals( pmodela3 , 90);
    }
        if( pmodela4 == NULL){
        pmodela4 = glmReadOBJ("data/head.obj");
        glmUnitize( pmodela4 );
        glmFacetNormals( pmodela4 );
        glmVertexNormals( pmodela4 , 90);
    }


////////////////////////////////////////////////
glPushMatrix();

    glTranslatef(x,0,0);
    glPushMatrix();///head
        glTranslatef(0,0.5,0);
        glRotatef(angle3,0,1,0);
        glmDraw(pmodela4,GLM_TEXTURE);
    glPopMatrix();

    glPushMatrix();///legL
        glRotatef(angle2,0,0,1);
        glColor3f(1,1,1);
        glTranslatef(-0.1,-0.45,0);
        glmDraw(pmodela3,GLM_TEXTURE);
    glPopMatrix();

    glPushMatrix();///legR
        glRotatef(-angle2,0,0,1);
        glColor3f(1,1,1);
        glTranslatef(0.1,-0.45,0);
        glRotatef(180,0,1,0);
        glmDraw(pmodela3,GLM_TEXTURE);
    glPopMatrix();


    glPushMatrix();///body
        glScalef(0.4,0.4,0.4);
        glColor3f(1,1,1);
        glmDraw(pmodela1,GLM_TEXTURE);
    glPopMatrix();

    glPushMatrix();///hands
        glTranslatef(0.15,0.3,0);///整根位置
        glRotatef(angle,0,0,1);//旋轉
        glTranslatef(0.135,0,0);///中心點位置
        glRotatef(90,0,0,1);
        glScalef(3,3,3);
        glColor3f(1,1,1);
        glmDraw(pmodela2,GLM_TEXTURE);
        glPushMatrix();///hands
            glTranslatef(0,-0.05,0);
            glRotatef(angle*3,0,0,1);//旋轉
            glTranslatef(0,-0.05,0);
            glColor3f(1,1,1);
            glmDraw(pmodela2,GLM_TEXTURE);
        glPopMatrix();
    glPopMatrix();
    ///左手
    glPushMatrix();///hands
        glTranslatef(-0.15,0.3,0);///整根位置
        glRotatef(angle,0,0,1);//旋轉
        glTranslatef(-0.135,0,0);///中心點位置
        glRotatef(90,0,0,1);
        glScalef(3,3,3);
        glColor3f(1,1,1);
        glmDraw(pmodela2,GLM_TEXTURE);
        glPushMatrix();///hands
            glTranslatef(0,+0.05,0);
            glRotatef(-angle*3,0,0,1);//旋轉
            glTranslatef(0,+0.05,0);
            glColor3f(1,1,1);
            glmDraw(pmodela2,GLM_TEXTURE);
        glPopMatrix();
    glPopMatrix();
glPopMatrix();
    glutSwapBuffers();
    angle+=0.5;
    angle2-=0.05;
    if(angle2<=-8) angle2=0;
    x+=0.001;
    if(x>=1) x=-1;
    angle3+=0.5;
}
int main(int argc, char**argv)
{
    glutInit( &argc, argv );
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("week12 homework");
    myTexture("data/aqua.png");
    glutIdleFunc(display);
    glutDisplayFunc(display);
    glEnable(GL_DEPTH);
    glutMainLoop();
}
