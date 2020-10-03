


//== I2C addresses =====

//Watchdog
#define WATCHDOG_TIMEOUT 5000

//MCP9808 temperature sensor
#define MCP9808_MOTOR_DRIVER_ADDR 0x1A
#define MCP9808_RECITIFER_ADDR 0x19

//ADS1115 adc
#define ADS1115_BAT_VOLTAGE_ADDR 0x48 //One channel is connected to the heatsink NTC
#define ADS1115_EXTERNAL_SENSORS_ADDR 0x49
#define ADS1115_MOTOR_CURRENT_ADDR 0x4B //One channel is connected to brake 2 position slide-resistor

//INA219 voltage and current sensor
#define INA219_5V_GEN_SUPPLY_ADDR 0x42
#define INA219_LIPO1_ADDR 0x40
#define INA219_LIPO2_ADDR 0x41
#define INA219_LIPO3_ADDR 0x45

//DRV8830 motor driver
#define DRV8830_PITCH_MOTOR_ADDR 0xC0 // ID = 7 Bit=  0x60 .. (8 Bit= 0xC0)
#define DRV8830_BRAKE_RIGHT_ADDR 0xC4 //ID = 7 Bit=  0x62 .. (8 Bit= 0xC4)
#define DRV8830_BRAKE_LEFT_ADDR 0xD0 //ID = 7 Bit=  0x68 .. (8 Bit= 0xD0)

#define PITCH_MOTOR_SHUNT_VALUE 0.3 //in Ohm
#define BRAKE_RIGHT_MOTOR_SHUNT_VALUE 0.3 //in Ohm
#define BRAKE_LEFT_MOTOR_SHUNT_VALUE 0.3 //in Ohm

#define PITCH_MOTOR_MAX_CURRENT 300 //in mA
#define BRAKE_RIGHT_MOTOR_MAX_CURRENT 300 //in mA
#define BRAKE_LEFT_MOTOR_MAX_CURRENT 300 //in mA

#define PITCH_MOTOR_OC_CUTOFF_TIME 2500 //in ms. This is the time an over current situation is allowed to exist before it will be shut of
#define BRAKE_RIGHT_MOTOR_OC_CUTOFF_TIME 2600 //in ms. This is the time an over current situation is allowed to exist before it will be shut of
#define BRAKE_LEFT_MOTOR_OC_CUTOFF_TIME 2600 //in ms. This is the time an over current situation is allowed to exist before it will be shut of

//LTC4151 voltage and current sensor
#define LTC4151_GENERATOR_ADDR 0x6C

//BME280
#define BME280_ADDR 0x76
#define SEALEVELPRESSURE_HPA (1013.25)

//ADXL345
#define ADXL345_ADDR 0x53

//Pin definitions
#define ENABLE_PERIPHERAL_POWER_PIN 27
#define LOAD_RESISTOR_ENABLE_PIN 26
#define SCL_PIN 22
#define SDA_PIN 21
#define WS2812_POWER_PIN 25
#define HALL_SENSOR1_PIN 32
#define HALL_SENSOR2_PIN 33
#define PITCH_POSITION_SENSOR_PIN 35
#define ENABLE_MOTOR_POWER_PIN 13
#define BRAKE_FORCE1_PIN 36
#define BRAKE_FORCE2_PIN 39

//Hall sensor
//Note: Max measurable frequence is limited by the setting of HALL_SENSOR_DEBOUNCE_TIME. This defines how long the sensor input is ignored after it was triggered
//Note Min measureable frequency is limited by MIN_FREQUENCY
/*
  Rotation: 2
  Periodendauer: 500ms

  Am Sensor: 1
  Periodendauer: 1/1=1000ms
*/

//Critical values:
//you should be really carefull about chaging this values. In every case you should properly test it. Wrong values could lead to eratic high values.
#define NUMBER_OF_MAGNETS 2.0 //This defines the number of magnets on the rotor. It is needed to calculate the right RPM from the measured time periods

#define PERIOD_DISCARD_TIME 500 //Time after the last measured period time will be discard because its to old (in ms). So if a hall sensor does not detect a magnet within the time PERIOD_DISCARD_TIME after the last detecion the period time will be reset to PERIOD_TIME_TO_LOW_TO_MEASURE_VALUE

#define HALL_SENSOR_DEBOUNCE_TIME 20 //Typical debounce time within a new trigger of the hall sensor is not allowed to be detected(in ms). This also limits the max detectable frequency to 1/HALL_SENSOR_DEBOUNCE_TIME
#define MAX_POSSIBLE_PERIOD_TIME_DIFFERENCE (MAX_POSSIBLE_PERIODTIME*0.4) //This defines the max allowed difference of the last two values of the periodtime. This should help to avoid/detect eratic values

//Non-citical (but still important values)
#define HALL_SENSOR_STANDARD_VALUE 1850 //This is the standard measurement value if no magnet is in the range of the hall sensor
#define HALL_SENSOR_MAX_ALLWOED_DEVIATION_TO_TRIGGER 400 //This defines the amount of value change a passing magnet needs to create to trigger a detection at the hall sensor
#define MIN_POSSBILE_FREQUENCY 2.0 //in Hz. This defines the minimal frequency/rps that is possible to measure. 
#define PERIOD_TIME_TO_LOW_TO_MEASURE_VALUE 10000000 //This is the value that is allocated if the period time gets so high (defined by PERIOD_DISCARD_TIME) that it is to low to measure the period time properly.
#define MAX_POSSIBLE_FREQUENCY 1.0/(HALL_SENSOR_DEBOUNCE_TIME/1000.0) //See HALL_SENSOR_DEBOUNCE_TIME for explenation. The calculation is just here to convert the HALL_SENSOR_DEBOUNCE_TIME into a frequency.

#define RPM_READING_WRONG_SELECTION_VALUE 9999.9 //This value will be applied if a value of a non existing hall sensor is requested
#define RPM_READING_FAULT_VALUE 9998.9 //Value that is applied to the actual RPM value as soon as the RPM exceds the measuring range
#define RPM_READING_MAX_DIF_VIOLATION_VALUE 9997.9 //This value will be applied if the difference between the last two readings is exceeding MAX_POSSIBLE_RPS_DIFFERENCE

#define MAX_MAGNET_FREQUENCY (MAX_POSSIBLE_FREQUENCY*NUMBER_OF_MAGNETS)
#define MIN_MAGNET_FREQUENCY (MIN_POSSBILE_FREQUENCY*NUMBER_OF_MAGNETS)

#define MAX_POSSIBLE_PERIODTIME (1.0/MIN_MAGNET_FREQUENCY)*1000.0 //((1.0/MIN_POSSBILE_FREQUENCY)*NUMBER_OF_MAGNETS)*1000.0

#define MAX_ALLOWED_RPM 10

//Brakes
//Smaller values = brake is closer to the braking surface; Range is the possible voltage range on the ADC so: 0-5000mV
#define BRAKE_RIGHT_POSITION_OPENED_STANDARD_VALUE 4500
#define BRAKE_RIGHT_POSITION_CLOSED_STANDARD_VALUE 3300

#define BRAKE_LEFT_POSITION_OPENED_STANDARD_VALUE 4500
#define BRAKE_LEFT_POSITION_CLOSED_STANDARD_VALUE 3300

//You need to be carefull with these values: Higher value means faster driving of the motors but also higher current consumption in normal operation. So adapt over current protection value if needed!
#define BRAKE_RIGHT_CLOSING_SPEED 50
#define BRAKE_LEFT_CLOSING_SPEED 50

//Pitch actuator
#define PITCH_SENSOR_POSITION_FULL_POWER_STANDARD_VALUE 4000
#define PITCH_SENSOR_POSITION_NO_POWER_STANDARD_VALUE 500

//You need to be carefull with these values: Higher value means faster driving of the motors but also higher current consumption in normal operation. So adapt over current protection value if needed!
#define PITCH_MOTOR_INCR_POWER_SPEED 50
#define PITCH_MOTOR_DECR_POWER_SPEED 50

#define PITCH_TARGET_POWER_LEVEL_STANDARD 50 //this defines the standard power that will be sued to drive the windturbine in standard secnarios
#define PITCH_POWER_REDUCTION_FACTOR 0.8 //This defines to wich value the pitchPower will be decreased as soon as the actual rpm is greater than MAX_ALLOWED_RPM
//#define PITCH_POWER_INCREASING_FACTOR 0.8 //This defines to wich value the pitchPower will be increases as soon as the 
#define MAX_ALLOWED_PITCH_POWER_DEVIATION 5 //This value defines how much percentage the actual pitch power setting is allowed to deviate from the target pitch power setting: In case it is above this value a new adaption will be started

//Time constants
#define JOBS_PERIOD_TIME_1000MS 1000
