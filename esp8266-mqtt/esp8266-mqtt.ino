#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* mqttServer = "test.mosquitto.org";
const int mqttPort = 1883;

const char* cred[] = {"Digital_School", "@bestlab"};

const char* client_id = "WebLight";
const char* thread = "pedropadilha13/weblight/#";
const char* response_topic = "pedropadilha13/weblight/responses";

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {

  Serial.begin(115200);

  wifi_setup();

  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);

  connect();

  client.subscribe(thread);

}

void wifi_setup() {
  WiFi.begin(cred[0], cred[1]);
  Serial.println("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Success!");
  Serial.print("IP Address is: ");
  Serial.println(WiFi.localIP());
}

void connect() {
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
    if (client.connect(client_id)) {
      Serial.println("connected");
    } else {
      Serial.print("failed with state ");
      Serial.println(client.state());
      delay(2000);
    }
  }
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

  String command = "";
  String pin = "";
  boolean toCommand = true;
  for (int i = 24; i < strlen(topic); i++) {
    if (topic[i] == 47) {
      toCommand = false;
    } else {
      if (toCommand) {
        command += (char) topic[i];
      } else {
        pin += (char) topic[i];
      }
    }
  }

  if (pin.equals("")) {
    pin = message;
  }

  if (command.equals("responses")) {
    Serial.println("(This was simply a response most likely sent by this device to broadcast the requested data.)");
  } else {
    Serial.print("Command: ");
    Serial.println(command);
    Serial.print("pin: ");
    Serial.println(pin);

    int pinNumber = pin.toInt();

    if (command.equals("read") || command.equals("r") || command.equals("digitalRead") || command.equals("readDigital")) {
      //Serial.print("digitalRead");
      //Serial.println(pin.toInt());
      pinMode(pinNumber, INPUT);
      int reading = digitalRead(pinNumber);
      //Serial.print("reading: ");
      //Serial.println(reading);
      char response[8];
      itoa(reading, response, 10);
      client.publish(response_topic, response);
    } else if (command.equals("analogRead") || command.equals("readAnalog")) {
      //Serial.print("analogRead");
      //Serial.println(pinNumber);
      pinMode(pinNumber, INPUT);
      int reading = analogRead(pinNumber);
      //Serial.print("reading: ");
      //Serial.println(reading);
      char response[8];
      itoa(reading, response, 10);
      client.publish(response_topic, response);
    } else if (command.equals("digitalWrite") || command.equals("writeDigital") || command.equals("write") || command.equals("w")) {
      //Serial.print("digitalWrite");
      //Serial.println(pinNumber);
      pinMode(pinNumber, OUTPUT);
      boolean state = (message == "1" || message == "HIGH" || message == "true" || message == "on");
      digitalWrite(pinNumber, state);
    } else if (command.equals("analogWrite") || command.equals("writeAnalog")) {
      //Serial.print("analogWrite");
      //Serial.println(pinNumber);
      pinMode(pinNumber, OUTPUT);
      analogWrite(pinNumber, message.toInt());
    }
  }

  Serial.println("\n---------------------------\n");


}

void loop() {
  if (!client.connected()) {
    connect();
  }
  client.loop();
}
