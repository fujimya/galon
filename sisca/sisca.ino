#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
int buzled = 15;
#define setUrl "http://service.sekolahpintar.xyz/SET.php?ref=https://galon-bb6fe.firebaseio.com/&auth=LyvGC7jKhrLylAHGj5PViua4JqMlGtEwqZiPts5V&path=/"
#define getUrl "http://toko-kirin.pe.hu/GET.php?ref=https://gasd-b37b2.firebaseio.com/&auth=lULpek1PSZD0SZQqiUonS5M3ilQTnl4y2lUVvkU7&path=/"
String json, buz = "hidup";
static char outstr[15];

ESP8266WiFiMulti WiFiMulti;
int buzzer = 4;

int trigPin = 13; //Trig - green Jumper
int echoPin = 15; //Echo - yellow Jumper
long duration, cm, meter;


void setup() {
  //Define inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
    Serial.begin(115200);
  WiFiMulti.addAP("Brtt", "qwerty123");
  while (WiFiMulti.run() != WL_CONNECTED) {
    Serial.print("Menyambungkan.");
    delay(100);
    Serial.print(".");
    delay(100);
    Serial.print(".");
    delay(100);
    Serial.print(".");
    delay(100);
    Serial.print(".");
    delay(100);
    Serial.println(".");
    delay(100);

  }
  Serial.println("Terhubung");
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(100);
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(1000);
}


void loop() {
  getLevel();
  delay(500);
}

void getLevel(){
    // Sensor dipicu oleh pulsa HIGH dari 10us atau lebih.
  // Berikan pulsa LOW pendek terlebih dahulu untuk memastikan pulsa HIGH bersih:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Baca sinyal dari sensor: pulsa HIGH yang
  // duration adalah waktu (dalam mikrodetik) dari pengirim
  // Dari ping untuk penerimaan Echo off dari sebuah objek.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  // convert jarak kedalam cm dan meter
  cm = (duration/2) / 29.1;
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  dtostrf(cm, 9, 6, outstr);
  setData(setUrl, "galon/level", outstr);
}


//set data firebase

void setData(String ref, String path, String data)
{
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    ref += path;
    ref += "&data=";
    ref += data;
    HTTPClient http;
    http.begin(ref);
    int httpCode = http.GET();


    if (httpCode > 0) {

      if (httpCode == HTTP_CODE_OK)
      {
        digitalWrite(buzzer, HIGH);
        delay(300);
        digitalWrite(buzzer, LOW);
        delay(300);
      }
    }
    else {
      digitalWrite(buzzer, HIGH);
      delay(200);
      
      digitalWrite(buzzer, LOW);
      delay(200);
      digitalWrite(buzzer, HIGH);
      delay(100);
      digitalWrite(buzzer, LOW);
    }
    http.end();

  }
}

