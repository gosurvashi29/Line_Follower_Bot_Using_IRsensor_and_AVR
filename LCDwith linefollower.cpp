# define F_CPU 1000000
# include<avr/io.h>
# include<util/delay.h>
void lcd_init();
void disp_cmd(unsigned int cmd);
void disp_data(int cmd);
void disp_num(unsigned int num);
void disp_string(  char *str);



int main(void)
{
	DDRC=0X00;
	PORTC=0X00;
	
	DDRD=0XFF;
	DDRB = 0XFF;
	
	lcd_init();
	
disp_cmd(0X80);
disp_string("line follower");
	
	while(1)
	{
		if(PINC == 0b00000001)		//if Left Sensor comes upon the black line
		{
			PORTD =0X10;
			_delay_ms(10);
			disp_cmd(0X01);
			_delay_ms(10);
			disp_cmd(0X80);
			disp_string("left");
			
			_delay_ms(30);    
			        	// Turn LEFT
		}
		
		else if(PINC == 0b00000010)	// if Right Sensorcomes upon the black line
		{
			PORTD =0x40;
			_delay_ms(10);
			disp_cmd(0X01);
			_delay_ms(10);
			disp_cmd(0X80);
			disp_string("right");
			_delay_ms(30);
			// Turn RIGHT
		}
		else if(PINC == 0b10000000)
		{
			PORTD =0b01010000;
			_delay_ms(10);
			disp_cmd(0X01);
			_delay_ms(10);
			disp_cmd(0X80);
			disp_string("forward");
			_delay_ms(30);					// Move Forward
		}
		else if (PINC == 0b00000000)
		{
			PORTD= 0X00;
			_delay_ms(10);
			disp_cmd(0X01);
			_delay_ms(10);
			disp_cmd(0X80);
			disp_string("stop");
			_delay_ms(30);
		}
	}
	return 0;
}
void lcd_init()
{
	disp_cmd(0X02);
	disp_cmd(0X28);
	disp_cmd(0X0C);
	disp_cmd(0X06);
}

void disp_cmd(unsigned int cmd)
{
	PORTB=((cmd & 0XF0)+0X04);
	_delay_ms(1);
	PORTB=PORTB - 0X04;
	PORTB=(((cmd<<4)& 0XF0)+0X04);
	_delay_ms(1);
	PORTB=PORTB-0X04;
	
}
void disp_data( int cmd)
{
	PORTB=((cmd  & 0XF0)+0X05);
	_delay_ms(1);
	PORTB=PORTB - 0X04;
	PORTB=(((cmd <<4)& 0XF0)+0X05);
	_delay_ms(1);
	PORTB=PORTB-0X04;
	
}

void disp_string( char *str)
{
	int i=0;
	while (str[i]!='\0')
	{
		disp_data (str[i]);
		i++;
		
	}
}

void disp_num(unsigned int num)
{
	int a=0;
	if (num==0)
	{
		disp_data(48);
	}
	disp_cmd (0X04);
	while (num!=0)
	{
		a=num % 10;
		disp_data(a+48);
		num=num/10;
	}
}