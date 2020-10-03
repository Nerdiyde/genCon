
void init_gpios()
{
  pinMode(ENABLE_PERIPHERAL_POWER_PIN, OUTPUT);
  pinMode(ENABLE_MOTOR_POWER_PIN, OUTPUT);
}
 
void enable_peripheral_power()
{
  digitalWrite(ENABLE_PERIPHERAL_POWER_PIN, HIGH);
}

void disable_peripheral_power()
{
  digitalWrite(ENABLE_PERIPHERAL_POWER_PIN, LOW);
}

void enable_motor_power()
{
  digitalWrite(ENABLE_MOTOR_POWER_PIN, HIGH);
}
