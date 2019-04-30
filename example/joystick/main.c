#include <stdio.h>
#include <signal.h>
#include <linux/input.h>
#include "sense.h"
	
char running=1;
float x=0;
float y=0;
uint16_t color;
pi_framebuffer_t* fb;

void handler(int sig){
	running=0;
}

void callbackFn(unsigned int code){
	setPixel(fb->bitmap,x,y,0);
	switch(code){
		case KEY_UP:
			y=y==0?7:y-1;
			break;
		case KEY_DOWN:
			y=y==7?0:y+1;
			break;
		case KEY_RIGHT:
			x=x==7?0:x+1;
			break;
		case KEY_LEFT:
			x=x==0?7:x-1;
			break;
		default:
			running=0;
	}
	setPixel(fb->bitmap,x,y,color);
}

int main(){
	signal(SIGINT,handler);
	pi_joystick_t* joystick=getJoystickDevice();
	fb=getFBDevice();
	clearBitmap(fb->bitmap,0);
	color=getColor(255,0,0);
	setPixel(fb->bitmap,0,0,color);
	while (running){
		pollJoystick(joystick,callbackFn,1000);
	}
	clearBitmap(fb->bitmap,0);
	freeFrameBuffer(fb);
	freeJoystick(joystick);
}
