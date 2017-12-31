#include <Servo.h>
#include <LiquidCrystal.h>
Servo myservo;
//port6_arduino
char receive[64];//Initialized variable to store recieved dataz
char mystr[64];
char ourstr[64];
LiquidCrystal lcd(3,4,5,6,7,8);
int ErVal,SpVal,i,l,k;
void setup() 
{
  // Begin the Serial at 9600 Baud
  Serial.begin(9600);
  myservo.attach(A1);
  myservo.write(10);
  lcd.begin(16, 2);  
  lcd.print("Hello World!");
}

void loop()
{
  Serial.println("loop Session begins");
  delay(2000);
  if (Serial.available()>0)
  {
  Serial.readBytes(receive,64);//Read the serial data and store in var
  strcpy(ourstr,receive);                  //copies received data to another string 
  Serial.println("1st print of receive:");
  Serial.println(receive);
  delay(4000);
  Serial.println("1st print of ourstr:");
  Serial.println(ourstr);
  
  delay(4000);
  l=strlen(ourstr);
  for(i=0;i<l;i++)
{
  if(ourstr[i]=='d')
  {
    i=i+1;
    for(k=0;k<10;k++)
    {
      mystr[k]=ourstr[i];
      i=i+1;
      Serial.println(mystr[k]);
    } 
    break;
  }
}
  ErVal=ErCheck(mystr)    ;                //get error value on received data
  {
  if(ErVal==0)                             
  loop();                                  //back to loop if error
  delay(100);                 
  Serial.println(mystr);                    //prints string on serical monitor
  if(mystr[0]=='1')                      // if any incoming vehicle
  {
    SpVal=SpCheck(mystr);                   // gets space status
    if(SpVal==1)                            // if space available
    {
    Welcome();                              
    
    }
    else                                    
    {
    Deny();                                
    }
  }
  
  }
}
Serial.println("End Of Session");
delay(4000);
}
  //else{
  //delay(5000);
  //Serial.println("No data available");
  
//Serial.readBytes(mystr,64);
//Serial.println(mystr);
 int ErCheck(char A[])
 {
    if((A[6]=='e')&&(A[7]=='f')&&(A[8]=='g')&&(A[9]=='h'))
   {
    Serial.println(A);
    Serial.println("returning 1 from errcheck");
    delay(2000);
    return 1;
 }
    else 
    {
    Serial.println(A);
      Serial.println("returning 0 from errcheck");
      delay(4000);
    return 0;
 }
 }
int SpCheck(char mystr[])
{
  if(mystr[1]=='0' || mystr[2]=='0' || mystr[3]=='0' || mystr[4]=='0')
 {
    Serial.println("returning 1 from SpCheck");
    return 1;
 }
    else
 {
    Serial.println("returning 0 from SpCheck");
   return 0;
}
}
void Welcome()
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Spaces left");
    delay(3000);
    lcd.setCursor(0, 0);
    lcd.print("Gate Opening");
    myservo.write(100);
    delay(5000);
    Serial.println("Incoming Vehicle");
    delay(5000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Gate Closing");
    delay(1000);
    myservo.write(10);
    delay(5000);
    Serial.println("Vehicle inside gate now");
    delay(5000);
    lcd.clear();
}
void Deny()
{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("No Space Left");
    delay(5000);
    lcd.clear();
}
