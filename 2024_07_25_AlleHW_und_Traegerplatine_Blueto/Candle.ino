// Candlelight Simulation ,wird aktiviert bei Auflegen der Modifikationskarte Schlummermodus.
// Angepasste Version des AZ-Delivery BLOGS "Stimmungslaterne".

#ifdef CandleLight
void SimulateFire (bool On, int FireSquence)
{
  if (On)
  {
    long nowmilli = millis();
    if (nowmilli - lastTimeCandle >= intervalCandle)
    {
      byte LightValue[LED_COUNT * 3];
      byte FireColor = 60;
      intervalCandle = random(150, 200);
      lastTimeCandle = nowmilli;
      FireColor = 60; //random(0,50);
      for (int i = 0; i < LED_COUNT; i++)
      { // For each pixel...
        LightValue[i * 3] = random(240, 255); // 250
        LightValue[i * 3 + 1] = random(30, 60); // 50
        LightValue[i * 3 + 2] = 0;
      }
      // Switch some lights darker
      byte LightsOff  = random(0, 4);
      for (int i = 0; i < LightsOff; i++)
      {
        byte Selected = random(LED_COUNT);
        LightValue[Selected * 3] = random(50, 60);
        LightValue[Selected * 3 + 1] = random(5, 10);
        LightValue[Selected * 3 + 2] = 0;
      }
      for (int i = 0; i < LED_COUNT; i++)
      { // For each pixel...
        strip.setPixelColor(i, strip.Color(LightValue[i * 3], LightValue[i * 3 + 1], LightValue[i * 3 + 2]));
        strip.show();   // Send the updated pixel colors to the hardware.
      }
    }
  }
  else
  {
    for (int i = 0; i < LED_COUNT; i++)
    { // For each pixel...
      strip.setPixelColor(i, strip.Color(0, 0, 0));
      strip.show();   // Send the updated pixel colors to the hardware.
    }
  }
}
#endif