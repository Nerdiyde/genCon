void init_mcp9808()
{
  if (!pcb_temp_mtrDrvr.begin(MCP9808_MOTOR_DRIVER_ADDR)) {
    Serial.println("Couldn't find MCP9808 at motor driver!");
  }
  
  if (!pcb_temp_rctfr.begin(MCP9808_RECITIFER_ADDR)) {
    Serial.println("Couldn't find MCP9808 at recitifier!");
  }

  
  pcb_temp_mtrDrvr.setResolution(3);
  pcb_temp_rctfr.setResolution(3);
  // Mode Resolution SampleTime
  //  0    0.5°C       30 ms
  //  1    0.25°C      65 ms
  //  2    0.125°C     130 ms
  //  3    0.0625°C    250 ms

  
  pcb_temp_mtrDrvr.wake();
  pcb_temp_rctfr.wake();

  // Read and print out the temperature, also shows the resolution mode used for reading.
  //Serial.print("Resolution in mode: ");
  //Serial.println (tempsensor.getResolution());
  //float c = tempsensor.readTempC();
  //float f = tempsensor.readTempF();
  Serial.print("Temp mtrDrvr: "); 
  Serial.print(pcb_temp_mtrDrvr.readTempC(), 4); 
  Serial.println("°C");
  Serial.print("Temp rctfr: "); 
  Serial.print(pcb_temp_rctfr.readTempC(), 4); 
  Serial.println("°C");
  //Serial.print(f, 4); Serial.println("*F.");
  
  //delay(2000);
  //Serial.println("Shutdown MCP9808.... ");
  //tempsensor.shutdown_wake(1); // shutdown MSP9808 - power consumption ~0.1 mikro Ampere, stops temperature sampling
  //Serial.println("");
  //delay(200);
  
}

float read_mtrDrv_temp()
{
  return pcb_temp_mtrDrvr.readTempC();
}

float read_recitifier_temp()
{
  return pcb_temp_rctfr.readTempC();
}
