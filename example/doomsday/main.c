#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include "sense.h"

int run=1;

/*the interrupt handler*/
void handler(int sig){
    run=0;
}
/*animationStep
  screen: a bitmap to draw on
  step: the animation step (0-3)
  color: the color of the animation
  draws a box of width step+1 clearing the middle*/
void animationStep(sense_fb_bitmap_t* screen,int step,int color){
    int i,j;
    for (i=3-step;i<5+step;i++)
        for (j=3-step;j<5+step;j++)
            if (i==3-step||i==4+step||j==3-step||j==4+step)
                setPixel(screen,i,j,color);
            else
                setPixel(screen,i,j,0);
}
/*explodeAnimation
	fb: a framebuffer object
	color: the color of the animation
	executes an explode animation*/
void explodeAnimation(pi_framebuffer_t* fb,uint16_t color){
    int i;
    for (i=0;i<4;i++){
        animationStep(fb->bitmap,i,color);
        usleep(100000);
    }
}

int main(int argc,char** argv){
    int i;
    sense_fb_bitmap_t screen;
    uint16_t color;
    uint16_t colorgood=getColor(0,255,0);
    uint16_t colorwarn=getColor(255,255,51);
    uint16_t colordanger=getColor(255,0,0);
    pi_framebuffer_t* fb=getFBDevice();
	int start=99;
	if (argc>1){
		start=atoi(argv[1]);
	}
    memset(&screen,0,sizeof(screen));
    printf("Press ctrl-c to exit early\n");
    for (i=start;i>=0 && run;i--)
    {
        color=colorgood;
        if (i<20)
            color=colorwarn;
        if (i<10)
            color=colordanger;
        clearBitmap(&screen,0);
        setFramebufferNumber(&screen,i,color);
        printf("%d\n",i);
        useBitmap(fb,&screen);
        sleep(1);
    }
    for (int i=0;i<5 && run;i++){
        explodeAnimation(fb,getColor(255,0,0));
        explodeAnimation(fb,getColor(0,0,255));
    }
    printf("Exiting...\n");
    clearBitmap(fb->bitmap,0);
    freeFrameBuffer(fb);
    return 0;
}
