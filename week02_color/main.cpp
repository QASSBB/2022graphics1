#include <GL/glut.h> ///使用GLUT外掛簡化程式

void display ()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glColor3f(1,1,0);///設定色彩
    glBegin(GL_POLYGON);
        glColor3f(1,1,0);///紅色
        glVertex2f(-1,-1);

        glColor3f(0,1,0);///綠色
        glVertex2f(+1,-1);

        glColor3f(0,0,1);///綠色
        glVertex2f(0,+1);
    glEnd();
    glutSwapBuffers();///畫好後，交換出來
}

int main (int argc,char** argv)///main()主函式 進階版
{
    glutInit( &argc,argv);///把參數，送給glutInit 初始化
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_DEPTH);///雙緩衝區+3D深度功能
    glutCreateWindow("第二周的程式!");///開GLUT視窗

    glutDisplayFunc(display);///用來顯示的函式
    glutMainLoop();///主要的程式迴圈
}
