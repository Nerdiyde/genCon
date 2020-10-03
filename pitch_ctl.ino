
uint16_t read_pitch_sensor()
{
  return analogRead(PITCH_POSITION_SENSOR_PIN);
}

boolean pitch_is_in_position_full_power()
{
  return read_pitch_sensor() >= pitchSensor_position_fullPower;
}

boolean pitch_is_in_position_no_power()
{
  return read_pitch_sensor() <= pitchSensor_position_noPower;
}

void start_incr_pitch_power()
{
  if (pitchPowerDecrRunning) pitchPowerDecrRunning = false;
  pitchPowerIncrRunning = true;
  send_speed_pitch_motor(PITCH_MOTOR_INCR_POWER_SPEED);
  Serial.println("Started increasing pitch power...");
}

void start_decr_pitch_power()
{
  if (pitchPowerIncrRunning) pitchPowerIncrRunning = false;
  pitchPowerDecrRunning = true;
  send_speed_pitch_motor(-PITCH_MOTOR_DECR_POWER_SPEED);
  Serial.println("Started decreasing pitch power...");
}

void check_pitch_state()
{
  uint16_t pitchPosition = read_pitch_sensor();
  if (pitchPowerDecrRunning)
  {
    Serial.print("Decreasing pitch power: ");
    Serial.print(pitchPosition);
    Serial.print("; current: ");
    Serial.print(read_pitchMotor_current());
    Serial.print("; percent: ");
    Serial.println(pitch_power_in_percent());
    if (pitch_is_in_position_no_power())
    {
      Serial.println("Pitch reached \"no power\" position.");
      stop_pitch_movement();
      stop_pitch_motor();
    }
  } else if (pitchPowerIncrRunning)
  {
    Serial.print("Increasing pitch power! Position: ");
    Serial.print(pitchPosition);
    Serial.print("; current: ");
    Serial.print(read_pitchMotor_current());
    Serial.print("; percent: ");
    Serial.println(pitch_power_in_percent());
    if (pitch_is_in_position_full_power())
    {
      Serial.println("Pitch reached \"full power\" position.");
      stop_pitch_movement();
      stop_pitch_motor();
    }
  }

  if (pitchPowerIncrRunning && pitch_power_in_percent() >= pitchTargetPowerLevel)
  {
    Serial.print("Pitch power increased to target position:");
    Serial.print(pitchTargetPowerLevel);
    Serial.print("; actual position: ");
    Serial.println(pitch_power_in_percent());
    stop_pitch_movement();
    stop_pitch_motor();

  } else if (pitchPowerDecrRunning && pitch_power_in_percent() <= pitchTargetPowerLevel)
  {
    Serial.print("Pitch power decreased to target position:");
    Serial.print(pitchTargetPowerLevel);
    Serial.print("; actual position: ");
    Serial.println(pitch_power_in_percent());
    stop_pitch_movement();
    stop_pitch_motor();
  }
}

void stop_pitch_movement()
{
  if (pitchPowerDecrRunning || pitchPowerIncrRunning)
  {
    pitchPowerDecrRunning = false;
    pitchPowerIncrRunning = false;
  }
}


boolean pitch_movement_running()
{
  return pitchPowerDecrRunning || pitchPowerIncrRunning;
}

int16_t pitch_power_in_percent()
{

  return map(read_pitch_sensor(), pitchSensor_position_noPower, pitchSensor_position_fullPower, 0, 100);
}

uint16_t pitch_position_in_mV()
{
  return read_pitch_sensor();
}

void set_pitch_power_level(int16_t targetPowerLevel)
{
  pitchTargetPowerLevel = targetPowerLevel;
  Serial.print("Will set pitch power target to:");
  Serial.println(pitchTargetPowerLevel);
  uint16_t actualPitchPower = pitch_power_in_percent();
  if (actualPitchPower < targetPowerLevel)
  {
    if (!pitchPowerIncrRunning)
    {
      start_incr_pitch_power();
    }
  } else if (actualPitchPower > targetPowerLevel)
  {
    if (!pitchPowerDecrRunning)
    {
      start_decr_pitch_power();
    }
  }
}

void set_automatic_pitch_adjustment(boolean state)
{
  automaticPitchAdjustActivated = state;
}

boolean get_automatic_pitch_adjustment_setting()
{
  return automaticPitchAdjustActivated;
}

void check_pitch_needs_adaption()
{ //this function should set the pitch in dependence on the rotation speed
  if (get_automatic_pitch_adjustment_setting())
  {
    int16_t pitchPowerDeviation = abs(pitch_power_in_percent() - pitchTargetPowerLevel);
    uint16_t actualRpm = rpm(1);

    if (actualRpm >= MAX_ALLOWED_RPM && !pitch_movement_running())
    { //We need to reduce the pitchpower if RPM of the rotor is to high
      Serial.print("Actual RPM is higher than MAX_ALLOWED_RPM at: ");
      Serial.print(actualRpm);
      Serial.println("; will start decreasing pitch power.");
      set_pitch_power_level(pitchTargetPowerLevel * PITCH_POWER_REDUCTION_FACTOR);
    } else if (actualRpm <= MIN_POSSBILE_FREQUENCY && !pitch_movement_running() && (pitchPowerDeviation>MAX_ALLOWED_PITCH_POWER_DEVIATION))
    {
      Serial.print("Actual RPM is <= than MIN_POSSBILE_FREQUENCY at: ");
      Serial.print(actualRpm);
      Serial.println("; will start incrreasing pitch power.");
      set_pitch_power_level(PITCH_TARGET_POWER_LEVEL_STANDARD);
    } else if ((pitchPowerDeviation>MAX_ALLOWED_PITCH_POWER_DEVIATION) && !pitch_movement_running())
    {
      Serial.print("Actual pitch power deviation is higher than MAX_ALLOWED_PITCH_POWER_DEVIATION at: ");
      Serial.print(pitchPowerDeviation);
      Serial.println("; will start adaption.");
      set_pitch_power_level(pitchTargetPowerLevel);
    }
  }

}
