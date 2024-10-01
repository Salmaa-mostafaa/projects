#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

unsigned char num0=0,num1=0,num2=0,num3=0,num4=0,num5=0;
unsigned char flag=0;

void inti(void){

	DDRC|=0X0F;                //7 SEGMENT
	PORTC|=0X0F;
	DDRA|=0X7F;
	PORTA&=~0X7F;
	DDRB&=~(1<<PB7);            //Toggle button
	PORTB|=(1<<PB7);
	DDRB&=(1<<PB0)&(1<<PB1);    //HOURS
	DDRB&=(1<<PB3)&(1<<PB4);    //MIN
	DDRB&=(1<<PB5)&(1<<PB6);     //SEC
	PORTB|=(1<<PB0)|(1<<PB1)|(1<<PB3)|(1<<PB4)|(1<<PB5)|(1<<PB6);
	DDRD|=(1<<PD0);                //BUZZER/
	PORTD&=~(1<<PD0);
	DDRD|=(1<<PD4);               //Counting Up LED
	DDRD|=(1<<PD5);               //Counting Down LED
	PORTD&=~(1<<PD4);
	PORTD&=~(1<<PD5);


	SREG|=(1<<7);
	GICR|=(1<<INT0)|(1<<INT1)|(1<<INT2);
	MCUCR|=(1<<ISC01)|(1<<ISC11)|(1<<ISC10);


	TCCR1A|=(1<<FOC1A);
	TCCR1B|=(1<<CS10)|(1<<CS12)|(1<<WGM12);     //TIMER 1 COMP
	TCNT1=0;
	OCR1A=15625;
	TIMSK|=(1<<OCIE1A);
	PORTD|=(1<<PD2);
	PORTB|=(1<<PB2);

}

void DISPLAY(void){
       	PORTA=0;
       	PORTA|=(1<<0);
       	PORTC=(PORTC & 0XF0)|(num0 & 0X0F);
       	_delay_ms(2);
       	PORTA=0;
       	PORTA|=(1<<1);
        PORTC=(PORTC & 0XF0)|(num1 & 0X0F);
       	_delay_ms(2);
       	PORTA=0;
       	PORTA|=(1<<2);
       	PORTC=(PORTC & 0XF0)|(num2 & 0X0F);
       	_delay_ms(2);
       	 PORTA=0;
       	 PORTA|=(1<<3);
       	 PORTC=(PORTC & 0XF0)|(num3 & 0X0F);
       	 _delay_ms(2);
       	 PORTA=0;
       	 PORTA|=(1<<4);
       	 PORTC=(PORTC & 0XF0)|(num4 & 0X0F);
       	 _delay_ms(2);
       	 PORTA=0;
       	 PORTA|=(1<<5);
       	 PORTC=(PORTC & 0XF0)|(num5 & 0X0F);
       	 _delay_ms(2);
}

void CountUP(void){
	if(num0<9){
		num0++;
	}
	else{
		num0=0;
	if(num1<5){
		num1++;
	}
	 else{
		num1=0;
	if(num2<9){
		num2++;
	}
	 else{
		 num2=0;
	  if(num3<5){
		 num3++;
	}
	else{
		 num3=0;
	 if(num4<9){
		num4++;
	}
	else{
		num4=0;
	if(num5<5){
		num5++;
    }
	else{
		num5=0;

		     }
	       }
         }
	   }
	 }
   }
 }

void CountDOWN(void){
	if(num0>0){
		num0--;
	}
		else{
			num0=9;
			if(num1>0){
				num1--;
			}
			else{
				num1=5;
				if(num2>0){
					num2--;
				}
					else{
						num2=9;
						if(num3>0){
							num3--;
						}
						else{
							num3=5;
							if(num4>0){
								num4--;
							}
								else{
									num4=9;
									if(num5>0){
										num5--;
									}
									else{
										num5=0;
										num4=0;
										num3=0;
										num2=0;
										num1=0;
										num0=0;
									}
								}
							}
						}
					}
				}
	if(num0==0 && num1==0 && num2==0 && num3==0 && num4==0 && num5==0){
			PORTD|=(1<<PD0);

		}
}

void hours_inc(void){
	if(num4<9){
				num4++;
			}
			else{
				num4=0;
			if(num5<5){
				num5++;
			}
			 else{
				num5=0;
			 }
	}
	}
void hours_dec(void){
	if(num4>0){
					num4--;
				}
				else{
				if(num5>0){
					num4=9;
					num5--;
				}
				 else{
					num5=0;
	}
	}
}
void min_inc(void){
	if(num2<9){
				num2++;
			}
			else{
				num2=0;
			if(num3<5){
				num3++;
			}
			 else{
				num3=0;
			 }
	}
}
void min_dec(void){
	if(num2>0){
					num2--;
				}
				else{
				if(num3>0){
					num2=9;
					num3--;
				}
				 else{
					num3=0;
	}
	}
}
void sec_inc(void){
	if(num0<9){
			num0++;
		}
		else{
			num0=0;
		if(num1<5){
			num1++;
		}
		 else{
			num1=0;
		 }
}
}
void sec_dec(void){
	if(num0>0){
				num0--;
			}
			else{
			if(num1>0){
				num0=9;
				num1--;
			}
			 else{
				num1=0;
}
}
}

       ISR(INT0_vect){
    	   num0=0,num1=0,num2=0,num3=0,num4=0,num5=0;
}

       ISR(INT1_vect){
	   SREG|=(1<<7);
	   TCCR1B&=(1<<CS12)&(1<<CS11)&~(1<<CS10);
}

       ISR(INT2_vect){
	   SREG|=(1<<7);
	   TCCR1B|=(1<<CS10)|(1<<CS12);
}
       ISR(TIMER1_COMPA_vect){
    		   if(flag==0){
    	   			CountUP();
    	   		}
    		   else{
    			   CountDOWN();
    		   }
       }

int main(void){
	inti();
	PORTD|=(1<<PD4);

	while(1){
		DISPLAY();
       if(!(PINB & (1<<PB7))){
    	   _delay_ms(15);
    	   if(!(PINB & (1<<PB7))){
    	   flag^=1;
    	   PORTD^=(1<<PD4);
    	   PORTD^=(1<<PD5);
    	   	 if(flag==0)
    	   	 PORTD&=~(1<<PD0);
    	   			    	   }
    	   while(!(PINB & (1<<PB7))){
    		   DISPLAY();
    	   }
       }
       if(!(PINB & (1<<PB5))){
          	   _delay_ms(15);
          	   if(!(PINB & (1<<PB5))){
          		   if(!(TCCR1B & 0X07)){
          		 sec_dec();
          	   }
          	   }
          	   while(!(PINB & (1<<PB5))){
          		   DISPLAY();
          	   }
}
       if(!(PINB & (1<<PB6))){
                 	   _delay_ms(15);
                 	   if(!(PINB & (1<<PB6))){
                 		  if(!(TCCR1B & 0X07)){
                 		 sec_inc();
                 		  }
                 	   }
                 	   while(!(PINB & (1<<PB6))){
                 		   DISPLAY();
                 	   }
       }
       if(!(PINB & (1<<PB3))){
                 	   _delay_ms(15);
                 	   if(!(PINB & (1<<PB3))){
                 		  if(!(TCCR1B & 0X07)){
                 		 min_dec();
                 	   }
                 	   }
                 	   while(!(PINB & (1<<PB3))){
                 		   DISPLAY();
                 	   }
       }
              if(!(PINB & (1<<PB4))){
                        	   _delay_ms(15);
                        	   if(!(PINB & (1<<PB4))){
                        		   if(!(TCCR1B & 0X07)){
                        		 min_inc();
                        		   }
                        	   }
                        	   while(!(PINB & (1<<PB4))){
                        		   DISPLAY();
                        	   }
              }
              if(!(PINB & (1<<PB0))){
                        	   _delay_ms(15);
                        	   if(!(PINB & (1<<PB0))){
                        		   if(!(TCCR1B & 0X07)){
                        		 hours_dec();
                        	   }
                        	   }
                        	   while(!(PINB & (1<<PB0))){
                        		   DISPLAY();
                        	   }
              }
                     if(!(PINB & (1<<PB1))){
                               	   _delay_ms(15);
                               	   if(!(PINB & (1<<PB1))){
                               		 if(!(TCCR1B & 0X07)){
                               		 hours_inc();
                               	   }
                               	   }
                               	   while(!(PINB & (1<<PB1))){
                               		   DISPLAY();
                               	   }
                     }
}
}
