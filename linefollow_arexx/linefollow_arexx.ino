// definiere Limits für hell und dunkel; Histerese für Schwankung eventuell hilfreich
#define LIMITLL 145
#define LIMITLR 370
#define LIMITGL 580
#define LIMITGR 790

// motor power zwischen 128 und ?
int mp = 128;

// flags für Linie (schwarz) gefunden
int lineflag = 0;

int loopcounter = 0;

void setup() {
  // put your setup code here, to run once:
  
  // LED-für LS
  pinMode(7, OUTPUT);

  // Fototransistoren für LS
  pinMode(A6, INPUT);
  pinMode(A7, INPUT);

  // Motorpins rechts
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  // Motorpins links
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);

  //rotation sensor right
  pinMode(2, INPUT);
  //rotation sensor left
  pinMode(3, INPUT);
  
  // Serial 
  Serial.begin(115200);
  
}

// runright(0); => stop
void runright(int ps = 128) {
  // Motor links an; Wertebereich 128-?
  analogWrite(5, ps);
  analogWrite(6, 0);
}

// runleft(0); => stop
void runleft(int ps = 128) {
  // Motor rechts an; Wertebereich 128-?
  analogWrite(9, ps);
  analogWrite(10, 0);
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
  int rsensor = analogRead(A7);
  int lsensor = analogRead(A6);

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
