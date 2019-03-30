#ifndef ARDUINO_LED
#define ARDUINO_LED     (13)
#endif
#ifndef ARDUINO_D2
#define ARDUINO_D2     (2)
#endif

#ifdef STDIO_UART_BAUDRATE
#define SERIAL_BAUDRATE STDIO_UART_BAUDRATE
#else
#define SERIAL_BAUDRATE 9600
#endif

int ledPin = ARDUINO_LED;
int digitalPin2 = ARDUINO_D2;

int movingState = 0;

void setup(void)
{
    Serial.begin(SERIAL_BAUDRATE);
    pinMode(ledPin, OUTPUT);
    pinMode(digitalPin2, INPUT);
}

void loop(void)
{

    movingState = digitalRead(digitalPin2);

    if (movingState == HIGH)
    {
        digitalWrite(13, HIGH);
        Serial.write("Moving object detected!\n");
    }
    else
    {
        digitalWrite(13, LOW);
        Serial.write("No moving object detected...\n");
    }  
    delay(1000); // Wait for 1000 millisecond(s)
}
