/*
  Troll Bridge Arduino Interface
  by Thomas Martinez
  
  controls the troll bridge lock mechanism
*/

int RED_LED_PIN = 9;
int GREEN_LED_PIN = 8;

int TRUE_BTN_PIN = 2;
int FALSE_BTN_PIN = 3;

int trueButtonState = 0;
int falseButtonState = 0;

int unlocktime = 5000;
bool acceptingInput = false;

void setup()
{
  Serial.begin(9600);

  // setup LED pins
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  //btn pins
  pinMode(2, INPUT);
  pinMode(3, INPUT);

  // temp stuff
  acceptingInput = true;
  //unlock();
}

void loop()
{
  trueButtonState = digitalRead(2);
  falseButtonState = digitalRead(3);

  if (trueButtonState == HIGH && acceptingInput) {
    acceptingInput = false;
    Serial.println("input: TRUE");
    unlock();
  }
  if (falseButtonState == HIGH && acceptingInput) {
    acceptingInput = false;
    Serial.println("input: FALSE");
    unlock();
  }

  delay(10);
}

// lock door
void lock()
{
  Serial.println("locking");

  // update LEDs
  digitalWrite(RED_LED_PIN, HIGH);
  digitalWrite(GREEN_LED_PIN, LOW);
}

//unlock door
void unlock()
{
  Serial.println("unlocking");

  // update LEDs
  digitalWrite(GREEN_LED_PIN, HIGH);
  digitalWrite(RED_LED_PIN, LOW);

  delay(unlocktime);

  lock();

  //temp
  acceptingInput = true;
}