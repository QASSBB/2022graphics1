
#include <stdio.h>
int main()
{
    FILE * fout = fopen("file.txt", "w+");
    fprintf(fout,"3.1515926");
    fclose(fout);

    float angle=0;
    FILE * fin = fopen("file.txt", "r");
    fscanf(fin,"%f", &angle);
    printf("Åª¨ì¤F¨¤«×%f",angle);
    fclose(fin);
}
