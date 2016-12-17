#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    leftLineFollower, sensorLineFollower)
#pragma config(Sensor, in2,    centerLineFollower, sensorLineFollower)
#pragma config(Sensor, in3,    rightLineFollower, sensorLineFollower)
#pragma config(Sensor, in6,    gyro,           sensorGyro)
#pragma config(Sensor, dgtl1,  piston1,        sensorDigitalOut)
#pragma config(Sensor, dgtl2,  piston2,        sensorDigitalOut)
#pragma config(Sensor, dgtl3,  limitbas,       sensorDigitalIn)
#pragma config(Sensor, dgtl4,  llimithaut,     sensorDigitalIn)
#pragma config(Sensor, I2C_1,  rightIME,       sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_2,  leftIME,        sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_3,  armIME,         sensorNone)
#pragma config(Motor,  port1,           baseArrGauche, tmotorVex393_HBridge, openLoop, reversed, driveLeft)
#pragma config(Motor,  port2,           baseAvGauche,  tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_2)
#pragma config(Motor,  port3,           ElevAvGauche,  tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           ElevArrGauche, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           PelleDroite,   tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           PelleGauche,   tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           ElevArrDroit,  tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           ElevAvDroit,   tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           baseAvdroit,   tmotorVex393_MC29, openLoop, encoderPort, I2C_1)
#pragma config(Motor,  port10,          baseArrDroit,  tmotorVex393_HBridge, openLoop, driveRight)
#pragma platform(VEX)
//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////

void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
  // Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
  bStopTasksBetweenModes = true;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task autonomous()
{
  // .....................................................................................
  // Insert user code here.
  // .....................................................................................
	setMultipleMotors(75, baseAvdroit, baseArrDroit, baseAvGauche, baseArrGauche);
	sleep(15000);
	stopMultipleMotors(baseAvdroit, baseArrDroit, baseAvGauche, baseArrGauche);
//	AutonomousCodePlaceholderForTesting();  // Remove this function call once you have "real" code.
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task usercontrol()
{
	repeat (forever) {
		joystickControl(baseAvdroit, Ch2, 10);
		joystickControl(baseArrDroit, Ch2, 10);
		joystickControl(baseAvGauche, Ch3, 10);
		joystickControl(baseArrGauche, Ch3, 10);

		armControl(PelleDroite, Btn6U, Btn6D, 75);
		armControl(PelleGauche, Btn6U, Btn6D, 75);
		if (vexRT[Btn5U] == 1) {
			if (vexRT[Btn5D] == 0) {
				if (SensorValue[llimithaut] == 1) {
					setMultipleMotors(75, ElevArrGauche, ElevAvGauche, ElevAvDroit, ElevArrDroit);
				} else {
					stopMultipleMotors(ElevAvGauche, ElevArrGauche, ElevArrDroit, ElevAvDroit);
				}
			} else {
				stopMultipleMotors(ElevAvDroit, ElevArrDroit, ElevArrGauche, ElevAvGauche);
			}
		} else {
		}
		if (vexRT[Btn5D] == 1) {
			if (vexRT[Btn5U] == 0) {
				if (SensorValue[limitbas] == 1) {
					setMultipleMotors(-75, ElevAvDroit, ElevArrDroit, ElevArrGauche, ElevAvGauche);
				} else {
					stopMultipleMotors(ElevAvDroit, ElevArrDroit, ElevArrGauche, ElevAvGauche);
				}
			} else {
				stopMultipleMotors(ElevAvDroit, ElevArrDroit, ElevArrGauche, ElevAvGauche);
			}
		} else {
		}
		if (vexRT[Btn5D] == 0) {
			if (vexRT[Btn5U] == 0) {
				stopMultipleMotors(ElevArrGauche, ElevAvDroit, ElevAvGauche, ElevArrDroit);
			}
		}
		if (vexRT[Btn8D] == 1)
    {
      SensorValue[piston1]= 1; //activer les pistons
			SensorValue[piston2]= 1;
			time1[timer1]=0;//remetttre a 0 le compteur de temps
    }
    //si le temps est plus grand que un quart de seconde,desactive les pistons
    if (time1[timer1]>250)
    {
    	SensorValue[piston2]= 0;
    	SensorValue[piston1]= 0;
    }





	} // fin de boucle

}
