#include "main.h"

#define PMW3901_CS_LOW()  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET)
#define PMW3901_CS_HIGH() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET)

// 初始化时用到的寄存器 其实没用嫌麻烦 直接引入了MAVLINK的模块
struct PmwRegs {
	uint8_t Product_id;
	uint8_t Revision_id;
	uint8_t Motion;
	uint8_t Delta_X_L;
	uint8_t Delta_X_H;
	uint8_t Delta_Y_L;
	uint8_t Delta_Y_H;
};

uint8_t PMW3901_ReadReg(uint8_t reg);
void PMW3901_WriteReg(uint8_t reg, uint8_t data);
uint8_t PMW3901_init(SPI_HandleTypeDef spi_ch,uint8_t delay_time);
uint8_t  PMW3901_Performance_Optimization();
void pollingMotion(int * x, int * y, uint8_t * r07,uint16_t scale_per_mille);
