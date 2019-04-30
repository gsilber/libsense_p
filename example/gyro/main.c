#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include "sense.h"

int run=1;
void interrupt_handler(int sig){
	run=0;
}
int main(){
	int cnt=0;
	pi_i2c_t* device;
	coordinate_t data;
	signal(SIGINT, interrupt_handler);
	device=geti2cDevice();
	if (device){
		configureAccelGyro(device);
		while (run){
			usleep(2000);
			while (run && getGyroPosition(device,&data)){
				if (cnt==109){ //sample rate, display once per second
					cnt=0;
 					printf("Gyro: %f %f %f\n",data.x,data.y,data.z);
				}
				cnt++;
			}
		}
		printf("\nExiting...\n");
		freei2cDevice(device);
	}
}
