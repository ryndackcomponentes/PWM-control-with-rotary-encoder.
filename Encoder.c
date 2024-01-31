#define F_CPU 16000000

#include <avr/io.h>
#include <stdio.h>
#include "LCD.h"
#include <util/delay.h>

int le_encoder(void);
void calcula_PWM(int);

int main(void){
// Configura os pinos de entrada. 
    DDRD &= ~((1<<PD0)+(1<<PD1));
    PORTD |= ((1<<PD0)+(1<<PD1));

// Configura PWM.
    DDRB |= (1<<PB3);
    TCCR2A |= ((1<<COM2A1)+(1<<WGM21)+(1<<WGM20));
    TCCR2B |= (1<<CS20);
    OCR2A = 0;

// Inicia o LCD.
    LCD_init();
    LCD_move_cursor(0,0);

// Loop de execução.
    while(1){
        calcula_PWM(le_encoder());
    }
return 0;
}

// Realiza a leitura do encoder rotativo, e retorna 1, -1 ou 0, dependendo da direção para a qual ele foi girado.
int le_encoder(void){

static int8_t A_B = 3;                                                              // A_B |==> Armazena os estados anterior e atual do encoder.
static int8_t incremento;                                                           // incremeto|==> Variavel retornada pela função, indica o sentido de rotação do encoder.
static int8_t entradas[]= {0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0};     // entradas[] |==> Vetor com as mudanças de estados possíveis.
  
// Cria um binario de 4 bits com os 2 MSDs indicando o estado passado e os 2 LSDs indicando o estado atual do encoder.
    A_B<<=2;
    A_B |= (PIND & 0x03);
    incremento += entradas[A_B & 0x0f];

// Evita incrementos e decrementos descontrolados.
    if((incremento>1)||(incremento<-1)){
        incremento=0;
    }
    
    
return incremento;
}

// Exibe na tela de um display LCD o duty cicle de um PWM determinado com um rotary encoder e manda esse PWM pro PB3.
void calcula_PWM(int incremento){

static uint8_t D;                    // D = duty cicle em percentual
static uint8_t duty = 0;             // duty = duty cicle valor passado para o OCR2A para dutyrole do PWM
char s_duty[20];                     // s_duty = string com o duty cicle em percentual para exibir no LCD.
if (incremento){
            if(duty>10){
                if(duty<245){
                    duty += 3*incremento;
                }
                else if(duty<253){
                    duty += incremento;
                }
                else if(incremento>0){
                    duty = 255;
                }
                else{
                    duty += incremento;
                }
            }
            else if(duty>2){
                duty += incremento;
            }
            else if(incremento<0){
                duty = 0;
            }
            else{
                duty += incremento;
            }
            D=100*duty/255;
            if(duty > 254){
                sprintf(s_duty, "Duty: %d%%  Max    ", D);
            }
            else if(duty < 1){
                sprintf(s_duty, "Duty: %d%%  Min    ", D);
            }
            else{
                sprintf(s_duty, "Duty: %d%%         ", D);
            }
            OCR2A = duty;
            LCD_move_cursor(0,0);
            LCD_write(s_duty);
             _delay_ms(20);
        }
}
