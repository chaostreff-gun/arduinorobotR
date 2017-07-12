// define limits and histerese
#define LIMITLL 145
#define LIMITLR 370
#define LIMITGL 580
#define LIMITGR 790
#define HISTERESE 30

void setup() {
  // put your setup code here, to run once:
  
  // LED-für LS
  pinMode(7, OUTPUT);

  // Fototransistoren für LS
  pinMode(A6, INPUT);
  pinMode(A7, INPUT);

  // Motorpins
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);

  //rotation sensor left
  pinMode(3, INPUT);
  //rotation sensor right
  pinMode(2, INPUT);
  
  // Serial 
  Serial.begin(115200);

  // Motor links an
  //digitalWrite(9, HIGH);
  //digitalWrite(10, LOW);
}

int rotationL = 0;
int rotationR = 0;
int rotationLlast = 0;
int rotationRlast = 0;
int rL = 0;
int rR = 0;

void loop() {
  
  // Anschalten der LED
  digitalWrite(7, HIGH);

  rL = digitalRead(3);
  Serial.println("");
  Serial.print("rL: ");
  Serial.println(rL);
  
  rR = digitalRead(2);
  Serial.println("");
  Serial.print("rR: ");
  Serial.println(rR);

  // count rotations
  if (rL == 1 && rotationLlast == 0) {
    rotationLlast = rL;
    rotationL++;
    Serial.print("left last: ");
    Serial.print(rotationLlast);
    Serial.print(" left: ");
    Serial.println(rotationL);
  }

  if (rR == 1 && rotationRlast == 0) {
    rotationRlast = rR;
    rotationR++;
    Serial.print("right last: ");
    Serial.print(rotationRlast);
    Serial.print(" right: ");
    Serial.println(rotationR);
  }

  // reset rotation counters
  if (rotationL > 1000) {
    rotationL = 0;
  }
  if (rotationR > 1000) {
    rotationR = 0;
  }

  // left line lost
  if (analogRead(A6) > LIMITLL + HISTERESE && rotationL < 1000) {
    // Linker Sensor Linie verloren
    // Motor rechts aus
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);  
    // Motor links an
    analogWrite(9, 128);
    digitalWrite(10, LOW);
  }

  // right line lost
  if (analogRead(A7) > LIMITLR + HISTERESE && rotationR < 1000) {
    // Rechter Sensor Linie verloren
    // Motor rechts an
    analogWrite(5, 128);
    digitalWrite(6, LOW);  
    // Motor links aus
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
  }
/*
  if (analogRead(A6) > grenzwertLinks) {
    // Linker Sensor Linie verloren
    // Motor rechts aus
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);  
    // Motor links an
    digitalWrite(9, HIGH);
    digitalWrite(10, LOW);   
  }

  if (analogRead(A7) > grenzwertRechts) {
    // Rechter Sensor Linie verloren
    // Motor rechts an
    digitalWrite(5, HIGH);
    digitalWrite(6, LOW);  
    // Motor links aus
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);   
  }  

  if (analogRead(A6) < grenzwertLinks && analogRead(A7) < grenzwertRechts) {
    // Beide auf Linie, vorwärts!
    // Rechts
    digitalWrite(5, HIGH);
    digitalWrite(6, LOW);
    // Links: 
    digitalWrite(9, HIGH);
    digitalWrite(10, LOW);   
  }
  */
  // debug limits
  Serial.print("SensLinks: ");
  Serial.print(analogRead(A6));
  Serial.print(" SensRechts: ");
  Serial.println(analogRead(A7));

  // debug rotation
  Serial.print("links: ");
  Serial.print(digitalRead(3));
  Serial.print("rechts: ");
  Serial.println(digitalRead(2));
}
