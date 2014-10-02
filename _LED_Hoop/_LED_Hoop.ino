
#include "FastSPI_LED2.h"
#include <avr/sleep.h>

#define NUM_LEDS 196

struct CRGB leds[NUM_LEDS];

int external_rainbow_counter = 0;
int cycle_counter = 0;
int third_counter = 0;
int LED_steps = 1;

int iteration_counter = 0;

boolean swap = true;


int program_state = 0;

const int buttonPin = 2; 
const int LEDPin = 11; 

void setup() {
	
  //Sanity check delay - allows reprogramming if accidently blowing power w/leds
  delay(2000);

  //LED brightness 0-255, less bright at 3.5v, 5v draws too much
  //LEDS.setBrightness(128); //Normal Brightness
  LEDS.setBrightness(255);  //Brighter, looks good
  
  LEDS.addLeds<WS2811, 11, BRG>(leds, NUM_LEDS); //Add LEDs to list, GRB ordering
   
 // pi88ii8ii8nMode(buttonPin, INPUT);  
 // attachInterrupt(0, wakeUp, LOW);
   
}
/*
//Wake up code
void wakeUp(){
  
}

void sleep(){
   set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
     attachInterrupt(0,wakeUp, LOW);
      sleep_mode();           
 
    sleep_disable();       
    detachInterrupt(0);
  
}*/

void loop() { 
  
  memset(leds, 0,  NUM_LEDS * sizeof(struct CRGB));  //Clear all LED settings
 
  iteration_counter++; //Increment global counter
  
  //Set LEDs
  //patternNeon();
  //patternRainbow();
  patternFun();
  LEDS.show();  //Show LEDs
  
  delay(5);  //Delay display
  
  //external_rainbow_counter++;
  //cycle_counter++;
  //patternFauxVision2();
 // patternOneOffRainbow();
 // patternRedVioletWhite();
  //patternFauxVision();
  //LEDS.show();
}


//Patterns 
void patternNeon(){
  
  int one_seventh = NUM_LEDS/7;
  
  int led_length = 7;
  
  int location = 0;
 
  //Orange
  location = (led_length)%NUM_LEDS;
  setColor(7, location, led_length, 255, 165, 0, true, false);
 
  //Lime Yellow
  location = (one_seventh*1+led_length)%NUM_LEDS;
  setColor(7, location, led_length, 173, 255, 47, true, false);
   
  location = (one_seventh*2+led_length)%NUM_LEDS;
  setColor(7, location, led_length, 255, 105, 180, true, false);
   
  //Green
  location = (one_seventh*3+led_length)%NUM_LEDS;
  setColor(7, location, led_length, 0, 0, 255, true, false);
   
  //Blue
  location = (one_seventh*4+led_length)%NUM_LEDS;
  setColor(7, location, led_length, 0, 191, 255, true, false);
   
  //Purple
  location = (one_seventh*5+led_length)%NUM_LEDS;
  setColor(7, location, led_length, 160, 32, 240, true, false);
  
   //Red
  location = (one_seventh*6+led_length)%NUM_LEDS;
  setColor(7, location, led_length, 255, 0, 0, true, false);
}

void patternRainbow(){
  
  for(int iLed = 0; iLed< NUM_LEDS; iLed++){
    fill_rainbow( &(leds[iLed]), 1, (iteration_counter+iLed)%255);
  }
}

//Pattern fun
void patternFun(){
  
  
  
  int offset = 0;
  int breaks = 12;
  int led_length = 3;
  
  
  setColor(breaks, offset, led_length, 0, 0, 128, true, false);
  setColor(breaks, offset+(NUM_LEDS/12), led_length, 0, 0, 255, true, false);
  setColor(breaks, offset+(NUM_LEDS/12)*2, led_length, 0, 128, 255, true, false);
  setColor(breaks, offset+(NUM_LEDS/12)*3, led_length, 0, 255, 255, true, false);
  setColor(breaks, offset+(NUM_LEDS/12)*4, led_length, 128, 255, 255, true, false);
  setColor(breaks, offset+(NUM_LEDS/12)*5, led_length, 255, 255, 255, true, false);
  setColor(breaks, offset+(NUM_LEDS/12)*6, led_length, 255, 128, 255, true, false);
  setColor(breaks, offset+(NUM_LEDS/12)*7, led_length, 255, 0, 255, true, false);
  setColor(breaks, offset+(NUM_LEDS/12)*8, led_length, 128, 0, 255, true, false);
  setColor(breaks, offset+(NUM_LEDS/12)*9, led_length, 128, 128, 255, true, false);
  setColor(breaks, offset+(NUM_LEDS/12)*10, led_length, 128, 128, 128, true, false);
  setColor(breaks, offset+(NUM_LEDS/12)*11, led_length, 128, 0, 128, true, false);
      
  
}


//Utlity functions
void setColor(int breaks, int offset, int led_length, int r, int g, int b, boolean use_iterator_location, boolean use_iterator_color){
  
  int location = 0;
  
  if(use_iterator_location){
     location = ((NUM_LEDS/breaks)+offset+iteration_counter)%NUM_LEDS;
  }
  else{
    location = ((NUM_LEDS/breaks)+offset)%NUM_LEDS;
  }
  
  for(int LED = 0; LED<led_length; LED++){
    
    if((location+LED)>=NUM_LEDS){
       fill_solid( &(leds[(location+LED)%NUM_LEDS]), 1, CRGB( r, g, b));
    }
    else{
     fill_solid( &(leds[location+LED]), 1, CRGB( r, g, b));
    }
  }
}

void patternCycler(){
  
  if(cycle_counter%15==0){
        if( (LED_steps%12)  == 0){
         swap = !swap;
       }
      if(swap){
        LED_steps++;
      }
      else{
         LED_steps--;
      }
    
    
  }
  for(int iLed = 0; iLed < NUM_LEDS; iLed+=LED_steps) {
    
  //  fill_solid( &(leds[iLed]), 1 , CRGB( abs(ax)/60, abs(ay)/60, abs(az)/60) );
     //fill_rainbow( &(leds[iLed]), 1, external_rainbow_counter);
       
  }
 
  LEDS.show();
  
}

