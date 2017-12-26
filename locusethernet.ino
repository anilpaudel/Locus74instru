// Presentz a "Will be back soon web page", as stand-in webserver.
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
int ledPin8 = 8;
int inPin = 4,inPin5=5;     // pushbutton connected to digital pin 7
int val=0,val2=0,val3=0,val1=0;
byte Ethernet::buffer[900]; // tcp/ip send and receive buffer

char page[] =
"HTTP/1.0 503 Service Unavailable\r\n"
"Content-Type: text/html\r\n"
"Retry-After: 600\r\n"
"\r\n"
"<html>"
  "<head>"
  "<meta http-equiv=\"refresh\" content =\"8\" / >"
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
// "< meta http-equiv = \"refresh\" content =\"5\">"
void setup(){
  Serial.begin(9600);
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
      word len = ether.packetReceive();
      word pos = ether.packetLoop(len);
      Serial.print(strlen(page));
      //Serial.println((char *)Ethernet::buffer + pos);
   if(strstr((char *)Ethernet::buffer + pos, "on") != 0) {
      Serial.println("Received ON command");
      digitalWrite(ledPin8, HIGH);
    }
    Serial.print(strlen(page));
  
    // IF LED10=OFF turn it OFF  
    if(strstr((char *)Ethernet::buffer + pos, "off") != 0) {
      Serial.println("Received OFF command");
      digitalWrite(ledPin8, LOW);
  
    }  
    for(int i=0;i<10;i++)
    {
         val = digitalRead(inPin);
         val = digitalRead(inPin);
         
    }
 
     if(val==LOW)
  {
    Serial.println("low");
  page[339]='_';
  page[340]='L';
  page[341]='O';  
  page[342]='W';
  } 
  if(val==HIGH)
  {
    Serial.println("high");
  page[339]='H';
  page[340]='I';
  page[341]='G';  
  page[342]='H';

  }
   if(val1==LOW)
  {
    Serial.println("low");
  page[359]='_';
  page[360]='L';
  page[361]='O';  
  page[362]='W';
  } 
  if(val1==HIGH)
  {
    Serial.println("high");
  page[359]='H';
  page[360]='I';
  page[361]='G';  
  page[362]='H';
  }
  if(val2==LOW)
  {
    Serial.println("low");
  page[379]='_';
  page[380]='L';
  page[381]='O';  
  page[382]='W';
  } 
  if(val2==HIGH)
  {
    Serial.println("high");
  page[379]='H';
  page[380]='I';
  page[381]='G';  
  page[382]='H';

  }
   if(val3==LOW)
  {
    Serial.println("low");
  page[399]='_';
  page[400]='L';
  page[401]='O';  
  page[402]='W';
  } 
  if(val3==HIGH)
  {
   
  Serial.println("high");
  page[399]='H';
  page[400]='I';
  page[401]='G';  
  page[402]='H';
  
  }


   if (ether.packetLoop(ether.packetReceive())) {
    memcpy(ether.tcpOffset(), page, sizeof page);
    ether.httpServerReply(sizeof page - 1);
 delay(3000);
   }
}
 // if (ether.packetLoop(ether.packetReceive())) {
   // memcpy(ether.tcpOffset(), page, sizeof page);
    //ether.httpServerReply(sizeof page - 1);
