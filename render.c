#include <sodium.h>
#include<stdio.h>
#include <unistd.h>
#include<time.h>

typedef struct{ //colors are just globs of r, g, b
    int rgb[3];
}color;
typedef struct{ //this contains all of the colors to render.
    int h;
    int w;
    color **colors;
}map;

void wait(int ms) //this is such a funny way of sleeping this is what I shall do.
{
    clock_t start_time = clock();
    while (clock() < start_time + ms);
}
void logg(int i, int j) //debugging function because printfing is bad when you're trying to debug something that relies on printfs

    FILE *ptr = fopen("logg", "a");//open file
    if (ptr == NULL) { //oh no file did not open panic
        printf("ERROR: something went wrong while opening file\n");
    }
    fprintf(ptr, "%d|%d\n",i,j); //log whatever to file
    fclose(ptr); //close file
}
//Insertion sort to organize arrays (to find largest/smallest element)
void sortHelper(int arraySize, int* array)
{
    for(int i = 1; i<arraySize; i++)
    {
        int key = array[i];
        int j = i - 1;
        while (j >= 0 && array[j] > key) {
            array[j + 1] = array[j];
            j = j - 1;
        }
        array[j + 1] = key;
    }
}
int basicLines(int set) //this is the lines on the screen one, kind of weird looking
{
    char randString[32]; //random generator stuff
    if(sodium_init() <0){
        printf("A Catastrophic Faliure Occured (EXIT CODE 2)\n");
        return 2;
    }
    randombytes_buf(randString, 32);
    //printf("%d",set);
    color screen[set];
    int r = randombytes_uniform(225); //start with a random color
    int g = randombytes_uniform(225);
    int b = randombytes_uniform(225);

    for(int i = 0; i<set; i++) //set all of the lines to that color
    {
        screen[i].rgb[0] = r;
        screen[i].rgb[1] = g;
        screen[i].rgb[2] = b;
        printf("\x1b[48;2;%d;%d;%dm  \x1b[0m",screen[i].rgb[0],screen[i].rgb[1],screen[i].rgb[2]); //print
    }
    printf("\n");
    //whole bunch of testing variables:
    int m = 1; //arbitrary tracker for infinite loop to make debugging easier. Exact value doesn't matter, can't be 50.
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
        wait(10000);
        //m++;
    }
    return 0;
}
void funsiesHelper(int h, int w, int horror[h][w][3]) //renders the whole huge brick of colors
{
    for(int i = 0; i<h; i++) //just a double for loop to get all of them
    {
        for(int j = 0; j<w; j++)
        {
            printf("\x1b[48;2;%d;%d;%dm  \x1b[0m",horror[i][j][0],horror[i][j][1],horror[i][j][2]);
        }
        printf("\n");
    }
}
int forfunsies(int h, int w) //this is the one with little stars, doens't really work
{
    char randString[32]; //random generator stuff
    if(sodium_init() <0){
        printf("A Catastrophic Faliure Occured (EXIT CODE 2)\n");
        return 2;
    }
    randombytes_buf(randString, 32);
    int horror[h][w][3];
    int r = randombytes_uniform(225); //starting color = white
    int g = randombytes_uniform(225);
    int b = randombytes_uniform(225);
    int lim = 0;
    for(int i = 0; i<h; i++) //render first brick of color
    {
        for(int j = 0; j<w; j++)
        {
            horror[i][j][0] = r;
            horror[i][j][1] = g;
            horror[i][j][2] = b;

        }
    }
    //funsiesHelper(h,w,horror);
    //return 0;
    int randh = randombytes_uniform(h); //random location and r,g,or b to change
    int randw = randombytes_uniform(w);
    int randc = randombytes_uniform(3);
    while(1 == 1) //forever
    {
        int testarr[4] = {randh, randw, h-randh, w-randw}; //this will be used to find the biggest direction to expand in (want expansion to reach edge!)
        sortHelper(4,testarr); //sort it
        lim = testarr[3]; //biggest one at end
        int thing = 0; //loop through to edge
        lim = testarr[3]; //biggest one is as far as it will go
        while(thing < lim) //loooooop
        {
            int i=0;
            for(int i = 0; i<thing; i++) //it's goign to expand each time in circles
            {
                //printf("%d",i);
                    if(i == 0&&horror[randh][randw][randc]<225) //center one
                    {
                        horror[randh][randw][randc]+=1;
                    }
                    else{
                        //expand, but make sure that each one is within the box and color stays within (0,225)
                        if(randh-i >= 0 && randw-i >=0&&horror[randh-i][randw-i][randc] <225)
                        {
                            horror[randh-i][randw-i][randc] +=1;
                        }
                        if(randh+i < h && randw+i <w&&horror[randh+i][randw+i][randc]<225)
                        {
                            horror[randh+i][randw+i][randc] +=1;
                        }
                        if(randh-i >= 0 && randw+i <w&&horror[randh-i][randw+i][randc]<225)
                        {
                            horror[randh-i][randw+i][randc] +=1;
                        }
                        if(randh+i < h && randw-i >= 0&&horror[randh+i][randw-i][randc]<225)
                        {
                            horror[randh+i][randw-i][randc] +=1;
                        }
                        if(randw-i >=0&&horror[randh][randw-i][randc]<225)
                        {
                            horror[randh][randw-i][randc] +=1;
                        }
                        if(randw+i <w&&horror[randh][randw+i][randc]<225)
                        {
                            horror[randh][randw+i][randc] +=1;
                        }
                        if(randh-i >=0&& horror[randh-i][randw][randc]<225)
                        {
                            horror[randh-i][randw][randc] +=1;
                        }
                        if(randh+i <h&&horror[randh+i][randw][randc]<225)
                        {
                            horror[randh+i][randw][randc] +=1;
                        }
                    }

                //funsiesHelper(h,w,horror);
            }
            funsiesHelper(h,w,horror); //render
            wait(10000);//pause to make it pretty
            //getchar();
            thing ++;
        }
            randh = randombytes_uniform(h); //new random position and color
            randw = randombytes_uniform(w);
            randc = randombytes_uniform(3);
            sortHelper(4,testarr);
            lim = testarr[0];
            //return 0;
    }

    return 0;
}
void testScreen(int h, int w)
{
    for(int i = 0; i<h; i++)
    {
        printf("\x1b[48;2;%d;%d;%dm",225-(i*(225/h)),225-(i*(225/h)),225);//each row has a color for prettyness, they are blue.
        for(int j = 0; j<w; j++) //double for loop
        {
            printf("  ");
        }
        printf("\x1b[0m"); //return color to normal
        printf("\n");
    }
}
int radialMode(int h, int w) //gradient up and down right now (yes the name doesn't match)
{
    char randString[32]; //random generator stuff
    if(sodium_init() <0){
        printf("A Catastrophic Faliure Occured (EXIT CODE 2)\n");
        return 2;
    }
    randombytes_buf(randString, 32);
    int happening = randombytes_uniform(1); //this will be to determine type of gradient LATER
    //for r,g,b decide whether or not to increase/decrease it
    int r = randombytes_uniform(2);
    int g = randombytes_uniform(2);
    int b = randombytes_uniform(2);
    int curr = 225; //starting color = white
    int curg = 225; //keep track of this to avoid nasty lines
    int curb = 225;
    int a = 1; //tracks colors
    while(1==1) //forever
    {
            while(a < 225) //go to white, a increments
            {
                //only update current color if decided that it's to be changed
                if(r == 1)
                {
                    curr = a;
                }
                if(g == 1)
                {
                    curg = a;
                }
                if(b == 1)
                {
                    curb = a;
                }
                printf("\x1b[48;2;%d;%d;%dm",curr,curg,curb); //set color for row
                for(int j = 0; j<w; j++)
                {
                    printf("  "); //actually render spaces all accross row
                }
                printf("\x1b[0m"); //set to normal
                printf("\n");
                a++;
                wait(10000); //wait to make it look nice
            }
            while(a > 0) //now go back down (a started at 225 after the last incrementation)
            {
                //again, only edit if decided to (haven't re generated the r,g,b yet)
                if(r == 1)
                {
                    curr = a;
                }
                if(g == 1)
                {
                    curg = a;
                }
                if(b == 1)
                {
                    curb = a;
                }
                printf("\x1b[48;2;%d;%d;%dm",curr,curg,curb);
                for(int j = 0; j<w; j++)
                {
                    printf("  ");
                }
                printf("\x1b[0m");
                printf("\n");
                a--;
                wait(10000);
            }
            r = randombytes_uniform(2); //now generate new r,g,b
            g = randombytes_uniform(2);
            b = randombytes_uniform(2);
        }
        /*if(happening == 1)
        {

        }*/


    return 0;
}
