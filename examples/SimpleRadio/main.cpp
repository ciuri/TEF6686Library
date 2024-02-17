#include <Arduino.h>
#include <TEF6686.h>

TEF6686 tef;
unsigned long lastRDSTime;

void setup()
{
  Serial.begin(9600);
  tef.Init(21, 22, 100000); //SDA pin = 22 , SCL pin = 23, i2c freq = 100000
  tef.Audio_Set_Mute(0); // disable mute
  tef.Tune_To(tef.MODULE_FM, 10360); // tune FM to 103,6
}

void loop()
{
  if (millis() - 50 > lastRDSTime) 
  {
    tef.UpdateRDSStatus(); // should be called at least every 87ms
    tef.UpdateQualityStatus();
    Serial.printf("Freq: %i.%i, MS: %i, TA: %i, PTY: %s, PS: %s,  RT: %s, Quality: %i\n", tef.Currentfreq / 100, tef.Currentfreq % 100, tef.rdsData.ms, tef.rdsData.ta, ptyLabels[tef.rdsData.pty], tef.rdsData.psText, tef.rdsData.rtText, tef.quality);
    lastRDSTime = millis();
  }
}
