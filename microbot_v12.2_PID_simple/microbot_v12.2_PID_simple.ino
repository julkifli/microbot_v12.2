// MiCROBOT V12.2
// by Julkifli Awang Besar
// PID code for MiCROBOT Hikari with MiCROBOT PCB chassis

//edit bye neo

// use thelatest QTRSensors Library version 4.0
// install from arduino library manager, search for "QTRSensors" and the version is 4.0
#include <QTRSensors.h>

#define BUTTON 12
#define REMOTE_BUTTON 2 // Jsumo micro start module
#define BUZZER 10
#define LED 13
#define LEFT_MOTOR_PWM 5
#define LEFT_MOTOR_IN1 9
#define LEFT_MOTOR_IN2 4
#define RIGHT_MOTOR_PWM 6
#define RIGHT_MOTOR_IN1 7
#define RIGHT_MOTOR_IN2 8
#define NUM_SENSORS 8
#define NUM_OF_SAMPLES_PER_SENSOR 4
#define TIMEOUT 2500
#define EMITTER_PIN 11

// initialize sensor object
QTRSensors qtr;

// tuning parameters
const float KP = 0.028;  
const float KD = 4;
const float KI = 0; // increment in small value.. probably no need for line following
unsigned int left_base_speed = 70; // base speed for left motor, increase for faster robot but need to re-tune PID(depends).
unsigned int right_base_speed = 70; // base speed for right motor, increase for faster robot but need to re-tune PID(depends).
// end of tuning

// global variables
int current_error = 0;
int previous_error = 0;
int proportional = 0;
int integral = 0;
int derivative = 0;
int adjustment = 0;
int left_motor_speed = 0; 
int right_motor_speed = 0;
unsigned int center_position = ((NUM_SENSORS - 1) * 1000) / 2;
unsigned int current_position = 0;
unsigned int sensor_values[NUM_SENSORS];

void setup()
{   
    // QTRsensors configuration
    qtr.setTypeAnalog();
    qtr.setSensorPins((const unsigned char []) { A6, A0, A1, A2, A3, A4, A5, A7 }, NUM_SENSORS);
    qtr.setSamplesPerSensor(NUM_OF_SAMPLES_PER_SENSOR);
    qtr.setEmitterPin(EMITTER_PIN);
    qtr.setTimeout(TIMEOUT);
    // end QTRSensors configuration

    // pins configuration
    pinMode(LEFT_MOTOR_IN1, OUTPUT);
    pinMode(LEFT_MOTOR_IN2, OUTPUT);
    pinMode(LEFT_MOTOR_PWM, OUTPUT);
    pinMode(RIGHT_MOTOR_IN1, OUTPUT);
    pinMode(RIGHT_MOTOR_IN2, OUTPUT);
    pinMode(RIGHT_MOTOR_PWM, OUTPUT);
    pinMode(LED, OUTPUT);
    pinMode(BUZZER, OUTPUT);
    pinMode(BUTTON, INPUT);
    // end pins configuration
    
    // double beep
    tone(BUZZER, 1000, 100);
    delay(200);
    tone(BUZZER, 1000, 100);
    
    // sensor calibration
    while (!digitalRead(BUTTON));    // wait for button press
    delay(500);
    digitalWrite(LED_BUILTIN, HIGH); // turn on Arduino's LED to indicate we are in calibration mode
    for (int i = 0; i < 250; i++)
    {
        qtr.calibrate();
    }
    delay(500);
    tone(BUZZER, 1000, 100);
    digitalWrite(13, LOW);  // LED off, calibration done.
    // end sensor calibration

    while (!digitalRead(BUTTON));    // wait for button press
    delay(1500);    // delay for 1.5 sec before robot start moving
}

void loop() 
{
    // check for robot position
    current_position = qtr.readLineBlack(sensor_values);    // if the line is white, use qtr.readLineWhite(sensors_values)
    
    // calculate the error
    current_error = current_position - center_position;
    previous_error = current_error;

    // PID calculation
    proportional = current_error;
    integral = integral + current_error;
    derivative = current_error - previous_error;
    adjustment = (KP * proportional) + (KD * derivative) + (KI * integral);

    // set up motor speed + adjustment
    left_motor_speed = left_base_speed - adjustment; 
    right_motor_speed = right_base_speed + adjustment;

    // constrain speed value to 0 - 255
    left_motor_speed = constrain(left_motor_speed, 0, 255); 
    right_motor_speed = constrain(right_motor_speed, 0, 255);

    // send output to left motor
    digitalWrite(LEFT_MOTOR_IN1, LOW);  // if motor is reversed, change to digitalWrite(RIGHT_MOTOR_IN1, HIGH);
    digitalWrite(LEFT_MOTOR_IN2, HIGH); // if motor is reversed, change to digitalWrite(RIGHT_MOTOR_IN1, LOW);
    analogWrite(LEFT_MOTOR_PWM, left_motor_speed);
    
    // send output to right motor
    digitalWrite(RIGHT_MOTOR_IN1, HIGH); // if motor is reversed, change to digitalWrite(RIGHT_MOTOR_IN1, LOW);
    digitalWrite(RIGHT_MOTOR_IN2, LOW); // if motor is reversed, change to digitalWrite(RIGHT_MOTOR_IN1, HIGH);
    analogWrite(RIGHT_MOTOR_PWM, right_motor_speed);
}
