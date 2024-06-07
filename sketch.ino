#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

// Configurações da rede WiFi e do servidor MQTT
const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* mqtt_server = "broker.hivemq.com";

// Instâncias dos clientes WiFi e MQTT
WiFiClient espClient;
PubSubClient client(espClient);

// Pinos do sensor PIR
const int pir = 19;

void setup_wifi() { 
  delay(10);
  // Conectando-se à rede WiFi
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA); 
  WiFi.begin(ssid, password); 

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  // Função de callback do MQTT
  String temp; 
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) { 
    temp += (char)payload[i];
  }
  Serial.println(temp);
}

void reconnect() { 
  // Loop até reconectar
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);
    // Tentativa de conexão
    if (client.connect(clientId.c_str())) {
      Serial.println("Connected to " + clientId);
    } else {
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(pir, INPUT);
  setup_wifi(); 
  client.setServer(mqtt_server, 1883); 
  client.setCallback(callback); 
}

float generateRandomFloat(float min, float max) {
  return min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  int pirState = digitalRead(pir);
  Serial.println(pirState);
  delay(100);

  if (pirState == 1) {
    // Gerar latitude e longitude aleatórias dentro da ZEE do Brasil
    float latitude = generateRandomFloat(-34.0, 5.5);
    float longitude = generateRandomFloat(-55.0, -30.0);

    // Criar um objeto JSON
    StaticJsonDocument<200> doc;
    doc["lat"] = latitude;
    doc["long"] = longitude;
    
    // Converter o objeto JSON para uma string
    char jsonBuffer[200];
    serializeJson(doc, jsonBuffer);

    // Publicar a mensagem JSON no tópico /cav91
    client.publish("/cav91", jsonBuffer);
    Serial.println(jsonBuffer);  // Exibir a mensagem no Serial Monitor
    delay(5000);  
  }
}
