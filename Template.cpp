/*
 * Template.cpp
 *
 * Created on: 25.06.2014
 * Author: Atheel Redah
 *
 */

#include "rodos.h"
#include <stdio.h>
#include "hal.h"
#include "math.h"
#include <string>


static Application module01("Template", 2001);

#define LED_GREEN GPIO_060
#define LED_ORANGE GPIO_061
#define LED_RED GPIO_062
#define LED_BLUE GPIO_063

#define BT_UART UART_IDX2
#define USB_UART UART_IDX3

#define IMU_I2C I2C_IDX2

HAL_UART bt_uart(BT_UART);
HAL_GPIO GreenLED(LED_GREEN);
HAL_GPIO BlueLED(LED_BLUE);

struct SensorData{

};

Topic<SensorData> SensorDataTopic(-1, "Sensor Data");
CommBuffer<SensorData> SensorDataBuffer;
Subscriber SensorDataSubscriber(SensorDataTopic, SensorDataBuffer);


class Telemetry: public Thread {

public:

	Telemetry(const char* name) : Thread(name) {
	}

	void init() {
		bt_uart.init(921600);
		GreenLED.init(true, 1, 0);
		BlueLED.init(true, 1, 0);
	}

	void run() {

		while (1) {
			GreenLED.setPins(~GreenLED.readPins());
			PRINTF("Hello Rodos, the time now is %f \r\n",SECONDS_NOW());
			bt_uart.write("Hello Rodos\n", 12);
            suspendCallerUntil(NOW()+250*MILLISECONDS);
            BlueLED.setPins(~BlueLED.readPins());
            suspendCallerUntil(NOW()+250*MILLISECONDS);
		}
	}
};
Telemetry Telemetry("Telemetry");


/***********************************************************************/

class Testing_IMU: public Thread {

public:

	Testing_IMU(const char* name) : Thread(name) {
	}

	void init() {
		bt_uart.init(921600);
		GreenLED.init(true, 1, 0);
		BlueLED.init(true, 1, 0);
	}

	void run() {

		while (1) {
			GreenLED.setPins(~GreenLED.readPins());
			PRINTF("Hello Rodos, the time now is %f \r\n",SECONDS_NOW());
			bt_uart.write("Hello Rodos\n", 12);
            suspendCallerUntil(NOW()+250*MILLISECONDS);
            BlueLED.setPins(~BlueLED.readPins());
            suspendCallerUntil(NOW()+250*MILLISECONDS);
		}
	}
};
Testing_IMU Testing__IMU("Testing_IMU");


/***********************************************************************/
//HAL_GPIO CS_G(GPIO_018); /* declare HAL_GPIO for GPIO_018 = PB2 (IMU Chip Select pin for the Gyro) */
//HAL_GPIO CS_XM(GPIO_032); /* declare HAL_GPIO for GPIO_032 = PC0 (IMU Chip Select pin for the Accelerometer + Magnetometer)*/
//HAL_GPIO IMU_EN(GPIO_055); /* declare HAL_GPIO for GPIO_055 = PD7 (IMU Power Enable pin) */
//HAL_SPI IMU(SPI_IDX1); /* declare HAL_SPI for SPI_IDX1 = SPI1 (IMU), please refer to hal_spi.h for correct SPI mapping */
//
//class sensor_SPI : public GenericIOInterface {
//
//public:
////	HAL_SPI(const char* name) : GenericIOInterface(name){
//	//}
//
//void init(){
//CS_G.init(true, 1, 1); /* initialization of the HAL object should be called one time only in the project*/
//CS_XM.init(true, 1, 1); /* initialization of the HAL object should be called one time only in the project*/
//IMU_EN.init(true, 1, 1); /* initialization of the HAL object should be called one time only in the project*/
//IMU.init(1000000); /* initialization of the HAL object should be called one time only in the project*/
//
//
//};
//
//
//void run(){
//	while(1) {
//	/* Declare: Registers */
//		uint8_t LSM9DS0_WHO_AM_I_G[1] = {0x0F};
//		uint8_t LSM9DS0_CTRL_REG1_G[2] = {0x20, 0b01001111};
//		uint8_t LSM9DS0_OUT_X_L_G[1] = {0x28};
//
//		uint8_t DATA[2]; 		// buffer for Sensor Data
//
//		LSM9DS0_CTRL_REG1_G[0] = LSM9DS0_CTRL_REG1_G[0] & 0x3F; /* If write, bit 0 of the subAddress (MSB) should be 0;
//		If single byte, bit 1 of the subAddress should be 0 */
//
//	/* Setup: Registers */
//		CS_G.setPins(0); // Initiate communication
//		IMU.write (LSM9DS0_CTRL_REG1_G, 2); /* initialize the LSM9DS0_CTRL_REG1_G register (0x20) */
//		CS_G.setPins(1); // Close communication
//
//		LSM9DS0_WHO_AM_I_G[0] = 0x80 | (LSM9DS0_WHO_AM_I_G[0] & 0x3F); /* If read, bit 0 of the subAddress (MSB) should be 1;
//		If single byte, bit 1 of the subAddress should be 0 (0x80), otherwise 1 (0xC0)*/
//
//
//	/* Read: Sensors */
//		CS_G.setPins(0); // Initiate communication
//
//		IMU.writeRead(LSM9DS0_WHO_AM_I_G, 1, DATA, 2); /* Read from the gyroscope WHO_AM_I register (0xD4) */
//		LSM9DS0_OUT_X_L_G[0] |= 0b11000000;
//		IMU.writeRead(LSM9DS0_OUT_X_L_G, 1, DATA, 3); /* read the LSM9DS0_OUT_X_L_G register (0x28) */
//
//		CS_G.setPins(1); // Close communication
//
//
//		PRINTF("Data0 = %x, Data1 = %x, Data2 = %x \r\n", DATA[0],DATA[1],DATA[2]);
//		//suspendCallerUntil(NOW()+50*MILLISECONDS);
//	}
//	}
//};
//sensor_SPI sensor_SPI("sensor_SPI");

HAL_GPIO CS_G(GPIO_018); /* declare HAL_GPIO for GPIO_018 = PB2 (IMU Chip Select pin for the Gyro) */
HAL_GPIO CS_XM(GPIO_032); /* declare HAL_GPIO for GPIO_032 = PC0 (IMU Chip Select pin for the Accelerometer + Magnetometer)*/
HAL_GPIO IMU_EN(GPIO_055); /* declare HAL_GPIO for GPIO_055 = PD7 (IMU Power Enable pin) */
HAL_SPI IMU(SPI_IDX1); /* declare HAL_SPI for SPI_IDX1 = SPI1 (IMU), please refer to hal_spi.h for correct SPI mapping */
class SensorIMU: public Thread {

public:

	SensorIMU(const char* name) : Thread(name) {
	}

	void init() {
		CS_G.init(true, 1, 1); /* initialization of the HAL object should be called one time only in the project*/
		CS_XM.init(true, 1, 1); /* initialization of the HAL object should be called one time only in the project*/
		IMU_EN.init(true, 1, 1); /* initialization of the HAL object should be called one time only in the project*/
		bt_uart.init(921600);
	}

	void run() {

		SensorData imuData;

		while (1) {
			uint8_t LSM9DS0_WHO_AM_I_G[1] = {0x0F}; /* Gyro WHO_AM_I register address*/
			uint8_t LSM9DS0_CTRL_REG1_G[2] = {0x20,0b01001111};

			uint8_t LSM9DS0_OUT_X_L_G[1] = {0x28};

			uint8_t DATA[3];
//			uint8_t DATA01[2];
			IMU.init(1000000); /* initialization of the HAL object should be called one time only in the project*/

			LSM9DS0_CTRL_REG1_G[0] = LSM9DS0_CTRL_REG1_G[0] & 0x3F; /* If write, bit 0 of the subAddress (MSB) should be 0;
			If single byte, bit 1 of the subAddress should be 0 */
			CS_G.setPins(0); // Initiate communication
			IMU.write (LSM9DS0_CTRL_REG1_G, 2); /* initialize the LSM9DS0_CTRL_REG1_G register (0x20) */
			CS_G.setPins(1); // Close communication
			LSM9DS0_WHO_AM_I_G[0] = 0x80 | (LSM9DS0_WHO_AM_I_G[0] & 0x3F); /* If read, bit 0 of the subAddress (MSB) should be 1;
			 If single byte, bit 1 of the subAddress should be 0 (0x80), otherwise 1 (0xC0)*/
			CS_G.setPins(0); // Initiate communication
//			IMU.writeRead(LSM9DS0_WHO_AM_I_G, 1, DATA, 2); /* Read from the gyroscope WHO_AM_I register (0xD4) */
			LSM9DS0_OUT_X_L_G[0] |= 0b11000000;
			IMU.writeRead(LSM9DS0_OUT_X_L_G, 1, DATA, 3); /* read the LSM9DS0_OUT_X_L_G register (0x28) */
			CS_G.setPins(1); // Close communication

//			IMU.read(LSM9DS0_OUT_X_L_G, 1);
//			PRINTF("LSM9DS0_WHO_AM_I_G = %x \r\n", DATA[1]);
//			sprintf(imuData.i, "LSM9DS0_WHO_AM_I_G = %x \r\n", DATA[1]);
//			sprintf(imuData.i, "LSM9DS0_OUT_X_L_G = %x \r\n", DATA[1]);
			char buff[50];
			sprintf(buff,"Data0 = %x, Data1 = %x, Data2 = %x \r\n", DATA[0],DATA[1],DATA[2]);
			bt_uart.write(buff,strlen(buff));
			suspendCallerUntil(NOW()+50*MILLISECONDS);
//			int16_t gyroX = (DATA[1]) | DATA[2] << 8;
//			float output = gyroX*8.75f;
//			sprintf(imuData.i, "LSM9DS0_OUT_X_L_G = %f \r\n", output);

			//SensorDataTopic.publish(imuData);
		    suspendCallerUntil(NOW()+50*MILLISECONDS);

		}
	}
};
SensorIMU SensorIMU("SensorIMU");
/***********************************************************************/

