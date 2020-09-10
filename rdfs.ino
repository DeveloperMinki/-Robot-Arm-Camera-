// this is motor control code //

// motor control pin
const int motorDirPin = 10; // L298 Input 1
const int motorPWMPin = 9; // L298 Input 2

int a= 1;
String ledString=" ";
int16_t R;

String serArray[5];


// encoder pin
const int encoderPinA = 2;
const int encoderPinB = 3;


 int angin=0;
int encoderPos = 0;
const float ratio = 360./50./52.;

// P control
float Kp =3;
float targetDeg = 0;
float zeroDeg=0;

 String serarray[0];
  String ledSting=" ";

void doEncoderA(){  encoderPos += (digitalRead(encoderPinA)==digitalRead(encoderPinB))?1:-1;}
void doEncoderB(){  encoderPos += (digitalRead(encoderPinA)==digitalRead(encoderPinB))?-1:1;}

void doMotor(bool dir, int vel){
  digitalWrite(motorDirPin, dir);
  analogWrite(motorPWMPin, dir?(255 - vel):vel);
}


void setup() {
  pinMode(encoderPinA, INPUT_PULLUP);
  attachInterrupt(0, doEncoderA, CHANGE);
 
  pinMode(encoderPinB, INPUT_PULLUP);
  attachInterrupt(1, doEncoderB, CHANGE);
 
  pinMode(motorDirPin, OUTPUT);
  pinMode(motorPWMPin, OUTPUT);

  Serial.begin(9600);
 
}

void loop() {
  serialsig();

  targetDeg=R;

  float motorDeg = float(encoderPos)*ratio;
 
  float error = targetDeg - motorDeg;
  float control = (Kp*error);
  

  doMotor( (control>=0)?HIGH:LOW, min(abs(control), 255));

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

void serialsig(){
  if(Serial.available()){
    char ch=Serial.read();
    ledString+=ch;
    if(ch=='*'){
      if(ledString.length()>0){
        int startCMD=0;
        int tmpcnt=0;
        int idx;
        String tmpString=ledString;
        tmpString.trim();
        while(tmpString.length()>0){
          idx=tmpString.indexOf(",");
          if(idx==-1){
            serArray[tmpcnt]=tmpString;
            serArray[tmpcnt].trim();
            tmpcnt++;
            break;
            
          }
          serArray[tmpcnt]=tmpString.substring(0,idx);
          tmpString=tmpString.substring(idx+1);
          tmpString.trim();
          serArray[tmpcnt].trim();
          tmpcnt++;
          
        }
        R=serArray[1].toInt();
        Serial.println(R);
      }
      ledString="";
    }
  }
}
