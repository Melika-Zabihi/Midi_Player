#include<stdio.h>
#include<string.h>

void header(FILE *file);
void lenght(FILE *file);
void format(FILE *file);
int tracks(FILE *file);
void division(FILE *file);
int read_tracks(FILE *file, int tracks_end);
void hex_to_note(int n);

int main()
{
    unsigned char byte;
    char name[100];
    int End_of_track;
    FILE *midi;

    gets(name);
    midi=fopen(name,"rb");

    if(midi==NULL)
    {
        printf("Sorry, file was not found!\n");
        return 0;
    }

    printf("-------------\n");
    header(midi);
    length(midi);
    format(midi);
    End_of_track=tracks(midi);
    division(midi);
    printf("-------------\n");

    read_tracks(midi,End_of_track);

    fclose(midi);
}

int read_tracks(FILE *file , int track_end)
{
    int read=0, tempo,d=0, note[10000],n=0,numeratur,denominator;
    char velocity,notes, temp[100],len;
    unsigned char event,byte,tem[3],track_chunk[4];
    fread(track_chunk,4,1,file);
    while(1)
    {
        //every time, it scans one byte and checks what kind of event it is
        fread(&byte,1,1,file);

        if(byte==0xFF)
        {
            fread(&event,1,1,file);

            if(event==0x01 || event==0x02 || event==0x03 || event==0x04 ||
            event==0x05 || event==0x06 || event==0x07 || event==0x7F)
            {
                fread(&len,1,1,file);
                fread(temp,len,1,file);
            }

            if(event==0x20)
                fread(&temp,1,1,file);

            if(event==0x2F)
            {
                d++;
                if(d == track_end)
                {
                    printf("This is the end of file\n");
                    return 0;
                }
                fread(track_chunk,4,1,file);
            }
            if(event==0x51) //this shows the tempo of the midi file
            {
                fread(&len,1,1,file);
                fread(tem,len,1,file);
                tempo=tem[2] | tem[1]<<8 | tem[0]<<16;
                printf("The tempo is: %d\n",tempo);
            }

            if(event==0x54)
            {
                fread(&len,1,1,file);
                fread(temp,len,1,file);
            }
            if(event==0x58) //this shows the signature of the midi file
            {
                fread(&len,1,1,file);
                fread(temp,len,1,file);
                numeratur=temp[0];
                denominator=temp[1];
                printf("Time Signature is: %d/%d\n", numeratur, denominator);

            }
            if(event==0x59) //this shows the key signature of the midi file
            {
                fread(&len,1,1,file);
                fread(temp,len,1,file);
                printf("Key Signature is %d\n",temp[1] | temp[0]<<8);
            }
        }

        if(byte>=0x90 && byte<=0x9F) //this shows what note is playing
        {
            fread(&notes,1,1,file);
            fread(&velocity,1,1,file);
            note[n]=notes;
            printf("'Note on' and its note is ");
            hex_to_note( note[n] );
            n++;
            read=1;
        }
        if(byte>=0x80 && byte<=0x8F && read==1) //this shows the note was ended
        {
            printf("'Note off'\n");
            fread(temp,1,1,file);
            read=0;
        }

    }
}

// it gets notes by its hex number and changes it to their char notes
void hex_to_note( int n )
{
    char line[100],*result,note[2];
    int i,hex;
    FILE *file;
    file=fopen("hex_to_note.txt","r");
    for(i=0; i<129; i++)
    {
        fgets(line, 20, file);
        sscanf(line,"%d %s\n",&hex,&note);
        if(hex == n)
            printf("%s\n",note);
    }
}

//functions for printing the header chunk
void header(FILE *file)
{
    unsigned char chunk_type[4];
    fread(chunk_type, 4, 1, file);
    chunk_type[4]='\0';
    printf("%s\n",chunk_type);
}
void length(FILE *file)
{
    unsigned char length[4];
    fread(length, 4, 1, file);
    printf("lenght %d\n",length[3] | length[2]<<8 | length[1]<<16 | length[0]<<24);
}
void format(FILE *file)
{
    unsigned char format[2];
    fread(format, 2, 1, file);
    printf("format %d\n",format[1] | format[0]<<8);
}
int tracks(FILE *file)
{
    unsigned char tracks[2];
    int a;
    fread(tracks, 2, 1, file);
    a=tracks[1] | tracks[0]<<8;
    printf("tracks %d\n",a);
    return a;
}
void division(FILE *file)
{
    unsigned char division[2];
    fread(division, 2, 1, file);
    printf("division %d\n",division[1] | division[0]<<8);
}

