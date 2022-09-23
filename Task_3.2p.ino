#include <BH1750FVI.h>
#include <WiFiNINA.h>
// Create the Lightsensor instance
BH1750FVI LightSensor(BH1750FVI::k_DevModeContLowRes);

char ssid[] = "SatyamRaina";
char pass[] = "bankai00";

WiFiClient client;

char   HOST_NAME[] = "maker.ifttt.com";
String PATH_NAME   = "/trigger/sunlight_in/with/key/hYj7ynNMosn9ZxBJnAgxC3ISQMmTTKL7_gye7aYoHuR"; // change your EVENT-NAME and YOUR-KEY
String queryString = "?value1=57&value2=25";


void setup() 
{
  Serial.begin(115200);
  LightSensor.begin();  

    WiFi.begin(ssid, pass);

  Serial.begin(9600);
  while (!Serial);

  // connecting web server on port 80:
  if (client.connect(HOST_NAME, 80)) {
    Serial.println("Connected to server");
  }
  else {// if not connected:
    Serial.println("connection failed");
  }
}

void loop() 
{  
  uint16_t lux = LightSensor.GetLightIntensity();
    
  Serial.print("Light: ");
  Serial.println(lux);
  
if (lux>100 && sunlight == true)
{
    client.println("GET " + PATH_NAME + queryString + " HTTP/1.1");
    client.println("Host: " + String(HOST_NAME));
    client.println("Connection: Close");
    client.println(); 


    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.print(c);
      }
    }  
    client.stop();
    Serial.println();
    Serial.println("Not connected");
    delay(10000);
  }

else if(lux<100 && sunlight == false)
{
  client.println("No sunlight output");
} 
}
