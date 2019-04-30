#include <stdio.h>
#include "sense.h"

int main(){
    pi_i2c_t* device=geti2cDevice();
    if (device){
        configureHumiditySensor(device);
        printf("Temp: %+-10.5gc\n",getTemp(device));
        printf("Humidity: %+-10.5g%\n",getHumidity(device));
        configurePressureSensor(device);
        printf("Pressure: %+-10.5gmBar\n",getPressure(device));

        freei2cDevice(device);
    }
}
