#include <LiquidCrystal_I2C.h>
#include <OneWire.h>


LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

void setup()
{
  lcd.init();
  lcd.backlight();
  lcd.setCursor(3, 0);
  lcd.print("Termometr");
  delay(2000);
}

void loop()
{

  OneWire  ds(4); //pin to sensor
  byte i;
  byte present = 0;
  byte data[9];
  byte addr[8];
  float celsius;

  if ( !ds.search(addr))
  {
    ds.reset_search();
    delay(250);
    return;
  }

  ds.reset();
  ds.select(addr);
  ds.write(0x44, 1);

  delay(100);

  present = ds.reset();
  ds.select(addr);
  ds.write(0xBE);

  for ( i = 0; i < 9; i++)
  {
    data[i] = ds.read();
  }

  int16_t raw = (data[1] << 8) | data[0];

  byte cfg = (data[4] & 0x60);
  if (cfg == 0x00) raw = raw & ~7;
  else if (cfg == 0x20) raw = raw & ~3;
  else if (cfg == 0x40) raw = raw & ~1;


  celsius = (float)raw / 16.0;
  lcd.setCursor(0, 0);
  lcd.print("PIEC = ");
  lcd.setCursor(7, 0);
  lcd.print(celsius);
  lcd.setCursor(12, 0);
  lcd.print("*C");
  ///////////////////////////////////////////////////////////////////////////////////////

  OneWire  ds1(5); //pin to sensor
  byte j;
  byte present1 = 0;
  byte data1[9];
  byte addr1[8];
  float celsius1;

  if ( !ds1.search(addr1))
  {
    ds1.reset_search();
    delay(250);
    return;
  }

  ds1.reset();
  ds1.select(addr1);
  ds1.write(0x44, 1);

  delay(100);

  present1 = ds1.reset();
  ds1.select(addr1);
  ds1.write(0xBE);

  for ( j = 0; j < 9; j++)
  {
    data1[j] = ds1.read();
  }

  int16_t raw1 = (data1[1] << 8) | data1[0];

  byte cfg1 = (data1[4] & 0x60);
  if (cfg1 == 0x00) raw1 = raw1 & ~7;
  else if (cfg1 == 0x20) raw1 = raw1 & ~3;
  else if (cfg1 == 0x40) raw1 = raw1 & ~1;


  celsius1 = (float)raw1 / 16.0;

  lcd.setCursor(0, 1);
  lcd.print("BOJLER = ");
  lcd.setCursor(9, 1);
  lcd.print(celsius1);
  lcd.setCursor(14, 1);
  lcd.print("*C");


}
