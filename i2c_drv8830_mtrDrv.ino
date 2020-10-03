void init_drv8830()
{
  /*
  if (pitchMotor.begin()) {
    Serial.println("pitchMotor motor-driver was found.");    
  }  
  if (rightBrakeMotor.begin()) {
    Serial.println("rightBrake motor-driver was found.");    
  }  
  if (leftBrakeMotor.begin()) {
    Serial.println("leftBrake motor-driver was found.");    
  }  
  pitchMotor.drive(DRV8830_STANBY, 0);
  rightBrakeMotor.drive(DRV8830_STANBY, 0);
  leftBrakeMotor.drive(DRV8830_STANBY, 0);*/
  
 stop_all_motors();
  
}
