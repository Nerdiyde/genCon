
uint16_t read_brakeRight_force()
{
  return analogRead(BRAKE_FORCE1_PIN);
}

uint16_t read_brakeLeft_force()
{
  return analogRead(BRAKE_FORCE2_PIN);
}



// == right Brake ================================================================

boolean brakeRight_is_in_position_open()
{
  return read_brakeSensorRight_voltage() >= brakeRight_position_opened;
}

boolean brakeRight_is_in_position_close()
{
  return read_brakeSensorRight_voltage() <= brakeRight_position_closed;
}

void start_closing_brake_right()
{
  if (brakeRightOpeningRunning) brakeRightOpeningRunning = false;
  brakeRightClosingRunning = true;
  send_speed_brakeRight_motor(BRAKE_RIGHT_CLOSING_SPEED);
  Serial.println("Started closing of right brake...");
}

void start_opening_brake_right()
{
  if (brakeRightClosingRunning) brakeRightClosingRunning = false;

  brakeRightOpeningRunning = true;
  send_speed_brakeRight_motor(-BRAKE_RIGHT_CLOSING_SPEED);
  Serial.println("Started opening of right brake...");
}

void check_right_brake_state()
{
  uint16_t breakPosition = read_brakeSensorRight_voltage();
  if (brakeRightClosingRunning)
  {
    if (brakeRight_is_in_position_close())
    {
      Serial.println("Right brake reached close position");
      stop_right_brake();
      stop_brakeRight_motor();
      brakeRightClosingRunning = false;
    }
    Serial.print("Closing right brake! Position: ");
    Serial.print(breakPosition);
    Serial.print("; current: ");
    Serial.println(read_brakeMotorRight_current());
  } else if (brakeRightOpeningRunning)
  {
    if (brakeRight_is_in_position_open())
    {
      Serial.println("Right brake reached open position");
      stop_right_brake();
      stop_brakeRight_motor();
      brakeRightOpeningRunning = false;
    }
    Serial.print("Opening right brake! Position: ");
    Serial.println(breakPosition);
  }
}

void stop_right_brake()
{
  if (brakeRightClosingRunning || brakeRightOpeningRunning)
  {
    brakeRightClosingRunning = false;
    brakeRightOpeningRunning = false;
  }
}

int16_t brake_position_right_closed_in_percent()
{
  return map(read_brakeSensorRight_voltage(), brakeRight_position_opened, brakeRight_position_closed, 0, 100);
}

uint16_t brake_position_right_in_mV()
{
  return read_brakeSensorRight_voltage();
}


// == left Brake ================================================================

boolean brakeLeft_is_in_position_open()
{
  return read_brakeSensorLeft_voltage() >= brakeLeft_position_opened;
}

boolean brakeLeft_is_in_position_close()
{
  return read_brakeSensorLeft_voltage() <= brakeLeft_position_closed;
}

void start_closing_brake_left()
{
  if (brakeLeftOpeningRunning) brakeLeftOpeningRunning = false;
  brakeLeftClosingRunning = true;
  send_speed_brakeLeft_motor(BRAKE_LEFT_CLOSING_SPEED);
  Serial.println("Started closing of left brake...");
}

void start_opening_brake_left()
{
  if (brakeLeftClosingRunning) brakeLeftClosingRunning = false;

  brakeLeftOpeningRunning = true;
  send_speed_brakeLeft_motor(-BRAKE_LEFT_CLOSING_SPEED);
  Serial.println("Started opening of left brake...");
}

void check_left_brake_state()
{
  uint16_t breakPosition = read_brakeSensorLeft_voltage();
  if (brakeLeftClosingRunning)
  {
    if (brakeLeft_is_in_position_close())
    {
      Serial.println("Left brake reached close position");
      stop_left_brake();
      stop_brakeLeft_motor();
      brakeLeftClosingRunning = false;
    }
    Serial.print("Closing left brake! Position: ");
    Serial.print(breakPosition);
    Serial.print("; current: ");
    Serial.println(read_brakeMotorLeft_current());
  } else if (brakeLeftOpeningRunning)
  {
    if (brakeLeft_is_in_position_open())
    {
      Serial.println("left brake reached open position");
      stop_left_brake();
      stop_brakeLeft_motor();
      brakeLeftOpeningRunning = false;
    }
    Serial.print("Opening left brake! Position: ");
    Serial.println(breakPosition);
  }
}

void stop_left_brake()
{
  if (brakeLeftClosingRunning || brakeLeftOpeningRunning)
  {
    brakeLeftClosingRunning = false;
    brakeLeftOpeningRunning = false;
  }
}
/*

#define BRAKE_RIGHT_POSITION_OPENED_STANDARD_VALUE 4500
#define BRAKE_RIGHT_POSITION_CLOSED_STANDARD_VALUE 3300

#define BRAKE_LEFT_POSITION_OPENED_STANDARD_VALUE 4500
#define BRAKE_LEFT_POSITION_CLOSED_STANDARD_VALUE 3300

read_brakeSensorLeft_voltage() >= brakeLeft_position_opened;
}

boolean brakeLeft_is_in_position_close()
{
  return read_brakeSensorLeft_voltage() <= brakeLeft_position_closed;
  */
int16_t brake_position_left_closed_in_percent()
{
  return map(read_brakeSensorLeft_voltage(), brakeLeft_position_opened, brakeLeft_position_closed, 0, 100);
}

uint16_t brake_position_left_in_mV()
{
  return read_brakeSensorLeft_voltage();
}
