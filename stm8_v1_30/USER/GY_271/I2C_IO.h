
#ifndef I2C_IO_H_
#define I2C_IO_H_
#include "stm8s.h"
#define I2C_WR	0		/* D��????bit */
#define I2C_RD	1		/* ?��????bit */
#define GPIO_PORT_I2C	GPIOA			/* GPIO???�� */
// #define RCC_I2C_PORT 	RCC_AHB1Periph_GPIOC		/* GPIO???������?�� */
#define I2C_SCL_PIN		GPIO_PIN_1			/* ��??����?SCL����?��??��?GPIO */
#define I2C_SDA_PIN		GPIO_PIN_2			/* ��??����?SDA��y?Y??��?GPIO */

/* ?����??��D��SCLo��SDA��?o�� */
#define I2C_SCL_0()  GPIO_PORT_I2C->ODR &= (uint8_t) (~I2C_SCL_PIN)				/* SCL = 1 */
#define I2C_SCL_1()  GPIO_PORT_I2C->ODR |= (uint8_t) I2C_SCL_PIN				/* SCL = 0 */

#define I2C_SDA_0()  GPIO_PORT_I2C->ODR &= (uint8_t) (~I2C_SDA_PIN)				/* SDA = 1 */
#define I2C_SDA_1()  GPIO_PORT_I2C->ODR |= (uint8_t) I2C_SDA_PIN				/* SDA = 0 */

#define I2C_SDA_READ()  ((GPIO_PORT_I2C->IDR & I2C_SDA_PIN) != 0)	/* ?��SDA?��??���䨬? */
#define I2C_SCL_READ()  ((GPIO_PORT_I2C->IDR & I2C_SCL_PIN) != 0)	/* ?��SCL?��??���䨬? */

void bsp_InitI2C(void);
void i2c_Start(void);

void i2c_Stop(void);
void i2c_SendByte(uint8_t _ucByte);
uint8_t i2c_ReadByte(void);
uint8_t i2c_WaitAck(void);
void i2c_Ack(void);
void i2c_NAck(void);
uint8_t i2c_CheckDevice(uint8_t _Address);

#endif 
