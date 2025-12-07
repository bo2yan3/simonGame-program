
// LED and BUTTON declaration
#define GREEN 9
#define RED 8

const int ledPins[] = {13, 12, 11, 10};
const int buttonPins[] = {7, 6, 5, 4}; 



// Button State Tracking
int switchState0;  
int switchState1;  
int switchState2;
int switchState3; 

int prev0 = LOW; 
int prev1 = LOW; 
int prev2 = LOW; 
int prev3 = LOW; 

// Sequence Trackingf

int sequence[5] = {0}; 
int userSequence[5] = {0}; 
int mode = 0; 
int count; 
bool correctSequence; 

// Timeout Constant

unsigned long timeOut = 20000; 

// FUNCTION PROTOTYPES

// Light LED 
void lightLED(int num); 

// Correct and Incorrect Sequence Entered
void win(void); 
void lose(void); 

// Check user button input
void userInput(int* userSequence, int mode); 

// Verifies user input to the generated sequence
bool sequenceCheck(int* userSequence, int* sequence, int mode); 

void setup()
{
  
  // setup for LED as OUTPUT & BUTTON as INPUT
  for (int i = 0; i < 4; i++){
    pinMode(ledPins[i], OUTPUT); 
    pinMode(buttonPins[i],INPUT); 
  }
  
  // Set random seed
  randomSeed(analogRead(0)); 
  
  // Serial setup 
  Serial.begin(9600); 
}

void loop()
{
  unsigned long now = millis(); 
  
  switchState0 = digitalRead(buttonPins[0]); 
  switchState1 = digitalRead(buttonPins[1]); 
  switchState2 = digitalRead(buttonPins[2]); 
  switchState3 = digitalRead(buttonPins[3]); 
  
  if (mode == 0){
  	// generate a sequence when mode == 0
    // sequence is generated when user loses, or game starts
    
    for (int i = 0; i < 5; i++){
    	sequence[i] = random(4); 
      
    }
    
    mode++; 
  }
  
  
  if (mode == 1){
    
    delay(1000);
    
    lightLED(sequence[0]);
    
    count = 0; 
    
    while (count < mode && now + timeOut * mode >= millis() ){
    	userInput(userSequence, mode); 
    }
    
    correctSequence = sequenceCheck(userSequence, sequence, mode); 
    
    delay (1000); 
    
    if (correctSequence == false){
    	lose(); 
      
      	mode = 0; 
    }
    
    else if (correctSequence == true){
    	win();
      
      	mode++; 
    }
  	
    for (int i = 0; i < 5; i++){
    	userSequence[i] = 0; 
    }
    
    
  }
  
  else if (mode == 2){
    
    delay(1000); 
  
    lightLED(sequence[0]);
    lightLED(sequence[1]); 
    
    count = 0; 
    
    while (count < mode && now + timeOut * mode >= millis() ){
    	userInput(userSequence, mode);  
    }
    
    correctSequence = sequenceCheck(userSequence, sequence, mode); 
    
    if (correctSequence == false){
    	lose(); 
      
      	mode = 0; 
    }
    
    else if (correctSequence == true){
    	win();
      
      	mode++; 
    }
  }
  
  
  else if (mode == 3){
  
    delay(1000); 
  
    lightLED(sequence[0]);
    lightLED(sequence[1]); 
    lightLED(sequence[2]);
    
    count = 0; 
    
    while (count < mode && now + timeOut * mode >= millis() ){
    	userInput(userSequence, mode);  
    }
    
    correctSequence = sequenceCheck(userSequence, sequence, mode); 
    
    if (correctSequence == false){
    	lose(); 
      
      	mode = 0; 
    }
    
    else if (correctSequence == true){
    	win();
      
      	mode++; 
    }
  }
  
  else if (mode == 4){

    delay(1000); 
  
    lightLED(sequence[0]);
    lightLED(sequence[1]); 
    lightLED(sequence[2]);
    lightLED(sequence[3]); 
    
    count = 0; 
    
    while (count < mode && now + timeOut * mode >= millis() ){
    	userInput(userSequence, mode);  
    }
    
    correctSequence = sequenceCheck(userSequence, sequence, mode); 
    
    if (correctSequence == false){
    	lose(); 
      
      	mode = 0; 
    }
    
    else if (correctSequence == true){
    	win();
      
      	mode++; 
    }
  }
  
  else if (mode == 5){
    delay(1000); 
  
    lightLED(sequence[0]);
    lightLED(sequence[1]); 
    lightLED(sequence[2]);
    lightLED(sequence[3]); 
    lightLED(sequence[4]);
    
    count = 0; 
    
    while (count < mode && now + timeOut * mode >= millis() ){
    	userInput(userSequence, mode);  
    }
    
    correctSequence = sequenceCheck(userSequence, sequence, mode); 
    
    if (correctSequence == false){
    	lose(); 
      
      	mode = 0; 
    }
    
    else if (correctSequence == true){
    	win();
        win();
        win(); 
      
      	mode = 0; 
    }  
  }
  
  
  prev0 = switchState0;
  prev1 = switchState1;
  prev2 = switchState2;
  prev3 = switchState3;
  
}


void userInput(int* userSequence, int mode){
  
  switchState0 = digitalRead(buttonPins[0]); 
  switchState1 = digitalRead(buttonPins[1]); 
  switchState2 = digitalRead(buttonPins[2]); 
  switchState3 = digitalRead(buttonPins[3]); 
  
  // update array up until mode; 
  
  if (count < mode){
    
    if (switchState0 == HIGH && prev0 == LOW){
    	userSequence[count] = 0; 
        count++; 
      
    }
    
    else if (switchState1 == HIGH && prev1 == LOW){
      userSequence[count] = 1; 
      count++;  
      
    }
    
    else if (switchState2 == HIGH && prev2 == LOW){
      userSequence[count] = 2; 
      count++; 
       
    }
    
    else if (switchState3 == HIGH && prev3 == LOW){
      userSequence[count] = 3; 
      count++; 
      
    }
    
  }
  
  prev0 = switchState0;
  prev1 = switchState1;
  prev2 = switchState2;
  prev3 = switchState3;

}

bool sequenceCheck(int* userSequence, int* sequence, int mode){
  for (int i = 0; i < mode; i++){
    
    if (sequence[i] != userSequence[i]){
    	return false; 
    }
  }
  
  return true; 
}




void lightLED(int num){
  
  digitalWrite(ledPins[num], HIGH); 
  delay(500); 
  digitalWrite(ledPins[num], LOW); 
  delay(500); 

}

void win(void){
	digitalWrite(GREEN, HIGH); 
  	delay(750); 
  	digitalWrite(GREEN, LOW); 
  	delay(750); 
}
void lose(void){
	digitalWrite(RED, HIGH); 
  	delay(750); 
  	digitalWrite(RED, LOW); 
  	delay(750); 
  
  	digitalWrite(RED, HIGH); 
  	delay(750); 
  	digitalWrite(RED, LOW); 
  	delay(750);
  
  	digitalWrite(RED, HIGH); 
  	delay(750); 
  	digitalWrite(RED, LOW); 
  	delay(750);
} 

