#include <windows.h>
#include <stdio.h>
int main()
{
    printf("PlaySound()���e\n");
    PlaySound("07071034.wav", NULL, SND_SYNC);
    printf("PlaySound()����\n");
}
