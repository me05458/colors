#include <math.h>
#include <unistd.h>
#include "render.h"
#include<stdio.h>

int getConfig(int line) //return - 0 cool, 1- bad
{//reads a line from config file
    FILE *ptr = fopen("config", "r"); //open file
    if (ptr == NULL) { //oh no panic
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
    if(getConfig(1) == 1) //if mode 1 then basic lines
    {
        int set = 0; //will be size
        if(argc ==1) //if no arguments specified, 10 is default size
        {
            set = 10;
        }
        else
        {
            int counter = 0;
            char c = argv[1][counter];
            //slurp up each character and multiply 10^its possition to make the full number
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
        return basicLines(set); //make basic lines
    }
    else {
        if(getConfig(1)==2) //if config is 2 then draw stars
        {
            int x = 0; //these will be the dimensions
            int y = 0;
            if(argc <=2) //if not enough arguments default = 10 in both directions
            {
                y = 10;
                x = 10;
            }
            else
            {
                //slurp up the numbers as in config mode 1
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
            return forfunsies(x,y); //this draws the stars
        }
        else
        {
            if(getConfig(1) == 3) //if config mode = 3 test screen size
            {
                int x = 0; //this will be the size
                int y = 0;
                if(argc <=2) //if not enough arguments, defalt = 10
                {
                    y = 10;
                    x = 10;
                }
                else
                {
                    //slurp up the size as above
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
                testScreen(x,y); //this will print a test square
                return 0;
            }
            else
            {
                if(getConfig(1) == 4) //if config is 4, pretty gradient mode
                {
                    int x = 0; //this will be the size (note that x doesn't matter for now)
                    int y = 0;
                    if(argc <=2) //if not enough arguments, default = 10
                    {
                        y = 10;
                        x = 10;
                    }
                    else //slurp up the size
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
                    radialMode(x,y); //this will do the gradients
                }
                else
                {
                    printf("ERROR: config is not set up\n"); //if nothing, give user an error
                    return 0;
                }
            }
        }
    }
}
