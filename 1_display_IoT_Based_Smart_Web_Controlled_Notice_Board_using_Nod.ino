#include <LiquidCrystal_I2C.h>

//#include <LiquidCrystal_PCF8574AT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

LiquidCrystal_I2C lcd1(0x27, 16, 2);
AsyncWebServer server(80);

const char* ssid = "EED_N11";  //wifi ssid name
const char* password = "eed@n11N";   //wifi password

//const char* ssid = "Redmi";  //wifi ssid name
//const char* password = "99999999";   //wifi password

//const char* ssid = "Shivam 5g";  //wifi ssid name
//const char* password = "Patak123@";   //wifi password

String message1;

String inputParam1;


const char* PARAM_INPUT_1 = "input1";


const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>Smart Notice Board</title>
  <meta name="viewport" content="width=device-width, initial-scale=5">
<p> <font size="9" face="sans-serif"> <marquee> Web Controlled Smart Notice Board </marquee> </font> </p>
  </head><body><center>
  <form action="/get">
    Enter the Text to Display1: <input type="text" name="input1">
         <br>    <br>    <br>
     <input type="submit" value="Send">
  </form><br>

</center></body></html>)rawliteral";

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

void setup()
{
  Serial.begin(115200);
  Wire.begin();
  //lcd1.begin();
  //lcd1.init();
  lcd1.init();
  lcd1.backlight();
  lcd1.clear();
  lcd1.setCursor(0, 0);
  lcd1.print("IoT Notice Board");

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi Failed!");
    return;
  }
  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/html", index_html);
  });

  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest * request) {

    if (request->hasParam(PARAM_INPUT_1)) {
      message1 = request->getParam(PARAM_INPUT_1)->value();

      inputParam1 = PARAM_INPUT_1;

      lcd1.setCursor(0, 1);
      lcd1.print("Msg - ");
      lcd1.print(message1);


    }
    else {
      message1 = "No message sent";
      inputParam1 = "none";

    }

    Serial.println(message1);


    request->send(200, "text/html", index_html);
  });
  server.onNotFound(notFound);
  server.begin();
}

void loop()
{
//  for (int positionCounter = 0; positionCounter < 16; positionCounter++)
//    {
//    lcd1.scrollDisplayLeft();
//    delay(1000);
//    }


}




/*#include <ESP8266WiFi.h>
  #include <ESPAsyncTCP.h>
  #include <ESPAsyncWebServer.h>
  #include <LiquidCrystal.h>
  LiquidCrystal lcd(D0, D1, D2, D3, D4, D5);
  AsyncWebServer server(80);
  const char* ssid = "EED_N11";  //wifi ssid
  const char* password = "[eed@n11N]";   //wifi password
  const char* PARAM_INPUT_1 = "input1";
  const char index_html[] PROGMEM = R"rawliteral(
  <!DOCTYPE HTML><html><head>
  <title>Smart Notice Board</title>
  <meta name="viewport" content="width=device-width, initial-scale=5">
  <p> <font size="9" face="sans-serif"> <marquee> Smart Notice Board </marquee> </font> </p>
  </head><body><center>
  <form action="/get">
    Enter Text to Display: <input type="text" name="input1">
    <input type="submit" value="Send">
  </form><br>

  </center></body></html>)rawliteral";

  void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
  }

  void setup()
  {
  Serial.begin(115200);
   lcd.begin(16, 2);
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print("Smart Notice Board");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi Failed!");
    return;
  }
  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String message;
    String inputParam;
    if (request->hasParam(PARAM_INPUT_1)) {
      message = request->getParam(PARAM_INPUT_1)->value();
      inputParam = PARAM_INPUT_1;
       lcd.clear();
       lcd.setCursor(0,0);

      lcd.print(message);
    }
    else {
      message = "No message sent";
      inputParam = "none";
    }
    Serial.println(message);

  request->send(200, "text/html", index_html);
  });
  server.onNotFound(notFound);
  server.begin();
  }

  void loop()
  {
    for (int positionCounter = 0; positionCounter < 29; positionCounter++)
    {
      lcd.scrollDisplayLeft();
      delay(500);
    }
  }*/
