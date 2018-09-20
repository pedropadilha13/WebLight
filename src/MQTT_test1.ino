#include <ESP8266WiFi.h>
#include <PubSubClient.h>
 
const char* mqttServer = "test.mosquitto.org";
const int mqttPort = 1883;
 
WiFiClient espClient;
PubSubClient client(espClient);
 
void setup() {
 
  Serial.begin(115200);

  pinMode(0, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);

  digitalWrite(2, 1);

  char* cred[][2] = {
      {"Pedro", "3331926740"},
       {"Pedro's iPhone", "oioioioi"}
    };

  WiFi.begin(cred[0][0], cred[0][1]);

  Serial.println("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (millis() > 10000) {
      WiFi.begin(cred[1][0], cred[1][1]);
    }
  }
  
  Serial.println("Success!");
  Serial.print("IP Address is: ");
  Serial.println(WiFi.localIP());
 
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
 
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("PruPruBonitinha")) {
 
      Serial.println("connected");  
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
 
    }
  }
 
  client.subscribe("pedropadilha13/trabalho/#");
 
}
 
void callback(char* topic, byte* payload, unsigned int length) {
 
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
 
  Serial.print("Message: ");
  String message = "";
  
  for (int i = 0; i < length; i++) {
    message += (char) payload[i];
  }

  Serial.println(message);

  String pin = "";
  for (int i = 24; i < strlen(topic); i++) {
    pin += (char) topic[i];
  }
  Serial.print("Pin: ");
  boolean state = (message == "1" || message == "HIGH" || message == "true" || message == "on");
  Serial.print(pin);
  Serial.print(", ");
  Serial.println(state);
  digitalWrite(pin.toInt(), state);
 
  Serial.println();
  Serial.println("-----------------------");
 
}
 
void loop() {
  client.loop();
}
