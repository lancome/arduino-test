#include <OneWire.h>
#include <DallasTemperature.h>

const int ledPin = 4;
const int pirPin = 7;
OneWire oneWire(8);
DallasTemperature sensors(&oneWire);

void setup()
{
  Serial.begin(9600);
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial.begin(9600);
  sensors.begin();
  Serial.flush();
}

void loop()
{
  delay(1000);
  
  String input = serialRead();  
  
  Serial.print("begin");
  printName("Temperature");
  Serial.print(getTemperature(sensors),1);
  printName("PIR");
  Serial.print(getBool(pirPin));
  printName("LED");
  Serial.print(getBool(ledPin));
  Serial.println("end");
  
  on(ledPin, input, "ledon");
  off(ledPin, input, "ledoff");
}

float getTemperature(DallasTemperature sensor)
{
  sensor.requestTemperatures();
  float temperature = sensor.getTempCByIndex(0);
  return temperature;
}

int getBool(int pin)
{
  return digitalRead(pin);
}

String serialRead()
{
  String input = "";
  while(Serial.available()){
    input += (char)Serial.read();
  }
  return input;
}

void on(int pin, String input, String string)
{
  if(input == string){
    digitalWrite(pin, HIGH);
    Serial.println("ON");
  }
}

void off(int pin, String input, String string)
{
  if(input == string){
    digitalWrite(pin, LOW);
    Serial.println("OFF");
  }
}

void printName(String name)
{
  Serial.print(" ");
  Serial.print(name);
  Serial.print(" ");
}

//stty -F /dev/ttyACM0 cs8 9600 ignbrk -brkint -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts
