#include <DHT.h>
#include <DHT_U.h>
#include <U8g2lib.h>

#define DHTPIN 16
#define DHTTYPE DHT22

/* ----------------------------------------------------------------------------------------------------- */

// Definicion de constructores y variables globales

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

/* ----------------------------------------------------------------------------------------------------- */
void  printBMP_OLED(void );

float h;
float t;
float hic;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
  u8g2.begin();
  dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  dhctRead();
  printBMP_OLED();
    delay(2000);
}

void dhctRead(){
  h = dht.readHumidity();
  t = dht.readTemperature();

  hic = dht.computeHeatIndex(t, h, false);
  Serial.print(hic);
  Serial.print(F("°C "));
}

void printBMP_OLED(void)
{
	  u8g2.clearBuffer();          // clear the internal memory
    u8g2.setFont(u8g2_font_ncenB10_tr); // choose a suitable font
    
    u8g2.drawStr(10,30, '%f', hic);  // write something to the internal memory
    
    u8g2.sendBuffer();          // transfer internal memory to the display


}
