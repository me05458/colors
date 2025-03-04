#include <math.h>
#include <unistd.h>
#include "render.h"
#include<stdio.h>

int getConfig(int line) //return - 0 cool, 1- bad
{
    FILE *ptr = fopen("config", "r");
    if (ptr == NULL) {
        printf("ERROR: something went wrong while opening file\n");
    }
    int result = -1;
    int i = 0;
    while (fscanf(ptr, "%d", &result) > 0 && i < line) {
            i++;
    }
    if(result<0)
    {
        printf("ERROR: file has inadequate number of lines or something like that\n");
    }
    return result;

}
void testScreen(int h, int w)
{
    for(int i = 0; i<h; i++)
    {
        for(int j = 0; j<w; j++)
        {
            printf("-]");
        }
        printf("\n");
    }
}
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
    if(getConfig(1) == 1)
    {
        int set = 0;
        if(argc ==1)
        {
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
        return basicLines(set);
    }
    else {
        if(getConfig(1)==2)
        {
            int x = 0;
            int y = 0;
            if(argc <=2)
            {
                y = 10;
                x = 10;
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
                    x+=tmp*(int)pow(10,i);
                }
                counter = 0;
                c = argv[1][counter];
                while(c != NULL)
                {
                    counter++;
                    c = argv[2][counter];
                }
                for(int i=counter-1; i>=0; i--)
                {
                    int tmp = charEater(argv[2][(counter-1)-i]);
                    //int tmp = 1;
                    y+=tmp*(int)pow(10,i);
                }
            }
            return forfunsies(x,y);
        }
        else
        {
            if(getConfig(1) == 3)
            {
                int x = 0;
                int y = 0;
                if(argc <=2)
                {
                    y = 10;
                    x = 10;
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
                        x+=tmp*(int)pow(10,i);
                    }
                    counter = 0;
                    c = argv[1][counter];
                    while(c != NULL)
                    {
                        counter++;
                        c = argv[2][counter];
                    }
                    for(int i=counter-1; i>=0; i--)
                    {
                        int tmp = charEater(argv[2][(counter-1)-i]);
                        //int tmp = 1;
                        y+=tmp*(int)pow(10,i);
                    }
                }
                testScreen(x,y);
                return 0;
            }
            else
            {
                printf("ERROR: config is not set up\n");
                return 0;
            }
        }
    }
    //return basicLines(set);
}
