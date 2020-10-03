

void send_speed_pitch_motor(int16_t speedSetting)
{
  motor_pitch.drive(speedSetting);  
  Serial.print("Speed set to pitchMotor: ");
  Serial.println(speedSetting);
  delay(1000);
}

void stop_all_motors()
{
  stop_pitch_motor();
  stop_brakeRight_motor();
  stop_brakeLeft_motor();
}

void stop_pitch_motor()
{
  send_speed_pitch_motor(0);  
  stop_pitch_movement();
}

void send_speed_brakeRight_motor(int16_t speedSetting)
{
  motor_brake_right.drive(speedSetting);  
  Serial.print("Speed set to brakeRightMotor: ");
  Serial.println(speedSetting);
}

void stop_brakeRight_motor()
{
  send_speed_brakeRight_motor(0);  
  stop_right_brake();
}


void send_speed_brakeLeft_motor(int16_t speedSetting)
{
  motor_brake_left.drive(speedSetting);  
  Serial.print("Speed set to brakeLeftMotor: ");
  Serial.println(speedSetting);
}

void stop_brakeLeft_motor()
{
  send_speed_brakeLeft_motor(0);
  stop_left_brake();  
}

float read_pitchMotor_current()
{
  return (read_pitchMotor_shunt_voltage()/(float)PITCH_MOTOR_SHUNT_VALUE);
}

float read_brakeMotorLeft_current()
{
  return (read_brakeMotorLeft_shunt_voltage()/(float)BRAKE_LEFT_MOTOR_SHUNT_VALUE);
}

float read_brakeMotorRight_current()
{
  return (read_brakeMotorRight_shunt_voltage()/(float)BRAKE_RIGHT_MOTOR_SHUNT_VALUE);
}

/*
#define PITCH_MOTOR_OC_CUTOFF_TIME 5000 //in ms. This is the time an over current situation is allowed to exist before it will be shut of
#define BRAKE_MOTOR_RIGHT_MOTOR_OC_CUTOFF_TIME 5000 //in ms. This is the time an over current situation is allowed to exist before it will be shut of
#define BRAKE_MOTOR_LEFT_MOTOR_OC_CUTOFF_TIME 5000 //in ms. This is the time an over current situation is allowed to exist before it will be shut of
*/

boolean check_pitchMotor_blocking()
{
  float current=read_pitchMotor_current();
  boolean ocDetected=current>=PITCH_MOTOR_MAX_CURRENT;
  uint32_t nowTimestamp=millis();
  
  if (ocDetected && pitchMotorOcDetectedTime==0)
  { //over current is detected for the first time
    pitchMotorOcDetectedTime=nowTimestamp;
    Serial.print("PitchMotor OC detected: ");
    Serial.println(current);
  } else if (ocDetected && pitchMotorOcDetectedTime!=0 && (nowTimestamp-pitchMotorOcDetectedTime)>=PITCH_MOTOR_OC_CUTOFF_TIME)
  { //over current is detected and cut off time is exceeded
    stop_pitch_motor();
    pitchMotorOcDetectedTime=0;
    Serial.print("PitchMotor deactivated due to OCP: ");
    Serial.println(current);
  } else if (pitchMotorOcDetectedTime!=0 && !ocDetected && (nowTimestamp-pitchMotorOcDetectedTime)>=PITCH_MOTOR_OC_CUTOFF_TIME)
  { //over current gone and cut off time is exceeded so we can reset the oc detection time
    pitchMotorOcDetectedTime=0;
    Serial.println("PitchMotor detection time resetted.");
  }
  return ocDetected;
}

boolean check_BrakeMotorRight_blocking()
{
  float current=read_brakeMotorRight_current();
  boolean ocDetected=current>=BRAKE_RIGHT_MOTOR_MAX_CURRENT;
  uint32_t nowTimestamp=millis();
  
  if (ocDetected && rightBrakeMotorOcDetectedTime==0)
  { //over current is detected for the first time
    rightBrakeMotorOcDetectedTime=nowTimestamp;
    Serial.print("rightBrakeMotor OC detected: ");
    Serial.println(current);
  } else if (ocDetected &&  rightBrakeMotorOcDetectedTime!=0 && (nowTimestamp-rightBrakeMotorOcDetectedTime)>=BRAKE_RIGHT_MOTOR_OC_CUTOFF_TIME)
  { //over current is detected and cut off time is exceeded
    stop_brakeRight_motor();
    rightBrakeMotorOcDetectedTime=0;
    Serial.print("rightBrakeMotor deactivated due to OCP: ");
    Serial.println(current);
  } else if (rightBrakeMotorOcDetectedTime!=0 && !ocDetected && (nowTimestamp-rightBrakeMotorOcDetectedTime)>=BRAKE_RIGHT_MOTOR_OC_CUTOFF_TIME)
  { //over current gone and cut off time is exceeded so we can reset the oc detection time
    rightBrakeMotorOcDetectedTime=0;
    Serial.println("rightBrakeMotor detection time resetted.");
  }
  return ocDetected;
}


boolean check_BrakeMotorLeft_blocking()
{
  float current=read_brakeMotorLeft_current();
  boolean ocDetected=current>=BRAKE_LEFT_MOTOR_MAX_CURRENT;
  uint32_t nowTimestamp=millis();
  
  if (ocDetected && leftBrakeMotorOcDetectedTime==0)
  { //over current is detected for the first time
    leftBrakeMotorOcDetectedTime=nowTimestamp;
    Serial.print("leftBrakeMotor OC detected: ");
    Serial.println(current);
  } else if (ocDetected && leftBrakeMotorOcDetectedTime!=0 && (nowTimestamp-leftBrakeMotorOcDetectedTime)>=BRAKE_LEFT_MOTOR_OC_CUTOFF_TIME)
  { //over current is detected and cut off time is exceeded
    stop_brakeLeft_motor();
    leftBrakeMotorOcDetectedTime=0;
    Serial.print("leftBrakeMotor deactivated due to OCP: ");
    Serial.println(current);
  } else if (leftBrakeMotorOcDetectedTime!=0 && !ocDetected && (nowTimestamp-leftBrakeMotorOcDetectedTime)>=BRAKE_LEFT_MOTOR_OC_CUTOFF_TIME)
  { //over current gone and cut off time is exceeded so we can reset the oc detection time
    leftBrakeMotorOcDetectedTime=0;
    Serial.println("leftBrakeMotor detection time resetted.");
  }
  return ocDetected;
}
