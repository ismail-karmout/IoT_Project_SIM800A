// // //  #include <SoftwareSerial.h>
// // // SoftwareSerial gprsSerial(2,3);
 
// // // #include <String.h>
// // // #include <DHT.h> 
 
// // // #define DHTPIN A0
 
// // // DHT dht(DHTPIN, DHT11);
// // // // int led = 13; 


 
// // // void setup()
// // // {
// // //   gprsSerial.begin(9600); 
// // //   // pinMode(led, OUTPUT);              // the GPRS baud rate   
// // //   Serial.begin(9600);    // the GPRS baud rate 
// // //   dht.begin();
 
// // //   delay(1000);
// // // }
 
// // // void loop()
// // // {
// // //       float h = dht.readHumidity();
// // //       float t = dht.readTemperature(); 
// // //       delay(100);   
         
// // //       Serial.print("Temperature = ");
// // //       Serial.print(t);
// // //       Serial.println(" °C");
// // //       Serial.print("Humidity = ");
// // //       Serial.print(h);
// // //       Serial.println(" %");

// // //       //  if(h > 70.00) { 
// // //       //   digitalWrite(led, HIGH); 
// // //       //   }else {
// // //       //   digitalWrite(led, LOW);
// // //       // }    
      
   
// // //   if (gprsSerial.available())
// // //     Serial.write(gprsSerial.read());
 
// // //   gprsSerial.println("AT");
// // //   delay(1000);
 
// // //   gprsSerial.println("AT+CPIN?");
// // //   delay(1000);
 
// // //   gprsSerial.println("AT+CREG?");
// // //   delay(1000);
 
// // //   gprsSerial.println("AT+CGATT?");
// // //   delay(1000);
 
// // //   gprsSerial.println("AT+CIPSHUT");
// // //   delay(1000);
 
// // //   gprsSerial.println("AT+CIPSTATUS");
// // //   delay(2000);
 
// // //   gprsSerial.println("AT+CIPMUX=0");
// // //   delay(2000);
 
// // //   ShowSerialData();
 
// // //   gprsSerial.println("AT+CSTT=\"www.inwi.ma\"");//start task and setting the APN,
// // //   delay(1000);
 
// // //   ShowSerialData();
 
// // //   gprsSerial.println("AT+CIICR");//bring up wireless connection
// // //   delay(3000);
 
// // //   ShowSerialData();
 
// // //   gprsSerial.println("AT+CIFSR");//get local IP adress
// // //   delay(2000);
 
// // //   ShowSerialData();
 
// // //   gprsSerial.println("AT+CIPSPRT=0");
// // //   delay(3000);
 
// // //   ShowSerialData();
  
// // //   gprsSerial.println("AT+CIPSTART=\"TCP\",\"ismailiot.000webhostapp.com\",\"21\"");//start up the connection
// // //   // gprsSerial.println("AT+CIPSTART=\"TCP\",\"127.0.0.1\",\"3306\"");//start up the connection
// // //   delay(6000);
 
// // //   ShowSerialData();
 
// // //   gprsSerial.println("AT+CIPSEND");//begin send data to remote server
// // //   delay(4000);
// // //   ShowSerialData();
  
// // //   String str="GET https://ismailiot.000webhostapp.com/add.php/?temperature=" + String(t) +"&humidity="+String(h);
// // //   // String str="GET http://localhost/testcode/dht.php?temperature="+ String(t) +"&humidity="+ String(h);

// // //   Serial.println(str);
// // //   gprsSerial.println(str);//begin send data to remote server
  
// // //   delay(4000);
// // //   ShowSerialData();
 
// // //   gprsSerial.println((char)26);//sending
// // //   delay(5000);//waitting for reply, important! the time is base on the condition of internet 
// // //   gprsSerial.println();
 
// // //   ShowSerialData();
 
// // //   gprsSerial.println("AT+CIPSHUT");//close the connection
// // //   delay(100);
// // //   ShowSerialData();
// // // } 
// // // void ShowSerialData()
// // // {
// // //   while(gprsSerial.available()!=0)
// // //   Serial.write(gprsSerial.read());
// // //   delay(5000); 
  
// // // }




// #include <SoftwareSerial.h>
// SoftwareSerial gprsSerial(2, 3);

// #include <String.h>
// #include <DHT.h>

// #define DHTPIN A0

// DHT dht(DHTPIN, DHT11);

// void setup()
// {
//   gprsSerial.begin(9600);
//   Serial.begin(9600);
//   dht.begin();
//   delay(1000);
// }

// void loop()
// {
//   float h = dht.readHumidity();
//   float t = dht.readTemperature();
//   delay(100);

//   Serial.print("Temperature = ");
//   Serial.print(t);
//   Serial.println(" °C");
//   Serial.print("Humidity = ");
//   Serial.print(h);
//   Serial.println(" %");

//   // Perform HTTP GET request
//   gprsSerial.println("AT");
//   delay(1000);

//   gprsSerial.println("AT+CPIN?");
//   delay(1000);

//   gprsSerial.println("AT+CREG?");
//   delay(1000);

//   gprsSerial.println("AT+CGATT?");
//   delay(1000);

//   gprsSerial.println("AT+CIPSHUT");
//   delay(1000);

//   gprsSerial.println("AT+CIPSTATUS");
//   delay(2000);

//   gprsSerial.println("AT+CIPMUX=0");
//   delay(2000);

//   ShowSerialData();

//   gprsSerial.println("AT+CSTT=\"www.inwi.ma\"");//start task and setting the APN,
//   delay(1000);

//   ShowSerialData();

//   gprsSerial.println("AT+CIICR");//bring up wireless connection
//   delay(3000);

//   ShowSerialData();

//   gprsSerial.println("AT+CIFSR");//get local IP address
//   delay(2000);

//   ShowSerialData();

//   gprsSerial.println("AT+CIPSPRT=0");
//   delay(3000);

//   ShowSerialData();

//   gprsSerial.println("AT+CIPSTART=\"TCP\",\"ismailiot.000webhostapp.com\",\"80\"");//start up the connection
//   delay(6000);

//   ShowSerialData();

//   gprsSerial.println("AT+CIPSEND");//begin send data to remote server
//   delay(4000);
//   ShowSerialData();

//   // Construct the HTTP request string
//   String httpRequest = "GET /add.php?temperature=" + String(t) + "&humidity=" + String(h) + " HTTP/1.1\r\n";
//   httpRequest += "Host: ismailiot.000webhostapp.com\r\n";
//   httpRequest += "Connection: close\r\n\r\n";

//   Serial.println(httpRequest);
//   gprsSerial.println(httpRequest);//begin send data to remote server

//   delay(4000);
//   ShowSerialData();

//   gprsSerial.println((char)26);//sending
//   delay(5000);//wait for reply, important! the time is based on the condition of the internet
//   gprsSerial.println();

//   ShowSerialData();

//   gprsSerial.println("AT+CIPSHUT");//close the connection
//   delay(100);
//   ShowSerialData();
// }

// void ShowSerialData()
// {
//   while (gprsSerial.available() != 0)
//     Serial.write(gprsSerial.read());
//   delay(5000);
// }

 

//  #include <DHT.h>
// #include <SoftwareSerial.h>

// #define DHT11_PIN 2

// SoftwareSerial gsmSerial(10, 11); // RX, TX pins for SIM800A module

// void setup() {
//   Serial.begin(9600);
//   gsmSerial.begin(9600);

//   delay(1000); // Allow time for the SIM800A module to initialize

//   sendATCommand("AT"); // Check if the SIM800A module is responding
//   delay(1000);

//   sendATCommand("AT+CMGF=1"); // Set SMS mode to text mode
//   delay(1000);
// }

// void loop() {
//   int chk = DHT.read11(DHT11_PIN);
//   float temperature = DHT.temperature;
//   float humidity = DHT.humidity;

//   String data = "temperature=" + String(temperature) + "&humidity=" + String(humidity);
//   sendToServer(data);

//   delay(5000); // Delay between measurements
// }

// void sendToServer(String data) {
//   sendATCommand("AT+CREG?"); // Check network registration status
//   delay(1000);

//   sendATCommand("AT+CIPSHUT"); // Close any existing TCP/IP connection
//   delay(1000);

//   sendATCommand("AT+CIPMUX=0"); // Set to single TCP/IP connection mode
//   delay(1000);

//   sendATCommand("AT+CSTT=\"www.inwi.ma\",\"\",\"\""); // Set APN details
//   delay(1000);

//   sendATCommand("AT+CIICR"); // Bring up wireless connection
//   delay(1000);

//   sendATCommand("AT+CIFSR"); // Get local IP address
//   delay(1000);

//   sendATCommand("AT+CIPSTART=\"TCP\",\"https://ismailiot.000webhostapp.com/\",80"); // Establish TCP/IP connection to the PHP server
//   delay(2000);

//   String postRequest = "POST /add.php HTTP/1.1\r\n";
//   postRequest += "Host: https://ismailiot.000webhostapp.com\r\n";
//   postRequest += "Content-Type: application/x-www-form-urlencoded\r\n";
//   postRequest += "Content-Length: " + String(data.length()) + "\r\n\r\n";
//   postRequest += data;

//   sendATCommand("AT+CIPSEND=" + String(postRequest.length())); // Send the POST request length
//   delay(2000);

//   gsmSerial.print(postRequest);

//   sendATCommand("AT+CIPCLOSE"); // Close TCP/IP connection
//   delay(1000);
// }

// void sendATCommand(String command) {
//   gsmSerial.println(command);
//   delay(500);
//   while (gsmSerial.available()) {
//     Serial.write(gsmSerial.read());
//   }
//   Serial.println();
// }
 

#include <SoftwareSerial.h>
#include <DHT.h>

// Configuration du module SIM800A
#define SIM800_RX_PIN 10
#define SIM800_TX_PIN 11
#define SIM800_BAUD_RATE 9600

SoftwareSerial sim800Serial(SIM800_RX_PIN, SIM800_TX_PIN);

// Configuration du capteur DHT11
#define DHT_PIN 2
#define DHT_TYPE DHT11

DHT dht(DHT_PIN, DHT_TYPE);

// Configuration du serveur et de l'URL
const char* server = "ismailiot.000webhostapp.com";
const char* url = "/add.php";

void setup() {
  Serial.begin(9600);
  sim800Serial.begin(SIM800_BAUD_RATE);
  
  delay(1000);
  Serial.println("Initializing SIM800A...");
  sim800Serial.println("AT");
  delay(2000);
  
  // Vérifier si le module SIM800A est prêt
  if (sim800Serial.find("OK")) {
    Serial.println("SIM800A initialized.");
  } else {
    Serial.println("SIM800A initialization failed. Check connections and SIM card.");
    while (1);
  }
  
  dht.begin();
}

void loop() {
  float temperature = dht.readTemperature(); // Lire la température depuis le capteur DHT11
  float humidity = dht.readHumidity();       // Lire l'humidité depuis le capteur DHT11

  // Vérifier si la lecture des données du capteur est réussie
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Connexion au serveur
  if (sim800Serial.available()) {
    sim800Serial.flush();
  }
  sim800Serial.println("AT+CIPSHUT");
  delay(2000);
  sim800Serial.println("AT+CIPMUX=0");
  delay(2000);
  sim800Serial.println("AT+CSTT=\"www.inwi.ma\",\"\",\"\"");
  delay(2000);
  sim800Serial.println("AT+CIICR");
  delay(4000);
  sim800Serial.println("AT+CIFSR");
  delay(2000);
  sim800Serial.println("AT+CIPSTART=\"TCP\",\"" + String(server) + "\",80");
  delay(4000);
  
  // Construction de la requête HTTP GET
  String httpRequest = "GET " + String(url) + "?temperature=" + String(temperature) + "&humidity=" + String(humidity) + " HTTP/1.1\r\n" +
                       "Host: " + String(server) + "\r\n" +
                       "Connection: close\r\n\r\n";

  sim800Serial.print("AT+CIPSEND=");
  sim800Serial.println(httpRequest.length());
  delay(2000);
  
  sim800Serial.print(httpRequest);
  delay(5000);
  
  // Fermeture de la connexion
  sim800Serial.println("AT+CIPCLOSE");
  delay(2000);

  delay(60000); // Attendre 1 minute avant d'envoyer les prochaines données
}
