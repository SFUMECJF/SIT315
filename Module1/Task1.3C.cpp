int movingState = 0;
int completelyTitled = 0;
void setup()
{
  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(3,INPUT);
  pinMode(13, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(2),pin_ISR_motion,CHANGE);
  attachInterrupt(digitalPinToInterrupt(3),pin_ISR_tilted,CHANGE);
}

void loop()
{
  if (movingState == HIGH || completelyTitled == HIGH) 
  {
    digitalWrite(13, HIGH);
  } else 
  {
    digitalWrite(13, LOW);
  }
  
}

void pin_ISR_motion()
{
  movingState = movingState==0? 1: 0;
  
  switch(movingState){
    case 0: Serial.println("moving object gone");
    break;
    case 1: Serial.println("moving object detected");
    break;
  }
}

void pin_ISR_tilted()
{
  completelyTitled = digitalRead(3);
  switch(completelyTitled){
    case 0: Serial.println("getting balanced...");
    break;
    case 1: Serial.println("completely tilted!!!");
    break;
  }
}
