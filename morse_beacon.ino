
/*
 ***********************************************
 EA1NK Morse Beacon
 2012 - Juan J. Lamas - EA1NK
 ***********************************************
 */
 

// Arduino pin configuration

int led=13; // Pin13 as led
int pwm=11; //Pin11 as tone output


// Beacon configuration.

char text[]="vvv vvv vvv the brown fox jumps over the lazy dog k "; // Beacon message.
int interval = 10 ; // Beacon interval is sec.


// Morse code speed & tone configuration WPM.

int speed=32; // Beacon speed 
int freq=550; // Tone in Hz

// Dot, dash and space timings using PARIS standard, dot = 60 milliseconds at 20 WPM.

float dot=(1200/speed);
float dash=3*dot;
float fig_space=dot;
float char_space=3*dot;
float word_space=7*dot;


void send_code(String encoded_ltr){

  Serial.println("");
  Serial.println(encoded_ltr);



  for(int i=0;i < encoded_ltr.length();i++){

    if(encoded_ltr[i] == '.'){
      
      tone(pwm,freq,dot);
      digitalWrite(led,HIGH);
      delay(dot);
      digitalWrite(led,LOW);

      Serial.write("dit "); 
    }

    if(encoded_ltr[i] == '-'){
      
      tone(pwm,freq,dash);
      digitalWrite(led,HIGH);
      delay(dash); 
      digitalWrite(led,LOW);
      Serial.write("dah "); 

    }


    if(encoded_ltr[i] == '|'){
      digitalWrite(led,LOW);
      delay(word_space);
      digitalWrite(led,LOW);
      Serial.write("  "); 

    }

    else {

      //Do nothing

    }

    digitalWrite(led,LOW);
    delay(fig_space);

    Serial.write(i);


  } 





}





void ltr_to_code(char ltr){

  char letters[]={
    'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','1','2','3','4','5','6','7','8','9','0',' ','.',',','?','/' };
  String code[]={
    ".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--",
    "--..",".----","..---","...--","....-",".....","-....","--...","---..","----.","-----","|",".-.-.-","--..--","..--..","-..-."  };

  for (int i=0;i<sizeof(letters);i++){
    
    
    
    if (ltr == letters[i]){

      send_code(code[i]);
      digitalWrite(led,LOW);
      delay(char_space);
    } 

  }
}


void setup(){
  
  // Initialize digital pin as output.
  
  pinMode(pwm,OUTPUT);
  pinMode(led,OUTPUT); 
  Serial.begin(9600);


}

void loop() {

  // We loop trough the array items and play the message. 
  
   
  for (int a=0;a<sizeof(text);a++){
    Serial.write(text[a]);
    Serial.write(" ");
    ltr_to_code(text[a]);

  }

  delay(interval * 1000);

}


