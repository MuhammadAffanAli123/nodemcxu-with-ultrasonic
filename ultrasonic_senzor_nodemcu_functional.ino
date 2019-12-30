

#define TRIGGER D2
#define ECHO    D3

// NodeMCU Pin D1 > TRIGGER | Pin D2 > ECHO

#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <FirebaseArduino.h>
#include <time.h>

#define FIREBASE_HOST "iot-garbage-8e43b.firebaseio.com"
#define FIREBASE_AUTH "6J781e5m7x2sddBVBDSIthGnLSakoDbRbZus3QsU"
#define WIFI_SSID "Cabel net free net"
#define WIFI_PASSWORD "pakistan@321"
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "eJG9SZX4jXfAbuIsAnWZ5VN8XyjUtOV_";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Cabel net free net";
char pass[] = "pakistan@321";


BlynkTimer timer;
int distance = 0;
int thresh[3] = {30 , 20 , 10};
WidgetLED green(V1);
WidgetLED orange(V2);
WidgetLED red(V3);

void setup() {
  
  Serial.begin (19200);
  Blynk.begin(auth, ssid, pass);
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(BUILTIN_LED, OUTPUT);
   WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  
}
int n = 0;
String numbers= "numbers" ;


void loop() {

  time_t rawtime;
  struct tm * timeinfo;

  time ( &rawtime );
  timeinfo = localtime ( &rawtime );
  long duration;
  digitalWrite(TRIGGER, LOW);  
  delayMicroseconds(2); 
  
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10); 
  
  digitalWrite(TRIGGER, LOW);
  duration = pulseIn(ECHO, HIGH);
  distance = (duration/2) / 29.1;

 
 if(distance >= 20 && distance  < 36  ){
    green.on();
     Serial.println("Green Light Open ");
     Firebase.pushString( "message/empty", "Empty: green Light Open");
      Firebase.setString( "color/col","EMPTY");
          
    }
 else   if(distance > 10 && distance  < 20 )
   { green.on();
    orange.on();
     Serial.println("Half full");
     Firebase.pushString( "message/half","Half Full: green & Yelllow Light Open");
      Firebase.setString( "color/col","HALF");
  }
     else if(distance < 10)
   { green.on();
    orange.on();
    red.on();
     Serial.println("full:");
      Firebase.pushString( "message/full"," Full: green & Yelllow & Red  Light Open");
       Firebase.setString( "color/col","Full");
  }
  else{
    green.off();
    orange.off();
    red.off();
    Serial.println("out of range");
  
}
delay(10000);
  
  
  Serial.print(distance);
  Serial.println("Centimeter distance:");
 // Blynk.virtualWrite(V5, distance);
  delay(200);
  Blynk.run();
}
