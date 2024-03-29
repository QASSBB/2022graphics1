#include <GL/glut.h>
void myTeapot(float x,float y)
{
    glPushMatrix();///備份矩陣(備份舊的位置)
        glTranslatef(x,y,0);
        glColor3f(1,1,0);///黃色
        glutSolidTeapot(0.3);///茶壺
    glPopMatrix();///還原矩陣(還原舊的位置)
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    myTeapot(0.5,0.5);
    myTeapot(0.5,-0.5);
    myTeapot(-0.5,-0.5);
    myTeapot(-0.5,0.5);

    glutSwapBuffers();
}
int main (int argc,char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH);
    glutCreateWindow("week03_移動");
    glutDisplayFunc(display);
    glutMainLoop();
}
