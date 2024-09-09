// C++ code
//

#include <math.h>

#define clk_in 8
#define clk_out 9
#define TX 7
#define RX 6
#define BIT_TIME 20
#define BAUD_RATE 9600


static int r_data = 0b00000000;
//static int r_data = 0;
static int r_counter = 0;
static int  r_clk_ref = 0;
static int  r_clk_now = 0;

static int t_data = 0b01111110;
//unsigned static char t_data = 'a';
int t_bit;
static int t_counter = 0;
unsigned static long r_time_ref = 0 ;
static int currClk = 0;

void setup()
{
  Serial.begin(BAUD_RATE);
  pinMode(TX, OUTPUT);
  pinMode(RX, INPUT);
  pinMode(clk_out, OUTPUT);
  pinMode(clk_in, INPUT);
}

void loop()
{
  usart_tx();
  usart_rx();
}


void usart_rx(){
  r_clk_now = digitalRead(clk_in);
  if(r_clk_now - r_clk_ref == 1){
    r_clk_ref = r_clk_now;
    bitWrite(r_data,r_counter,digitalRead(RX));
    //Serial.print(digitalRead(RX));//test***************
  }
  else{
    r_clk_ref = r_clk_now;
    return;
  }
  if(r_counter == 8){
    r_counter = 0;
    return;
  }
  r_counter++;
}
  
  

void usart_tx(){
  if(millis() - r_time_ref > BIT_TIME){	
    currClk = !currClk;
    digitalWrite(clk_out,currClk);
      if(currClk == 1){
    	t_bit = bitRead(t_data, t_counter);
        //Serial.print(t_bit);//test***************
    	digitalWrite(TX, t_bit);
        t_counter++;
        if(t_counter == 8){
          t_counter = 0;
        }
      }
    return;
  }
  else{
    return;
  }
}

    
  
  
  
  