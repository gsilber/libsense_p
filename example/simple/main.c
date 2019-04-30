#include <stdio.h>
#include "sense.h"

int main(){
	char ch;
	int colors[]={getColor(255,0,0),getColor(0,255,0),getColor(0,0,255),0};
	int count=0;
	pi_framebuffer_t* fb=getFBDevice();
	printf("press enter to cycle, q to quit\n");
	while(ch!='q'){
		clearBitmap(fb->bitmap,colors[count++]);
		ch=getchar();
		count=count%4;
	}
	clearBitmap(fb->bitmap,0);
	freeFrameBuffer(fb);
}
