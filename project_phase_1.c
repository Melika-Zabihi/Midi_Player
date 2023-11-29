#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include "beep.h"
int note_to_frequence();
int main()
{
    int i, time[100];
    double freq;
    char note[1000][3], line[1000];
    FILE *NoteFile;

    NoteFile=fopen("NOTES.txt","r");
    fgets(line, 20, NoteFile);
    sscanf(line,"-N %s -d %d\n",&note[0],&time[0]);
    beep(392.00,750);

    // reads all the notes from line 2 to 100 from NOTES.txt
    for(i=1; i<=100; i++)
    {
        fgets(line, 20, NoteFile);
        if(i==55 || i==60)
        continue;
        sscanf(line,"-n -N %s -d %d\n",&note[i],&time[i]);
        freq=note_to_frequence(note[i]);
        beep(freq,time[i]+250);
    }
    fclose(NoteFile);
}

// gets the note and changes it to its frequence from note_frequence.txt file
int note_to_frequence(char x[3])
{
    int i;
    double freq[110];
    char line[110], note[110][3],*result;
    FILE *NoteFile2;
    NoteFile2=fopen("note_frequence.txt", "r");

    // it searchs the notes until it finds it and returns the frequence equal to it
    for(i=0; i<109; i++)
    {
        fgets(line, 20, NoteFile2);
        sscanf(line,"%s %lf\n",&note[i],&freq[i]);
        result=strstr(note[i],x);
        if (result!=NULL)
        {
            return (freq[i]);
        }
    }
}
