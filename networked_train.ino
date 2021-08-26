#include <SPI.h>
#include <WiFiNINA.h>
#include <String.h>

char ssid[] = "Shenkar-New";     // your network SSID (name)
char pass[] = "Shenkarwifi";        // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;               // your network key index number (needed only for WEP)

int status = WL_IDLE_STATUS;

// Initialize the WiFi client library
WiFiClient client;

// server address:
IPAddress server(52,211,158,121);

unsigned long lastConnectionTime = 0;            // last time you connected to the server, in milliseconds
const unsigned long postingInterval = 10L * 1000L; // delay between updates, in milliseconds
int sns1=0 , sns2=0 , sns3=0 , sns4=0;
// initialize seats 
int seat1=0 , seat2=0 , seat3=0 , seat4=0;
int booked[5]={0,0,0,0,0},m=0;

int sensed1=0 , sensed2=0 , sensed3=0 , sensed4=0;
 
String MyString ;

void setup() {
  
   // initialize LEDs:
    pinMode(8,OUTPUT);// red led seat 1
    pinMode(5,OUTPUT);// red led seat 2
    pinMode(12,OUTPUT);// red led seat 3
    pinMode(7,OUTPUT);// red led seat 4
    pinMode(9,OUTPUT);// green led seat 1
    pinMode(13,OUTPUT);// green led seat 2
    pinMode(11,OUTPUT);// green led seat 3
    pinMode(6,OUTPUT);// green led seat 4
    pinMode(1,OUTPUT);// yellow led seat 1
    pinMode(2,OUTPUT);// yellow led seat 2
    pinMode(3,OUTPUT);// yellow led seat 3
    pinMode(4,OUTPUT);// yellow led seat 4 
    // leds test:
    digitalWrite(1,HIGH);digitalWrite(8,HIGH);digitalWrite(9,HIGH); delay(4000);
    digitalWrite(1,LOW);digitalWrite(8,LOW);digitalWrite(9,LOW);
    digitalWrite(2,HIGH);digitalWrite(5,HIGH);digitalWrite(13,HIGH);delay(4000);
    digitalWrite(2,LOW);digitalWrite(5,LOW);digitalWrite(13,LOW);
    digitalWrite(3,HIGH);digitalWrite(11,HIGH);digitalWrite(12,HIGH);delay(4000);
    digitalWrite(3,LOW);digitalWrite(11,LOW);digitalWrite(12,LOW);
    digitalWrite(4,HIGH);digitalWrite(6,HIGH);digitalWrite(7,HIGH);delay(4000);
    digitalWrite(4,LOW);digitalWrite(6,LOW);digitalWrite(7,LOW);
    
    //Initialize serial and wait for port to open:
    Serial.begin(9600);
    while (!Serial) {  }

    // check for the WiFi module:
    if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true); }

    // attempt to connect to WiFi network:
    while (status != WL_CONNECTED) {
      Serial.print("Attempting to connect to SSID: ");
      Serial.println(ssid);
      // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
       status = WiFi.begin(ssid, pass);

      // wait 10 seconds for connection:
       delay(10000);
                                   }
  // you're connected now, so print out the status:
   printWifiStatus();
               }

void loop() {
  delay(500);
  sns1 = analogRead(A0);
  sns2 = analogRead(A1);
  sns3 = analogRead(A2);
  sns4 = analogRead(A3);
  delay(500);

  if (sns1>600)sensed1=1;else sensed1=0;
  if (sns2>800)sensed2=1;else sensed2=0;
  if (sns3>800)sensed3=1;else sensed3=0;
  if (sns4>800)sensed4=1;else sensed4=0;
  
    if (sensed1==1){ if (seat1==0){
      Serial.println("seat1 is occupied"); seat1=1;
      httpRequest("/seat_status?fromStop=tel%20aviv&toStop=herzelia&user_id=5&time=21:00%2020/7/2021&seat=1&saved=1");}else;}
  
      else{if (seat1==1){
      Serial.println("seat1 is available");seat1=0;
      httpRequest("/seat_status?fromStop=tel%20aviv&toStop=herzelia&user_id=5&time=21:00%2020/7/2021&seat=1&saved=0");}else;}
  
    if (sensed2==1){ if (seat2==0){
      Serial.println("seat2 is occupied"); seat2=1;
      httpRequest("/seat_status?fromStop=tel%20aviv&toStop=herzelia&user_id=5&time=21:00%2020/7/2021&seat=2&saved=1");}else;}
    
     else{if (seat2==1){
      Serial.println("seat2 is available");seat2=0;
      httpRequest("/seat_status?fromStop=tel%20aviv&toStop=herzelia&user_id=5&time=21:00%2020/7/2021&seat=2&saved=0");}else;}   
        
    if (sensed3==1){ if (seat3==0){
      Serial.println("seat3 is occupied"); seat3=1;
      httpRequest("/seat_status?fromStop=tel%20aviv&toStop=herzelia&user_id=5&time=21:00%2020/7/2021&seat=3&saved=1");}else;}
    
      else{if (seat3==1){
      Serial.println("seat3 is available");seat3=0;
      httpRequest("/seat_status?fromStop=tel%20aviv&toStop=herzelia&user_id=5&time=21:00%2020/7/2021&seat=3&saved=0");}else;}
    
    if (sensed4==1){ if (seat4==0){
      Serial.println("seat4 is occupied"); seat4=1;
      httpRequest("/seat_status?fromStop=tel%20aviv&toStop=herzelia&user_id=5&time=21:00%2020/7/2021&seat=4&saved=1");}else;}
    
      else{if (seat4==1){
      Serial.println("seat4 is available");seat4=0;
      httpRequest("/seat_status?fromStop=tel%20aviv&toStop=herzelia&user_id=5&time=21:00%2020/7/2021&seat=4&saved=0");}else;}
  
    if(seat1==0){ 
      digitalWrite(8,LOW);
    if(booked[0]==0){digitalWrite(9,HIGH);digitalWrite(1,LOW);}
       else{     digitalWrite(9,LOW);digitalWrite(1,HIGH);}}
       else{digitalWrite(8,HIGH);digitalWrite(9,LOW);digitalWrite(1,LOW);}
  
    if(seat2==0){ 
      digitalWrite(5,LOW);
    if(booked[1]==0){digitalWrite(13,HIGH);digitalWrite(2,LOW);}
      else{     digitalWrite(13,LOW);digitalWrite(2,HIGH);}}
      else{digitalWrite(5,HIGH);digitalWrite(13,LOW);digitalWrite(2,LOW);}
  
    if(seat3==0){ 
      digitalWrite(12,LOW);
    if(booked[2]==0){digitalWrite(11,HIGH);digitalWrite(3,LOW);}
      else{     digitalWrite(11,LOW);digitalWrite(3,HIGH);}}
      else{digitalWrite(12,HIGH);digitalWrite(11,LOW);digitalWrite(3,LOW);}
  
    if(seat4==0){ 
      digitalWrite(7,LOW);
    if(booked[3]==0){digitalWrite(6,HIGH);digitalWrite(4,LOW);}
      else{     digitalWrite(6,LOW);digitalWrite(4,HIGH);}}
      else{digitalWrite(7,HIGH);digitalWrite(6,LOW);digitalWrite(4,LOW);} 
  
  // if ten seconds have passed since your last connection,
  // then connect again and send data:

    //currentMillis = millis();
    
    char charValue = m+'1';
    String reQ = "/seat_booked_status?fromStop=Tel%20Aviv&toStop=Herzelia&time=21:00%2020/7/2021&seat=";
    reQ.concat(charValue);
    Serial.println(reQ);
    if (millis() - lastConnectionTime > postingInterval) {
    //char charValue = m+'1'; // converting integer to character
   // if (reQ.indexOf("seat=3") > 0){reQ="/seat_booked_status?fromStop=Tel%20Aviv&toStop=Herzelia&time=18:17%2014/5/2021&seat=34";}
      httpRequest(reQ);

    //httpRequest("/seat_booked_status?fromStop=Tel%20Aviv&toStop=Herzelia&time=18:17%2014/5/2021&seat=1");
    //m++; m=m%4;
    
    //lastConnectionTime=currentMillis;
    delay(2000);
    if(!client.available()) Serial.println("Client not available after request - check the code!");
  
    String MyString="";
    while (client.available()) {char c = client.read(); MyString= MyString + c; Serial.write(c); }
    //Serial.println(MyString);
    client.flush();
    if (MyString.indexOf("booked") > 0 && MyString.indexOf("not booked") == -1){
      //Serial.println("!!!EXTRACTED TRUE  m= ");
      booked[m]=1;
     }else{booked[m]=0;}
    
    m++; m=m%4;
    lastConnectionTime=millis();
  }
  
}



// this method makes a HTTP connection to the server:
void httpRequest(String myRequest) {
  // close any connection before send a new request.
  // This will free the socket on the NINA module
  client.stop();

  String getRequest = "GET " + myRequest + " HTTP/1.1";
  // if there's a successful connection:
  if (client.connect(server, 8080)) {
    Serial.println("connecting...");
    // send the HTTP GET request:
    //client.println("GET /seat_status?fromStop=tel%20aviv&toStop=herzelia&user_id=5&time=18:17%2014/5/2021&seat=1&saved=1 HTTP/1.1");
    client.println(getRequest);
    client.println("Host: http://52.211.158.121:8080");
    //client.println("User-Agent: ArduinoWiFi/1.1");
    client.println("Connection: close");
    client.println();

    // note the time that the connection was made:
    //lastConnectionTime = millis();
    }else{
    // if you couldn't make a connection:
    Serial.println("connection failed");
         }
}


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  }
