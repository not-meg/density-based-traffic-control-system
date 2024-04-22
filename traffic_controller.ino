#define MAX_TIME 10*2// secs
#define MIN_DIST 1 // cms
#define MAX_DIST 5 // cms

int currentRoad, previousRoad;
int currRoadTimeGiven;
int sensorPinsTrig[4][2] = {{5,3},{7,-1},{12,11},{8,-1}};
int sensorPinsEcho[4][2] = {{4,2},{6,-1},{13,10},{9,-1}};
int roadDensitySensor[4] = {LOW, LOW, LOW, LOW};
int redPins[4]    = {44,34,42,28};
int yellowPins[4] = {40,36,26,38};
int greenPins[4]  = {32,24,30,22};
int numRoadsWithVehicles = 0;

void readSensors(int currentRoad, int previousRoad)
{
  int v1, v2;
  long duration;
  int i;

  numRoadsWithVehicles = 0;

  for (i = 0; i < 4; i++) {
    digitalWrite(sensorPinsTrig[i][0], LOW);
    delayMicroseconds(2);
    digitalWrite(sensorPinsTrig[i][0], HIGH);
    delayMicroseconds(10);  
    digitalWrite(sensorPinsTrig[i][0], LOW);
    duration = pulseIn(sensorPinsEcho[i][0], HIGH);
    v1 = (duration*0.0343)/2;

    if (sensorPinsTrig[i][1] != -1) {
      digitalWrite(sensorPinsTrig[i][1], LOW);
      delayMicroseconds(2);
      digitalWrite(sensorPinsTrig[i][1], HIGH);
      delayMicroseconds(10);  
      digitalWrite(sensorPinsTrig[i][1], LOW);
      duration = pulseIn(sensorPinsEcho[i][1], HIGH);
      v2 = (duration*0.0343)/2;   
    } else {
      v2 = 0;
    }

    if ((v1 >= MIN_DIST && v1 <= MAX_DIST) ||
      (v2 >= MIN_DIST && v2 <= MAX_DIST)) {
      roadDensitySensor[i] = HIGH;
      numRoadsWithVehicles += 1;
    } else {
      roadDensitySensor[i] = LOW;   
    }

    /*Serial.print(" road = ");
    Serial.print(i+1);
    Serial.print(", [trig_pin1 = ");
    Serial.print(sensorPinsTrig[i][0]);
    Serial.print(", echo_pin1 = ");
    Serial.print(sensorPinsEcho[i][0]);
    Serial.print(", v1 = ");
    Serial.print(v1); 
    Serial.print("], [trig_pin2 = ");
    Serial.print(sensorPinsTrig[i][1]);      
    Serial.print(", echo_pin2 = ");
    Serial.print(sensorPinsEcho[i][1]);   
    Serial.print(", v2 = ");
    Serial.print(v2);       
    Serial.print("], currentRoad ");
    Serial.print(currentRoad);
    Serial.print(", sensorStatus ");
    Serial.print(roadDensitySensor[i]);   
    Serial.print(", previousRoad ");
    Serial.println(previousRoad); */
  }
}

void GiveGreenSignal(int previousRoad, int currentRoad)
{
  if (previousRoad != currentRoad) {
    if (previousRoad != -1) {
      TurnOff(greenPins[previousRoad]);
      TurnOn(yellowPins[previousRoad]);
      delay(1000);
      TurnOn(redPins[previousRoad]);  
      TurnOff(yellowPins[previousRoad]);
    }
    TurnOff(redPins[currentRoad]);
    TurnOn(greenPins[currentRoad]);
  }
}

void TurnOn(int pin)
{
  digitalWrite(pin, HIGH);
}

void TurnOff(int pin)
{
  digitalWrite(pin, LOW); 
}

void MakeAllRed()
{
  TurnOff(greenPins[0]);
  TurnOff(greenPins[1]);
  TurnOff(greenPins[2]);
  TurnOff(greenPins[3]);

  TurnOff(yellowPins[0]);
  TurnOff(yellowPins[1]);
  TurnOff(yellowPins[2]);
  TurnOff(yellowPins[3]);
  
  TurnOn(redPins[0]);
  TurnOn(redPins[1]);
  TurnOn(redPins[2]);
  TurnOn(redPins[3]);

  currRoadTimeGiven = 0;
  currentRoad = 0;
  previousRoad = -1;
}

void NextRoad()
{
  currentRoad = (currentRoad+1)%4;
  currRoadTimeGiven = 0;
}

void setup()
{
  int i;
  Serial.begin(9600);

  for (i = 0; i < 4; i++) {
    pinMode(greenPins[i], OUTPUT);
    pinMode(yellowPins[i], OUTPUT);
    pinMode(redPins[i], OUTPUT);
  }

  for (i = 0; i < 4; i++) {
    pinMode(sensorPinsTrig[i][0], OUTPUT);
    if (sensorPinsTrig[i][1] != -1) {
      pinMode(sensorPinsTrig[i][1], OUTPUT);
    }

    pinMode(sensorPinsEcho[i][0], INPUT);
    if (sensorPinsEcho[i][1] != -1) {
      pinMode(sensorPinsEcho[i][1], INPUT);
    }
  }

  MakeAllRed();
}

void loop()
{
  if (currRoadTimeGiven > MAX_TIME) {
    NextRoad();
  }

  readSensors(currentRoad, previousRoad);

  if (numRoadsWithVehicles == 0) {
    MakeAllRed();
    delay(500);
  } else if (roadDensitySensor[currentRoad] == HIGH) {
    GiveGreenSignal(previousRoad, currentRoad);
    previousRoad = currentRoad;
    currRoadTimeGiven++;
    delay(500);
  } else {
    NextRoad();
  }
}