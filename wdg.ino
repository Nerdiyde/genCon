
void IRAM_ATTR resetModule() {
  ets_printf("Wdg bite\n");
  esp_restart();
}

void init_wdg()
{
  watchdogTimer = timerBegin(0, 80, true);                  //timer 0, div 80
  timerAttachInterrupt(watchdogTimer, &resetModule, true);  //attach callback
  timerAlarmWrite(watchdogTimer, WATCHDOG_TIMEOUT * 1000, false); //set time in us
  timerAlarmEnable(watchdogTimer);                          //enable interrupt  
}

void feed_wdg()
{  
  timerWrite(watchdogTimer, 0); //reset timer (feed watchdog)
}
