#include <stdio.h>
#include <GL/glut.h>
#include <mmsystem.h>
void timer (int t){
    printf("�_�ɡA�{�b�ɶ�: %d\n",t);
    PlaySound("do.wav", NULL , SND_ASYNC);
    glutTimerFunc(2000,timer, t+1);
}
void display(){
}
int main (int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("week14 timer");

    glutTimerFunc(5000, timer, 0);

    glutDisplayFunc(display);
    glutMainLoop();
}