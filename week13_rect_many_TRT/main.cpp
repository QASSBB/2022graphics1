#include <GL/glut.h>
float angle[20],oldX=0;
int angleID=0;
void mouse(int Button, int state, int x, int y){
    oldX= x;
}
void keyboard (unsigned char key,int x,int y){
    if(key=='0') angleID=0;
    if(key=='1') angleID=1;
    if(key=='2') angleID=2;
    if(key=='3') angleID=3;
}
void motion(int x,int y){
    angle[angleID] += (x-oldX);
    oldX = x;
    glutPostRedisplay();
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1,1,1);///白色
    glRectf(0.3,0.5,-0.3,-0.5); ///身體
    glPushMatrix();
        glTranslatef(0.3,0.4,0); ///把手臂放回身體
        glRotatef(angle[0],0,0,1);    ///旋轉
        glTranslatef(-0.3,-0.4,0); ///手臂的旋轉中心
        glColor3f(1,0,0);
        glRectf(0.3,0.5,0.7,0.3);

        glPushMatrix();
            glTranslatef(0.7,0.4,0); ///把手臂放回身體
            glRotatef(angle[1],0,0,1);    ///旋轉
            glTranslatef(-0.7,-0.4,0); ///手臂的旋轉中心
            glColor3f(0,1,0);
            glRectf(0.7,0.5,1,0.3);
        glPopMatrix();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-0.3,0.4,0); ///把手臂放回身體
        glRotatef(angle[2],0,0,1);    ///旋轉
        glTranslatef(0.3,-0.4,0); ///手臂的旋轉中心
        glColor3f(1,0,0);
        glRectf(-0.3,0.5,-0.7,0.3);

        glPushMatrix();
            glTranslatef(-0.7,0.4,0); ///把手臂放回身體
            glRotatef(angle[3],0,0,1);    ///旋轉
            glTranslatef(0.7,-0.4,0); ///手臂的旋轉中心
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
    glutCreateWindow("week13 rect TRT");

    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutDisplayFunc(display);
    glutMainLoop();
}
