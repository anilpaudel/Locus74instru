// Present a "Will be back soon web page", as stand-in webserver.
// 2011-01-30 <jc@wippler.nl> http://opensource.org/licenses/mit-license.php
 
#include <EtherCard.h>
#include <string.h>

#define STATIC 0  // set to 1 to disable DHCP (adjust myip/gwip values below)

#if STATIC
// ethernet interface ip address
static byte myip[] = { 192,168,1,200 };
// gateway ip address
static byte gwip[] = { 192,168,1,1 };
#endif

// ethernet mac address - must be unique on your network
static byte mymac[] = { 0x74,0x69,0x69,0x2D,0x30,0x31 };
int count4,count5,count6,count7,count3,count8,i;
bool val3,val4,val5,val6,val7,val8;
const int inPin3=3;
const int inPin4=4;
const int inPin5=5;
const int inPin6=6;
const int inPin7=7;
const int inPin8=8;
char senddata[64]="abcd000000efgh"; 
byte Ethernet::buffer[500]; // tcp/ip send and receive buffer

char page[] =
"HTTP/1.0 503 Service Unavailable\r\n"
"Content-Type: text/html\r\n"
"Retry-After: 600\r\n"
"\r\n"
"<html>"
  "<head>"
  "<meta http-equiv=\"refresh\" content =\"15\" / >"
  "<title>"
    "Service Temporarily Unavailable"
  "</title>"
  "</head>"
  "<body bgcolor=red  >"
"<form action=? method=get>"
 "<input type=submit name=poweron value=on />"
  "<input type=submit name=poweroff value=off />"
"</form>"
"InputValue=____<br>"
"InputValue1=____<br>"
"InputValue2=____<br>"
"InputValue3=____<br>"
  "</body>"
"</html>"
;

void setup(){
  Serial.begin(9600);
   pinMode(inPin3,INPUT);
    pinMode(inPin4,INPUT);
    pinMode(inPin5,INPUT);
    pinMode(inPin6,INPUT);
    pinMode(inPin7,INPUT);
    pinMode(inPin8,INPUT);
    
  Serial.println("\n[backSoon]");
  
  if (ether.begin(sizeof Ethernet::buffer, mymac) == 0) 
    Serial.println( "Failed to access Ethernet controller");
#if STATIC
  ether.staticSetup(myip, gwip);
#else
  if (!ether.dhcpSetup())
    Serial.println("DHCP failed");
#endif

  ether.printIp("IP:  ", ether.myip);
  ether.printIp("GW:  ", ether.gwip);  
  ether.printIp("DNS: ", ether.dnsip);  
}

void loop(){
  //Serial.println("start");
      word len = ether.packetReceive();
      word pos = ether.packetLoop(len);
  
   if(strstr((char *)Ethernet::buffer + pos, "on") != 0) {
      //Serial.println("Received ON command");
      //digitalWrite(ledPin8, HIGH);
    }

    // IF LED10=OFF turn it OFF  
    if(strstr((char *)Ethernet::buffer + pos, "off") != 0) {
      //Serial.println("Received OFF command");
     // digitalWrite(ledPin8, LOW);
  
    }  
    
   count8=0;
    count3=0;
    count4=0;
    count5=0;
    count6=0;
    count7=0;
   
    for(i=0;i<10;i++)
    {
         val4 = digitalRead(inPin4);
         if(val4==HIGH)
         {
          count4+=1;    

         }
    }
    for(int i=0;i<10;i++)
    {
         val5 = digitalRead(inPin5);
          if(val5==HIGH)
         {
              count5+=1;  

         }
         }
         for(int i=0;i<10;i++)
    {
         val6 = digitalRead(inPin6);
        if(val6==HIGH)
         {
              count6+=1;  

         }
    }
    for(int i=0;i<10;i++)
    {
         val7 = digitalRead(inPin7);
         if(val7==HIGH)
         {
              count7+=1;  

         }
    }
     for(i=0;i<10;i++)
    {
        val3 = digitalRead(inPin3);
         if(val3==HIGH)
         {
              count3+=1;  

         }
    }
     for(i=0;i<10;i++)
    {
         val8 = digitalRead(inPin8);
         
        
        
         if(val8==HIGH)
         {
              count8+=1;  

         }
    }
   if(count3<=5)
{
  senddata[4]='0';
   // Serial.write(senddata,64);
}
else
{
senddata[4]='1';
// Serial.write(senddata,64);
}

if(count8<=5)
{

senddata[5]='0';
 //Serial.write(senddata,64);
}
else
{
senddata[5]='1';
 //Serial.write(senddata,64);

}
//Serial.println("Centre");
   if(count4<=5)
  {
   // Serial.println("low");
  page[339]='_';
  page[340]='L';
  page[341]='O';  
  page[342]='W';
  senddata[6]='0';

  } 
   else
  {
   //Serial.println("high");
   page[339]='H';
  page[340]='I';
  page[341]='G';  
  page[342]='H';
    senddata[6]='1';

  }
   if(count5<=5)
  {

  page[359]='_';
  page[360]='L';
  page[361]='O';  
  page[362]='W';
    senddata[7]='0'; 

  } 
  else
  {

  page[359]='H';
  page[360]='I';
  page[361]='G';  
  page[362]='H';
    senddata[7]='1';

  }
   if(count6<=5)
  {
    //Serial.println("low");
  page[379]='_';
  page[380]='L';
  page[381]='O';  
  page[382]='W';
    senddata[8]='0';
  } 
  else
  {
    //Serial.println("high");
  page[379]='H';
  page[380]='I';
  page[381]='G';  
  page[382]='H';
  senddata[8]='1';
  }

  if(count7<=5)
  {
  page[399]='_';
  page[400]='L';
  page[401]='O';  
  page[402]='W';
 }
 else 
  {
  //Serial.println("high");
  page[399]='H';
  page[400]='I';
  page[401]='G';  
  page[402]='H';
    senddata[9]='1';

  }
  delay(1000);
  Serial.write(senddata,64);
  delay(3000);
  
count8=strlen(page);
//Serial.println(count8);
// wait for an incoming TCP packet, but ignore its contents
  if (ether.packetLoop(ether.packetReceive())) {
    memcpy(ether.tcpOffset(), page, sizeof page);
    ether.httpServerReply(sizeof page - 1);
  }
  //Serial.println("End ");
}
