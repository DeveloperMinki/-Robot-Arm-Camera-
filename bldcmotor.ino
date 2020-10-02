// motor control pin
const int motorDirPin = 10; // L298 Input 1
const int motorPWMPin = 9; // L298 Input 2

int a= 1;
String ledString=" ";
int16_t R;

String serArray[5];


// encoder pin
const int encoderPinA = 18;
const int encoderPinB = 19;
const int encoderPinC = 20;

int pot=0;
int ao=1;

 int angin=0;
int encoderPos = 0;
const float ratio = 360./12.;

// P control
float Kp =3;
float targetDeg = 0;
float zeroDeg=0;

 String serarray[0];
  String ledSting=" ";

void doEncoderA(){  encoderPos += (digitalRead(encoderPinA)==digitalRead(encoderPinB))?1:-1;Serial.println("A");}
void doEncoderB(){  encoderPos += (digitalRead(encoderPinB)==digitalRead(encoderPinC))?1:-1;Serial.println("b");}
void doEncoderC(){  encoderPos += (digitalRead(encoderPinC)==digitalRead(encoderPinA))?1:-1;Serial.println("c");}
void doMotor(bool dir, int vel){
  digitalWrite(motorDirPin, dir);
  analogWrite(motorPWMPin, dir?(255 - vel):vel);
}


void setup() {
  pinMode(encoderPinA, INPUT_PULLUP);
  attachInterrupt(5, doEncoderA, CHANGE);
 
  pinMode(encoderPinB, INPUT_PULLUP);
  attachInterrupt(4, doEncoderB, CHANGE);

  pinMode(encoderPinC, INPUT_PULLUP);
  attachInterrupt(3, doEncoderC, CHANGE);
 
  pinMode(motorDirPin, OUTPUT);
  pinMode(motorPWMPin, OUTPUT);

  Serial.begin(9600);
 
}

void loop() {

 
  targetDeg=R;

  float motorDeg = float(encoderPos)*ratio;
 
  float error = targetDeg - motorDeg;
  float control = (Kp*error);
  if(ao==2){encoderPos=0; ao=3;}
  if(ao==1){encoderPos=0; ao=2;}
  
  doMotor( (control>=0)?HIGH:LOW, min(abs(control), 255));
 
 // Serial.print("encoderPos : ");
 // Serial.println(encoderPos);


  Serial.print("encoderPos : ");
  Serial.print(encoderPos);
  Serial.print("   motorDeg : ");
  Serial.print(float(encoderPos)*ratio);
  Serial.print("   error : ");
    Serial.print(error);
  Serial.print("    control : ");
  Serial.print(control);
  Serial.print("    motorVel : ");
  Serial.println(min(abs(control), 255));
}
