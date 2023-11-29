#include<stdio.h>
int main()
{
    unsigned char chunk_type[4], lenght[4], format[2], track[2], division[2];
    char name[100];
    FILE *midi;

    gets(name);
    midi=fopen(name,"rb");

    if(midi==NULL) //checks if the file was found
    {
        printf("Sorry file was not found!");
        return 0;
    }

    printf("------------\n");

    fread(chunk_type, 4, 1, midi);
    chunk_type[4]='\0';
    printf("%s\n",chunk_type);

    fread(lenght, 4, 1, midi);
    printf("lenght %d\n",lenght[3] | lenght[2]<<8 | lenght[1]<<16 | lenght[0]<<24);

    fread(format, 2, 1, midi);
    printf("format %d\n",format[1] | format[0]<<8);

    fread(track, 2, 1, midi);
    printf("track %d\n",track[1] | track[0]<<8);

    fread(division, 2, 1, midi);
    printf("division %d\n",division[1] | division[0]<<8);

    printf("-------------\n");

    fclose(midi);

}
