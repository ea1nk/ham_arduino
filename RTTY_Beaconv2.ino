
//Arduino pin definition

#define RTTY 11 //PWM Pin

// RTTY Parametres

#define BAUDOT
//#define ASCII
//#define BITS 7 //  7 or 8 for ASCII
#define LETTERS 31
#define FIGURES 27

// END

#include <stdint.h>
 
int start_tone = 1200; //Start tone in Hz
int shift = 170; //Shift in Hz
int stop_tone = start_tone - shift;

char message[] = "";

int baudot[31][3] ={{65,45,3},  // A -
                    {66,63,25}, // B ?
                    {67,58,14}, // C :
                    {68,5,9},  // D WHO ARE YOU
                    {69,51,1},  // E 3
                    {70,33,13}, // F !
                    {71,38,26}, // G &
                    {72,35,20}, // H #
                    {73,56,6},  // I 8
                    {74,42,11}, // J BELL
                    {75,40,15}, // K (
                    {76,41,18}, // L )
                    {77,46,28}, // M .
                    {78,44,12}, // N ,
                    {79,57,24}, // O 9
                    {80,48,22}, // P 0
                    {81,49,23}, // Q 1
                    {82,52,10}, // R 4
                    {83,46,5},  // S .
                    {84,53,16}, // T 5
                    {85,55,7},  // U 7
                    {86,59,30}, // V ;
                    {87,50,19}, // W 2
                    {88,47,29}, // X /
                    {89,54,21}, // Y 6
                    {90,34,17}, // Z "
                    {32,32,4},  // Space
                    {0,0,0},  // Blank
                    {13,13,8},  // Carriage Return
                    {10,10,2},  // Line feed
                    };
                        
                        


void setup(){

  pinMode(RTTY,OUTPUT);
  Serial.begin(9600);

}


void loop(){
  
  rtty_tx(000000000000000000000000000000);
  sprintf(message,"\n\nRYRYRYRYRYRYRYRYRYRY\n");
  rtty_transmit(message);
  sprintf(message,"DE: EA1NK EA1NK EA1NK \n\n");
  rtty_transmit(message);
  sprintf(message,".: ARDUINO BAUDOT BEACON :. \n\n");
  rtty_transmit(message);
  sprintf(message,"0 1 2 3 4 5 6 7 8 9\n");
  rtty_transmit(message);
  sprintf(message,"--------------------\n");
  rtty_transmit(message);
  sprintf(message,". : , ; ! ( ) # & ? - \n\n");
  rtty_transmit(message);
  sprintf(message,"RYRYRYRYRYRYRYRYRYRY\n");
  rtty_tx(000000000000000000000000000000);
  
  rtty_transmit(message);
  pinMode(RTTY,LOW);
  
  delay(10000);  
}



void rtty_transmit(char *beacontext){


  char c;
  
  c = *beacontext ++; 
  
  while (c!= '\0'){

  #ifdef BAUDOT    
    baudot_byte(c);
  #endif
  
  #ifdef ASCII
     ascii_byte(c);
  #endif
  
  c= *beacontext ++;
  } 

}

void rtty_bit(int bit){


  if(bit){

    tone(RTTY,start_tone);
    //Serial.print(1);

  } 

  else {

    tone(RTTY,stop_tone);
    //Serial.print(0);
  }

  delayMicroseconds(10000);
  delayMicroseconds(10000);
  delayMicroseconds(1000);
  
  //Standard American Teletype sets Stop and Signal lenghts to 22ms for 45.45 Bd.
  //Standard American Teletype used by hams use Signal lenght of 22ms and Stop Pulse of 31ms.
}


#ifdef BAUDOT
enum baudot_mode {
  
none,
letters,
figs
  
};




void baudot_byte(char c){
  
  enum baudot_mode mode = none;
  int b;
  
  if(c < 123 && c > 96 || c < 91 && c >64){ // Letters 
    
      if (c < 123 && c > 96){ 
            c = c - 32; 
      }
  
      
      if(mode != letters){
        
        rtty_tx(LETTERS);
        mode = letters; 
      }
      
      b=0;
    }
  
   
   else { // Figures
     
    c = c; 
    if(mode != figs){
        
    rtty_tx(FIGURES);
    mode = figs;   
   
   }
   b=1;
  }
  

  
  int i;
  for(i=0;i< 32;i++){
    
    if( c == baudot[i][b] ){
       
        rtty_tx(baudot[i][2]);
        
     }
    
  }
}

#endif  


#ifdef ASCII

void ascii_byte(char c){


  int i;
 
  rtty_bit(0); //Start

  for (i=0;i<BITS;i++){

    if(c & 1) rtty_bit(1);
    else rtty_bit(0);
    c = c >> 1;

  }

  rtty_bit(1); //Stop
  rtty_bit(1); //Stop
  
  //Two bit stops here.

}


#endif
void rtty_tx(char character){
  
 int i;
 
 rtty_bit(0); //Start

  for (i=0;i<5;i++){

    if(character & 1) rtty_bit(1);
    else rtty_bit(0);
    character = character >> 1;

  }

 rtty_bit(1); //Stop
 rtty_bit(1); //Stop
  
  //Two bit stops here.   
}
