// #include <SoftwareSerial.h>
// #include <DHT.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>


// #define DHTPIN A0
// #define DHTTYPE DHT11

// DHT dht(DHTPIN, DHTTYPE);

// SoftwareSerial gprsSerial(2, 3); // RX, TX pins for SIM800A
// String apn = "www.inwi.ma"; // APN of your GSM provider
// // String gprsUser = "username"; // Username for GPRS/Internet connection
// // String gprsPass = "password"; // Password for GPRS/Internet connection



// void setup() {
//   Serial.begin(9600);
//   gprsSerial.begin(9600);
//   dht.begin();
  
//   delay(2000); // Wait for SIM800A to initialize

//   // if (gsmInit()) {
//   //   Serial.println("GSM initialized successfully.");
//   // } else {
//   //   Serial.println("GSM initialization failed. Check SIM800A connection and settings.");
//   //   while (1);
//   // }
  
//   // if (mysqlInit()) {
//   //   Serial.println("MySQL initialized successfully.");
//   // } else {
//   //   Serial.println("MySQL initialization failed. Check MySQL connection and settings.");
//   //   while (1);
//   // }
// }

// void loop() {
//   float temperature = dht.readTemperature();
//   float humidity = dht.readHumidity();

//   if (isnan(temperature) || isnan(humidity)) {
//     Serial.println("Failed to read data from DHT sensor.");
//     delay(2000);
//     return;
//   }
  
//   if (mysqlInsertData(temperature, humidity)) {
//     Serial.println("Data inserted successfully into MySQL database.");
//   } else {
//     Serial.println("Failed to insert data into MySQL database.");
//   }

//   delay(5000); // Delay between data readings
// }

// bool gsmInit() {
//   gprsSerial.println("AT"); // Send AT command
//   delay(1000);
  
//   gprsSerial.println("AT+CMGF=1"); // Set SMS mode to text
//   delay(1000);
  
//   gprsSerial.println("AT+CNMI=2,2,0,0,0"); // Configure module to send SMS data to serial out upon receipt
//   delay(1000);
  
//   gprsSerial.println("AT+CIPSHUT"); // Deactivate GPRS PDP context
//   delay(1000);

//   gprsSerial.println("AT+CIPSTATUS"); // Check if the module is connected to the network
//   delay(1000);

//   String response = gprsSerial.readString();
//   if (response.indexOf("CONNECTED") == -1) {
//     gprsSerial.println("AT+CSTT=\"www.inwi.ma\"");//start task and setting the APN,
//     delay(2000);
    
//     gprsSerial.println("AT+CIICR"); // Activate GPRS PDP context
//     delay(3000);
    
//     gprsSerial.println("AT+CIFSR"); // Get local IP address
//     delay(2000);
    
//     gprsSerial.println("AT+CIPSTART=\"TCP\",\"" + String(server) + "\",3306"); // Start a TCP connection
//     delay(2000);
    
//     gprsSerial.println("AT+CIPSTATUS"); // Check if the module is connected to the network
//     delay(2000);
    
//     response = gprsSerial.readString();
//     if (response.indexOf("CONNECTED") == -1) {
//       return false;
//     }
//   }

//   return true;
// }

// bool mysqlInit() {
//   MySQL_Connection conn((Client *)&gprsSerial);
//   IPAddress serverIP = IPAddress();
//   serverIP.fromString(server);


//   if (conn.connect(serverIP, 3306, user, password)) {
//     return true;
//   } else {
//     return false;
//   }
// }

// bool mysqlInsertData(float temperature, float humidity) {
//   MySQL_Connection conn((Client *)&gprsSerial);
//   MySQL_Cursor *cursor = new MySQL_Cursor(&conn);

//   char query[128];
//   sprintf(query, "INSERT INTO dht11 (`Temperature`, `Humidity`) VALUES (%.2f, %.2f)", temperature, humidity);

//   cursor->execute(query);
//   delete cursor;

//   if (conn.connected()) {
//     conn.close();
//   }

//   return true;
// }


#include <SoftwareSerial.h>
SoftwareSerial gprsSerial(2,3);
 
#include <String.h>
#include <DHT.h> 
 
#define DHTPIN A0
char server[] = "127.0.0.1"; // MySQL server address
char user[] = "root"; // MySQL username
char password[] = ""; // MySQL password
char database[] = "temperaturhumiditydata"; // MySQL database name
DHT dht(DHTPIN, DHT11);

void setup()
{
  gprsSerial.begin(9600);               // the GPRS baud rate   
  Serial.begin(9600);    // the GPRS baud rate 
  dht.begin();
 
  delay(1000);
  if (mysqlInit()) {
    Serial.println("MySQL initialized successfully.");
  } else {
    Serial.println("MySQL initialization failed. Check MySQL connection and settings.");
    while (1);
  }
}
float h = dht.readHumidity();
float t = dht.readTemperature();
void loop()
{
       
      delay(100);   
         
      Serial.print("Temperature = ");
      Serial.print(t);
      Serial.println(" °C");
      Serial.print("Humidity = ");
      Serial.print(h);
      Serial.println(" %");    
      
     if (mysqlInsertData(t, h)) {
    Serial.println("Data inserted successfully into MySQL database.");
  } else {
    Serial.println("Failed to insert data into MySQL database.");
  }
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
  
  gprsSerial.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"");//start up the connection
  delay(6000);
 
  ShowSerialData();
 
  gprsSerial.println("AT+CIPSEND");//begin send data to remote server
  delay(4000);
  ShowSerialData();
  
  String str="GET https://api.thingspeak.com/update?api_key=O13AOCHYYNU2LQ19&field1=" + String(t) +"&field2="+String(h);
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
bool mysqlInit() {
  MySQL_Connection conn((Client *)&gprsSerial);
  IPAddress serverIP = IPAddress();
  serverIP.fromString(server);


  if (conn.connect(serverIP, 3306, user, password)) {
    return true;
  } else {
    return false;
  }
} 
bool mysqlInsertData(float temperature, float humidity) {
  MySQL_Connection conn((Client *)&gprsSerial);
  MySQL_Cursor *cursor = new MySQL_Cursor(&conn);

  char query[128];
  sprintf(query, "INSERT INTO dht11 (`Temperature`, `Humidity`) VALUES (%.2f, %.2f)", t, h);

  cursor->execute(query);
  delete cursor;

  if (conn.connected()) {
    conn.close();
  }

  return true;
}
void ShowSerialData()
{
  while(gprsSerial.available()!=0)
  Serial.write(gprsSerial.read());
  delay(5000); 
  
}
