// libraries: https://pubsubclient.knolleary.net/

#include <WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>

const char* ssid       = "*****";
const char* password   = "*****";
IPAddress servermqtt(192, 168, 1, 7);
WiFiClient wclient;
PubSubClient client(wclient);

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++){ Serial.print((char)payload[i]); }
  Serial.println();
}

void MQTT_connect() {
  client.setServer(servermqtt, 1883);
  client.setCallback(callback);
  while (!client.connected()) {
    Serial.printf("Connecting to MQTT ");
    Serial.printf(" ..");
    if (client.connect("*****")) {
      Serial.println(" CONNECTED");
      // HOW TO SEND A COMMAND: "client.publish(path,value);"
      client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void WIFI_connect() {
    Serial.printf("Connecting to %s ", ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println(" CONNECTED");
}

void setup() {
    Serial.begin(115200);
    WIFI_connect();
    MQTT_connect();
    if((client.connected()) && (WiFi.status() == WL_CONNECTED)) {Serial.println("Everthing is connected and ready to use!");}
}

void loop() {
}
