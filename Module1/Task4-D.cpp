int movingState = 0;
int completelyTitled = 0;
int ambientState = 0;

const uint16_t t1_load = 0;
const uint16_t t1_comp = 46875;

void setup()
{
  Serial.begin(9600);
 
  pinMode(13, OUTPUT);
  
  pciSetup(2);
  pciSetup(3);
  pciSetup(4);
  
  //Timer interrupts
  DDRB |= (1 << PB5);

  TCCR1A = 0;
  
  TCCR1B &= ~(1 << WGM13);
  TCCR1B |= (1 << WGM12);
 
  TCCR1B |= (1 << CS12);
  TCCR1B &= ~(1 << CS11);
  TCCR1B |= (1 << CS10);

  TCNT1 = t1_load;
  OCR1A = t1_comp;
  
  TIMSK1 = (1 << OCIE1A);
  
  sei();
}

void loop()
{

}

void pin_ISR_motion()
{
  movingState = digitalRead(2);
  
  switch(movingState)
  {
    case 0: Serial.println("moving object gone");
    break;
    case 1: Serial.println("moving object detected");
    break;
  }
}

void pin_ISR_tilted()
{
  completelyTitled = digitalRead(3);
}

void pin_ISR_ambient()
{
  ambientState = digitalRead(4);
}

ISR (PCINT2_vect) // handle pin change interrupt for D0 to D7 here
{

  if(digitalRead(3) != completelyTitled)
    pin_ISR_tilted();
  if(digitalRead(2) != movingState)
    pin_ISR_motion();
  if(digitalRead(4) != ambientState)
    pin_ISR_ambient();
} 

void pciSetup(byte pin)
{
    *digitalPinToPCMSK(pin) |= bit (digitalPinToPCMSKbit(pin));  // enable pin
    PCIFR  |= bit (digitalPinToPCICRbit(pin)); // clear any outstanding interrupt
    PCICR  |= bit (digitalPinToPCICRbit(pin)); // enable interrupt for the group
}


void ReadAmbientAndTilt()
{
  Serial.print("Brightness: ");
  switch(ambientState)
  {
    case 0: Serial.println("normal");
    break;
    case 1: Serial.println("too bright, please fix!");
    break;
  }
  Serial.print("Tilt Status: ");
  switch(completelyTitled)
  {
    case 0: Serial.println("normal");
    break;
    case 1: Serial.println("tilted, please fix!");
    break;
  }
}


ISR(TIMER1_COMPA_vect)
{
  PORTB ^= (1 << PB5);
  ReadAmbientAndTilt();
}
