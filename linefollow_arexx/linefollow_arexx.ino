// definiere Limits für hell und dunkel; Histerese für Schwankung eventuell hilfreich
#define LIMITLL 145
#define LIMITLR 370
//#define LIMITGL 580
//#define LIMITGR 790

// Pins
#define SENSORLEFT A6
#define SENSORRIGHT A7
#define SENSORLED 7
#define ROTSENSORRIGHT 2
#define ROTSENSORLEFT 3
#define RIGHTMOT1 5
#define RIGHTMOT2 6
#define LEFTMOT1 9
#define LEFTMOT2 10

// motor power zwischen 128 und 255
int mp = 128;

// flags für Linie (schwarz) gefunden
int lineflag = 0;

int loopcounter = 0;

void setup() { 
  // LED-für LS
  pinMode(SENSORLED, OUTPUT);
  digitalWrite(SENSORLED, HIGH);

  // Fototransistoren für LS
  pinMode(SENSORLEFT, INPUT);
  pinMode(SENSORRIGHT, INPUT);

  // Motorpins rechts
  pinMode(RIGHTMOT1, OUTPUT);
  pinMode(RIGHTMOT2, OUTPUT);
  // Motorpins links
  pinMode(LEFTMOT1, OUTPUT);
  pinMode(LEFTMOT2, OUTPUT);

  //rotation sensor right
  pinMode(ROTSENSORRIGHT, INPUT);
  //rotation sensor left
  pinMode(ROTSENSORLEFT, INPUT);
  
  // Serial 
  Serial.begin(115200);
  
}

// runright(0); => stop
void runright(int ps = 128) {
  // Motor links an; Wertebereich 128-255
  analogWrite(RIGHTMOT1, ps);
  analogWrite(RIGHTMOT2, 0);
}

// runleft(0); => stop
void runleft(int ps = 128) {
  // Motor rechts an; Wertebereich 128-255
  analogWrite(LEFTMOT1, ps);
  analogWrite(LEFTMOT2, 0);
}

// Debugausgabe
void debugoutput(char text[] = "", signed int number = -1) {
  strcat(text, ": ");
  Serial.print(text);
  Serial.println(number);
}

void loop() {
  loopcounter++;

  // Abfrage der Sensoren
  int rsensor = analogRead(SENSORRIGHT);
  int lsensor = analogRead(SENSORLEFT);

  // beide Sensoren auf der Linie
  if(rsensor <= LIMITLR && lsensor <= LIMITLL) {
    lineflag = 1;
    // Motor rechts an
    runright(mp);
    // Motor links an
    runleft(mp);
  }

  // rechter Sensor hat die Linie verloren
  if(rsensor > LIMITLR) {
    lineflag = 0;
    // Motor rechts an
    runright(mp);
    // Motor links aus
    runleft(0);
  }

  // linker Sensor hat die Linie verloren
  if(lsensor > LIMITLL) {
    lineflag = 0;
    // Motor rechts aus
    runright(0);
    // Motor links an
    runleft(mp);
  }

  // Debug Limits
  debugoutput("rechts", rsensor);
  debugoutput("links", lsensor);

  // Debug linefag
  debugoutput("line", lineflag); 

  // loop counter
  debugoutput("loop", loopcounter);
}
