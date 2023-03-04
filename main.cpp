#include"mbed.h"
#include"Air_Quality.h"
AirQuality airqualitysensor;
int current_quality = -1;
PinName analogPin = p15;

// Interrupt Handler
void AirQualityInterrupt()
{
    AnalogIn sensor(analogPin);
    airqualitysensor.last_vol = airqualitysensor.first_vol;
    airqualitysensor.first_vol = sensor.read()*1000;
    airqualitysensor.timer_index = 1;
}

// Main loop
int main()
{
    airqualitysensor.init(analogPin, AirQualityInterrupt);
    while(1) {
        current_quality=airqualitysensor.slope();
        if (current_quality >= 0) { // if a valid data returned.
            if (current_quality == 0)
                printf("High pollution! Force signal active\n\r");
            else if (current_quality == 1)
                printf("High pollution!\n\r");
            else if (current_quality == 2)
                printf("Low pollution!\n\r");
            else if (current_quality == 3)
                printf("Fresh air\n\r");
        }
    }
}
