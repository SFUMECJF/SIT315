float a5_value;
float volts;
float temperature;

void setup()
{
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  a5_value = analogRead(A5);
  volts = (a5_value * 5.0)/1024;
  temperature = (volts - 0.5) * 100.0;
  
  Serial.print("Vout: "); Serial.print(a5_value);
  Serial.print(", "); Serial.print(volts); Serial.print("V");
  Serial.print(", Celcius: "); Serial.print(temperature);
  
  if(temperature>40){
   	digitalWrite(13, HIGH);
  	Serial.println(" It's burning hot!");
  }else{
    digitalWrite(13, LOW);
    Serial.println();
  }  
  delay(1000); // Wait for 1000 millisecond(s)
}
