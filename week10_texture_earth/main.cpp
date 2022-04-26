#include <opencv/highgui.h> ///使用 OpenCV 2.1 比較簡單, 只要用 High GUI 即可
#include <opencv/cv.h>
#include <GL/glut.h>
GLUquadric * sphere = NULL; ///指標，指到二次曲面
int myTexture(char * week09_opencv)
{

    IplImage * img = cvLoadImage(week09_opencv); ///OpenCV讀圖
    cvCvtColor(img,img, CV_BGR2RGB); ///OpenCV轉色彩 (需要cv.h)
    glEnable(GL_TEXTURE_2D); ///1. 開啟貼圖功能
    GLuint id; ///準備一個 unsigned int 整數, 叫 貼圖ID
    glGenTextures(1, &id); /// 產生Generate 貼圖ID
    glBindTexture(GL_TEXTURE_2D, id); ///綁定bind 貼圖ID
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); /// 貼圖參數, 超過包裝的範圖T, 就重覆貼圖
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); /// 貼圖參數, 超過包裝的範圖S, 就重覆貼圖
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); /// 貼圖參數, 放大時的內插, 用最近點
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); /// 貼圖參數, 縮小時的內插, 用最近點
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img->width, img->height, 0, GL_RGB, GL_UNSIGNED_BYTE, img->imageData);
    return id;
}
float angle = 0; ///旋轉角度
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
        glRotatef(90,1,0,0);  ///將地球轉正
        glRotatef(angle,0,0,1);
        gluQuadricTexture(sphere,1);///設好貼圖
        gluSphere(sphere,1,30,30);///畫圓球
    glPopMatrix();
        //glutSolidTeapot(0.3);
        /*glBegin(GL_POLYGON);
            glTexCoord2f(0,1);glVertex2f(-1,-1);
            glTexCoord2f(1,1);glVertex2f(+1,-1);
            glTexCoord2f(1,0);glVertex2f(+1,+1);
            glTexCoord2f(0,0);glVertex2f(-1,+1);
        glEnd();*/
    glutSwapBuffers();
    angle+=0.1; ///每次執行display()加一度
}
int main(int argc, char**argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("week09 texture");

    glEnable(GL_DEPTH_TEST); ///開啟3D功能(地球才有3D的效果)
    glutIdleFunc(display); ///idle呼叫display
    glutDisplayFunc(display);
    myTexture("earth.jpg"); ///地球的地圖，等下才會進來
    sphere = gluNewQuadric(); ///準備好二次曲面
    glutMainLoop();
}
