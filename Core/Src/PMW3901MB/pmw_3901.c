#include "pmw_3901.h"


SPI_HandleTypeDef pmw_spi;
uint8_t pmw_delay_time;

/**
 * @brief  读取PMW3901单个寄存器值
 * @param  reg: 要读取的寄存器地址（0x00~0x7F）
 * @retval 寄存器返回值
 */
uint8_t PMW3901_ReadReg(uint8_t reg)
{
    uint8_t value = 0;
    reg &= ~0x80u;

    PMW3901_CS_LOW();
    HAL_SPI_Transmit(&pmw_spi, &reg, 1, 100);
    HAL_Delay(pmw_delay_time);
    HAL_SPI_Receive(&pmw_spi, &value, 1, 100);
    PMW3901_CS_HIGH();
    return value;
}

/**
 * @brief  写入PMW3901单个寄存器值
 * @param  reg: 要写入的寄存器地址
 * @param  data: 要写入的数据
 * @retval 无
 */
void PMW3901_WriteReg(uint8_t reg, uint8_t data)
{
    reg |= 0x80u;  // 置位最高位（写操作标志）

    PMW3901_CS_LOW();
    // 先发送寄存器地址（带写标志）
    HAL_SPI_Transmit(&pmw_spi, &reg, 1, 100);
    // 发送要写入的数据
    HAL_SPI_Transmit(&pmw_spi, &data, 1, 100);
    PMW3901_CS_HIGH();
    HAL_Delay(1);  // 写操作后短延时
}


/**
 * @brief  PMW3901初始化
 * @param  spi_ch: SPI句柄（已初始化好的SPI外设）
 * @param  delay_time: 读寄存器前的延时时间（ms）
 * @retval 初始化结果：0-成功，1-ID不匹配，初始化失败 2, 3 见函数内部
 */
uint8_t PMW3901_init(SPI_HandleTypeDef spi_ch,uint8_t delay_time)
{
	uint8_t chip_id;
	pmw_spi = spi_ch;
	pmw_delay_time = delay_time;
	chip_id = PMW3901_ReadReg(0x00);

	// 上电后延迟40ms
    HAL_Delay(40);

    // 1. 复位传感器（根据PMW3901手册，复位寄存器0x3A写入0x5A）
	PMW3901_WriteReg(0x3A, 0x5A);
	HAL_Delay(50);  // 复位后等待稳定

	// 读取芯片id
	chip_id = PMW3901_ReadReg(0x00);

	//
    if (chip_id != 0x49)
    {
        return 1;  // ID不匹配，初始化失败
    }

    struct PmwRegs pmwReg = {0,0,0,0,0,0};

//    配置传感器
    pmwReg.Product_id = chip_id;
    pmwReg.Revision_id = PMW3901_ReadReg(0x01);
    pmwReg.Motion = PMW3901_ReadReg(0x02);
    pmwReg.Delta_X_L = PMW3901_ReadReg(0x03);
    pmwReg.Delta_X_H = PMW3901_ReadReg(0x04);
    pmwReg.Delta_Y_L = PMW3901_ReadReg(0x05);
    pmwReg.Delta_Y_H = PMW3901_ReadReg(0x06);

    return PMW3901_Performance_Optimization();

}

/**
 * @brief  PMW3901优化寄存器
 * @retval 初始化结果：0-成功 2-0x67读取异常 3-0x47读取异常
 */
uint8_t  PMW3901_Performance_Optimization(){
	PMW3901_WriteReg(0x7F, 0x00);
	PMW3901_WriteReg(0x55, 0x01);
	PMW3901_WriteReg(0x50, 0x07);
	PMW3901_WriteReg(0x7F, 0x0E);

	PMW3901_WriteReg(0x43, 0x10);
	for(int a = 0; a < 3; a++) {
		uint8_t r1 = PMW3901_ReadReg(0x47);
		// 读到目标值，直接返回成功
		if (r1 == 0x08){
			break;
		}
		// 非最后一次循环时，短延时后重试（避免频繁读取）
		if(a < 2){
			PMW3901_WriteReg(0x43, 0x10);
			HAL_Delay(1); // 延时1ms，可根据需求调整
		}
		if(a == 2){
//			0x47读取异常
			return 3;
		}
	}
	uint8_t r2 = PMW3901_ReadReg(0x67);

	if(r2 == 0x00){
		PMW3901_WriteReg(0x48, 0x02);
	}else if(r2 == 0b10000000){
		PMW3901_WriteReg(0x48, 0x04);
	}else{
//		0x67读取异常
		return 2;
	}


	PMW3901_WriteReg(0x7F, 0x00);
	PMW3901_WriteReg(0x51, 0x7B);
	PMW3901_WriteReg(0x50, 0x00);
	PMW3901_WriteReg(0x55, 0x00);
	PMW3901_WriteReg(0x7F, 0x0E);

	uint8_t r3 = PMW3901_ReadReg(0x73);
	if (r3 == 0x00){
		uint8_t c1 = PMW3901_ReadReg(0x70);
		uint8_t c2 = PMW3901_ReadReg(0x71);

		if(c1 <= 28){
			c1 += 14;
		}else{
			c1 += 11;
		}

		if(c1 > 0x3F){
			c1 = 0x3F;
		}

		c2 = (c2 * 45) / 100;

		PMW3901_WriteReg(0x7F, 0x00);
		PMW3901_WriteReg(0x61, 0xAD);
		PMW3901_WriteReg(0x51, 0x70);
		PMW3901_WriteReg(0x7F, 0x0E);

		PMW3901_WriteReg(0x70, c1);
		PMW3901_WriteReg(0x71, c2);

	}

	PMW3901_WriteReg(0x7F, 0x00);
	PMW3901_WriteReg(0x61, 0xAD);
	PMW3901_WriteReg(0x7F, 0x03);
	PMW3901_WriteReg(0x40, 0x00);
	PMW3901_WriteReg(0x7F, 0x05);
	PMW3901_WriteReg(0x41, 0xB3);
	PMW3901_WriteReg(0x43, 0xF1);
	PMW3901_WriteReg(0x45, 0x14);
	PMW3901_WriteReg(0x5B, 0x32);
	PMW3901_WriteReg(0x5F, 0x34);
	PMW3901_WriteReg(0x7B, 0x08);
	PMW3901_WriteReg(0x7F, 0x06);
	PMW3901_WriteReg(0x44, 0x1B);
	PMW3901_WriteReg(0x40, 0xBF);
	PMW3901_WriteReg(0x4E, 0x3F);
	PMW3901_WriteReg(0x7F, 0x08);
	PMW3901_WriteReg(0x65, 0x20);
	PMW3901_WriteReg(0x6A, 0x18);
	PMW3901_WriteReg(0x7F, 0x09);
	PMW3901_WriteReg(0x4F, 0xAF);
	PMW3901_WriteReg(0x5F, 0x40);
	PMW3901_WriteReg(0x48, 0x80);
	PMW3901_WriteReg(0x49, 0x80);
	PMW3901_WriteReg(0x57, 0x77);
	PMW3901_WriteReg(0x60, 0x78);
	PMW3901_WriteReg(0x61, 0x78);
	PMW3901_WriteReg(0x62, 0x08);
	PMW3901_WriteReg(0x63, 0x50);
	PMW3901_WriteReg(0x7F, 0x0A);
	PMW3901_WriteReg(0x4D, 0x11);
	PMW3901_WriteReg(0x55, 0x80);
	PMW3901_WriteReg(0x74, 0x1F);
	PMW3901_WriteReg(0x75, 0x1F);
	PMW3901_WriteReg(0x4A, 0x78);
	PMW3901_WriteReg(0x4B, 0x78);
	PMW3901_WriteReg(0x44, 0x08);
	PMW3901_WriteReg(0x45, 0x50);
	PMW3901_WriteReg(0x64, 0xFF);
	PMW3901_WriteReg(0x65, 0x1F);
	PMW3901_WriteReg(0x7F, 0x14);
	PMW3901_WriteReg(0x65, 0x65);
	PMW3901_WriteReg(0x66, 0x08);
	PMW3901_WriteReg(0x63, 0x70);
	PMW3901_WriteReg(0x48, 0x48);
	PMW3901_WriteReg(0x7F, 0x07);
	PMW3901_WriteReg(0x41, 0x0D);
	PMW3901_WriteReg(0x43, 0x14);
	PMW3901_WriteReg(0x4B, 0x0E);
	PMW3901_WriteReg(0x45, 0x0F);
	PMW3901_WriteReg(0x44, 0x42);
	PMW3901_WriteReg(0x4C, 0x80);
	PMW3901_WriteReg(0x7F, 0x10);
	PMW3901_WriteReg(0x5B, 0x02);
	PMW3901_WriteReg(0x7F, 0x07);
	PMW3901_WriteReg(0x40, 0x41);
	PMW3901_WriteReg(0x70, 0x00);

	HAL_Delay(10);  // 等待10MS

	PMW3901_WriteReg(0x32, 0x44);
	PMW3901_WriteReg(0x7F, 0x07);
	PMW3901_WriteReg(0x40, 0x40);
	PMW3901_WriteReg(0x7F, 0x06);
	PMW3901_WriteReg(0x62, 0xF0);
	PMW3901_WriteReg(0x63, 0x00);
	PMW3901_WriteReg(0x7F, 0x0D);
	PMW3901_WriteReg(0x48, 0xC0);
	PMW3901_WriteReg(0x6F, 0xD5);
	PMW3901_WriteReg(0x7F, 0x00);
	PMW3901_WriteReg(0x5B, 0xA0);
	PMW3901_WriteReg(0x4E, 0xA8);
	PMW3901_WriteReg(0x5A, 0x50);
	PMW3901_WriteReg(0x40, 0x80);

	return 0;
}


/** 豆包生成的
 * @brief  轮询模式读取PMW3901传感器的移动状态及位移数据
 * @details  通过轮询读取PMW3901寄存器数据，解析X/Y轴位移、运动状态，
 *          结合缩放比例输出实际位移值，同时返回SQUAL（表面质量）判定跟踪可靠性
 * @param  [out] x              输出X轴位移值（经缩放后），单位：原始位移*scale_per_mille/1000
 * @param  [out] y              输出Y轴位移值（经缩放后），单位：原始位移*scale_per_mille/1000
 * @param  [out] q              输出SQUAL值（表面质量/跟踪可靠性）：
 *                              - 0~30：跟踪失败，数据冻结；
 *                              - >30：跟踪可靠，为最新SQUAL寄存器值
 * @param  [in]  scale_per_mille 位移缩放比例（千分比），范围0~1000，
 *                              例如500表示位移值缩小为原始值的50%
 * @note   1. 函数内部使用静态变量缓存上一帧数据，跟踪失败时冻结数据；
 *         2. PMW3901的0x02寄存器bit7为运动标志位（1=有新运动数据，0=无运动）；
 *         3. X/Y轴原始位移为int16_t，缩放后转为int32_t避免溢出；
 *         4. SQUAL（0x07寄存器）值越大，表面纹理越丰富，跟踪越可靠。
 * @see     PMW3901_ReadReg, PMW3901_Init
 */
void pollingMotion(int *x, int *y, uint8_t *q,uint16_t scale_per_mille)
{
    static int16_t last_x = 0;
    static int16_t last_y = 0;
    static uint8_t last_q = 0;

    uint8_t motion = PMW3901_ReadReg(0x02);

    uint8_t x_l = PMW3901_ReadReg(0x03);
    uint8_t x_h = PMW3901_ReadReg(0x04);
    uint8_t y_l = PMW3901_ReadReg(0x05);
    uint8_t y_h = PMW3901_ReadReg(0x06);

    uint8_t r07 = PMW3901_ReadReg(0x07);  // SQUAL
    uint8_t r0C = PMW3901_ReadReg(0x0C);  // 快门速度(暂时没用)

    int16_t cur_x = (int16_t)((x_h << 8) | x_l);
    int16_t cur_y = (int16_t)((y_h << 8) | y_l);

    if (r07 != 0) {
        /* ---------- 跟踪可靠 ---------- */
        if (motion & 0x80) {
            // 有新运动（可能为 0）
            last_x = cur_x;
            last_y = cur_y;
        } else {
            // 明确检测到“没有运动”
            last_x = 0;
            last_y = 0;
        }

        last_q = r07;   // 明确、可信
    }
    /* ---------- 跟踪失败 ---------- */
    //什么都不更新，冻结上一帧

    *x = (int32_t)last_x * scale_per_mille / 1000;
    *y = (int32_t)last_y * scale_per_mille / 1000;
    *q = last_q;
}

//void pollingMotion(int * x, int * y, uint8_t * q){
//
//	uint8_t isMoved = PMW3901_ReadReg(0x02);
//
//	uint8_t x_l = PMW3901_ReadReg(0x03);
//	uint8_t x_h = PMW3901_ReadReg(0x04);
//	uint8_t y_l = PMW3901_ReadReg(0x05);
//	uint8_t y_h = PMW3901_ReadReg(0x06);
//
//	uint8_t r07 = PMW3901_ReadReg(0x07);
//	uint8_t r0C = PMW3901_ReadReg(0x0C);
//
//	*x = (int16_t)((x_h << 8) | x_l);
//	*y = (int16_t)((y_h << 8) | y_l);
//	*q = r07;

//	if (isMoved & 0x80){
//		uint8_t x_l = PMW3901_ReadReg(0x03);
//		uint8_t x_h = PMW3901_ReadReg(0x04);
//		uint8_t y_l = PMW3901_ReadReg(0x05);
//		uint8_t y_h = PMW3901_ReadReg(0x06);
//
//		uint8_t r07 = PMW3901_ReadReg(0x07);
//		uint8_t r0C = PMW3901_ReadReg(0x0C);
//
////		*x = (int16_t)((x_h << 8) | x_l);
////		*y = (int16_t)((y_h << 8) | y_l);
////		*q = r07;
//		if (!(r0C == 0x1F && r07 < 0x19)){
//			*x = (int16_t)((x_h << 8) | x_l);
//			*y = (int16_t)((y_h << 8) | y_l);
//			*q = r07;
//		}
//		else {
//			*x = (int16_t)((x_h << 8) | x_l);
//			*y = (int16_t)((y_h << 8) | y_l);
//			*q = r07;
//		}
//	}else{
//		*x = *y = 0;
//		*q = 100;
//	}
//}
//uint8_t isMoved = PMW3901_ReadReg(0x02);
//		  if (isMoved & 0x80){
//			  uint8_t x_l = PMW3901_ReadReg(0x03);
//			  uint8_t x_h = PMW3901_ReadReg(0x04);
//			  uint8_t y_l = PMW3901_ReadReg(0x05);
//			  uint8_t y_h = PMW3901_ReadReg(0x06);
//
//			  uint8_t r07 = PMW3901_ReadReg(0x07);
//			  uint8_t r0C = PMW3901_ReadReg(0x0C);
//
//			  if (!(r0C == 0x1F && r07 < 0x19)){
//				 int x = (int16_t)((x_h << 8) | x_l);
//				 int y = (int16_t)((y_h << 8) | y_l);
//
//				 char xy_buf[32];
//				 snprintf(xy_buf, sizeof(xy_buf), "X: %d, Y: %d\r\n", x, y);
//				 HAL_UART_Transmit(&huart2, (uint8_t*)xy_buf, strlen(xy_buf), 100);
//				 HAL_Delay(200);
//
//			  }
//		  }
