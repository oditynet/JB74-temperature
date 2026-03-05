
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <mcp2515.h>

// OLED settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

MCP2515 mcp2515_8(8);                       // Set CS to pin 8
struct can_frame canMsg;

byte Mess_3_out2 = 0;
byte Mess_3_out3 = 0;
byte Mess_3_out4 = 0;
byte Mess_3_out5 = 0;
byte Mess_2_out4 = 0;
byte Mess_1_out5 = 0;

String text_dis_1;  // Температура АКПП
String text_dis_2;  // Температура двигателя
String text_dis_3;  // Давление переднее левое?
String text_dis_4;  // Давление заднее правое?
String text_dis_5;  // Давление переднее правое?
String text_dis_6;  // Давление заднее левое?

uint16_t tmr;
void beepBuzzer(int durationMs) {
  tone(4, 2000);           // Включаем звук на частоте 2000 Гц
  delay(durationMs);       // Ждем указанное количество миллисекунд
  noTone(4);               // Выключаем звук
  digitalWrite(4, LOW);    // Для надежности
}

void setup() {
  pinMode(4, OUTPUT);                        // Set Out active buzzer pin 4
  digitalWrite(4, 0);
  
  Wire.begin();
  
  // Инициализация OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    // Если адрес 0x3C не работает, попробуйте 0x3D
    for(;;);
  }
  
  SPI.begin();
  mcp2515_8.reset();
  mcp2515_8.setBitrate(CAN_500KBPS, MCP_8MHZ);
  mcp2515_8.setConfigMode();
  mcp2515_8.setFilterMask(MCP2515::MASK0, false, 0x07FF);
  mcp2515_8.setFilter(MCP2515::RXF0, false, 0x3F6);
  mcp2515_8.setFilter(MCP2515::RXF1, false, 0x380);
  mcp2515_8.setFilterMask(MCP2515::MASK1, false, 0x07FF);
  mcp2515_8.setFilter(MCP2515::RXF2, false, 0x3E2);
  mcp2515_8.setFilter(MCP2515::RXF3, false, 0x600);
  mcp2515_8.setFilter(MCP2515::RXF4, false, 0x600);
  mcp2515_8.setFilter(MCP2515::RXF5, false, 0x600);
  mcp2515_8.setListenOnlyMode();
  
  // Приветственный экран
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(2);  // Устанавливаем размер текста 2 для всего
  
  display.setCursor(20, 10);
  display.println(F("SUZUKI"));
  display.setCursor(35, 35);
  display.println(F("JIMNY"));
  
  display.display();
  beepBuzzer(150);
  digitalWrite(4, 0);
  delay(4000);
  
  display.clearDisplay();
  display.display();
}

void loop() {
  if (mcp2515_8.readMessage(&canMsg) == MCP2515::ERROR_OK) {
    
    // --- Температура двигателя (ID 0x3F6) ---
    if (canMsg.can_id == 0x3F6) {
      Mess_2_out4 = canMsg.data[4];
      //Mess_2_out4 =30;
      text_dis_2 = String((Mess_2_out4) - 40);
      
      // Очищаем только область для температуры двигателя
      display.fillRect(0, 0, 64, 24, SSD1306_BLACK);
      
      display.setTextSize(3);
      display.setCursor(0, 0);
      //display.print(F("E:"));
      display.print(text_dis_2);
      display.write(247); // Символ градуса в библиотеке Adafruit_GFX
      
      display.display();
    }
    
    // --- Температура АКПП (ID 0x380) ---
    if (canMsg.can_id == 0x380) {
      Mess_1_out5 = canMsg.data[5];
      //Mess_1_out5=100;
      text_dis_1 = String((Mess_1_out5) - 40);
      
      // Очищаем только область для температуры АКПП
      display.fillRect(0, 24, 64, 24, SSD1306_BLACK);
      
      display.setTextSize(3);
      display.setCursor(0, 26);
      //display.print(F("T:"));
      display.print(text_dis_1);
      display.write(247);
      
      display.display();
    }
    
    // --- Давление в шинах (ID 0x3E2) ---
    if (canMsg.can_id == 0x3E2) {
      Mess_3_out2 = canMsg.data[2];
      Mess_3_out3 = canMsg.data[3];
      Mess_3_out4 = canMsg.data[4];
      Mess_3_out5 = canMsg.data[5];
    //Mess_3_out2 = 10;
    //Mess_3_out3 = 6;
    //Mess_3_out4 = 15;
    //Mess_3_out5 = 25;
      
      // Форматируем давление с одним знаком после запятой
      text_dis_5 = String((float(Mess_3_out5) * 0.014), 1);
      text_dis_4 = String((float(Mess_3_out4) * 0.014), 1);
      text_dis_3 = String((float(Mess_3_out3) * 0.014), 1);
      text_dis_6 = String((float(Mess_3_out2) * 0.014), 1);
      
      // Очищаем правую часть экрана (для давлений)
      display.fillRect(65, 0, 128, 64, SSD1306_BLACK);
      
      display.setTextSize(2);
      
      // Давление передние колеса (верх)
      display.setCursor(70, 0);
      display.print(text_dis_3);
      display.setCursor(70, 16);
      display.print(text_dis_6);
      
      // Давление задние колеса (низ)
      display.setCursor(70, 32);
      display.print(text_dis_5);
      display.setCursor(70, 48);
      display.print(text_dis_4);
      
      display.display();
    }
    
    // --- Аварийный сигнал при температуре 98°C ---
    if ((Mess_2_out4) == 138) {
      beepBuzzer(500);
      delay(1000);
    }
  }
  else 
    {
    display.fillRect(0, 0, 128, 64, SSD1306_BLACK);
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.print("CAN ERROR: ");
   // display.println(result);
    display.print("Check wiring!");

    display.setCursor(0, 16);
    display.print("Ping...");
    display.display();
    
    }
  delay(200);
}