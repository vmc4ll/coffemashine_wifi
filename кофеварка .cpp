#include 
    // подключяем библиотеку для работы с Wi-Fi server
    #include <WiFi.h>
    // указываем пины, к которым подключены светодиоды
    #define LED_GREEN 16
    #define LED_RED   17
    // вводим имя и пароль точки доступа
    const char* ssid     = "WIFINAME";
    const char* password = "WIFIPASSWORD";
    // инициализируем сервер на 80 порте
    WiFiServer server(80);
    // создаем буфер и счетчик для буфера
    char lineBuf[80];
    int charCount = 0;
     
    void setup() {
        // запас времени на открытие монитора порта — 5 секунд
        delay(5000);
        // инициализируем контакты для светодиодов
        pinMode(LED_GREEN, OUTPUT);
        pinMode(LED_RED, OUTPUT);
        // инициализируем монитор порта
        Serial.begin(115200);
        // подключаемся к Wi-Fi сети
        Serial.println();
        Serial.println();
        Serial.print("Connecting to ");  
        Serial.println(ssid);
        WiFi.begin(ssid, password);
        while(WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
        }
        Serial.println("");
        Serial.println("Wi-Fi connected");  
        Serial.println("IP-address: "); 
        // пишем IP-адрес в монитор порта   
        Serial.println(WiFi.localIP());
        server.begin();
    }
     
    void loop() {
        // анализируем канал связи на наличие входящих клиентов
        WiFiClient client = server.available();
        if (client) {
            Serial.println("New client");  
            memset(lineBuf, 0, sizeof(lineBuf));
            charCount = 0;
            // HTTP-запрос заканчивается пустой строкой
            boolean currentLineIsBlank = true;
            while (client.connected()) {
                if (client.available()) {
                    char c = client.read();
                    Serial.write(c);
                    // считываем HTTP-запрос
                    lineBuf[charCount] = c;
                    if (charCount < sizeof(lineBuf) - 1) {
                        charCount++;
                    }
                    // на символ конца строки отправляем ответ
                    if (c == '\n' && currentLineIsBlank) {
                        // отправляем стандартный заголовок HTTP-ответа
                        client.println("HTTP/1.1 200 OK");
                        client.println("Content-Type: text/html");
                        // тип контента: text/html
                        client.println("Connection: close");
                        // после отправки ответа связь будет отключена
                        client.println();
                        // формируем веб-страницу 
                        String webPage = "<!DOCTYPE HTML>";
                        webPage +="<html>";
                        webPage +="  <head>";
                        webPage +="    <meta name=\"viewport\" content=\"width=device-width,";
                        webPage +="    initial-scale=1\">";
                        webPage +="  </head>";
                        webPage +="  <h1>ESP32 - Web Server</h1>";
                        webPage +="  <p>LED #1";
                        webPage +="    <a href=\"on1\">";
                        webPage +="      <button>ON</button>";
                        webPage +="    </a>&nbsp;";
                        webPage +="    <a href=\"off1\">";
                        webPage +="      <button>OFF</button>";
                        webPage +="    </a>";
                        webPage +="  </p>";
                        webPage +="  <p>LED #2";
                        webPage +="    <a href=\"on2\">";
                        webPage +="      <button>ON</button>";
                        webPage +="    </a>&nbsp;";
                        webPage +="    <a href=\"off2\">";
                        webPage +="      <button>OFF</button>";
                        webPage +="    </a>";
                        webPage +="  </p>";
                        webPage +="</html>";
                        client.println(webPage);
                        break;
                    }
                    if (c == '\n') {
                        // анализируем буфер на наличие запросов 
                        // если есть запрос, меняем состояние светодиода
                        currentLineIsBlank = true;
                        if (strstr(lineBuf, "GET /on1") > 0) {
                            Serial.println("LED 1 ON");
                            digitalWrite(LED_GREEN, HIGH);
                        } else if (strstr(lineBuf, "GET /off1") > 0) {
                            Serial.println("LED 1 OFF");
                            digitalWrite(LED_GREEN, LOW);
                        } else if (strstr(lineBuf, "GET /on2") > 0) {
                            Serial.println("LED 2 ON");
                            digitalWrite(LED_RED, HIGH);
                        } else if (strstr(lineBuf, "GET /off2") > 0) {
                            Serial.println("LED 2 OFF");
                            digitalWrite(LED_RED, LOW);
                        }
                        // начинаем новую строку
                        currentLineIsBlank = true;
                        memset(lineBuf, 0, sizeof(lineBuf));
                        charCount = 0;
                    } else if (c != '\r') {
                        // в строке попался новый символ
                        currentLineIsBlank = false;
                    }
                }
            }
            // даем веб-браузеру время, чтобы получить данные
            delay(1);
            // закрываем соединение
            client.stop();
            Serial.println("client disconnected"); 
        }
    }


#define sensorPower1 7 //иницилизация пинов датчиков уровня 
#define SENSOR_1 A0 //иницилизация входов датчиков уровня 
#define l
int val = 0; / Переменная для хранения значения уровня воды

#define PIN_RELAY 10//инициализация пинов реле
void setup() {
pinMode(RElAY_1 ,OUTPUT);//инициализадия выходов реле 
pinMode(SENSOR_1,INPUT);//инициализация входов 

void loop 
int level = readSensor();

  Serial.print("Water level: ");// получить показания из функции b hfcgtxfnfnm
  Serial.println(level);

  delay(1000);
}

// Данная функция используется для получения показаний
int readSensor() 
{
  digitalWrite(SENSOR_1, HIGH);  // Включить датчик
  delay(10);                        // Ждать 10 миллисекунд
  int val = analogRead(sensorPin);  // Прочитать аналоговое значение от датчика
  if (val>10)                      //Если уровень выше 10 то запустить реле 
  DigitalWrite(RELAY_1 HIGH)
  digitalWrite(SENSOR_1, LOW);   // Выключить датчик
  return val;                       // Вернуть текущее показание
}int level = readSensor();

  Serial.print("Water level: ");
  Serial.println(level);

  delay(1000);
}

