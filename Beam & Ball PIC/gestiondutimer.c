#include <p18f4520.h> 
#include <timers.h>   
#include <math.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <usart.h>
#include <adc.h>
#include "xlcdV.h"  
#include "MesIncludes.h"  


void InterruptHandlerHigh (void);
void attente_ms(unsigned int duree);
void Init_Interruptions(void);
void ADC_call(void);
void Status(void);
void PWM_50(unsigned int time);
void PWM2_50(unsigned int time);
void PWM_74(unsigned int time);
void PWM_26(unsigned int time);
void PWM_X(unsigned int var);
void PWM_Digit(unsigned int var);
void AnalyserTrame(void);

unsigned char car_rx = 0;
unsigned int bit_buf=0b0000000000 ;
unsigned char Etat = EtatINIT ; //switch case
unsigned int adc =0,duty =0,vari =0;
int actual_position=0;
float previous_error = 0.0;
float integral = 0.0;
float setpoint = 220.0,tampon=0.0;
float derivative=0.0;
float error=0;
float output=0;
char flag=2; 
int dt=30;
int dt_=0;
float  Kp=3 ,Ki=0.5 ,Kd=1.1;  // p=2.5  i=0.5  d=2.5	//Kp=3 ,Ki=1 ,Kd=1.1;
float test=0;
int temp=0;
int tab[10];
int index=0;
int i=0,k=1;
int somme=0;
int somme2=0;
char buffer[100];

void main(void){

	for (i=0;i<100;i++) {
		buffer[i]=0;
	}
	i=0;

	Init_Interruptions();    //Initalisation

	OpenUSART( USART_TX_INT_OFF&
		USART_RX_INT_ON &
		USART_ASYNCH_MODE &
		USART_EIGHT_BIT &
		USART_CONT_RX,
		12 ); 
	IPR1bits.RCIP=1;   //EUSART Receive Interrupt Priority bit


	OpenADC(ADC_FOSC_32 &
		ADC_RIGHT_JUST &
		ADC_12_TAD,
		ADC_CH1 &
		ADC_INT_OFF &
		ADC_REF_VDD_VSS,13);


	OpenTimer1(TIMER_INT_ON   &
		T1_16BIT_RW    &
		T1_SOURCE_EXT  &
		T1_PS_1_1      &
		T1_OSC1EN_ON   &  
		T1_SYNC_EXT_ON    );

	WriteTimer1(32768); 

	PR2 = 0b11001111 ;   //freq300
	T2CON = 0b00000111 ;
	CCPR1L = 0b00111110 ;  //duty 30%
	CCP1CON = 0b00011100 ;
	bit_buf = (CCPR1L<<2) + ((CCP1CON&&00110000)>>4); //10 bit duty cycle
	gotoXLCD(1);
	printf(" INIT.");			



dt_=dt-9;// 9 ms temps exece  boucle while
	PWM_X(50);	///horizontal



	if (BoutonS2 == 0 || flag ==1) {

		/*	if (BoutonS2 == 0 ) {
		Status();
		}*/

		while(1){  

				if ( flag ==0) {break;}   

			i=0;
			somme=0;
			somme2=0;

			for(i=0;i<10;i++) {
				ADC_call(); 
				tab[i]=adc;
				somme += tab[i];
			} 

			i=0;
			somme2 = somme/10.0;
			actual_position = (somme2-5)*1.65;
			// varie de 0 a 430

			stdout = _H_USART ;
			if(actual_position>255){
				printf("Q%c",(char)actual_position);
			}
			else{
				printf("P%c",(char)actual_position);
			}

	
			error = setpoint - actual_position;
			integral = integral + (error*dt/1000);
			derivative = (error - previous_error)/dt*1000;
 			output = (Kp*error)+ (Ki*integral) + (Kd*derivative);
			previous_error = error;


			/*** ange servo =func(output) ********/

			if(output>500){
				PWM_X(25);
				duty=25;
			}
			else if(output<-500){
				PWM_X(75);
				duty=75;
			}

			//	else if(error>-20 && error<20){
			//PWM_X(50);
			//duty=50;} 

			else {
				tampon=0;
				tampon=-0.0525*output;
				//	tampon=-500.0*output*output*output;
				tampon+=50;
				duty=(int)tampon;			//duty=-(25/430)*output+50;
				PWM_X(duty);
				temp=0;
			}		
			
		}
	}
}

void attente_ms(unsigned int duree){
	unsigned int i;	
	i=duree;
	while(i) 
	{Delay1KTCYx(1);
	i --;} }

void Status(void){
	dt_ = dt-9;
	stdout = _H_USER;
	clearXLCD();
	gotoXLCD(1);
	printf("SP=%d dt=%d %f",(int)setpoint,dt,dt_);			
	gotoXLCD(LCD_LINE_TWO); //deuxieme ligne LCD
	printf("p=%d i=%d d=%d",(int)Kp,(int)Ki,(int)Kd);
}

void PWM_50(unsigned int time){
	PORTC=0;
	printf("%d  cm",adc);
	PR2 = 0b01111100 ;     
	CCPR1L = 0b00111110 ;
	CCP1CON = 0b00011100 ;
	bit_buf = (CCPR1L<<2) + ((CCP1CON&&00110000)>>4);
	gotoXLCD(LCD_LINE_TWO); //deuxieme ligne LCD
	printf("PWM 50 %d  bin",bit_buf);
	attente_ms(time);
}


void PWM2_50(unsigned int time){
	PORTC=0;
	PR2 = 0b11001111 ;   //freq300
	CCPR1L = 0b00111110 ;  //duty 30%
	CCP1CON = 0b00011100 ;
	bit_buf = (CCPR1L<<2) + ((CCP1CON&00110000)>>4);
	gotoXLCD(LCD_LINE_TWO); //deuxieme ligne LCD
	printf(" PWM2 50 %d  bin",bit_buf);
	attente_ms(time);
}

void PWM_74(unsigned int time2){
	PORTC=0;		
	PR2 = 0b01111100 ; 		 			
	CCPR1L = 0b01011100 ;
	CCP1CON = 0b00011100 ;
	bit_buf = (CCPR1L<<2) + ((CCP1CON&00110000)>>4);
	gotoXLCD(LCD_LINE_TWO); //deuxieme ligne LCD
	printf(" PWM 74 %d  bin",bit_buf);
	attente_ms(time2);
}

void PWM_26(unsigned int time3){
	PORTC=0;
	PR2 = 0b01111100 ; 
	CCPR1L = 0b00100000 ;
	CCP1CON = 0b00011100 ;
	bit_buf = (CCPR1L<<2) + ((CCP1CON&00110000)>>4);
	gotoXLCD(LCD_LINE_TWO); //deuxieme ligne LCD
	printf(" PWM 26 %d  bin",bit_buf);
	attente_ms(time3);
}

void PWM_X(unsigned int var){
	//	PORTC=0;
	//	stdout = _H_USER;						//////
	//	clearXLCD();
	//	gotoXLCD(LCD_LINE_ONE);					//15 msec
	//	printf("%d  mm", actual_position);
	//	gotoXLCD(LCD_LINE_TWO);
	//	printf("PWM %d ",var );					///////
//	stdout = _H_USART ;
//	printf("W%c",(char)var);
			
	vari=(var*5)-1;
	PR2 = 0b01111100 ; 
	CCPR1L = vari>>2 ;
	temp = vari&0b0000000011;
	temp = temp << 4;
	temp = temp | 0b00001100;
	CCP1CON = temp;
	attente_ms(dt_);
}

void PWM_Digit(unsigned int var){
	stdout = _H_USER;						//////
	clearXLCD();							//
	gotoXLCD(LCD_LINE_ONE);					//	15 msec
	printf("%d  mm", actual_position);		//
	gotoXLCD(LCD_LINE_TWO);					//
	printf("PWM %d ",var );					//
	PR2 = 0b10001010 ;
	vari=(int)(var*5.5);
	CCPR1L = vari>>2 ;
	temp = vari&0b0000000011;
	temp = temp << 4;
	temp = temp | 0b00001100;
	CCP1CON = temp;
	attente_ms(dt_);
}


void ADC_call(void) {         
	ConvertADC();  // Start conversion
	while(BusyADC()); // wait for completion
	adc = ReadADC();  // Read result
}



void Init_Interruptions(void)
{
	/*initialisations */

	TRISBbits.TRISB1=0;  //led1
	TRISBbits.TRISB2=0;  //led2
	TRISCbits.TRISC2=0;  //PWM
	TRISAbits.TRISA1=1;  //ADC
	BoutonS3=1;  //RBO definit en entrée
	BoutonS2=1;  //RA4 definit en entrée
	OpenXLCD(FOUR_BIT);
	RCONbits.IPEN=0; //2 niveau interrruption
	INTCON = 1;  //interruption control
	INTCONbits.GIE = 1;  //activation generales des interruptions
	INTCONbits.INT0IE = 0; /* mise à 0 avant de le mettre à 1 */
	INTCONbits.INT0IE = 1 ; //activation de l'interruption de la patte RB0
	INTCON2bits.INTEDG0=0; //evennement du falling edge
	INTCONbits.PEIE = 1; //activation des interruption des péripheriques (comme le timer)
	IPR1bits.TMR1IP=1;      //TMR1 Overflow Interrupt Priority bit    
	stdout = _H_USER ;

}



//----------------------------------------------------------------------------
// High priority interrupt vector
#pragma code InterruptVectorHigh = 0x08
void InterruptVectorHigh (void)
{
	_asm
		goto InterruptHandlerHigh //jump to interrupt routine
		_endasm
}

// Routine d'interruption
//----------------------------------------------------------------------------
// High priority interrupt routine
#pragma code
#pragma interrupt InterruptHandlerHigh
void InterruptHandlerHigh (void){

	if(PIR1bits.TMR1IF)
	{  
		PIR1bits.TMR1IF = 0 ;
		WriteTimer1(32768);
	}
	if(PIR1bits.RCIF) {   
		// car_rx = ReadUSART();
		buffer[index]=ReadUSART();
		if(buffer[index]==0){
			index=0;
		}
		else	{	
			index++;
			if (buffer[index-1]=='\x0A') {
				AnalyserTrame();
				Status();
				index=0;
			}
		}
		//PIR1bits.RCIF = 0 ;
	}
	if(BoutonS2 == 0 ){
		Etat++;
		Etat%=2;
	}
}

void AnalyserTrame() {

	char chaine[20];
	for(k=0;k<20;k++){
		chaine[k]=0;
	}
	for(k=0;k<index-2;k++){
		chaine[k]=buffer[k+1];
	}
	if (buffer[0] =='K') {
		Kp=(float)atof(chaine);
	}
	else if (buffer[0]=='L') {
		Ki=(float)atof(chaine);
	}
	else if (buffer[0]=='M') {
		Kd=(float)atof(chaine);
	}
	else if (buffer[0]=='D') {
		dt=(int)atoi(chaine);
	}
	else if (buffer[0]=='S') {
		setpoint=(float)atof(chaine);
	}
	else if (buffer[0]=='F') {
		flag=(char)atoi(chaine);
	}




}