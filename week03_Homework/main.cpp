#include <GL/glut.h>

#include <stdio.h>

float mouseX=0,mouseY=0;

void myTeapot(float x,float y)

{

    glPushMatrix();///�ƥ��x�}(�ƥ��ª���m)

        glTranslatef(x,y,0);

        glColor3f(40/255.0 ,175/255.0 ,236/255.0);

        glutSolidTeapot(0.1);

    glPopMatrix();///�٭�x�}(�٭��ª���m)

}

void display()

{

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    ///myTeapot((mouseX-150)/150.0,-(mouseY-150)/150.0);
    glutSwapBuffers();

}

void mouse(int button,int state,int x,int y)

{

    ///printf("%d %d %d %d\n",button,state,x,y);
    printf(" glVertex2f( (%d-150)/150.0, -(%d-150)/150.0);\n",x,y); ///�L�X�ƹ��y��
    mouseX=x; mouseY=y;

}



int main (int argc,char **argv)

{

    glutInit(&argc,argv);

    glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH);

    glutCreateWindow("week03_����");

    glutDisplayFunc(display);

    glutMouseFunc(mouse);

    glutMainLoop();

}
