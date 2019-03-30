int movingState = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(13, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(2),pin_ISR,CHANGE);
}

void loop()
{
  
  //Serial.println(digitalRead(2));

  if (movingState == HIGH) 
  {
    digitalWrite(13, HIGH);
  } else 
  {
    digitalWrite(13, LOW);
  }
  
}

void pin_ISR()
{
  movingState = digitalRead(2);
  Serial.print("Pin 2 value: "); Serial.println(movingState);
  switch(movingState){
    case 0: Serial.println("moving object gone");
    break;
    case 1: Serial.println("moving object detected");
    break;
  }
}
