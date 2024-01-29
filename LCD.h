/***************************************************************************************************
  Biblioteca para controle de um display LCD 16x2 (Arquivo.h)

 Autor: Willian Mateus Ferreira dos Santos                                       Data:14/11/2023

***************************************************************************************************/

#ifndef LCD_H_
#define LCD_H_
#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>

//define os ports para a configuração e controle do display LCD.
#define DDR_LCD     DDRD
#define DDR_config  DDRC
#define PORT_LCD    PORTD
#define PORT_config PORTC

//define os pinos de configuração do display (Registor select, Read/Write e enable).
#define RS     PC2
#define RW     PC1
#define Enable PC0

//Define os pinos para o envio de dados.
#define D4     PD4
#define D5     PD5
#define D6     PD6
#define D7     PD7

//Protótipos das funções usadas na biblioteca do display.
void LCD_init(void);
void LCD_envia_dados(uint8_t);
void LCD_clear(void);
void LCD_write(char []);
void LCD_move_cursor(uint8_t, uint8_t);
#endif