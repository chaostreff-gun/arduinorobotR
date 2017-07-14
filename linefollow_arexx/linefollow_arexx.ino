// definiere Limits für hell und dunkel; Histerese für Schwankung eventuell hilfreich
#define LIMITLL 145
#define LIMITLR 370
#define LIMITGL 580
#define LIMITGR 790

//motor power zwischen 128 und ?
int mp = 128;

//flags für hell und dunkel
int whiteflag = 0;
int blackflag = 0;

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
}
