#include"vl53l1x.h"


uint8_t dev = 0x52;
uint8_t sensorState=0;
uint16_t Distance;
uint8_t dataReady =0;
uint16_t timeout_counter = 0;
uint8_t status = 0;

//没有详细注释 详见STM32官网驱动程序
void vl53_Init(){
	HAL_Delay(2000);

	while(sensorState==0){
		status = VL53L1X_BootState(dev, &sensorState);
		HAL_Delay(2);
	}

	status = VL53L1X_SensorInit(dev);
	status = VL53L1X_SetDistanceMode(dev, 2); /* 1=short, 2=long */
	status = VL53L1X_SetTimingBudgetInMs(dev, 100); /* in ms possible values [20, 50, 100, 200, 500] */
	status = VL53L1X_SetInterMeasurementInMs(dev, 100); /* in ms, IM must be > = TB */
	status = VL53L1X_SetInterruptPolarity(dev,0); //This function programs the interrupt polarity, 1 = active high (default), 0 = active low.


	status = VL53L1X_StartRanging(dev);

}

uint16_t vl53_GetDistance(){
	while (dataReady == 0){
		status = VL53L1X_CheckForDataReady(dev, &dataReady);
		timeout_counter++;
		if (timeout_counter >= 1000)
			{
				status = (uint8_t)VL53L1X_ERROR_TIMEOUT;
				timeout_counter = 0;
			}
		status = VL53L1_WaitMs(dev, 1);
	}
	dataReady = 0;
	timeout_counter = 0;
	status = VL53L1X_GetDistance(dev, &Distance);
	return Distance;
}


