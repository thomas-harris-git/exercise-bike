#include "OLED_Driver.h"
#include "OLED_GUI.h"
#include "DEV_Config.h"
#include "Show_Lib.h"
#include "Debug.h"
#include "dtostrf.h"

int wheel_sensor = 0;
int button = 0;
bool Timer = false;
bool start_low = true;
float circumference = 0.00058564235; //in miles 
float circumference_metre = 0.9425;
float distance = 0.0;
float distance_in_sec = 0;
float Speed = 0.0;
unsigned long currentMillis = 0;
unsigned long previousMillis = 0;
unsigned long elapsedMillis = 0;
unsigned long duration = 1000;
char SpeedChar[5];
char DistanceChar[5];

extern OLED_DIS sOLED_DIS;

void setup()
{
  pinMode(2,INPUT);
  pinMode(3,INPUT);
   
  System_Init();

  OLED_SCAN_DIR OLED_ScanDir = SCAN_DIR_DFT;
  OLED_Init( OLED_ScanDir );

  OLED_ClearBuf();
  OLED_ClearScreen(OLED_BACKGROUND);

  GUI_DrawLine(0, 8, sOLED_DIS.OLED_Dis_Column - 1, 8, WHITE, LINE_SOLID , DOT_PIXEL_DFT);
  OLED_DisPage(0, 0);
  OLED_DisPage(0, 7);
  OLED_ClearBuf();

  GUI_DisString_EN(7, 2, "Distance(Miles):", &Font12, FONT_BACKGROUND, WHITE);
  OLED_DisPage(0, 3);
  OLED_ClearBuf();

  GUI_DisString_EN(7, 2, "Speed(m/s):", &Font12, FONT_BACKGROUND, WHITE);
  OLED_DisPage(0, 5);
  OLED_ClearBuf();

  dtostrf(distance, 5, 1, DistanceChar);
  GUI_DisString_EN(7, 2, DistanceChar, &Font12, FONT_BACKGROUND, WHITE);
  OLED_DisPage(0, 4);
  OLED_ClearBuf();

  dtostrf(Speed, 5, 1, SpeedChar);
  GUI_DisString_EN(7, 2, SpeedChar, &Font12, FONT_BACKGROUND, WHITE);
  OLED_DisPage(0, 6);
  OLED_ClearBuf();

  uint8_t sec = 0;
  DEV_TIME sDev_time;
  sDev_time.Hour = 00;
  sDev_time.Min = 00;
  sDev_time.Sec = 00;

  OLED_ClearBuf();
  GUI_Showtime(28, 0, 100, 24, &sDev_time, WHITE);
  OLED_Display(0, 22, 128, 22 + 16);

  wheel_sensor = digitalRead(2);
  if (wheel_sensor == LOW){
    start_low = true;
  }else{
    start_low = false;
  }
}

void Timer_Func() {
  uint8_t sec = 0;
  DEV_TIME sDev_time;
  sDev_time.Hour = 00;
  sDev_time.Min = 00;
  sDev_time.Sec = 00;
  previousMillis = currentMillis;  // reset for the next cycle

  while(Timer == true){

    currentMillis = millis(); // capture the current time
    elapsedMillis = currentMillis - previousMillis;
    if (elapsedMillis >=duration){ 
      
      previousMillis = currentMillis;  // reset for the next cycle
      Speed = distance_in_sec;
      distance_in_sec = 0;
      
      sec++;
      sDev_time.Sec = sec;
      if (sec == 60) {
        sDev_time.Min = sDev_time.Min + 1;
        sec = 0;
        if (sDev_time.Min == 60) {
          sDev_time.Hour =  sDev_time.Hour + 1;
          sDev_time.Min = 0;
          if (sDev_time.Hour == 24) {
            sDev_time.Hour = 0;
            sDev_time.Min = 0;
            sDev_time.Sec = 0;
          }
        }
      }
      
      OLED_ClearBuf();
      GUI_Showtime(28, 0, 100, 24, &sDev_time, WHITE);
      OLED_Display(0, 22, 128, 22 + 16);
    
      OLED_ClearBuf();
  
      dtostrf(distance, 5, 1, DistanceChar);
      GUI_DisString_EN(7, 2, DistanceChar, &Font12, FONT_BACKGROUND, WHITE);
      OLED_DisPage(0, 4);
      OLED_ClearBuf();
  
      dtostrf(Speed, 5, 1, SpeedChar);
      GUI_DisString_EN(7, 2, SpeedChar, &Font12, FONT_BACKGROUND, WHITE);
      OLED_DisPage(0, 6);
      OLED_ClearBuf();
    }
    
    wheel_sensor = digitalRead(2);
    if (wheel_sensor == HIGH){
      while (wheel_sensor == HIGH){
        wheel_sensor = digitalRead(2);
        currentMillis = millis(); // capture the current time
        elapsedMillis = currentMillis - previousMillis;
        if (elapsedMillis >=duration){ 
          
          previousMillis = currentMillis;  // reset for the next cycle
          Speed = distance_in_sec;
          distance_in_sec = 0;
          
          sec++;
          sDev_time.Sec = sec;
          if (sec == 60) {
            sDev_time.Min = sDev_time.Min + 1;
            sec = 0;
            if (sDev_time.Min == 60) {
              sDev_time.Hour =  sDev_time.Hour + 1;
              sDev_time.Min = 0;
              if (sDev_time.Hour == 24) {
                sDev_time.Hour = 0;
                sDev_time.Min = 0;
                sDev_time.Sec = 0;
              }
            }
          }
          
          OLED_ClearBuf();
          GUI_Showtime(28, 0, 100, 24, &sDev_time, WHITE);
          OLED_Display(0, 22, 128, 22 + 16);
        
          OLED_ClearBuf();
      
          dtostrf(distance, 5, 1, DistanceChar);
          GUI_DisString_EN(7, 2, DistanceChar, &Font12, FONT_BACKGROUND, WHITE);
          OLED_DisPage(0, 4);
          OLED_ClearBuf();
      
          dtostrf(Speed, 5, 1, SpeedChar);
          GUI_DisString_EN(7, 2, SpeedChar, &Font12, FONT_BACKGROUND, WHITE);
          OLED_DisPage(0, 6);
          OLED_ClearBuf();
        }
      button = digitalRead(3);
      if (button == HIGH){
        sDev_time.Hour = 00;
        sDev_time.Min = 00;
        sDev_time.Sec = 00;
        wheel_sensor = digitalRead(2);
        if (wheel_sensor == LOW){
          start_low = true;
          }else{
            start_low = false;
          }
          Timer = false;
          distance = 0;
          Speed = 0;
          distance_in_sec = 0;
          sec = 0;
  
          OLED_ClearBuf();
          GUI_Showtime(28, 0, 100, 24, &sDev_time, WHITE);
          OLED_Display(0, 22, 128, 22 + 16);
        
          OLED_ClearBuf();
      
          dtostrf(distance, 5, 1, DistanceChar);
          GUI_DisString_EN(7, 2, DistanceChar, &Font12, FONT_BACKGROUND, WHITE);
          OLED_DisPage(0, 4);
          OLED_ClearBuf();
      
          dtostrf(Speed, 5, 1, SpeedChar);
          GUI_DisString_EN(7, 2, SpeedChar, &Font12, FONT_BACKGROUND, WHITE);
          OLED_DisPage(0, 6);
          OLED_ClearBuf();
          
          break;
      }
      }
      distance = distance + circumference;
      distance_in_sec = distance_in_sec + circumference_metre;
    }

    button = digitalRead(3);
    if (button == HIGH){
      sDev_time.Hour = 00;
      sDev_time.Min = 00;
      sDev_time.Sec = 00;
      wheel_sensor = digitalRead(2);
      if (wheel_sensor == LOW){
        start_low = true;
        }else{
          start_low = false;
        }
        Timer = false;
        distance = 0;
        Speed = 0;
        distance_in_sec = 0;

        OLED_ClearBuf();
        GUI_Showtime(28, 0, 100, 24, &sDev_time, WHITE);
        OLED_Display(0, 22, 128, 22 + 16);
      
        OLED_ClearBuf();
    
        dtostrf(distance, 5, 1, DistanceChar);
        GUI_DisString_EN(7, 2, DistanceChar, &Font12, FONT_BACKGROUND, WHITE);
        OLED_DisPage(0, 4);
        OLED_ClearBuf();
    
        dtostrf(Speed, 5, 1, SpeedChar);
        GUI_DisString_EN(7, 2, SpeedChar, &Font12, FONT_BACKGROUND, WHITE);
        OLED_DisPage(0, 6);
        OLED_ClearBuf();
    }
}
}

void loop()
{  
  wheel_sensor = digitalRead(2);

  if (wheel_sensor == HIGH and start_low == true){
    Timer = true;
  }
  if (wheel_sensor == LOW and start_low == false){
    Timer = true;
  }
  if (Timer == true){
    Timer_Func();
  }
}
