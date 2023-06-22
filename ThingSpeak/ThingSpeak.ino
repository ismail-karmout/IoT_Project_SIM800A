#include <SoftwareSerial.h>
SoftwareSerial gprsSerial(2,3);
 
#include <String.h>
#include <DHT.h> 
#include <Stepper.h>
const int stepsPerRevolution = 200; 
Stepper stepper(stepsPerRevolution, 8, 9, 10, 11);  // Créer un objet Stepper

bool motorRunning = false;  // Déclarer et initialiser la variable motorRunning


// #define DHTTYPE DHT11   // Type de capteur DHT (DHT11 dans ce cas)
#define STEPS 200     // Nombre de pas par tour du moteur pas à pas
#define MOTOR_PIN1 8  // Broche du moteur pas à pas
#define MOTOR_PIN2 9  // Broche du moteur pas à pas
#define MOTOR_PIN3 10 // Broche du moteur pas à pas
#define MOTOR_PIN4 11 // Broche du moteur pas à pas
 
#define DHTPIN A0
int ledr = 13;
// int ledv = 13;
 
DHT dht(DHTPIN, DHT11);
// Stepper stepper(STEPS, MOTOR_PIN1, MOTOR_PIN3, MOTOR_PIN2, MOTOR_PIN4);  // Initialisation du moteur pas à pas

// boolean motorRunning = false;  // Variable pour stocker l'état du moteur
 
void setup()
{
  gprsSerial.begin(9600);               // the GPRS baud rate   
  Serial.begin(9600);
  // pinMode(ledr, OUTPUT);
  // pinMode(ledv, OUTPUT);

    // the GPRS baud rate 
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
      if(t > 20.00) { digitalWrite(ledr, HIGH); 
      } else { 
        digitalWrite(ledr, LOW); }  
      // if(h > 50.00) { digitalWrite(ledv, HIGH); } else { digitalWrite(ledv, LOW); }  
      if (h < 50  ) {
          startMotor();
       } else if (h > 55 ) {
          stopMotor();
       }

  delay(5000);  // Attente de 5 secondes entre chaque lecture d'humidité       
      
   
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
  
  String str="GET https://api.thingspeak.com/update?api_key=CW42OB9460XTQ0AV&field1=" + String(t) +"&field2="+String(h);
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
// Fonction pour démarrer le moteur
void startMotor() {
  motorRunning = true;
  stepper.setSpeed(25);  // Vitesse de rotation du moteur (ajustez selon vos besoins)
  stepper.step(STEPS);  // Faites une rotation complète du moteur
  // Serial.println("Démarrage du moteur !");
  
}

// Fonction pour arrêter le moteur
void stopMotor() {
  motorRunning = false;
  stepper.setSpeed(0);
  // Serial.println("Arrêt du moteur !");
}
 