#include <GL/glut.h>
#include <stdio.h>
#include "glm.h"
GLMmodel * pmodel = NULL;///全部的模型
GLMmodel * body = NULL;///分塊的模型
GLMmodel * head = NULL;
GLMmodel * arm1 = NULL;
GLMmodel * arm2 = NULL;
GLMmodel * hand1 = NULL;
GLMmodel * hand2 = NULL;
GLMmodel * bot = NULL;
GLMmodel * leg1 = NULL;
GLMmodel * leg2 = NULL;
float angle[20],oldX=0;
int angleID=0;
FILE * fout = NULL, * fin = NULL;
void myWrite(){
    if(fout == NULL) fout = fopen("file.txt", "w+");
    for(int i=0 ; i<20 ; i++){
        printf(" %.1f ", angle[i]);
        fprintf(fout, " %.1f ",angle[i]);
    }
    printf("\n");
    fprintf(fout,"\n");
}
void myread(){
    if(fout != NULL){   fclose(fout); fout=NULL;  }
    if(fin == NULL) fin = fopen("file.txt", "r");
    for(int i=0 ; i<20 ; i++){
        fscanf(fin, "%f",&angle[i]);
    }
    glutPostRedisplay();
}
void mouse(int Button, int state, int x, int y){
    oldX= x;
}
void keyboard (unsigned char key,int x,int y){
    if(key=='s') myWrite(); ///調好動作再存檔
    if(key=='r') myread();
    if(key=='0') angleID=0;
    if(key=='1') angleID=1;
    if(key=='2') angleID=2;
    if(key=='3') angleID=3;
}
void motion(int x,int y){
    angle[angleID] += (x-oldX);
    ///myWrite();
    oldX = x;
    glutPostRedisplay();
}
GLMmodel * myReadOne(Char * filename){
    GLMmodel * one=NULL;
    if(one==NULL){
        one = glmReadOBJ(filename);
        glmUnitize(one);
        glmFaceNormals(one);
        glmVertexNormals(one,90);
    }
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1,1,1);
    glRectf(0.3,0.5,-0.3,-0.5);

    if(body==NULL) body = myReadOne("data/body.obj"); ///身體
    glmDraw(body,GLM_TEXTURE | GLM_SMOOTH);

    glPushMatrix();
        glTranslatef(0.3,0.4,0);
        glRotatef(angle[0],0,0,1);
        glTranslatef(-0.3,-0.4,0);
        glColor3f(1,0,0);
        glRectf(0.3,0.5,0.7,0.3);

        glPushMatrix();
            glTranslatef(0.7,0.4,0);
            glRotatef(angle[1],0,0,1);
            glTranslatef(-0.7,-0.4,0);
            glColor3f(0,1,0);
            glRectf(0.7,0.5,1,0.3);
        glPopMatrix();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-0.3,0.4,0);
        glRotatef(angle[2],0,0,1);
        glTranslatef(0.3,-0.4,0);
        glColor3f(1,0,0);
        glRectf(-0.3,0.5,-0.7,0.3);

        glPushMatrix();
            glTranslatef(-0.7,0.4,0);
            glRotatef(angle[3],0,0,1);
            glTranslatef(0.7,-0.4,0);
            glColor3f(0,1,0);
            glRectf(-0.7,0.5,-1,0.3);
        glPopMatrix();
    glPopMatrix();


    glutSwapBuffers();
}
int main(int argc, char**argv)
{
    glutInit( &argc, argv );
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    ///glutInitWindowSize(600,600);
    glutCreateWindow("week15-1_angles_TRT_again");

    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutDisplayFunc(display);
    glutMainLoop();
}
