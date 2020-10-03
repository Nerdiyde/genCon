

//#undef __SAMD21__
//#undef __SAMD51__



//General
#include "config.h"
#include <Wire.h>

//Watchdog
#include "esp_system.h"
hw_timer_t *watchdogTimer = NULL;

//For MCP9808 temperature sensor
#include "Adafruit_MCP9808.h"
Adafruit_MCP9808 pcb_temp_mtrDrvr = Adafruit_MCP9808();
Adafruit_MCP9808 pcb_temp_rctfr = Adafruit_MCP9808();

//For ADS1115 ADC
#include<ADS1115_WE.h>
ADS1115_WE adc_bat_voltage(ADS1115_BAT_VOLTAGE_ADDR);
ADS1115_WE adc_external_sensors(ADS1115_EXTERNAL_SENSORS_ADDR);
ADS1115_WE adc_motor_current(ADS1115_MOTOR_CURRENT_ADDR);

//For DRV8830 motor driver
/*
  #include "FaBoMotor_DRV8830.h"
  FaBoMotor pitchMotor(DRV8830_PITCH_MOTOR_ADDR);
  FaBoMotor rightBrakeMotor(DRV8830_BRAKE_RIGHT_ADDR);
  FaBoMotor leftBrakeMotor(DRV8830_BRAKE_LEFT_ADDR);
*/

#include <SparkFunMiniMoto.h>
MiniMoto motor_pitch(DRV8830_PITCH_MOTOR_ADDR);
MiniMoto motor_brake_left(DRV8830_BRAKE_LEFT_ADDR);
MiniMoto motor_brake_right(DRV8830_BRAKE_RIGHT_ADDR);


//For INA219 voltage and current sensor
#include <INA219_WE.h>
INA219_WE ina219_5v_gen(INA219_5V_GEN_SUPPLY_ADDR);
INA219_WE ina219_lipo1(INA219_LIPO1_ADDR);
INA219_WE ina219_lipo2(INA219_LIPO2_ADDR);
INA219_WE ina219_lipo3(INA219_LIPO3_ADDR);

//LTC4151 voltage and current sensor
#include <LTC4151.h>
LTC4151 ltc4151_recitifier_input;

//BME280 climate sensor
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
Adafruit_BME280 bme_clima; // I2C

//ADX345 acceleration sensor
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
Adafruit_ADXL345_Unified adxl345_accel = Adafruit_ADXL345_Unified(1);

//Serial
String serialReceiveBuffer;

//RPM detection/Hall sensors
unsigned long oldTriggerTime1 = 0;
unsigned long oldTriggerTime2 = 0;
int32_t periodTime1 = PERIOD_TIME_TO_LOW_TO_MEASURE_VALUE;
int32_t periodTime2 = PERIOD_TIME_TO_LOW_TO_MEASURE_VALUE;
int32_t periodTimeOld1 = PERIOD_TIME_TO_LOW_TO_MEASURE_VALUE;
int32_t periodTimeOld2 = PERIOD_TIME_TO_LOW_TO_MEASURE_VALUE;
boolean lastPeriodTimeValid1 = true;
uint32_t periodTimeAge1 = 10000000;
uint16_t hallSensorOldValue1 = 0;
boolean hallSensor1IsTriggered = false;

//brakes
int16_t brakeRight_position_closed = BRAKE_RIGHT_POSITION_CLOSED_STANDARD_VALUE;
int16_t brakeRight_position_opened = BRAKE_RIGHT_POSITION_OPENED_STANDARD_VALUE;
boolean brakeRightOpeningRunning = false;
boolean brakeRightClosingRunning = false;

int16_t brakeLeft_position_closed = BRAKE_LEFT_POSITION_CLOSED_STANDARD_VALUE;
int16_t brakeLeft_position_opened = BRAKE_LEFT_POSITION_OPENED_STANDARD_VALUE;
boolean brakeLeftOpeningRunning = false;
boolean brakeLeftClosingRunning = false;

//pitch actuator
int16_t pitchSensor_position_fullPower = PITCH_SENSOR_POSITION_FULL_POWER_STANDARD_VALUE;
int16_t pitchSensor_position_noPower = PITCH_SENSOR_POSITION_NO_POWER_STANDARD_VALUE;
boolean pitchPowerIncrRunning = false;
boolean pitchPowerDecrRunning = false;
int16_t pitchTargetPowerLevel = PITCH_TARGET_POWER_LEVEL_STANDARD;
boolean automaticPitchAdjustActivated = true;

//Jobs
uint32_t JobsLastExecution1000ms = 0;

//motors
uint32_t pitchMotorOcDetectedTime = 0;
uint32_t rightBrakeMotorOcDetectedTime = 0;
uint16_t leftBrakeMotorOcDetectedTime = 0;

void setup()
{
  init_gpios();
  enable_motor_power();
  enable_peripheral_power();
  init_serial();
  init_mcp9808();
  init_ads1115();
  init_drv8830();
  init_ltc4151();
  init_ina219();
  init_bme280();
  init_adxl345();
  init_adc();
  init_wdg();
  /*
    Serial.print("Bat1: ");
    Serial.println(read_bat_voltage(1));
    Serial.print("Bat2: ");
    Serial.println(read_bat_voltage(2));
    Serial.print("Bat3: ");
    Serial.println(read_bat_voltage(3));
  */

}



void loop()
{
  //Important jobs section starting here! ============================================

  //petting the watchdog
  feed_wdg();

  //serial
  check_for_serial_receive_event();

  //hall sensors
  check_hall_sensors();

  //brake stuff
  check_right_brake_state();
  check_left_brake_state();

  //pitch setting stuff
  check_pitch_state();

  //motor stuff
  check_pitchMotor_blocking();
  check_BrakeMotorRight_blocking();
  check_BrakeMotorLeft_blocking();

  //Important jobs section ending here! ============================================


  //Execute once per second

  //drive_motor();
  /*
    Serial.print("pm_current=");
    Serial.print(read_pitchMotor_current());
    Serial.print("; bml_current=");
    Serial.print(read_brakeMotorLeft_current());
    Serial.print("; bmr_current=");
    Serial.print(read_brakeMotorRight_current());
    Serial.println();
  */


  /*
    Serial.print("pitch motor current:");
    Serial.println(read_pitchMotor_current());

    Serial.print("right motor current:");
    Serial.println(read_rightMotor_current());

    Serial.print("left motor current:");
    Serial.println(read_leftMotor_current());
  */

  //read_accelleration_values();
  if (regular_execution(&JobsLastExecution1000ms, JOBS_PERIOD_TIME_1000MS))
  {
    Serial.println("===========================================================");
    check_pitch_needs_adaption();
      Serial.print("RPM1: ");
      Serial.println(rpm(1));
    //Serial.println(read_hall_sensor1());
    //Serial.println(read_hall_sensor2());
    //Serial.println(read_brakeRight_force());
    //Serial.println(read_brakeLeft_force());
    /*
      Serial.print("periodTime1: ");
      Serial.println(periodTime(1));
      Serial.print("periodTime2: ");
      Serial.println(periodTime(2));

      Serial.print("RPM1: ");
      Serial.println(rpm(1));
      Serial.print("RPM2: ");
      Serial.println(rpm(2));
    */

    /*
      Serial.print("System voltage:");
      Serial.println(read_system_input_voltage());

      Serial.print("System current:");
      Serial.println(read_system_input_current());

      Serial.print("lipo2 current:");
      Serial.println(read_lipo2_current());

      Serial.print("lipo2 voltage (ina):");
      Serial.println(read_lipo2_voltage_ina());

      Serial.print("lipo 2 voltage:");
      Serial.println(read_lipo2_voltage());

      Serial.print("lipo 3 current:");
      Serial.println(read_lipo3_current());

      Serial.print("lipo 3 voltage (ina):");
      Serial.println(read_lipo3_voltage_ina());

      Serial.print("lipo 3 voltage:");
      Serial.println(read_lipo3_voltage());

      Serial.print("recetifier temp:");
      Serial.println(read_recitifier_temp());

      Serial.print("motor driver temp:");
      Serial.println(read_mtrDrv_temp());

      read_recitifier_data();
    */
    /*
        Serial.print("brakeRight position voltage:");
        Serial.println(read_brakeSensorLeft_voltage());

        Serial.print("brakeLeft position voltage:");
        Serial.println(read_brakeSensorRight_voltage());
    */
    /*
      Serial.print("pitch position voltage:");
      Serial.println(read_pitch_sensor());
    */

    /*
      Serial.print("ntc1 voltage:");
      Serial.println(read_ntc1_voltage());

      Serial.print("ntc2 voltage:");
      Serial.println(read_ntc2_voltage());

      Serial.print("ntc3 voltage:");
      Serial.println(read_ntc3_voltage());


      Serial.print("right motor current:");
      Serial.println(read_rightMotor_current());

      Serial.print("left motor current:");
      Serial.println(read_leftMotor_current());

      Serial.print("pitch motor current:");
      Serial.println(read_pitchMotor_current());

      Serial.print("lipo 1 voltage:");
      Serial.println(read_lipo1_voltage());


      Serial.print("lipo 3 voltage:");
      Serial.println(read_lipo3_voltage());

      Serial.print("heatsink voltage:");
      Serial.println(read_heatsink_voltage());

      //Serial.print("Battery voltage (ads):");
      //Serial.println(read_bat_voltage(2));
    */
    Serial.println();
  }



}
