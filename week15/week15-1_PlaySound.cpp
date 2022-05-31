#include <windows.h>
#include <stdio.h>
int main()
{
    printf("PlaySound()之前\n");
    PlaySound("07071034.wav", NULL, SND_SYNC);
    printf("PlaySound()之後\n");
}
