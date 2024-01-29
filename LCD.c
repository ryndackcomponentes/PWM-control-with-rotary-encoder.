/***************************************************************************************************/
/*  Biblioteca para controle de um display LCD 16x2 (Arquivo.c)
/*
/* Autor: Willian Mateus Ferreira dos Santos                                       Data:14/11/2023
/*
/***************************************************************************************************/


#include "LCD.h"

// Função para a inicialização do display LCD, nela define-se os bits mais significativos do PORT_LCD
//e do PORT_config como saida, em seguida envia-se os comandos para configurar o display na operação 
//no modo de 4 bit. 
void LCD_init(){
    DDR_LCD    = ((0xF0)|(DDR_LCD));
    DDR_config = ((0x07)|DDR_config);
    _delay_ms(15);
    PORT_config &= ~(1<<RW);
    PORT_config &= ~(1<Enable);
    PORT_config &= ~(1<<RS);
    PORT_LCD = (((0x02 & 0x0F)<<4)|(PORT_LCD & 0x0F));
    PORT_config |= (1<<Enable);
    _delay_ms(1);
    PORT_config &=~(1<<Enable);
    _delay_ms(2);
    LCD_envia_dados(0x28);
    LCD_envia_dados(0x0E);
    LCD_envia_dados(0x06);
    LCD_clear();
    LCD_envia_dados(0x80);
    
    _delay_ms(2);
}

// Implementa a rotina para envio de dados para o display, esses dados são enviados em duas etapas, 
//Primeiro - Os bits mais significativos são enviados, em seguida os bits menos significativos.
void LCD_envia_dados(uint8_t dados){
    PORT_config &= ~(1<<RS);
    PORT_LCD = ((dados & 0xF0)|(PORT_LCD & 0x0F));
    PORT_config |= (1<<Enable);
    _delay_ms(1);
    PORT_config &= ~(1<<Enable);
    _delay_ms(1);
    PORT_LCD = (((dados & 0x0F)<<4)|(PORT_LCD & 0x0F));
    PORT_config |= (1<<Enable);
    _delay_ms(1);
    PORT_config &=~(1<<Enable);
    _delay_ms(2);
}

// Envia os comandos para limpar o display LCD.
void LCD_clear(){
    LCD_envia_dados(0x01);
    _delay_ms(1);
    LCD_envia_dados(0x80);
    _delay_ms(1);
}

// Implementa a rotina para a escrita no display LCD. 
void LCD_write(char palavra[20]){
    int i=0;
    
    while (palavra[i]!='\0'){
        PORT_config |= (1<<RS);
        PORT_LCD = ((palavra[i] & 0xF0)|(PORT_LCD & 0x0F));
        PORT_config |= (1<<Enable);
        _delay_ms(1);
        PORT_config &= ~(1<<Enable);
        _delay_ms(1);
        PORT_LCD = (((palavra[i] & 0x0F)<<4)|(PORT_LCD & 0x0F));
        PORT_config |= (1<<Enable);
        _delay_ms(1);
        PORT_config &=~(1<<Enable);
        _delay_ms(2);
        i++;
    }

}

// Movimenta o cursor para a posição (x, y) desejada.
void LCD_move_cursor (uint8_t x, uint8_t y){
    LCD_envia_dados ((0x80|(x<<6))+y);
    _delay_us(100);
}
