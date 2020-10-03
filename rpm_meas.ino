
uint16_t read_hall_sensor1()
{
  return analogRead(HALL_SENSOR1_PIN);
}

uint16_t read_hall_sensor2()
{
  return analogRead(HALL_SENSOR2_PIN);
}

void check_hall_sensors()
{
  uint16_t hallSensorNewValue1 = analogRead(HALL_SENSOR1_PIN);
  unsigned long newTriggerTime1 = oldTriggerTime1;
  //if (newValue < (HALL_SENSOR_STANDARD_VALUE - HALL_SENSOR_MAX_ALLWOED_DEVIATION_TO_TRIGGER) || newValue > (HALL_SENSOR_STANDARD_VALUE + HALL_SENSOR_MAX_ALLWOED_DEVIATION_TO_TRIGGER))

  if (hallSensorNewValue1 < (HALL_SENSOR_STANDARD_VALUE - HALL_SENSOR_MAX_ALLWOED_DEVIATION_TO_TRIGGER) && (millis() - periodTimeAge1) > HALL_SENSOR_DEBOUNCE_TIME )
    //if (hallSensorNewValue1 < (HALL_SENSOR_STANDARD_VALUE - HALL_SENSOR_MAX_ALLWOED_DEVIATION_TO_TRIGGER))
  {
    if (!hallSensor1IsTriggered) //this is here because the hall sensor should be "not triggered" anymore until a new detection (of a magnet) is allowed. This avoids continous triggering while the magnet is still in range of the hall sensor
    {
      hallSensor1IsTriggered = true;
      if (false)
      {
        Serial.println("Hall sensor 1 detected");
        Serial.print("hallSensorNewValue1: ");
        Serial.println(hallSensorNewValue1);
        Serial.print("HALL_SENSOR_STANDARD_VALUE - HALL_SENSOR_MAX_ALLWOED_DEVIATION_TO_TRIGGER: ");
        Serial.println(HALL_SENSOR_STANDARD_VALUE - HALL_SENSOR_MAX_ALLWOED_DEVIATION_TO_TRIGGER);
        Serial.print("HALL_SENSOR_STANDARD_VALUE + HALL_SENSOR_MAX_ALLWOED_DEVIATION_TO_TRIGGER: ");
        Serial.println(HALL_SENSOR_STANDARD_VALUE + HALL_SENSOR_MAX_ALLWOED_DEVIATION_TO_TRIGGER);
        Serial.print("periodTime1: ");
        Serial.println(periodTime1);
        Serial.print("newTriggerTime1: ");
        Serial.println(newTriggerTime1);
        Serial.print("oldTriggerTime1: ");
        Serial.println(oldTriggerTime1);
      }


      if (false)
      {
        Serial.print("oldTriggerTime1: ");
        Serial.println(oldTriggerTime1);
      }
      newTriggerTime1 = millis();
      uint32_t difference = newTriggerTime1 - oldTriggerTime1;
      if (difference < MAX_POSSIBLE_PERIODTIME)
      {
        //in case difference is greater than MAX_POSSIBLE_PERIODTIME we are in the first measurement after the rotor was detected as not moving.
        //So oldTriggerTime1 will have a value that would give us an eratic periodTime.
        //So we will use this round to update the oldTriggerTime1 only and will calculate the periodTime1 the next time the hall sensor gets triggered.
        periodTime1 = difference;
      }
      periodTimeAge1 = millis();


      //MIN_POSSBILE_FREQUENCY NUMBER_OF_MAGNETS
      if (periodTime1 >= MAX_POSSIBLE_PERIODTIME)
      {
        periodTime1 = PERIOD_TIME_TO_LOW_TO_MEASURE_VALUE;
        //Serial.println("PERIOD_TIME_TO_LOW_TO_MEASURE_VALUE triggered");
      }

      lastPeriodTimeValid1 = abs(periodTime1 - periodTimeOld1) < MAX_POSSIBLE_PERIOD_TIME_DIFFERENCE;
      if (!lastPeriodTimeValid1)
      {
        Serial.println("MAX_POSSIBLE_PERIOD_TIME_DIFFERENCE triggered");
      }

      if (false)
      {
        Serial.print("newTriggerTime1: ");
        Serial.println(newTriggerTime1);
      }

      if (true)
      {
        Serial.print("RPM1: ");
        Serial.println(rpm(1));
      Serial.print("periodTime1: ");
      Serial.println(periodTime1);
      Serial.print("lastPeriodTimeValid1: ");
      Serial.println(lastPeriodTimeValid1);
      Serial.println();
      }

    }
    periodTimeOld1 = periodTime1;
  } else
  {
    hallSensor1IsTriggered = false; //reset "hallSensor1IsTriggered" as soon as the magnet is out of range of the hall sensor
  }
  oldTriggerTime1 = newTriggerTime1;

  //reset periodTime value in case the last update of the period time is to old we need to reset it to the PERIOD_TIME_TO_LOW_TO_MEASURE_VALUE
  if ((millis() - periodTimeAge1) > PERIOD_DISCARD_TIME)
  {
    periodTime1 = PERIOD_TIME_TO_LOW_TO_MEASURE_VALUE;
    //Serial.println("reset");
  }

  hallSensorOldValue1 = hallSensorNewValue1;
}

unsigned long periodTime(uint8_t id)
{
  uint32_t periodTime = 0;
  switch (id)
  {
    case 1:
      periodTime = periodTime1;
      break;
    case 2:
      periodTime = periodTime2;
      break;
    default:
      periodTime = RPM_READING_WRONG_SELECTION_VALUE;
      break;
  }
  return periodTime;
}

float rpm(uint8_t id)
{
  float roundsPerSecond = 0;
  switch (id)
  {
    case 1:
      roundsPerSecond = (1.0 / ((float)periodTime1 / 1000.0)) / (float)NUMBER_OF_MAGNETS;
      break;
    case 2:
      roundsPerSecond = (1.0 / ((float)periodTime2 / 1000.0)) / (float)NUMBER_OF_MAGNETS;
      break;
    default:
      roundsPerSecond = RPM_READING_WRONG_SELECTION_VALUE;
      break;
  }
  if (roundsPerSecond <= MIN_POSSBILE_FREQUENCY)
  {
    roundsPerSecond = 0.0;
  } else if (roundsPerSecond >= MAX_POSSIBLE_FREQUENCY)
  {
    roundsPerSecond = RPM_READING_FAULT_VALUE;
  }
  return roundsPerSecond;

}
