#include <ESP8266WiFi.h>
#include <WiFiClient.h>

const char * ssid = "CharGG"; 
const char * password = "kirikanan";
//192.168.184.154

const char * host = "192.168.184.14"; // your pc ip
//const int tcpPort = 56; // your pc ip

int newData;
String data;
WiFiServer server(56);
WiFiClient client;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  wifiConnect(); 
  server.begin();
}

void wifiConnect()
{
      WiFi.begin(ssid, password);
      Serial.println("");
      while (WiFi.status () != WL_CONNECTED)
      {
        delay(500);
        Serial.print(".");
      }
      Serial.println("");
      Serial.print("Connected to ");
      Serial.println(ssid);
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP());

}

void loop() {
    if (WiFi.status() != WL_CONNECTED)
    {
        wifiConnect();
    }   
    client = server.available();

    if (client){

            String data;
            Serial.println("Client connected");
            while (client.connected()){
                while(client.available()>0)
                {
                    data = client.readStringUntil('.');
                    Serial.println(data);
                    client.write("Server to client: ");
                    client.print(data);
                    client.write(" back to client \n");
                }
                delay(10);
        }   
    client.stop();
    Serial.println("Client Disconnected");
    }
}
