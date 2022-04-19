#include <opencv/highgui.h>//使用opencv外掛

int main ()

{///Ipl : Intel performance library

    IplImage * img = cvLoadImage("123.jpg"); //讀圖

    cvShowImage("week09",img); //秀圖

    cvWaitKey(0); //等待任意鍵繼續
}
