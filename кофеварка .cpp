Програмный код 
#include 
#include 
#include
#define 
#define 


void loop()
  {
  
const char 
const char 
WiFiServer 
 char lineBuf[80];
    int charCount = 0;
     
    void setup() {
        // запас времени на открытие монитора порта — 5 секунд
        delay(5000);
        // инициализируем контакты для светодиодов
        pinMode(RELAY, OUTPUT);
      pinMode(term ,INPUT);
      pinMode 
      


)

func main() {
	// On board LED is connected to GPIO 2
	led := machine.Pin(2)
	// Configure PIN as output
	led.Configure(machine.PinConfig{Mode: machine.PinOutput})

	// Infinite main loop
	for {
		// Turn LED off
		led.Low()
		// Wait for 1 second
		time.Sleep(time.Millisecond * 1000)
		// Turn LED on
		led.High()
		// Wait for 1 second
		time.Sleep(time.Millisecond * 1000)
	}
        pinMode(, OUTPUT);
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
           
        Serial.println(WiFi.localIP());
        server.begin();
    } 
                    void loop() {
        
        WiFiClient client = server.available();
        if (client) {
            Serial.println("New client");  //напечатать сообщение  New client 
            memset(lineBuf, 0, sizeof(lineBuf)); // установка памяти для буффера 
            charCount = 0;
            // HTTP-
            boolean currentLineIsBlank = true;
            while (client.connected()) {// когда клиент подключен 
                if (client.available()) {// если клиент в нормальном состоянии 
                    char c = client.read();//прочитать значение 
                    Serial.write(c); // записать значение 
                    
                    lineBuf[charCount] = c;
                    if (charCount < sizeof(lineBuf) - 1) {//поддержка размера буффера обмена 
                        charCount++;
                    }
                    
                    if (c == '\n' && currentLineIsBlank) {//
                        
                        client.println("HTTP/1.1 200 OK");//напечатать на стороне клиента фразу в скобках 
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
                        webPage +="  <h1>ESP32 - Web Server</h1>";//прописывается заголовок 
                        webPage +="  <p>LED #1";
                        webPage +="    <a href=\"pump_on\">";
                    
                        webPage +="      <button>PUMP_ON</button>"//создается объект кнопка 
                        webPage +="    </a>&nbsp;"; 
                        webPage +="  ;
                        webPage +=   
                        webPage +=" <script src=\"https://code.jquery.com/jquery-3.2.1.min.js\"></script>";
                        webPage +="    <a href=\"pump_off\">";
                        webPage +="      <button>PUMP_OFF</button>";
                        webPage +="    </a>";
                        webPage +="  </p>";
                        webPage +="  <p>LED #2";
                        webPage +="    <a href=\"led_on\">";
                        webPage +="      <button>LED_ON</button>";
                        webPage +="    </a>&nbsp;";
                        webPage +="    <a href=\"led_off\">";
                        webPage +="      <button>LED_OFF</button>";
                        webPage +="    </a>";
                        webPage +="  </p>";
                        webPage +="</html>";
                        client.println(webPage);
                        break;
                    }
                    if (c == '\n') {
                        // анализируем буфер на наличие запросов   // если есть запрос, меняем состояние светодиода
                        currentLineIsBlank = true;
                        if (strstr(lineBuf, "GET /pump_on") > 0) {
                            Serial.println("PUMP  ON");
                            digitalWrite(PUMP, HIGH);
                        } else if (strstr(lineBuf, "GET /pump_off") > 0) {
                            Serial.println("PUMP OFF");
                            digitalWrite(PUMP, LOW);
                        } else if (strstr(lineBuf, "GET /led_lamp on") > 0) {
                            Serial.println("LED_LAMP ON");
                            digitalWrite(LED_LAMP, HIGH);
                        } else if (strstr(lineBuf, "GET /led_lamp off") > 0) {
                            
                            Serial.println("LED_LAMP OFF");
                            digitalWrite(LED_LAMP, LOW); 
                             } else if (strstr(lineBuf, "GET /led_lamp off") > 0) { 
                              
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
