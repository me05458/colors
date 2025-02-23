#include<stdio.h>
#include <sodium.h>
#include <math.h>
#include <unistd.h>

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
void logg(int i, int j)
{
    FILE *ptr = fopen("logg", "a");
    if (ptr == NULL) {
        printf("ERROR: something went wrong while opening file\n");
    }
    fprintf(ptr, "%d|%d\n",i,j);
    fclose(ptr);
}
//printf("\x1b[38;2;%d;%d;%dmsomething\x1b[0m\n",red,blue,transparency);
int main(int argc, char *argv[]) {
    //printf("\x1b[38;2;%d;%d;0mhi\n\x1b[0m",i,225-i);
    //library init
    char randString[32];
    log(1000);
    if(sodium_init() <0){
        printf("A Catastrophic Faliure Occured (EXIT CODE 2)\n");
        return 2;
    }
    randombytes_buf(randString, 32);
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
    //printf("%d",set);
    color screen[set];
    int r = randombytes_uniform(225);
    int g = randombytes_uniform(225);
    int b = randombytes_uniform(225);

    for(int i = 0; i<set; i++)
    {
        screen[i].rgb[0] = r;
        screen[i].rgb[1] = g;
        screen[i].rgb[2] = b;
        printf("\x1b[48;2;%d;%d;%dm  \x1b[0m",screen[i].rgb[0],screen[i].rgb[1],screen[i].rgb[2]);
    }
    printf("\n");
    int m = 1;
    int q = -1;
    int f = 0;
    int t = -1;
    while(m!=50) //this is a pretty arbitrary limit to run forever (but also to be easy to fuss with for testing)
    {
        int tmp; //the possition at which to start the color change
        int rgbtmp; //which rgb part to change
        int sset; //decrease or increase color? (0 = increase, 1 = decrease)
        if(q < 0) //this if is here to prevent too many of them from happening at once! (and also for ease of propagation because reccursion is scary)
        {
            t = 0;
            q = 0;
            //generate some random values for the variables.
            tmp = randombytes_uniform(set);
            rgbtmp = randombytes_uniform(3);
            sset = randombytes_uniform(2);
            if(sset == 0) //add
            {
                if(screen[tmp].rgb[rgbtmp] < 225) //make sure it won't become too big
                {
                    screen[tmp].rgb[rgbtmp] +=1; //it looks better +10, at least for now.
                }
                else
                {
                    //screen[tmp].rgb[rgbtmp] -=1;
                    sset = 1;
                }
            }
            else //not add (in case of some third option)
            {
                //same as above, but for removal
                if(sset == 1) //remove
                {
                    if(screen[tmp].rgb[rgbtmp] > 0)
                    {
                        screen[tmp].rgb[rgbtmp] -=1;
                    }
                    else
                    {
                        //screen[tmp].rgb[rgbtmp] +=1;
                        sset = 0;
                    }
                }

            }
            //q is going to loop through them for propagation and delay.
            q = set-tmp; //amount of units in row after changed one
            f = 0;
            t = q; //temporary variable
        }
        else //now we're looping through the size of q
        {
            if(sset == 0) //add
            {
                //t-q is the amount q decreased by (so like normal iteration I don't know why I did it like this but I'm sure I had a reason)
                for(int j = tmp; j<tmp+(t-q);j++) //starts at the changed unit and propagates
                //for(int j = tmp; j<tmp+f; j++)
                {
                    if(screen[j].rgb[rgbtmp] < 225)
                    {
                        screen[j].rgb[rgbtmp] +=1;
                    }
                    else
                    {
                        //screen[j].rgb[rgbtmp] -=1;
                        sset = 1;
                    }
                }
                //if this is all it takes...
                if((t-q)<tmp)
                {
                    //logg(0,0);
                    for(int j = tmp-1; j>(tmp-1)-(t-q);j--) //starts at the changed unit and propagates (?) maybe (?)
                    //for(int j = tmp-1; j>(tmp-1)-f;j++)
                    {
                        if(screen[j].rgb[rgbtmp] < 225)
                        {
                            screen[j].rgb[rgbtmp] +=1;
                        }
                        else
                        {
                            //screen[j].rgb[rgbtmp] -=1;
                            sset = 1;
                        }
                    }
                }
                else
                {
                    q = -12;
                    //logg(1,1);
                }
            }
            else
            {
                for(int j = tmp; j<tmp+(t-q) ; j++)
                //for(int j = tmp; j<tmp+f; j++)
                {
                    if(screen[j].rgb[rgbtmp] > 0)
                    {
                        screen[j].rgb[rgbtmp] -=1;
                    }
                    else
                    {
                        //screen[j].rgb[rgbtmp] +=1;
                        sset = 0;
                    }
                }
                if((t-q)<tmp)
                {
                    //logg(0,0);
                    for(int j = tmp-1; j>(tmp-1)-(t-q);j--) //starts at the changed unit and propagates (?) maybe (?)
                    //for(int j = tmp-1; j>(tmp-1)-f;j++)
                    {
                        if(screen[j].rgb[rgbtmp] > 0)
                        {
                            screen[j].rgb[rgbtmp] -=1;
                        }
                        else
                        {
                            //screen[j].rgb[rgbtmp] +=1;
                            sset = 0;
                        }
                    }
                }
                else
                {
                    //logg(1,1);
                    q = -12;
                }
            }
            f++;
            q--; //decrease! Or you'll be stuck forever!
        }
        for(int i = 0; i<set; i++)
        {
            //printf("%d",i);
            //printf("%d/%d/%d\n",screen[i].rgb[0],screen[i].rgb[1],screen[i].rgb[2]);
            printf("\x1b[48;2;%d;%d;%dm  \x1b[0m",screen[i].rgb[0],screen[i].rgb[1],screen[i].rgb[2]);
        }
        printf("\n");
        sleep(0.5);
        //m++;
    }
    return 0;
}
