#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVO_MIN 102
#define SERVO_MAX 512

#define BASE_SERVO      0
#define SHOULDER_SERVO  1
#define ELBOW_SERVO     2
#define WRIST_SERVO     3
#define ROTATE_SERVO    4
#define GRIPPER_SERVO   5

String serialData = "";

int baseAngle = 90;
int shoulderAngle = 90;
int elbowAngle = 90;
int wristAngle = 90;
int rotateAngle = 90;
int gripperAngle = 30;

uint16_t angleToPulse(int angle)
{
  return map(angle, 0, 180, SERVO_MIN, SERVO_MAX);
}

void moveServo(uint8_t channel, int angle)
{
  angle = constrain(angle, 0, 180);
  pwm.setPWM(channel, 0, angleToPulse(angle));
}

void updateArm()
{
  moveServo(BASE_SERVO, baseAngle);
  moveServo(SHOULDER_SERVO, shoulderAngle);
  moveServo(ELBOW_SERVO, elbowAngle);
  moveServo(WRIST_SERVO, wristAngle);
  moveServo(ROTATE_SERVO, rotateAngle);
  moveServo(GRIPPER_SERVO, gripperAngle);
}

void parseAngles(String data)
{
  int values[6];

  int index = 0;
  char *token;

  char buffer[100];
  data.toCharArray(buffer, 100);

  token = strtok(buffer, ",");

  while (token != NULL && index < 6)
  {
    values[index++] = atoi(token);
    token = strtok(NULL, ",");
  }

  if (index == 6)
  {
    baseAngle = values[0];
    shoulderAngle = values[1];
    elbowAngle = values[2];
    wristAngle = values[3];
    rotateAngle = values[4];
    gripperAngle = values[5];

    updateArm();
  }
}

void setup()
{
  Serial.begin(115200);

  pwm.begin();
  pwm.setPWMFreq(50);

  delay(500);

  updateArm();

  Serial.println("ROBOTIC ARM READY");
}

void loop()
{
  while (Serial.available())
  {
    char c = Serial.read();

    if (c == '\n')
    {
      parseAngles(serialData);
      serialData = "";
    }
    else
    {
      serialData += c;
    }
  }
}