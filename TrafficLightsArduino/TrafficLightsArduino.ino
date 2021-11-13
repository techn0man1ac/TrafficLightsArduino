/*
Write by Techn0man1ac, special to
https://www.robo.house/
2021
*/
#define Button_Stop 2 // Stop Cars
#define Button_YBlnk 3  // Yellow blink mode
#define LED_Green 5   // Support PWM
#define LED_Yellow 6  // Support PWM
#define LED_Red 9     // Support PWM

bool enable = false; // need to start timer

unsigned long previousMillis = 0;
word interval = 0; //instead of delay()

byte mode = 0;

/* 
Modes:
Green Led on      -> 0;
Yellow led on     -> 1;
Red led on        -> 2;
All off, green on -> 3;
Yellow blink      -> 4.
*/

word wait[5]{1500, 1000, 2000, 5000, 500};

/*
Wait on ms:
wait[0] -> Green led light time;
wait[1] -> Yellow led light time;
wait[2] -> Red led light time;
wait[3] -> Red->Green time;
wait[4] -> Time blink.
*/

void setup() {
  Serial.begin(115200);
  pinMode(Button_Stop, INPUT);
  pinMode(Button_YBlnk, INPUT);
  pinMode(LED_Green, OUTPUT);
  pinMode(LED_Yellow, OUTPUT);
  pinMode(LED_Red, OUTPUT);
  colorSet(0); // Need to start
}

void loop() {
bool btnStpState = digitalRead(Button_Stop);
bool btnYBlnkState = digitalRead(Button_YBlnk);

if(btnYBlnkState == HIGH){ //Hight priority button
  enable = true;
  mode = 4;
  }else if(btnStpState == HIGH && enable == false){ // if button stop press
    enable = true;
    mode = 0;
  }

unsigned long currentMillis = millis();

if (currentMillis - previousMillis >= interval && enable == true) {
  previousMillis = currentMillis;  

  mode = colorSet(mode);
  Serial.println(String(btnYBlnkState) + " " + String(btnStpState) + " " + String(mode));
  }

}

int colorSet(byte clr){
interval = wait[clr]; 

switch (clr){ //Color,final state machine
  case 0:
  digitalWrite(LED_Green, HIGH);
  digitalWrite(LED_Yellow, LOW);
  digitalWrite(LED_Red, LOW);

  clr = 1;
		break;
  
  case 1:
  digitalWrite(LED_Green, LOW);
  digitalWrite(LED_Yellow, HIGH); 
  digitalWrite(LED_Red, LOW);   
  
  clr = 2;
		break;
  
  case 2:
  digitalWrite(LED_Green, LOW);
  digitalWrite(LED_Yellow,LOW);
  digitalWrite(LED_Red, HIGH);
 
  clr = 3;
		break;

  case 3:
  digitalWrite(LED_Green, HIGH);
  digitalWrite(LED_Yellow, LOW);
  digitalWrite(LED_Red, LOW);
  
  enable = false;
  clr = 0;
		break;

  case 4:
  digitalWrite(LED_Green, LOW);
  digitalWrite(LED_Yellow, !digitalRead(LED_Yellow));
  digitalWrite(LED_Red, LOW);
  
  clr = 3;
		break;

  default:
  return -1; // some wrong
  break;
  }

  return clr;
}