 #include <SoftwareSerial.h>
SoftwareSerial gprsSerial(2,3);
 
#include <String.h>
#include <DHT.h> 
 
#define DHTPIN A0
 
DHT dht(DHTPIN, DHT11);
// int led = 13; 


 
void setup()
{
  gprsSerial.begin(9600); 
  // pinMode(led, OUTPUT);              // the GPRS baud rate   
  Serial.begin(9600);    // the GPRS baud rate 
  dht.begin();
 
  delay(1000);
}
 
void loop()
{
      float h = dht.readHumidity();
      float t = dht.readTemperature(); 
      delay(100);   
         
      Serial.print("Temperature = ");
      Serial.print(t);
      Serial.println(" °C");
      Serial.print("Humidity = ");
      Serial.print(h);
      Serial.println(" %");

      //  if(h > 70.00) { 
      //   digitalWrite(led, HIGH); 
      //   }else {
      //   digitalWrite(led, LOW);
      // }    
      
   
  if (gprsSerial.available())
    Serial.write(gprsSerial.read());
 
  gprsSerial.println("AT");
  delay(1000);
 
  gprsSerial.println("AT+CPIN?");
  delay(1000);
 
  gprsSerial.println("AT+CREG?");
  delay(1000);
 
  gprsSerial.println("AT+CGATT?");
  delay(1000);
 
  gprsSerial.println("AT+CIPSHUT");
  delay(1000);
 
  gprsSerial.println("AT+CIPSTATUS");
  delay(2000);
 
  gprsSerial.println("AT+CIPMUX=0");
  delay(2000);
 
  ShowSerialData();
 
  gprsSerial.println("AT+CSTT=\"www.inwi.ma\"");//start task and setting the APN,
  delay(1000);
 
  ShowSerialData();
 
  gprsSerial.println("AT+CIICR");//bring up wireless connection
  delay(3000);
 
  ShowSerialData();
 
  gprsSerial.println("AT+CIFSR");//get local IP adress
  delay(2000);
 
  ShowSerialData();
 
  gprsSerial.println("AT+CIPSPRT=0");
  delay(3000);
 
  ShowSerialData();
  
  gprsSerial.println("AT+CIPSTART=\"TCP\",\"ismailiot.000webhostapp.com\",\"443\"");//start up the connection
  // gprsSerial.println("AT+CIPSTART=\"TCP\",\"127.0.0.1\",\"3306\"");//start up the connection
  delay(6000);
 
  ShowSerialData();
 
  gprsSerial.println("AT+CIPSEND");//begin send data to remote server
  delay(4000);
  ShowSerialData();
  
  String str="GET https://ismailiot.000webhostapp.com/add.php/?temperature=" + String(t) +"&humidity="+String(h);
  // String str="GET http://localhost/testcode/dht.php?temperature="+ String(t) +"&humidity="+ String(h);

  Serial.println(str);
  gprsSerial.println(str);//begin send data to remote server
  
  delay(4000);
  ShowSerialData();
 
  gprsSerial.println((char)26);//sending
  delay(5000);//waitting for reply, important! the time is base on the condition of internet 
  gprsSerial.println();
 
  ShowSerialData();
 
  gprsSerial.println("AT+CIPSHUT");//close the connection
  delay(100);
  ShowSerialData();
} 
void ShowSerialData()
{
  while(gprsSerial.available()!=0)
  Serial.write(gprsSerial.read());
  delay(5000); 
  
}