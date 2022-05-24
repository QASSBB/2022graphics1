#include <stdio.h>
#include <GL/glut.h>
void timer (int t){
    printf("起床，現在時間: %d\n",t);
}
void display(){
}
int main (int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("week14 timer");

    glutTimerFunc(2000, timer, 1);
    glutTimerFunc(3000, timer, 2);
    glutTimerFunc(4000, timer, 3);
    glutTimerFunc(5000, timer, 4);
    glutTimerFunc(6000, timer, 5);
    glutDisplayFunc(display);
    glutMainLoop();
}
