// 모터 제어 성공 프로토콜 포함본
String ledString=" "; //프로토콜
String serArray[5];//프로토콜
int16_t R ;//프로토콜
const int motorDirPin = 10; // L298 Input 1
const int motorPWMPin = 9; // L298 Input 2
int sensorValue = 0;
float Kp =9;
float targetDeg = 300;
int a=0;
int b=0;
float targetDeg_ex=0;

void setup() {
  // put your setup code here, to run once:
  pinMode(motorDirPin, OUTPUT);
  pinMode(motorPWMPin, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  control();
  sensorValue = analogRead(A0);
  // put your main code here, to run repeatedly:
  
  targetDeg=R;
  float motorDeg = (sensorValue-135)/2.46; //아날로그 센서
  float error=targetDeg-motorDeg;//200-90=110
  // 타겟값 180 현재값 20  두값 차이 160 5씩 더해가면서 
  //접근 만약에 5보다 작으면 최종값 입력
  //한번만 targetDeg_ex=moterDeg+5
  // error= moterDeg-targetDeg_ex;
  // targetDeg_ex>=moterDeg; 선택 연산자는 0; 센싱 
   if(abs(error)<=5)
  {
    float control = (Kp*error);
    doMotor( (error>=0)?HIGH:LOW, min(abs(control), 255));
  }
  if(abs(error)>5)
  {
    if(a==0)
    {
      if(error>=0)
      {
        targetDeg_ex=motorDeg+5;
        b=1;
        a=1;
      }
      if(error<0)
      {
        targetDeg_ex=motorDeg-5;
        b=2;
        a=1;
        
      }
      
      
    }
      
      error= targetDeg_ex-motorDeg;
      float control = (Kp*error);
      doMotor( (error>=0)?HIGH:LOW, min(abs(control), 255));
  }
  if(b==1){
      if(targetDeg_ex>=motorDeg)
    {
      a=0;
    }
  }
  if(b==2){
      if(targetDeg_ex<motorDeg)
    {
      a=0;
    }
  }
  
  
 
  Serial.print("  a");
  Serial.print(a);
  
  Serial.print("  motorDeg");
  Serial.println(motorDeg);
  
}
void doMotor(bool dir, int vel) // 모터 제어 코드
{
  digitalWrite(motorDirPin, dir);
  Serial.print(dir);Serial.print("   ");
  analogWrite(motorPWMPin, vel);
  Serial.print(vel);
  Serial.print("   ");
}
void control()
{
   if(Serial.available()){
    
    char ch = Serial.read();
    ledString+=ch;
    if(ch == '*'){
      //Serial.print('2');
      if(ledString.length()>0){
        int startCMD =0;
        int tmpcnt=0;
        int idx;
        String tmpString=ledString;
        tmpString.trim();
        while(tmpString.length()>0){
          idx = tmpString.indexOf(",");
          if(idx == -1){
            serArray[tmpcnt]= tmpString;
            serArray[tmpcnt].trim();
            tmpcnt++;
            break;
          }
          serArray[tmpcnt] = tmpString.substring(0,idx);
          tmpString = tmpString.substring(idx+1);
          tmpString.trim();
          serArray[tmpcnt].trim();
          tmpcnt++;
        }
        if(serArray[0]=="R"){
          R= serArray[1].toInt();
          Serial.println(R);
        }
      }
      ledString = "";
     
    }
  }
}
