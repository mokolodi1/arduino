// set pins
int analogPin = 0;
int ledPin = 13;

int pause = 50;          // milliseconds between readings
int valuesLength = 25;   // number of values taken
int values[25];
int currentIndex;

int cutoffValue = 1;
int cutoffCount = 2;

void setup()
{
  // set all values to 0
  for (int i = 0; i < valuesLength; i++) {
    values[i] = 0;
  }
  
  currentIndex = 0;
  
  Serial.begin(9600); // serial to computer
  pinMode(ledPin, OUTPUT);
}

/*int calculateAverage()
{
  int total = 0;
  for (int i = 0; i < valuesLength; i++) {
    total += values[i];
  }
  return (total / valuesLength);
}*/

int enoughAboveCutoff() {
  int countAbove = 0;
  for (int i = 0; i < valuesLength; i++) {
    if (values[i] > cutoffValue) {
      countAbove++;
    }
    if (countAbove > cutoffCount) {
      return (1);
    }
  }
  return (0);
}

void loop()
{
  values[currentIndex] = analogRead(analogPin);
  
  Serial.print("current value: ");
  Serial.print(values[currentIndex]);
  Serial.print("\n");
  
  // turn on led if there is audio
  if (enoughAboveCutoff() > 0) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
  
  currentIndex++;
  delay(pause);
}

