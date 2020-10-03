void init_ina219()
{

  if(!ina219_5v_gen.init()){
    Serial.println("INA219 for 5V generator voltage measurement not found!");
  }
  
  if(!ina219_lipo2.init()){
    Serial.println("INA219 for lipo2 measurement not found!");
  }
/* Set ADC Mode for Bus and ShuntVoltage
  * Mode *            * Res / Samples *       * Conversion Time *
  BIT_MODE_9        9 Bit Resolution             84 µs
  BIT_MODE_10       10 Bit Resolution            148 µs  
  BIT_MODE_11       11 Bit Resolution            276 µs
  BIT_MODE_12       12 Bit Resolution            532 µs  (DEFAULT)
  SAMPLE_MODE_2     Mean Value 2 samples         1,06 ms
  SAMPLE_MODE_4     Mean Value 4 samples         2,13 ms
  SAMPLE_MODE_8     Mean Value 8 samples         4,26 ms
  SAMPLE_MODE_16    Mean Value 16 samples        8,51 ms     
  SAMPLE_MODE_32    Mean Value 32 samples        17,02 ms
  SAMPLE_MODE_64    Mean Value 64 samples        34,05 ms
  SAMPLE_MODE_128   Mean Value 128 samples       68,10 ms
  */
  ina219_5v_gen.setADCMode(SAMPLE_MODE_128); // choose mode and uncomment for change of default
  ina219_lipo2.setADCMode(SAMPLE_MODE_128); // choose mode and uncomment for change of default
  
  /* Set measure mode
  POWER_DOWN - INA219 switched off
  TRIGGERED  - measurement on demand
  ADC_OFF    - Analog/Digital Converter switched off
  CONTINUOUS  - Continuous measurements (DEFAULT)
  */
   ina219_5v_gen.setMeasureMode(CONTINUOUS); // choose mode and uncomment for change of default
   ina219_lipo2.setMeasureMode(TRIGGERED); // choose mode and uncomment for change of default
  
  /* Set PGain
  * Gain *  * Shunt Voltage Range *   * Max Current *
   PG_40       40 mV                    0,4 A
   PG_80       80 mV                    0,8 A
   PG_160      160 mV                   1,6 A
   PG_320      320 mV                   3,2 A (DEFAULT)
  */
  ina219_5v_gen.setPGain(PG_320); // choose gain and uncomment for change of default
  ina219_lipo2.setPGain(PG_80); // choose gain and uncomment for change of default
  
  /* Set Bus Voltage Range
   BRNG_16   -> 16 V
   BRNG_32   -> 32 V (DEFAULT)
  */
  ina219_5v_gen.setBusRange(BRNG_16); 
  ina219_lipo2.setBusRange(BRNG_16); 

  /* If the current values delivered by the INA219 differ by a constant factor
     from values obtained with calibrated equipment you can define a correction factor.
     Correction factor = current delivered from calibrated equipment / current delivered by INA219
  */
  
  ina219_5v_gen.setCorrectionFactor(1.0); 
  ina219_lipo2.setCorrectionFactor(1.0); 
  
/*
  float shuntVoltage_mV = 0.0;
  float loadVoltage_V = 0.0;
  float busVoltage_V = 0.0;
  float current_mA = 0.0;
  float power_mW = 0.0; 
  bool ina219_overflow = false;
  
  shuntVoltage_mV = ina219_5v_gen.getShuntVoltage_mV();
  busVoltage_V = ina219_5v_gen.getBusVoltage_V();
  current_mA = ina219_5v_gen.getCurrent_mA();
  power_mW = ina219_5v_gen.getBusPower();
  loadVoltage_V  = busVoltage_V + (shuntVoltage_mV/1000);
  ina219_overflow = ina219_5v_gen.getOverflow();
  
  Serial.print("Shunt Voltage [mV]: "); Serial.println(shuntVoltage_mV);
  Serial.print("Bus Voltage [V]: "); Serial.println(busVoltage_V);
  Serial.print("Load Voltage [V]: "); Serial.println(loadVoltage_V);
  Serial.print("Current[mA]: "); Serial.println(current_mA);
  Serial.print("Bus Power [mW]: "); Serial.println(power_mW);
  if(!ina219_overflow){
    Serial.println("Values OK - no overflow");
  }
  else{
    Serial.println("Overflow! Choose higher PGAIN");
  }
  Serial.println();
  */
  
}


float read_lipo2_current()
{   
  ina219_lipo2.startSingleMeasurement();
  float current_mA = ina219_lipo2.getCurrent_mA();  
  return current_mA;  
}

float read_lipo2_voltage_ina()
{  
  ina219_lipo2.startSingleMeasurement();
  float busVoltage_V = ina219_lipo2.getBusVoltage_V();
  float shuntVoltage_mV = ina219_lipo2.getShuntVoltage_mV();
  float loadVoltage_V  = busVoltage_V + (shuntVoltage_mV/1000); 
  return loadVoltage_V;  
}

float read_lipo3_current()
{   
  ina219_lipo3.startSingleMeasurement();
  float current_mA = ina219_lipo2.getCurrent_mA();  
  return current_mA;  
}

float read_lipo3_voltage_ina()
{  
  ina219_lipo3.startSingleMeasurement();
  float busVoltage_V = ina219_lipo3.getBusVoltage_V();
  float shuntVoltage_mV = ina219_lipo3.getShuntVoltage_mV();
  float loadVoltage_V  = busVoltage_V + (shuntVoltage_mV/1000); 
  return loadVoltage_V;  
}

float read_system_input_current()
{  
  float current_mA = ina219_5v_gen.getCurrent_mA();
  return current_mA;
  
}

float read_system_input_voltage()
{  
  float busVoltage_V = ina219_5v_gen.getBusVoltage_V();
  float shuntVoltage_mV = ina219_5v_gen.getShuntVoltage_mV();
  float loadVoltage_V  = busVoltage_V + (shuntVoltage_mV/1000);  
  return loadVoltage_V;
  
}
