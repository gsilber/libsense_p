#include "sense.h"
#include <stdio.h>
#include <string.h>
#include <linux/input.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>

void drawBinary(sense_fb_bitmap_t* screen,int row,int number,uint16_t color){
	int i;
	for (i=0;i<8;i++){
		setPixel(screen,7-i,row,number & 1<<i?color:0);
	}
		
}
int run=1;
void handler(int sig){
	printf("\nExiting...\n");
	run=0;
}

void callbackFn(unsigned int code){
	printf("%d\n",code);
	if (code==KEY_ENTER) run=0;
}

int main(int argc,char** argv){
	int i;
	time_t raw;
	struct tm * tmi;
	sense_fb_bitmap_t screen;
	pi_framebuffer_t* fb=getFBDevice();
	pi_joystick_t* joystick=getJoystickDevice();
	signal(SIGINT, handler);
	memset(&screen,0,sizeof(screen));
	clearBitmap(fb->bitmap,0);
	printf("Press ctrl-c to exit\n");
	while (run){
		time(&raw);
		tmi=localtime(&raw);
		drawBinary(fb->bitmap,1,tmi->tm_hour,getColor(0,0,255));
		drawBinary(fb->bitmap,3,tmi->tm_min,getColor(0,255,0));
		drawBinary(fb->bitmap,5,tmi->tm_sec,getColor(255,0,0));
		pollJoystick(joystick,callbackFn,1000);
	}
	clearBitmap(fb->bitmap,0);
	freeFrameBuffer(fb);
	freeJoystick(joystick);
	return 0;
}
