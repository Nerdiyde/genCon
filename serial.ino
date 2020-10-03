void init_serial()
{
  Serial.begin(115200);
}


void check_for_serial_receive_event()
{
  while (Serial.available())
  {
    char character = (char)Serial.read();
    if (character == 13) {
      check_serial_message(serialReceiveBuffer);
      serialReceiveBuffer = "";
    } else
    {
      serialReceiveBuffer += character;
    }
  }
}

void check_serial_message(String message)
{
  Serial.print(F("SERIAL: \""));
  Serial.print(String(message));
  Serial.println(F("\" received."));

  message.toLowerCase();
  if (message == "stopm")
  {
    stop_all_motors();
  } else if (message == "cbr")
  {
    start_closing_brake_right();
  } else if (message == "obr")
  {
    start_opening_brake_right();
  } else if (message == "cbl")
  {
    start_closing_brake_left();
  } else if (message == "obl")
  {
    start_opening_brake_left();
  } else if (message == "cb")
  {
    start_closing_brake_left();
    start_closing_brake_right();
  } else if (message == "ob")
  {
    start_opening_brake_left();
    start_opening_brake_right();
  } else if (message == "bpl") //brake position left in percent and mV
  {
    Serial.println(brake_position_left_closed_in_percent());
    Serial.println(brake_position_left_in_mV());
  } else if (message == "bpr") //brake position right in percent and mV
  {
    Serial.println(brake_position_right_closed_in_percent());
    Serial.println(brake_position_right_in_mV());
  } else if (message == "ipp")
  {
    start_incr_pitch_power();
  } else if (message == "dpp")
  {
    start_decr_pitch_power();
  } else if (message == "ppp") //pitch position in percent and mV
  {
    Serial.println(pitch_power_in_percent());
    Serial.println(pitch_position_in_mV());
  } else if (message == "gupa")
    {
      Serial.println(get_automatic_pitch_adjustment_setting());
    } else if (message.indexOf('=') != -1)
  {
    String receivedValueString = message.substring(message.indexOf('=') + 1);
    String receivedCommand = message.substring(0, message.indexOf('='));
    float receivedValue = receivedValueString.toFloat();

    if (receivedCommand == "bmr")
    {
      send_speed_brakeRight_motor(receivedValue);
    } else if (receivedCommand == "bml")
    {
      send_speed_brakeLeft_motor(receivedValue);
    } else if (receivedCommand == "pm")
    {
      send_speed_pitch_motor(receivedValue);
    } else if (receivedCommand == "sppl")
    {
      set_pitch_power_level(receivedValue);
    } else if (receivedCommand == "supa")
    {
      set_automatic_pitch_adjustment(receivedValue);
    } else
    {
      serial_command_unknown_response(message);
    }
  } else
  {
    serial_command_unknown_response(message);
  }
  message = "";
}


void serial_command_unknown_response(String message)
{

}
