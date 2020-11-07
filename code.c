#include <avr/eeprom.h>

int sensorPin = A0;
int sensorInput;
double temp;
uint8_t seconds = 46874;
uint32_t lowAddress;
uint32_t highAddress;
uint32_t intTemp;


//16mhz clock speed
//Clock prescaler
void timer_delay(uint8_t seconds){
  while (1) {
    //Serial.println(TCNT1);
    if (TCNT1 >= 23437) {
      TCNT1 = 0;
      return;
    }
  }
}

void setup() {
  TCCR1A = 0b00000000;
  TCCR1B = 0b00000101;
  Serial.begin(9600); //Start the Serial Port at 9600 baud (default)
}

void loop()
{
  sensorInput = analogRead(A0);
  temp = (double)sensorInput / 1024;   //find percentage of input reading
  temp = temp * 5;                     //multiply by 5V to get voltage
  temp = temp - 0.5;                   //Subtract the offset 
  temp = temp * 100;                 //Convert to degrees
  
  
  
  intTemp = round(temp);
  
  if((int)intTemp < 20) {
    eeprom_write_dword(&lowAddress, intTemp);
  } else {
    eeprom_write_dword(&highAddress, intTemp);
  }
  
  Serial.println((int)eeprom_read_dword(&lowAddress));
  Serial.println((int)eeprom_read_dword(&highAddress));
  
  timer_delay(seconds);
}
  
      
