
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char* ssid = "mywifi";
const char* password = "1234567890";
String pageText = "<meta charset=\"UTF-8\"><style>input {width:200px;height:50px;font-size:25px;}</style><INPUT TYPE=\"button\" value='1. Röleyi Aç' onClick=\"parent.location='/r1ac'\"><INPUT TYPE=\"button\" value='2. Röleyi Aç' onClick=\"parent.location='/r2ac'\"><INPUT TYPE=\"button\" value='3. Röleyi Aç' onClick=\"parent.location='/r3ac'\"><INPUT TYPE=\"button\" value='4. Röleyi Aç' onClick=\"parent.location='/r4ac'\"><br><INPUT TYPE=\"button\" value='1. Röleyi Kapat' onClick=\"parent.location='/r1kapat'\"><INPUT TYPE=\"button\" value='2. Röleyi Kapat' onClick=\"parent.location='/r2kapat'\"><INPUT TYPE=\"button\" value='3. Röleyi Kapat' onClick=\"parent.location='/r3kapat'\"><INPUT TYPE=\"button\" value='4. Röleyi Kapat' onClick=\"parent.location='/r4kapat'\">";
int role1=14;                 
int role2=12;                 
int role3=13;                 
int role4=15;                 
ESP8266WebServer server(80);  
const int led = 2;            
void setup(void){
  pinMode(led, OUTPUT);     
  pinMode(role1, OUTPUT);
  pinMode(role2, OUTPUT);
  pinMode(role3, OUTPUT);
  pinMode(role4, OUTPUT);
  digitalWrite(role1,LOW);  
  digitalWrite(role2,LOW);
  digitalWrite(role3,LOW);
  digitalWrite(role4,LOW);

  Serial.begin(115200);     
  
  WiFi.begin(ssid, password);
  Serial.println("");        
  
  // Wait for connection
  digitalWrite(led,1);
  while (WiFi.status() != WL_CONNECTED) 
  {                                     
    digitalWrite(led,0);                
    delay(250);                         
    digitalWrite(led,1);
    delay(250);
    Serial.print(".");
  }
  digitalWrite(led,0);
  
  Serial.println("");
  Serial.print("Connected to ");       
  Serial.println(ssid);                
  Serial.print("IP address: ");        
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {         
    Serial.println("MDNS responder started");
  }

  server.on("/",[](){ 
    server.send(200, "text/plain", "esp8266 nin ana sayfasindasiniz!");});
    
  server.on("/r1ac",[](){ 
    server.send(200, "text/html", pageText);
    digitalWrite(role1,HIGH);});
    
  server.on("/r2ac", [](){ 
    server.send(200, "text/html", pageText);
    digitalWrite(role2,HIGH);});
    
  server.on("/r3ac", [](){ 
    server.send(200, "text/html", pageText);
    digitalWrite(role3,HIGH);});
    
  server.on("/r4ac", [](){ 
    server.send(200, "text/html", pageText);
    digitalWrite(role4,HIGH);});
    
  server.on("/r1kapat", [](){ 
    server.send(200, "text/html", pageText);
    digitalWrite(role1,LOW);});
    
  server.on("/r2kapat", [](){ 
    server.send(200, "text/html", pageText);
    digitalWrite(role2,LOW);});
    
  server.on("/r3kapat", [](){ 
    server.send(200, "text/html", pageText);
    digitalWrite(role3,LOW);});
    
  server.on("/r4kapat", [](){ 
    server.send(200, "text/html", pageText);
    digitalWrite(role4,LOW);});
  
  server.onNotFound([](){ 
  String message = "File Not Found\n\n";                 
  message += "URI: ";                                    
  message += server.uri();
  message += "\nMethod: ";                               
  message += (server.method() == HTTP_GET)?"GET":"POST"; 
  message += "\nArguments: ";                            
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);            
  });
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();
}

