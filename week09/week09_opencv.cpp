#include <opencv/highgui.h>//�ϥ�opencv�~��

int main ()

{///Ipl : Intel performance library

    IplImage * img = cvLoadImage("123.jpg"); //Ū��

    cvShowImage("week09",img); //�q��

    cvWaitKey(0); //���ݥ��N���~��
}
