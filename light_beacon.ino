/*

  EA1NK Light Beacon
  Blinks LED and transmit EA1NK callsign in morse code
  2012 - Juan J. Lamas - EA1NK

*/

// Pin 13 as LED
int led=13;

// Morse code message (1= dot, 2 = dash, 0=space)as array.
int msg[]={4,1,0,3,1,0,2,0,3,1,0,2,0,2,0,2,0,2,0,3,2,0,1,0,3,2,0,1,0,2,0,4};
         //  .     .   -     .   -   -   -   -     -   .      -   .   -   
         //  E        A           1                N              K

// Morse code speed configuration WPM.
int speed=12;

// Dot, dash and space timings using PARIS standard, dot = 60 milliseconds at 20 WPM.
float dot=(1200/speed);
float dash=3*dot;
float fig_space=dot;
float char_space=3*dot;
float word_space=7*dot;

void setup(){
  // Initialize digital pin as output.
   pinMode(led,OUTPUT); 
  
  
}

void loop() {
 
 // We loop trough the array items and play the message. 
 for (int i=0;i<sizeof(msg);i++){
   
   if (msg[i]==0){             // Value of array item = 0 then we play a space between figures.
    digitalWrite(led,LOW);
    delay(fig_space); 
   }   
   if (msg[i]==1) {            // Value of array item = 1 then we play a dot.
     digitalWrite(led,HIGH);
     delay(dot); 
   }
   if (msg[i]==2){            // Value of array item = 2 then we play a dash.
     digitalWrite(led,HIGH);
     delay(dash);    
   }
   if (msg[i]==3){            // Value of array item = 3 then we start a new char.
    digitalWrite(led,LOW);
    delay(char_space);   
   }
   if (msg[i]==4){            // Value of array item = 3 then we start a new word.
    digitalWrite(led,LOW);
    delay(word_space); 
   }
 }
  
  
  
  
}
