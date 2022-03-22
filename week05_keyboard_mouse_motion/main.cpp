#include <GL/glut.h>
#include <stdio.h>
float x=150,y=150,z=0,scale=1.0;
int oldX=0,oldY=0;
void display()
{
    glClearColor(0.5,0.5,0.5,1);///RGB�䤤A�b�z���\��.���ثe�S�}
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();///�ƥ��x�}
        glTranslatef((x-150)/150.0,-(y-150)/150.0,z);
        glScaled(scale,scale,scale);///���Y��scale��
        glColor3f(1,1,0);///���⪺
        glutSolidTeapot(0.3);///����
    glPopMatrix();///�٭�x�}
    glutSwapBuffers();

}
void keyboard(unsigned char key,int mouseX,int mouseY)
{

}
void mouse(int bitton,int state,int mouseX,int mouseY)
{
    oldX= mouseX; oldY= mouseY;
}
void motion(int mouseX,int mouseY)
{
    if( mouseX-oldX >0) scale*= 1.01;
    if( mouseX-oldX <0) scale*= 0.99;
    ///x+=(mouseX-oldX); y+=(mouseY-oldY);
    oldX =mouseX;     oldY= mouseY;
    display();
}
int main (int argc,char**argv)
{
    glutInit( &argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("week04 Rotate");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMotionFunc(motion);
    glutMouseFunc(mouse);
    glutMainLoop();
}
