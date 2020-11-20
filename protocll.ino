//R,100*
String ledString=" ";
String serArray[5];
int16_t R ;
int16_t P ;
String Y ;
String T ;
int16_t N ;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600) ; 
}

void loop() {
  // put your main code here, to run repeatedly:
control();
    
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
        if(serArray[0]=="T"){
          T = serArray[1];
          Serial.println(T);
      
        }
        if(serArray[0]=="R"){
          R= serArray[1].toInt();
          Serial.println(R);
        }
        if(serArray[0]=="P"){
          P = serArray[1].toInt();
        }
        if(serArray[0]=="Y"){
         Y = serArray[1];
         Serial.println(Y);
        }
        if(serArray[0]=="N"){
         N = serArray[1].toInt();
         Serial.println(N);
        }
     
      }
      ledString = "";
     
    }
  }
}
