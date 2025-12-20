
#include "main.h"
#include "mavlink/common/mavlink.h"
//#include "../mavlink/ardupilotmega/ardupilotmega.h"


void send_optical_flow(UART_HandleTypeDef *huart,int16_t flow_x, int16_t flow_y,
                       uint8_t quality,uint16_t distance);

void send_heart_beat(UART_HandleTypeDef *huart);

void send_distance_sensor(UART_HandleTypeDef *huart,uint16_t distance);

