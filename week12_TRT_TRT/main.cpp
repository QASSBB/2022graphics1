#include <GL/glut.h>
float angle=0;
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1,1,1); ///白色
    glutSolidTeapot(0.3);///茶壺身體
    glPushMatrix();
        glTranslatef(0.2,0,0);///3.將茶壺手臂往右邊移動
        glRotatef(angle,0,0,1); ///2.旋轉
        glTranslatef(0.2,0,0);/// 1.把茶壺旋轉中心放到世界中心
        glColor3f(1,0,0);///紅色
        glutSolidTeapot(0.2);///茶壺手臂
        glPushMatrix();
            glTranslatef(0.2,0,0);///3.將茶壺手臂往右邊移動
            glRotatef(angle,0,0,1); ///2.旋轉
            glTranslatef(0.2,0,0);/// 1.把茶壺旋轉中心放到世界中心
            glColor3f(1,0,0);///紅色
            glutSolidTeapot(0.2);///茶壺手臂
        glPopMatrix();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-0.2,0,0);///3.將茶壺手臂往右邊移動
        glRotatef(-angle,0,0,1); ///2.旋轉
        glTranslatef(-0.2,0,0);/// 1.把茶壺旋轉中心放到世界中心
        glColor3f(1,0,0);///紅色
        glutSolidTeapot(0.2);///茶壺手臂
        glPushMatrix();
            glTranslatef(-0.2,0,0);///3.將茶壺手臂往右邊移動
            glRotatef(-angle,0,0,1); ///2.旋轉
            glTranslatef(-0.2,0,0);/// 1.把茶壺旋轉中心放到世界中心
            glColor3f(1,0,0);///紅色
            glutSolidTeapot(0.2);///茶壺手臂
        glPopMatrix();
    glPopMatrix();
    glutSwapBuffers();
    angle+=0.05;
}
int main(int argc, char**argv)
{
    glutInit( &argc, argv );
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("week12 TRT");

    glutIdleFunc(display);
    glutDisplayFunc(display);
    glutMainLoop();
}
