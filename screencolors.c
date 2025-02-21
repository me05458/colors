#include<stdio.h>
#include <sodium.h>
#include <math.h>

typedef struct{
    int rgb[3]; //doesn't necessarily have that many numbers, just spaces for em;
}color;

//turns chars into ints
int charEater(char c)
{
    int result =  c - '0'; //the numbers are consecutive so subtract 0
    if(result > 9||result<0) //it's a letter/other character
        return -1;
    return result;
}
//printf("\x1b[38;2;%d;%d;%dmsomething\x1b[0m\n",red,blue,transparency);
int main(int argc, char *argv[]) {
        //printf("\x1b[38;2;%d;%d;0mhi\n\x1b[0m",i,225-i);
    //library init
    char randString[32];
    if(sodium_init() <0){
        printf("A Catastrophic Faliure Occured (EXIT CODE 2)\n");
        return 2;
    }
    randombytes_buf(randString, 32);
    int set = 0;
    if(argc ==1)
    {
        printf("please specify an action\n");
        set = 10;
    }
    else
    {
        int counter = 0;
        char c = argv[1][counter];
        while(c != NULL)
        {
            counter++;
            c = argv[1][counter];
        }
        for(int i=counter-1; i>=0; i--)
        {
            int tmp = charEater(argv[1][(counter-1)-i]);
            //int tmp = 1;
            set+=tmp*(int)pow(10,i);
        }
    }
    //printf("%d",set);
    color screen[set];
    int r = randombytes_uniform(225);
    int g = randombytes_uniform(225);
    int b = randombytes_uniform(225);

    for(int i = 0; i<set; i++)
    {
        screen[i].rgb[0] = 0;
        screen[i].rgb[1] = 0;
        screen[i].rgb[2] = 0;
        printf("\x1b[48;2;%d;%d;%dm  \x1b[0m",screen[i].rgb[0],screen[i].rgb[1],screen[i].rgb[2]);
    }
    printf("\n");
    int m = 1;
    int i = -1;
    while(m!=10)
    {
        int tmp;
        int rgbtmp;
        int sset;
        if(i < 0)
        {
            tmp = randombytes_uniform(set);
            rgbtmp = randombytes_uniform(3);
            sset = randombytes_uniform(2);
            //printf("%d|%d|%d\n",tmp,rgbtmp,set);
            if(sset == 0)
            {
                if(screen[tmp].rgb[rgbtmp] < 225)
                {
                    screen[tmp].rgb[rgbtmp] +=1;
                }
                else{
                    screen[tmp].rgb[rgbtmp] = 0;
                }
            }
            else
            {
                if(sset == 1)
                {
                    if(screen[tmp].rgb[rgbtmp] > 0)
                    {
                        screen[tmp].rgb[rgbtmp] -=1;
                    }
                    else
                    {
                        screen[tmp].rgb[rgbtmp] = 0;
                    }
                }
            }
            i = 10;
        }
        else
        {
            if(sset == 0)
            {
                if(screen[tmp].rgb[rgbtmp] < 225)
                {
                    screen[tmp].rgb[rgbtmp] +=1;
                }
                else{
                    screen[tmp].rgb[rgbtmp] = 0;
                }
            }
            else
            {
                if(sset == 1)
                {
                    if(screen[tmp].rgb[rgbtmp] > 0)
                    {
                        screen[tmp].rgb[rgbtmp] -=1;
                    }
                    else
                    {
                        screen[tmp].rgb[rgbtmp] = 0;
                    }
                }
            }
            i--;
        }
        for(int i = 0; i<set; i++)
        {
            //printf("%d",i);
            //printf("%d/%d/%d\n",screen[i].rgb[0],screen[i].rgb[1],screen[i].rgb[2]);
            printf("\x1b[48;2;%d;%d;%dm  \x1b[0m",screen[i].rgb[0],screen[i].rgb[1],screen[i].rgb[2]);
        }
        printf("\n");
    }
    return 0;
}
