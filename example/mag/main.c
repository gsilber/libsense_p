#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include "sense.h"

int main(){
	int i;
	pi_i2c_t* device;
	coordinate_t data;
	device=geti2cDevice();
	if (device){
		configureMag(device);
		for (i=0;i<5;i++){
			getMagData(device,&data);
 			printf("Mag: %f %f %f\n",data.x,data.y,data.z);
        	sleep(1);
		}
	}

}
