#include <GL/glut.h>
#include <stdio.h>
int mx[1000],my[1000];
int N=0;
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBegin(GL_LINE_LOOP);
    for(int i=0 ; i<N ; i++)
    {
        glVertex2f( (mx[i]-150)/150.0, -(my[i]-150)/150.0);
    }
    glEnd();
    glutSwapBuffers();
}

void mouse(int button,int state,int x,int y)
{
    if(state==GLUT_DOWN)
    {
        printf("    glVertex2f( (%d-150)/150.0,-(%d-150)/150.0);\n",x,y);
        N++;
        mx[N-1]=x; my[N-1]=y;
    }
    display();
}
int main (int argc,char**argv)
{
    glutInit( &argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("week04 Rotate");
    glutDisplayFunc(display);

    glutMouseFunc(mouse);/// 上週教過: mouse 按下去、放開來
    glutMainLoop();
}
