void init_ads1115()
{

  //Channels of ADS1115_BAT_VOLTAGE_ADDR:
  //Channel 0: Bat1 plus
  //Channel 1: Bat2 plus
  //Channel 2: Bat3 plus
  //Channel 3: Bat4 plus

  ADS1115_WE adc_bat_voltage(ADS1115_BAT_VOLTAGE_ADDR);
  ADS1115_WE adc_external_sensors(ADS1115_EXTERNAL_SENSORS_ADDR);
  ADS1115_WE adc_motor_current(ADS1115_MOTOR_CURRENT_ADDR);

#define ADS1115_BAT_VOLTAGE_ADDR 0x48 //One channel is connected to the heatsink NTC
#define ADS1115_EXTERNAL_SENSORS_ADDR 0x49
#define ADS1115_MOTOR_CURRENT_ADDR 0x4B //One channel is connected to brake 2 position slide-resistor

  if (!adc_bat_voltage.init()) {
    Serial.println("ADS1115 for bat-voltage measurement not found!");
  }

  if (!adc_external_sensors.init()) {
    Serial.println("ADS1115 for external sensors measurement not found!");
  }

  if (!adc_motor_current.init()) {
    Serial.println("ADS1115 for motor current measurement not found!");
  }

  adc_bat_voltage.reset();
  adc_external_sensors.reset();
  adc_motor_current.reset();

  //Set the voltage range of the ADC to adjust the gain
  adc_bat_voltage.setVoltageRange_mV(ADS1115_RANGE_6144);
  adc_external_sensors.setVoltageRange_mV(ADS1115_RANGE_6144);
  adc_motor_current.setVoltageRange_mV(ADS1115_RANGE_6144);

  //disable the comporater since we dont use it
  adc_bat_voltage.setAlertPinMode(ADS1115_DISABLE_ALERT); //uncomment if you want to change the default
  adc_external_sensors.setAlertPinMode(ADS1115_DISABLE_ALERT); //uncomment if you want to change the default
  adc_motor_current.setAlertPinMode(ADS1115_DISABLE_ALERT); //uncomment if you want to change the default

  //Set the conversion rate in SPS (samples per second)
  adc_bat_voltage.setConvRate(ADS1115_860_SPS);
  adc_external_sensors.setConvRate(ADS1115_860_SPS);
  adc_motor_current.setConvRate(ADS1115_860_SPS);

  //Enable or disable latch.Since we dont use this it will be disabled.
  adc_bat_voltage.setAlertLatch(ADS1115_LATCH_DISABLED);
  adc_external_sensors.setAlertLatch(ADS1115_LATCH_DISABLED);
  adc_motor_current.setAlertLatch(ADS1115_LATCH_DISABLED);

  //Set continuous or single shot mode:
  adc_bat_voltage.setMeasureMode(ADS1115_SINGLE);
  adc_external_sensors.setMeasureMode(ADS1115_SINGLE);
  adc_motor_current.setMeasureMode(ADS1115_SINGLE);

}

float read_lipo1_voltage()
{
  adc_bat_voltage.setVoltageRange_mV(ADS1115_RANGE_6144);
  adc_bat_voltage.setCompareChannels(ADS1115_COMP_0_GND);
  adc_bat_voltage.startSingleMeasurement();
  while(adc_bat_voltage.isBusy()){}
  return adc_bat_voltage.getResult_mV();
}

float read_lipo2_voltage()
{
  adc_bat_voltage.setVoltageRange_mV(ADS1115_RANGE_6144);
  adc_bat_voltage.setCompareChannels(ADS1115_COMP_1_GND);
  adc_bat_voltage.startSingleMeasurement();
  while(adc_bat_voltage.isBusy()){}
  return adc_bat_voltage.getResult_mV();
}

float read_lipo3_voltage()
{
  adc_bat_voltage.setVoltageRange_mV(ADS1115_RANGE_6144);
  adc_bat_voltage.setCompareChannels(ADS1115_COMP_2_GND);
  adc_bat_voltage.startSingleMeasurement();
  while(adc_bat_voltage.isBusy()){}
  return adc_bat_voltage.getResult_mV();
}

float read_heatsink_voltage()
{
  adc_bat_voltage.setVoltageRange_mV(ADS1115_RANGE_6144);
  adc_bat_voltage.setCompareChannels(ADS1115_COMP_3_GND);
  adc_bat_voltage.startSingleMeasurement();
  while(adc_bat_voltage.isBusy()){}
  return adc_bat_voltage.getResult_mV();
}

float read_ntc1_voltage()
{
  adc_external_sensors.setVoltageRange_mV(ADS1115_RANGE_6144);
  adc_external_sensors.setCompareChannels(ADS1115_COMP_0_GND);
  adc_external_sensors.startSingleMeasurement();
  while(adc_external_sensors.isBusy()){}
  return adc_external_sensors.getResult_mV();
}

float read_ntc2_voltage()
{
  adc_external_sensors.setVoltageRange_mV(ADS1115_RANGE_6144);
  adc_external_sensors.setCompareChannels(ADS1115_COMP_1_GND);
  adc_external_sensors.startSingleMeasurement();
  while(adc_external_sensors.isBusy()){}
  return adc_external_sensors.getResult_mV();
}

float read_ntc3_voltage()
{
  adc_external_sensors.setVoltageRange_mV(ADS1115_RANGE_6144);
  adc_external_sensors.setCompareChannels(ADS1115_COMP_2_GND);  
  adc_external_sensors.startSingleMeasurement();
  while(adc_external_sensors.isBusy()){}
  return adc_external_sensors.getResult_mV();
}

float read_brakeSensorRight_voltage()
{
  adc_external_sensors.setVoltageRange_mV(ADS1115_RANGE_6144);
  adc_external_sensors.setCompareChannels(ADS1115_COMP_3_GND);
  adc_external_sensors.startSingleMeasurement();
  while(adc_external_sensors.isBusy()){}
  return adc_external_sensors.getResult_mV();
}

float read_brakeSensorLeft_voltage()
{
  adc_motor_current.setVoltageRange_mV(ADS1115_RANGE_6144);
  adc_motor_current.setCompareChannels(ADS1115_COMP_3_GND);
  adc_motor_current.startSingleMeasurement();
  while(adc_motor_current.isBusy()){}
  return adc_motor_current.getResult_mV();
}

float read_brakeMotorLeft_shunt_voltage()
{
  adc_motor_current.setVoltageRange_mV(ADS1115_RANGE_6144);
  adc_motor_current.setCompareChannels(ADS1115_COMP_0_GND);
  adc_motor_current.startSingleMeasurement();
  while(adc_motor_current.isBusy()){}
  return adc_motor_current.getResult_mV();
}

float read_brakeMotorRight_shunt_voltage()
{
  adc_motor_current.setVoltageRange_mV(ADS1115_RANGE_6144);
  adc_motor_current.setCompareChannels(ADS1115_COMP_1_GND);
  adc_motor_current.startSingleMeasurement();
  while(adc_motor_current.isBusy()){}
  return adc_motor_current.getResult_mV();
}

float read_pitchMotor_shunt_voltage()
{
  adc_motor_current.setVoltageRange_mV(ADS1115_RANGE_6144);
  adc_motor_current.setCompareChannels(ADS1115_COMP_2_GND); 
  adc_motor_current.startSingleMeasurement();
  while(adc_motor_current.isBusy()){}
  return adc_motor_current.getResult_mV();
}
