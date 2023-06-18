#define PIN_INPUT A0
#define PIN_OUTPUT1 2
#define PIN_OUTPUT2 3

int window = 30;
int input = 0;
int error = 0;
int setpoint = 600;
int kp = 2;

void setup()
{
    pinMode(PIN_INPUT,INPUT);
    pinMode(PIN_OUTPUT1,OUTPUT);
    pinMode(PIN_OUTPUT2,OUTPUT);
    
  Serial.begin(9600);
}

void angleCorrection(int input)
{
  input = analogRead(PIN_INPUT);

  error = setpoint - input;

  // Proportional term
  error = kp * error;


if(error+setpoint < (setpoint - window)){
      digitalWrite(PIN_OUTPUT1,1);
      digitalWrite(PIN_OUTPUT2,0);
    }
    else{
      if(error+setpoint > (setpoint + window)){
        digitalWrite(PIN_OUTPUT1,0);
        digitalWrite(PIN_OUTPUT2,1);
      }
      else{
        //stop motor if position between +0 ~ -0
        digitalWrite(PIN_OUTPUT1,0);  //stop motor
        digitalWrite(PIN_OUTPUT2,0);  //stop motor
      }
    }
  debMA(" >Setpoint:");debMA(setpoint);
  debMA(" >Set+window:");debMA(setpoint+window);
  debMA(" >Set-window:");debMA(setpoint-window);
  debMA(" >Error:");debMA(error+setpoint);
  debMA(" >Reading:");debMAln(input);
}
