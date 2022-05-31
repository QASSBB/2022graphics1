#include <stdio.h>
#include "CMP3_MCI.h"
CMP3_MCI mp3;

int main ()
{
    mp3.Load("07071034.wav");
    mp3.Play();

    printf("輸入數字程式卡住");
    int N;
    scanf("%d",&N);
}
