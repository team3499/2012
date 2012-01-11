#include "main.h"

class Robot : public SimpleRobot
{
	RobotDrive robotDrive; // robot drive system
	LS leftLight;		//optical light reflective thingy sensors(left)
	LS middleLight;		//optical light reflective thingy sensors(middle)
	LS rightLight;		//optical light reflective thingy sensors(right)
	Joystick driJ; // joystick1
	Joystick accJ; //joystick2
	ArmPivot armPivot;//the arm pivot
	ArmRaise armRaise;//the elevator raise/lower
	Claw claw;//claw
	

public:
	Robot(void):
		robotDrive(1, 2),	// these must be initialized in the same order
		leftLight(7),  //light on left
		middleLight(8),  //light in middle
		rightLight(9),  //light on right
		driJ(1),		// as they are declared above.
		accJ(2),			//port numbers(here)
		armPivot(3),	//armpivot port
		armRaise(1,2),    //DIGITAL O ports 1 and 2
		claw(9)    //port number
	{
		robotDrive.SetExpiration(0.1);
	}

	/**
	 * Drive left & right motors for 2 seconds then stop
	 */
	void Autonomous(void)
	{
		robotDrive.SetSafetyEnabled(false);
		bool lastLit[3];//1=left,2middle,3=right. 0=none
		lastLit[0]=1;
		bool Lit[3];
		int state = 0;
		while(IsAutonomous() && state == 0){
		Lit[0]=0;//NOT USED
		Lit[1]=leftLight.Get();
		Lit[2]=middleLight.Get();
		Lit[3]=rightLight.Get();
		if(Lit[1]==0){//left
		 if(Lit[2]==0){//middle
		  if(Lit[3]==0){//right
			if(lastLit[0] == 1 && lastLit[1] == 0 && lastLit[2]==0 && lastLit[3] == 0){
				float rad=0.5;
				robotDrive.TankDrive(1.0,rad);
				while(!leftLight.Get() && !middleLight.Get() && !rightLight.Get()){
					rad+=0.005;
					if(rad>=1.0){
						rad = 0.5;
					}
					robotDrive.TankDrive(1.0,rad);
				}
				//look for a line based on switch
			} else if (lastLit[0] == 0){
				if(lastLit[1]==1){
					if(lastLit[2]==0){
						if(lastLit[3]==0){
							robotDrive.TankDrive(0.5,1.0);//go left
						} else { //right is lit
							robotDrive.TankDrive(0.0,0.0);//stop for now
							//fork
							//decide which way you go
						}
					} else {//middle is lit
						if(lastLit[3]==0){
							robotDrive.TankDrive(0.25,0.5);//go half left
						} else {//right is lit
							robotDrive.TankDrive(0.0,0.0);//stop for now
							//pick a direction
							//at a T
							state=1;
						}
					}
				} else {//left is not lit
					if(lastLit[2]==0){
						if(lastLit[3]==0){
							robotDrive.TankDrive(0.0,0.0);//stop for now
							//error!
							state=-1;
						} else {
							robotDrive.TankDrive(1.0,0.5);//go right
						}
					} else { // middle is lit
						if(lastLit[3]==0){
							robotDrive.TankDrive(1.0,1.0);//go strait
						} else { // right is lit
							robotDrive.TankDrive(0.5,0.25);//go half right
						}
					}
				}
			} else {
				robotDrive.TankDrive(0.0,0.0);//stop for now
				//error!
				state=-1;
			}
		   } else{//right is lit
				robotDrive.TankDrive(1.0,0.5);//go right
		   }
		  } else {//middle is lit
			  if(Lit[3]==0){
					robotDrive.TankDrive(1.0,1.0);//go strait
			  } else {
					robotDrive.TankDrive(0.5,0.25);//go half right
			  }
		  }
		} else {//left is lit
			if(Lit[2]==0){
				if(Lit[3]==0){
					robotDrive.TankDrive(0.5,1.0);//go left
				} else {//right is lit
					robotDrive.TankDrive(0.0,0.0);//stop for now
					//Y
					//pick a direction based on the switch
				}
			} else {//middle is lit
				if(Lit[3]==0){
					robotDrive.TankDrive(0.25,0.5);//go half left
				} else {//all are lit!
					robotDrive.TankDrive(0.0,0.0);//stop for now
					//T or faced funny!
					//pick a direction based on the switch
					state = 1;
				}
			}
		}
		lastLit[1]=Lit[1];
		lastLit[2]=Lit[2];
		lastLit[3]=Lit[3];
		if(lastLit[1]==0 && lastLit[2]==0 && lastLit[3]==0){
			lastLit[0]=1;
		}
		}//while isAutonomus() && state == 0
		switch(state){
		case -1:
			//error handling here!
			break;
		case 1:
			//end of line!
			robotDrive.TankDrive(0.25,0.25);
			//armPivot.Set(.75);//cant actually do this yet, it depends on readers
			//armRaise.Set(.75);//cant actually do this yet, it depends on readers
			Wait(1);
			robotDrive.TankDrive(0.0,0.0);
			claw.Open();
			//arm.Raise.Set(.70);//cant actually do this yet, it depends on readers
			robotDrive.TankDrive(-0.25,-0.25);
			//armRaise.Set(0.65);
			Wait(.5);
			robotDrive.TankDrive(-0.75,-0.75);
			Wait(1);
			robotDrive.TankDrive(-0.6,0.6);//turn around
			Wait(1.25);
			break;
		case 2://unused??
			break;
		}
	}

	/**
	 * Runs the motors with arcade steering. 
	 */
	void OperatorControl(void)
	{
		robotDrive.SetSafetyEnabled(true);
		while (IsOperatorControl())
		{
			robotDrive.ArcadeDrive(driJ); // drive with arcade style (use right stick)
			//Robot.ArcadeDrive(); // drive with arcade style (use right stick)
			armPivot.Move(accJ.GetY()/1+accJ.GetRawButton(1));//arm speed = normal if trigger
															//is NOT pulled, and half speed if it is
			armRaise.Move(accJ.GetRawButton(3),accJ.GetRawButton(2));
			claw.Set(accJ.GetZ());
			Wait(0.005);				// wait for a motor update time
		}
	}
};

START_ROBOT_CLASS(Robot);
