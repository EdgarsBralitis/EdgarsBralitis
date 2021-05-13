int readPin = A0;
int buzzerPin = 11;
int lightSensorReadValue;
int buzzerPinWriteValue;//sound volume (the higher this gets, the louder buzzer tick)

int counter = 0;
int countOfOutputsToSkip = 50;//This is for slowing down the Serial output.

int maxReadValue = 1023;//please, don't change this :)
int maxWriteValue = 255;//don't change this too pls :)

int minVolume = 200;//you can change this, note that it should not be higher than 255
int maxVolume = 255;//you can change this, note that it should not be higher than 255
/*if both minVolume and maxVolume are set to 255, its like using digitalWrite instead of analog one*/

int minFrequency = 1000;//play with this (the measurement unit is Hz) 
int maxFrequency = 10000;//play with this (the measurement unit is Hz)
long delayTime;

int frequency;//applied sound frequency

int getFrequency(int lightSensorReadValue) {
  return minFrequency + (maxFrequency - minFrequency) * float(lightSensorReadValue)/float(maxReadValue);
}

long getDelayInMicroSeconds(int frequency) {
    return long(1000000.0/frequency); 
};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT);
  pinMode(readPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  lightSensorReadValue = analogRead(readPin);
  
  buzzerPinWriteValue = minVolume + (maxVolume - minVolume) * (float(lightSensorReadValue)/maxReadValue);

  frequency = getFrequency(lightSensorReadValue);

  delayTime = getDelayInMicroSeconds(frequency);

  counter++;
  counter%=countOfOutputsToSkip;
  
  if (counter == 0) {
    Serial.print("Light level: " + String(100*float(lightSensorReadValue)/maxReadValue));
    Serial.print("% *** ");
    Serial.print("Sound frequency: ");
    Serial.print(frequency);
    Serial.print("Hz simulated by delay time of " + String(delayTime));
    Serial.print(" microSeconds *** Sound volume: " + String(100*float(buzzerPinWriteValue)/maxWriteValue));
    Serial.println(" %");
  }

  //delayTime = 1000;
  analogWrite(buzzerPin, buzzerPinWriteValue);
  delayMicroseconds(delayTime);
  analogWrite(buzzerPin, LOW);
  delayMicroseconds(delayTime);
}
