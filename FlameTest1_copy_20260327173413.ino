#include <OneWire.h>
#include <DallasTemperature.h>

#define DO_PIN 2
#define IR_OUT 9
#define A0_PIN A0

#define DO_PIN_GAS 7
#define A5_PIN A5
#define GAS_OUT 8
#define DO_PIN_TEMP 3
#define TEMP_OUT 10

OneWire onewire(DO_PIN_TEMP);
DallasTemperature tempsensor(&onewire);

const int Flame_Thresh=900;
const int temp_thresh=55;
const int Gas_Thresh=100;

void setup() {
  // put your setup code here, to run once:
  Serial.begin (9600);
  pinMode (DO_PIN, INPUT);
  pinMode (TEMP_OUT,OUTPUT);
  pinMode (IR_OUT,OUTPUT);
  pinMode (DO_PIN_GAS, INPUT);
  pinMode (GAS_OUT, OUTPUT);
  tempsensor.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  int Flame_Value=digitalRead(DO_PIN);
  int Flame_Analog=analogRead(A0_PIN);

  int Gas_Value=digitalRead(DO_PIN_GAS);
  int Gas_Analog=analogRead(A5_PIN);

  tempsensor.requestTemperatures();
  float celsius=tempsensor.getTempCByIndex(0);

  Serial.print("Temperature is ");
  Serial.println(celsius);

  Serial.print ("The gas sensor value is ");
  Serial.println (Gas_Analog);

  if (celsius>=temp_thresh){
    digitalWrite (TEMP_OUT, LOW);
  }
  else {
    digitalWrite (TEMP_OUT, HIGH);
  }

  Serial.print ("The flame sensor value is ");
  Serial.println (Flame_Analog);
  if(Flame_Value==LOW){
    Serial.println("The flame was detected");
  }
  else {
    Serial.println ("The flame was not detected");
  }

  if (Flame_Analog<=Flame_Thresh){
    digitalWrite(IR_OUT, LOW);
  }
  else{
    digitalWrite(IR_OUT, HIGH);
  }
  if(Gas_Analog>=Gas_Thresh){
    digitalWrite (GAS_OUT, LOW);
  }
  else {
    digitalWrite (GAS_OUT, HIGH);
  }
  delay(1000);
}
