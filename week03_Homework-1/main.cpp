#include <GL/glut.h>
#include <math.h>

void myCircle( float r )
{
    glBegin(GL_POLYGON);
    for(float a=0; a<3.1415926*2; a+=0.01){
        glVertex2f( r*cos(a),r*sin(a));
    }
    glEnd();
}
void display()
{

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glColor3f(40/255.0 ,175/255.0 ,236/255.0);
    glBegin(GL_POLYGON);
    glVertex2f( (42-150)/150.0, -(95-150)/150.0);
 glVertex2f( (62-150)/150.0, -(61-150)/150.0);
 glVertex2f( (66-150)/150.0, -(59-150)/150.0);
 glVertex2f( (96-150)/150.0, -(32-150)/150.0);
 glVertex2f( (98-150)/150.0, -(30-150)/150.0);
 glVertex2f( (138-150)/150.0, -(17-150)/150.0);
 glVertex2f( (140-150)/150.0, -(17-150)/150.0);
 glVertex2f( (191-150)/150.0, -(21-150)/150.0);
 glVertex2f( (191-150)/150.0, -(22-150)/150.0);
 glVertex2f( (238-150)/150.0, -(57-150)/150.0);
 glVertex2f( (239-150)/150.0, -(59-150)/150.0);
 glVertex2f( (247-150)/150.0, -(113-150)/150.0);
 glVertex2f( (247-150)/150.0, -(113-150)/150.0);
 glVertex2f( (245-150)/150.0, -(163-150)/150.0);
 glVertex2f( (244-150)/150.0, -(166-150)/150.0);
 glVertex2f( (219-150)/150.0, -(210-150)/150.0);
 glVertex2f( (217-150)/150.0, -(211-150)/150.0);
 glVertex2f( (168-150)/150.0, -(233-150)/150.0);
 glVertex2f( (167-150)/150.0, -(234-150)/150.0);
 glVertex2f( (117-150)/150.0, -(242-150)/150.0);
 glVertex2f( (116-150)/150.0, -(242-150)/150.0);
 glVertex2f( (78-150)/150.0, -(231-150)/150.0);
 glVertex2f( (77-150)/150.0, -(231-150)/150.0);
 glVertex2f( (55-150)/150.0, -(206-150)/150.0);
 glVertex2f( (55-150)/150.0, -(206-150)/150.0);
 glVertex2f( (42-150)/150.0, -(179-150)/150.0);
 glVertex2f( (41-150)/150.0, -(177-150)/150.0);
 glVertex2f( (28-150)/150.0, -(138-150)/150.0);
 glVertex2f( (28-150)/150.0, -(135-150)/150.0);

 glColor3f(0 ,0,0);
    glBegin(GL_POLYGON);
  glVertex2f( (33-150)/150.0, -(82-150)/150.0);
 glVertex2f( (34-150)/150.0, -(82-150)/150.0);
 glVertex2f( (53-150)/150.0, -(93-150)/150.0);
 glVertex2f( (54-150)/150.0, -(93-150)/150.0);
 glVertex2f( (81-150)/150.0, -(106-150)/150.0);
 glVertex2f( (82-150)/150.0, -(106-150)/150.0);
 glVertex2f( (82-150)/150.0, -(118-150)/150.0);
 glVertex2f( (78-150)/150.0, -(118-150)/150.0);
 glVertex2f( (51-150)/150.0, -(117-150)/150.0);
 glVertex2f( (49-150)/150.0, -(117-150)/150.0);
 glVertex2f( (19-150)/150.0, -(118-150)/150.0);
 glVertex2f( (19-150)/150.0, -(118-150)/150.0);
 glVertex2f( (104-150)/150.0, -(146-150)/150.0);
 glVertex2f( (104-150)/150.0, -(149-150)/150.0);
 glVertex2f( (82-150)/150.0, -(165-150)/150.0);
 glVertex2f( (82-150)/150.0, -(165-150)/150.0);
 glVertex2f( (35-150)/150.0, -(188-150)/150.0);
 glVertex2f( (35-150)/150.0, -(188-150)/150.0);
 glVertex2f( (187-150)/150.0, -(84-150)/150.0);
 glVertex2f( (190-150)/150.0, -(84-150)/150.0);
 glVertex2f( (219-150)/150.0, -(76-150)/150.0);
 glVertex2f( (221-150)/150.0, -(76-150)/150.0);
 glVertex2f( (253-150)/150.0, -(61-150)/150.0);
 glVertex2f( (253-150)/150.0, -(61-150)/150.0);
 glVertex2f( (190-150)/150.0, -(111-150)/150.0);
 glVertex2f( (190-150)/150.0, -(111-150)/150.0);
 glVertex2f( (227-150)/150.0, -(110-150)/150.0);
 glVertex2f( (227-150)/150.0, -(110-150)/150.0);
 glVertex2f( (276-150)/150.0, -(121-150)/150.0);
 glVertex2f( (276-150)/150.0, -(123-150)/150.0);
 glVertex2f( (176-150)/150.0, -(147-150)/150.0);
 glVertex2f( (180-150)/150.0, -(145-150)/150.0);
 glVertex2f( (223-150)/150.0, -(160-150)/150.0);
 glVertex2f( (227-150)/150.0, -(163-150)/150.0);
 glVertex2f( (254-150)/150.0, -(185-150)/150.0);
 glVertex2f( (255-150)/150.0, -(185-150)/150.0);
    glutSwapBuffers();
}

int main (int argc,char **argv)

{

    glutInit(&argc,argv);

    glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH);

    glutCreateWindow("week03_����");

    glutDisplayFunc(display);

    glutMainLoop();

}
