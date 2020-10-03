void init_adc()
{

  pinMode(HALL_SENSOR1_PIN, INPUT);
  pinMode(HALL_SENSOR2_PIN, INPUT);
  pinMode(PITCH_POSITION_SENSOR_PIN, INPUT);
  adcAttachPin(HALL_SENSOR1_PIN);
  adcAttachPin(HALL_SENSOR2_PIN);
  adcAttachPin(PITCH_POSITION_SENSOR_PIN);
  adcStart(HALL_SENSOR1_PIN);
  adcStart(HALL_SENSOR2_PIN);
  adcStart(PITCH_POSITION_SENSOR_PIN);
  analogReadResolution(12); // Default of 12 is not very linear. Recommended to use 10 or 11 depending on needed resolution.
  analogSetAttenuation(ADC_11db); // Default is 11db which is very noisy. Recommended to use 2.5 or 6.

  adcStart(HALL_SENSOR1_PIN);
  adcStart(HALL_SENSOR2_PIN);
  adcStart(PITCH_POSITION_SENSOR_PIN);  

}
