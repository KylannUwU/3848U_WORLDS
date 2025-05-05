#include "autons.hpp"
#include <string>
#include "main.h"

/////
// For installation, upgrading, documentations, and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////


#define RED true
#define BLUE false
bool AllianceSet = false;

// These are out of 127
const int DRIVE_SPEED = 110;
const int TURN_SPEED = 90;
const int SWING_SPEED = 90;

bool side = AllianceSet;

bool killtask = true;


void testing()
{

  chassis.pid_drive_set(20_in, 120);
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(90_deg,100);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(20_in, 120);
  chassis.pid_wait_quick_chain();
  chassis.pid_swing_set(ez::LEFT_SWING, 180_deg, 90,-30);
  chassis.pid_wait();

}


void IntakeCS()
{
    static int hue_detect_pos = 0;
    static bool is_paused = false;
    int desiredHue = 0;

    
    if(side == RED)
      desiredHue = 205;
    else
      desiredHue = 25;

    bool RingHue = false;

    while(!autonIsDone)
    {
      int current_pos = intake.get_position();
      
      if(side == RED)
        RingHue = opt2.get_hue() > desiredHue;

      else
        RingHue = opt2.get_hue() < desiredHue;
       

      

      if (RingHue) 
      { 
        if (hue_detect_pos == 0) 
          hue_detect_pos = current_pos;
          

        if (current_pos - hue_detect_pos <= 235) 
            intake.move_voltage(12000); 
        

        else 
        {
            // intake.move_voltage(-12000); 
            // pros::delay(150);
            intake.move_voltage(0); 
            pros::delay(300);
            hue_detect_pos = 0;
        }
      } 
      
      else 
      {
        hue_detect_pos = 0;
        is_paused = false;
        intake.move_voltage(12000); 
      }
      pros::delay(5);
    }  
}


void IntakeDetector()
{
  while((opt1.get_distance() > 55 || opt1.get_distance() == _NULL) && !autonIsDone )
  {
    intake.move_voltage(12000);
    pros::delay(20);
  }
  killtask = false;
  intake.move_voltage(0);
}



void IntakeTest()
{
  
    pros::Task IntakeTesting(IntakeCS);
}

#pragma region Skills




void Skills2()
{

  targetValueLB = 9000;
  pros::delay(400);
  targetValueLB = 4000;
  pros::delay(400);

  // SWING TO MOGO 
  chassis.pid_swing_set(ez::RIGHT_SWING, 90_deg, 110, -12 );
  pros::delay(650);
  chassis.pid_drive_set(-14_in, 120);
  pros::delay(570);
  mobile.set_value(true);
  pros::delay(200);

  // 5 RINGS ROUTE
  chassis.pid_turn_set(180_deg, 90);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(17_in, 120);
  chassis.pid_wait_until(4_in);
  intake.move_voltage(12000);
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(270_deg, 90);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(16_in, 120);
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(360_deg, 90);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(17_in, 90);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(10_in, 90);
  // chassis.pid_wait_quick_chain();
  pros::delay(900);
  chassis.pid_turn_set(225_deg, 90);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(14_in, 120);
  //chassis.pid_wait_quick_chain();
  pros::delay(1000);
  chassis.pid_drive_set(-3_in, 120);
  chassis.pid_wait_quick_chain();
  
  // DROP MOGO
  chassis.pid_turn_set(135_deg, 90);
  chassis.pid_wait_quick_chain();
  // chassis.pid_drive_set(-8_in, 120);
  // chassis.pid_wait_quick_chain();
  chassis.drive_set(-50,-50);
  pros::delay(700);
  chassis.drive_set(0,0);
  pros::delay(50);
  mobile.set_value(false);
  intake.move_voltage(-6000);

  // GO TO N WALL STAKE 
  chassis.pid_swing_set(ez::LEFT_SWING, 180_deg, 110, -30 );
  chassis.pid_wait_quick_chain();
  targetValueLB = 5700;
  pros::delay(300);
  intake.move_voltage(12000);
  chassis.pid_drive_set(48_in, 120);
  // chassis.pid_wait_quick();
  pros::delay(1600);
  chassis.pid_drive_set(-3_in, 120);
 // chassis.pid_wait_quick();
  pros::delay(500);
  chassis.pid_turn_set(270_deg, 90);
  chassis.pid_wait_quick_chain();
  // chassis.pid_drive_set(5_in, 120);
  // chassis.pid_wait_quick_chain();
  chassis.drive_set(90,90);
  pros::delay(400);
  intake.move_voltage(-1500);
  targetValueLB = 16500;
  pros::delay(700);
  chassis.drive_set(90,90);
  pros::delay(300);
  chassis.drive_set(0,0);
  pros::delay(200);
  targetValueLB = 4000;
  pros::delay(700);
 
  // GO TO MOGO 2
  chassis.pid_drive_set(-12_in, 120);
  pros::delay(1100);
  chassis.pid_turn_set(220_deg, 70);
  chassis.pid_wait();
  chassis.pid_drive_set(-46_in, 120);
  // chassis.pid_wait_quick_chain();
  pros::delay(1800);
  chassis.pid_turn_set(270_deg, 90);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-24_in, 120);
  // chassis.pid_wait_quick_chain();
  pros::delay(1300);
  mobile.set_value(true);

  // 5 RINGS ROUTE 
  chassis.pid_turn_set(180_deg, 90);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(15_in, 120);
  chassis.pid_wait_until(4_in);
  intake.move_voltage(12000);
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(90_deg, 90);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(16_in, 120);
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(0_deg, 90);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(17_in, 90);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(10_in, 90);
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(135_deg, 90);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(14_in, 120);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-6_in, 120);
  chassis.pid_wait_quick_chain();
 
  // DROP MOGO
  chassis.pid_turn_set(225_deg, 90);
  chassis.pid_wait_quick_chain();
  // chassis.pid_drive_set(-8_in, 120);
  // chassis.pid_wait_quick_chain();
  chassis.drive_set(-65,-65);
  pros::delay(700);
  chassis.drive_set(0,0);
  pros::delay(100);
  mobile.set_value(false);
  intake.move_voltage(-12000);
  pros::delay(100);

  // N WALL STAKE 2
  chassis.pid_swing_set(ez::RIGHT_SWING, 180_deg, 110, -10 );
  chassis.pid_wait_quick_chain();
  targetValueLB = 5700;
  pros::delay(300);
  intake.move_voltage(12000);
  chassis.pid_drive_set(45_in, 120);
  // chassis.pid_wait_quick_chain();s
  pros::delay(1500);
  chassis.pid_drive_set(-4_in, 120);
  chassis.pid_wait_quick_chain();
  intake.move_voltage(-1500);
  pros::delay(1200);
  targetValueLB = 7000;
  pros::delay(300);
  chassis.pid_turn_set(90_deg, 90);
  chassis.pid_wait_quick_chain();
  pros::Task IntakeDetector1(IntakeDetector);
  chassis.pid_drive_set(12_in, 120);
  chassis.pid_wait_quick_chain();
  pros::delay(400);
  targetValueLB = 16500;
  pros::delay(700);
  chassis.drive_set(90,90);
  pros::delay(200);
  chassis.drive_set(0,0);
  pros::delay(50);
  targetValueLB =4000;
  pros::delay(700);
  // if(killtask)
  // {
  //   IntakeDetector1.remove();
  //   killtask = false;
  //   pros::delay(20);
  // }
  // intake.move_voltage(12000);
  // pros::delay(500);
  // intake.move_voltage(-1500);
  // targetValueLB = 16500;
  // pros::delay(700);
  // chassis.drive_set(90,90);
  // pros::delay(200);
  // chassis.drive_set(0,0);
  // pros::delay(50);
  // targetValueLB =4000;
  // pros::delay(700);



  // GO TO MOGO 3
  chassis.pid_drive_set(-10_in, 120);
//  chassis.pid_wait_quick_chain(); 
  pros::delay(500);
  chassis.pid_turn_set(20_deg, 90);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-25_in, 120);
  chassis.pid_wait_quick_chain();
  // pros::delay(1700);
  chassis.pid_swing_set(ez::RIGHT_SWING, 90_deg, 90, 0);
  pros::delay(700);
  //chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-18_in, 120);
  // chassis.pid_wait_quick_chain();
  pros::delay(900);
  mobile.set_value(true);
  pros::delay(100);

  // 6 RINGS ROUTE
  
  //CORNER RING
  chassis.pid_turn_set(45_deg, 90);
  chassis.pid_wait_quick_chain();
  intake.move_voltage(12000);
  chassis.pid_drive_set(25_in, 120);
  chassis.pid_wait_quick_chain();
  // MID RING
  chassis.pid_turn_set(-45_deg, 90);
  chassis.pid_wait_quick_chain();
  intake.move_voltage(0);
  chassis.pid_drive_set(25_in, 120);
  chassis.pid_wait_until(16_in);
  intake.move_voltage(12000);
  chassis.pid_wait_quick_chain();
  // CORNER RING
  chassis.pid_turn_set(-135_deg, 90);
  chassis.pid_wait_quick_chain();
  intake.move_voltage(0);
  chassis.pid_drive_set(25_in, 120);
  chassis.pid_wait_until(16_in);
  intake.move_voltage(12000);
  chassis.pid_wait_quick_chain();
  // LAST ONLY1 RING
  chassis.pid_turn_set(-90_deg, 90);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(18_in, 120);
  chassis.pid_wait_quick_chain();
  //STACKED RING 1
  chassis.pid_turn_set(-180_deg, 50);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(13_in, 50);
  chassis.pid_wait_quick_chain();
  //STACKED RING 2
  // chassis.pid_turn_set(-90_deg, 50);
  // chassis.pid_wait_quick_chain();
  // chassis.pid_drive_set(12_in, 50);
  // chassis.pid_wait_quick_chain();
  // chassis.pid_drive_set(-5_in, 50);
  // chassis.pid_wait_quick_chain();
  //RELEASE MOGO
  chassis.pid_turn_set(45_deg, 90);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-15_in, 120);
  chassis.pid_wait_quick_chain();
 // mobile.set_value(false);
 pros::delay(800); 
 intake.move_voltage(-6000);
  pros::delay(50);


  //GO TO MOGO 4
  chassis.pid_drive_set(5_in, 120);
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(-75_deg, 90);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-85_in, 120);
  chassis.pid_wait_quick_chain();

  //HANG
  chassis.pid_turn_set(-45_deg, 90);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(40_in, 120);
  
  targetValueLB = 8000;
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(135_deg, 90);
  chassis.pid_wait_quick_chain();
  



  

}




#pragma endregion Skills
#pragma region AWP

void soloAWP_Blue_NEW()
{
  AllianceSet = false;
  chassis.pid_swing_set(ez::RIGHT_SWING, -45_deg, 90,0);
  //chassis.pid_wait_quick_chain();
  pros::delay(300);
  targetValueLB = 10000;
  pros::delay(300);
  targetValueLB = 4000;
  pros::delay(300);
  chassis.pid_swing_set(ez::RIGHT_SWING, 0_deg, 90,0);
  //chassis.pid_wait_quick_chain();
  pros::delay(350);
  chassis.pid_swing_set(ez::LEFT_SWING, 45_deg, 90,15);
  //chassis.pid_wait_quick_chain();
  pros::delay(350);
  intake.move_voltage(-12000);
  pros::delay(100);
  intake.move_voltage(0);
  pros::delay(400);

  pros::Task IntakeDTAWP(IntakeDetector);
  pros::delay(800);
  chassis.pid_turn_set(-55_deg, 90);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-40_in, 110);
  chassis.pid_wait_quick_chain();
  // pros::delay(1200);
  mobile.set_value(true);

  pros::delay(150);
  if(killtask)
    IntakeDTAWP.remove();

  chassis.pid_turn_set(-180_deg, 90);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(18_in, 110);
  chassis.pid_wait_until(3_in);
  intake.move_voltage(12000);
  chassis.pid_wait_quick_chain();
  // pros::delay(800);

  chassis.pid_turn_set(-270_deg, 90);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(5_in, 110);
  chassis.pid_wait_quick_chain();
  intake.move_voltage(12000);
  chassis.pid_swing_set(ez::RIGHT_SWING, -360_deg, 90,-30);
  chassis.pid_wait_quick();
  // pros::delay(700);
  chassis.pid_swing_set(ez::RIGHT_SWING, -405_deg, 90,15);
  chassis.pid_wait_quick_chain();
  // pros::delay(700);
  chassis.pid_drive_set(50_in, 110);
  chassis.pid_wait_until(48_in);
  // pros::delay(1400);
  mobile.set_value(false);
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(-130_deg, 90);
  chassis.pid_wait_quick_chain();
  // pros::delay(1200);
  chassis.pid_drive_set(-41_in, 110);
  chassis.pid_wait_until(-39);
  intake.move_voltage(-3000);
  mobile.set_value(true);
  chassis.pid_wait_quick_chain();
  
  chassis.pid_turn_set(-10_deg, 90);
  chassis.pid_wait_quick_chain();
  intake.move_voltage(12000);
  chassis.pid_drive_set(19_in, 110);   
  chassis.pid_wait_quick_chain();
  pros::delay(100);
  chassis.pid_swing_set(ez::LEFT_SWING, -400_deg, 110,75);
  chassis.pid_wait_quick_chain();


  
  
}








void soloAWP_Red_NEW()
{
  AllianceSet = true;
    chassis.pid_swing_set(ez::LEFT_SWING, 47_deg, 90,0);
  //chassis.pid_wait_quick_chain();
  pros::delay(300);
  targetValueLB = 10000;
  pros::delay(300);
  targetValueLB = 4000;
  pros::delay(300);
  chassis.pid_swing_set(ez::LEFT_SWING, 0_deg, 90,0);
  //chassis.pid_wait_quick_chain();
  pros::delay(350);
  chassis.pid_swing_set(ez::RIGHT_SWING, -47_deg, 90,15);
  //chassis.pid_wait_quick_chain();
  pros::delay(350);
  intake.move_voltage(-12000);
  pros::delay(100);
  intake.move_voltage(0);
  pros::delay(400);

  pros::Task IntakeDTAWP(IntakeDetector);
  pros::delay(800);
  chassis.pid_turn_set(60_deg, 90);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-37_in, 110);
  chassis.pid_wait_until(-35_in);
  mobile.set_value(true);
  chassis.pid_wait_quick_chain();

  if(killtask)
    IntakeDTAWP.remove();

  chassis.pid_turn_set(170_deg, 90);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(20_in, 110);
  chassis.pid_wait_until(3_in);
  intake.move_voltage(12000);
  chassis.pid_wait_quick_chain();
  // pros::delay(800);

  chassis.pid_turn_set(270_deg, 90);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(5_in, 110);
  chassis.pid_wait_quick_chain();
  intake.move_voltage(12000);
  chassis.pid_swing_set(ez::LEFT_SWING, 360_deg, 90,-30);
  chassis.pid_wait_quick();
  // pros::delay(700);
  chassis.pid_swing_set(ez::LEFT_SWING, 405_deg, 90,15);
  chassis.pid_wait_quick_chain();
  // pros::delay(700);
  chassis.pid_drive_set(50_in, 110);
  chassis.pid_wait_until(48_in);
  // pros::delay(1400);
  mobile.set_value(false);
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(130_deg, 90);
  chassis.pid_wait_quick_chain();
  // pros::delay(1200);
  chassis.pid_drive_set(-39_in, 110);
  chassis.pid_wait_until(-37_in);
  intake.move_voltage(-3000);
  mobile.set_value(true);
  chassis.pid_wait_quick_chain();
  
  chassis.pid_turn_set(10_deg, 90);
  chassis.pid_wait_quick_chain();
  intake.move_voltage(12000);
  chassis.pid_drive_set(21_in, 110);   
  chassis.pid_wait_quick_chain();
  pros::delay(100);
  chassis.pid_swing_set(ez::RIGHT_SWING, 400_deg, 110,77);
  chassis.pid_wait_quick_chain();



  
}



void AWP_BlueNeg() // Blue AWP Negative Starting Position awp ladybrown  to alliance stake
{
  AllianceSet = false;
  chassis.odom_theta_set(180_deg);
  
  chassis.pid_swing_set(ez::RIGHT_SWING, 135_deg, 90,0);
  // chassis.pid_wait_quick_chain();
  pros::delay(350);
  targetValueLB = 10000;
  pros::delay(400);
  targetValueLB = 4000;
  pros::delay(400);
  chassis.pid_swing_set(ez::RIGHT_SWING, 180_deg, 90,0);
  // chassis.pid_wait_quick_chain();
  pros::delay(370);
  chassis.pid_swing_set(ez::LEFT_SWING, 225_deg, 90,20);
  // chassis.pid_wait_quick_chain();
  pros::delay(370);
  intake.move_voltage(-12000);
  pros::delay(100);
  intake.move_voltage(0);
  pros::delay(300);
  pros::Task IntakeDTAWP(IntakeDetector);
  chassis.pid_drive_set(5_in, 40);
  pros::delay(600);
  chassis.pid_turn_set(130_deg, 70);
  chassis.pid_wait_quick();
  chassis.pid_drive_set(-35_in, 90);
  chassis.pid_wait_until(-10_in);

  if(killtask)
    IntakeDTAWP.remove();

  chassis.pid_wait_until(-34_in);
  mobile.set_value(true);

  pros::delay(300);
  chassis.pid_turn_set(315_deg, 120);
  chassis.pid_wait_quick_chain();
  intake.move_voltage(12000);
  chassis.pid_drive_set(22_in, 120);
  chassis.pid_wait();
  chassis.pid_swing_set(ez::LEFT_SWING, 0_deg, 120,0);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(11_in, 45);
  chassis.pid_wait_quick_chain();
  chassis.pid_swing_set(ez::LEFT_SWING, -45_deg, 120,50);
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(45_deg, 70);
  chassis.pid_wait_quick();
  chassis.pid_swing_set(ez::RIGHT_SWING, 0_deg, 120,50);
  chassis.pid_wait_quick();
  chassis.pid_swing_set(ez::RIGHT_SWING, 57_deg, 120,0);
  chassis.pid_wait_quick();
  chassis.pid_drive_set(30_in, 100);
  chassis.pid_wait_quick_chain();
  chassis.drive_set(120,120);
  pros::delay(500);
  chassis.drive_set(40,40);
  pros::delay(1000);
  chassis.drive_set(-100,-100);
  pros::delay(200);

  chassis.drive_set(0,0);
  pros::delay(100);
  chassis.pid_turn_set(40_deg, 120);
  chassis.pid_wait();
  chassis.pid_drive_set(-59_in, 120);
  chassis.pid_wait();

           
}


void AWP_RedNeg()
{
  AllianceSet = true;
  chassis.pid_swing_set(ez::LEFT_SWING, 45_deg, 90, 0); // antes: 225_deg
  // chassis.pid_wait_quick_chain();
  pros::delay(350);
  
  targetValueLB = 10000;
  pros::delay(400);
  targetValueLB = 4000;
  pros::delay(400);
  
  chassis.pid_swing_set(ez::LEFT_SWING, 0_deg, 90, 0); // antes: 180_deg
  // chassis.pid_wait_quick_chain();
  pros::delay(370);
  
  chassis.pid_swing_set(ez::RIGHT_SWING, -45_deg, 90, 20); // antes: 135_deg
  // chassis.pid_wait_quick_chain();
  pros::delay(370);
  
  intake.move_voltage(-12000);
  pros::delay(100);
  intake.move_voltage(0);
  pros::delay(300);
  
  pros::Task IntakeDTAWP(IntakeDetector);
  chassis.pid_drive_set(5_in, 40);
  pros::delay(600);
  
  chassis.pid_turn_set(50_deg, 70); // antes: 230_deg
  chassis.pid_wait_quick();
  
  chassis.pid_drive_set(-35_in, 90);
  chassis.pid_wait_until(-10_in);
  
  if (killtask)
    IntakeDTAWP.remove();
  
  chassis.pid_wait_until(-34_in);
  mobile.set_value(true);
  
  pros::delay(300);
  
  chassis.pid_turn_set(225_deg, 120); // antes: 45_deg
  chassis.pid_wait_quick_chain();
  
  intake.move_voltage(12000);
  chassis.pid_drive_set(18_in, 120);
  chassis.pid_wait_quick_chain();
  
  chassis.pid_swing_set(ez::RIGHT_SWING, 180_deg, 120, 0); // antes: 0_deg
  chassis.pid_wait_quick_chain();
  
  chassis.pid_drive_set(11_in, 45);
  chassis.pid_wait_quick_chain();
  
  chassis.pid_swing_set(ez::RIGHT_SWING, 225_deg, 120, 50); // antes: 45_deg (antes del espejo: -45_deg)
  chassis.pid_wait_quick_chain();
  
  chassis.pid_turn_set(135_deg, 70); // antes: 315_deg
  chassis.pid_wait_quick();
  
  chassis.pid_swing_set(ez::LEFT_SWING, 180_deg, 120, 50); // antes: 0_deg
  chassis.pid_wait_quick();
  
  chassis.pid_swing_set(ez::LEFT_SWING, 128_deg, 120, 0); // antes: 303_deg (antes del espejo: 57_deg)
  chassis.pid_wait_quick();
  
  chassis.pid_drive_set(30_in, 100);
  chassis.pid_wait_quick_chain();
  chassis.drive_set(120, 120);
  pros::delay(500);
  chassis.drive_set(40, 40);
  pros::delay(1000);
  chassis.drive_set(-100, -100);
  pros::delay(200);
  
  chassis.drive_set(0, 0);
  pros::delay(100);
  
  chassis.pid_turn_set(135_deg, 120); // antes: 320_deg (antes del espejo: 40_deg)
  chassis.pid_wait();
  chassis.pid_drive_set(-57_in, 120);
  chassis.pid_wait();
  
}




void AWP_BluePos()
{
  AllianceSet = false;
  chassis.pid_swing_set(ez::LEFT_SWING, 45_deg, 90,0); // chassis.pid_swing_set(ez::RIGHT_SWING, -45_deg, 90,0);
  pros::delay(300);
  targetValueLB = 10000;
  pros::delay(300);
  targetValueLB = 4000;
  pros::delay(300);
  chassis.pid_swing_set(ez::LEFT_SWING, 0_deg, 90,0); // chassis.pid_swing_set(ez::RIGHT_SWING, 0_deg, 90,0);
  pros::delay(370);
  chassis.pid_swing_set(ez::RIGHT_SWING, -55_deg, 95,12); // chassis.pid_swing_set(ez::LEFT_SWING, 45_deg, 90,15);
  pros::delay(400);
  intake.move_voltage(-12000);
  pros::delay(100);
  intake.move_voltage(0);
  pros::delay(400);
  pros::Task IntakeDTAWP(IntakeDetector);
  pros::delay(800);
  chassis.pid_turn_set(60_deg, 90); // chassis.pid_turn_set(-55_deg, 90);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-37_in, 120);
  chassis.pid_wait_until(-35_in);
  mobile.set_value(true);
  chassis.pid_wait_quick_chain();
  
  pros::delay(100);
  chassis.pid_turn_set(175_deg, 90); // chassis.pid_turn_set(-180_deg, 90);
  chassis.pid_wait_quick_chain();
  if(killtask)
  {
    IntakeDTAWP.remove();
    intake.move_voltage(-600);
  }
  //chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(25_in, 120);
  chassis.pid_wait_until(2_in);
  intake.move_voltage(12000);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-15_in, 120);
  chassis.pid_wait_quick_chain();
  chassis.pid_swing_set(ez::RIGHT_SWING, 115_deg, 100,15);
  chassis.pid_wait_quick_chain(); 
  intake.move_voltage(0);
  pros::Task IntakeColor(IntakeCS);
  chassis.pid_drive_set(30_in, 127);
  chassis.pid_wait_until(20_in);
  doinker.set_value(true); 
  chassis.pid_wait_quick_chain(); 
  chassis.pid_turn_set(50_deg, 120);
  pros::delay(700);
  doinker.set_value(false);
  chassis.pid_turn_set(80_deg, 120);
  pros::delay(300);
  chassis.pid_turn_set(50_deg, 120);
  pros::delay(300);
  // chassis.pid_turn_set(80_deg, 100);
  // pros::delay(400);
  chassis.pid_drive_set(12_in, 120);
  chassis.pid_wait_quick_chain(); 
  // chassis.pid_swing_set(ez::RIGHT_SWING, 130_deg, 100,-75);
  // pros::delay(1000);
  // chassis.pid_drive_set(-10_in, 120);
  // pros::delay(400);
  // chassis.pid_turn_set(70_deg, 100);
  // pros::delay(400);
  // chassis.pid_drive_set(15_in, 120);
  // pros::delay(900);
  chassis.pid_swing_set(ez::RIGHT_SWING, 145_deg, 100,5);
  pros::delay(1100);
  chassis.pid_drive_set(-52_in, 120);
  chassis.pid_wait_quick_chain();
 
}




void AWP_RedPos()
{
  AllianceSet = true;
  chassis.pid_swing_set(ez::RIGHT_SWING, -45_deg, 90,0);
  //chassis.pid_wait_quick_chain();
  pros::delay(350);
  targetValueLB = 10000;
  pros::delay(400);
  targetValueLB = 4000;
  pros::delay(400);
  chassis.pid_swing_set(ez::RIGHT_SWING, 0_deg, 90,0);
  //chassis.pid_wait_quick_chain();
  pros::delay(370);
  chassis.pid_swing_set(ez::LEFT_SWING, 50_deg, 90,20);
  //chassis.pid_wait_quick_chain();
  pros::delay(370);
  intake.move_voltage(-12000);
  pros::delay(100);
  intake.move_voltage(0);
  pros::delay(300);
  pros::Task IntakeDTAWP(IntakeDetector);
  chassis.pid_drive_set(5_in, 40);
  pros::delay(600);
  chassis.pid_turn_set(-45_deg, 110);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-37.5_in, 110);
  // chassis.pid_wait_quick_chain();
  chassis.pid_wait_quick_chain();
  mobile.set_value(true);
  pros::delay(150);
  chassis.pid_turn_set(-180_deg, 110);
  chassis.pid_wait_quick_chain();
 
  if(killtask)
  {
    IntakeDTAWP.remove();
    intake.move_voltage(-600);
  }
  chassis.pid_drive_set(23_in, 100);
  chassis.pid_wait_until(18_in);
  pros::Task AWPR(IntakeCS);
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(-260_deg, 100);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-15_in, 110);
  chassis.pid_wait_quick_chain();
  chassis.pid_swing_set(ez::RIGHT_SWING, -165_deg, 100, 15);
  chassis.pid_wait_quick_chain();
  doinker.set_value(true);
  chassis.pid_drive_set(11_in, 110); 
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(-215_deg, 120);
  chassis.pid_wait_quick_chain();
  doinker.set_value(false);
  chassis.pid_drive_set(9_in, 120);
  chassis.pid_wait_quick_chain();
  chassis.pid_swing_set(ez::RIGHT_SWING, -135_deg, 100,5);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-53_in, 120);
  chassis.pid_wait_quick_chain();
  
}

void BluePos_NOMID()
{
  
  chassis.drive_angle_set(90);

  AllianceSet = false;
  chassis.pid_drive_set(-26_in ,127);
  chassis.pid_wait_quick_chain();
  mobile.set_value(true);
  
  chassis.pid_turn_set(175_deg, 90); // chassis.pid_turn_set(-180_deg, 90);
  chassis.pid_wait_quick_chain();

  //chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(25_in, 120);
  chassis.pid_wait_until(2_in);
  intake.move_voltage(12000);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-15_in, 120);
  chassis.pid_wait_quick_chain();
  chassis.pid_swing_set(ez::RIGHT_SWING, 115_deg, 100,15);
  chassis.pid_wait_quick_chain(); 
  intake.move_voltage(0);
  pros::Task IntakeColor(IntakeCS);
  chassis.pid_drive_set(30_in, 127);
  chassis.pid_wait_until(20_in);
  doinker.set_value(true); 
  chassis.pid_wait_quick_chain(); 
  chassis.pid_turn_set(50_deg, 120);
  pros::delay(700);
  doinker.set_value(false);
  chassis.pid_turn_set(80_deg, 120);
  pros::delay(300);
  chassis.pid_turn_set(50_deg, 120);
  pros::delay(300);
  // chassis.pid_turn_set(80_deg, 100);
  // pros::delay(400);
  chassis.pid_drive_set(12_in, 120);
  chassis.pid_wait_quick_chain(); 
  // chassis.pid_swing_set(ez::RIGHT_SWING, 130_deg, 100,-75);
  // pros::delay(1000);
  // chassis.pid_drive_set(-10_in, 120);
  // pros::delay(400);
  // chassis.pid_turn_set(70_deg, 100);
  // pros::delay(400);
  // chassis.pid_drive_set(15_in, 120);
  // pros::delay(900);
  chassis.pid_swing_set(ez::RIGHT_SWING, 145_deg, 100,5);
  pros::delay(1100);
  chassis.pid_drive_set(-52_in, 120);
  chassis.pid_wait_quick_chain();
 
}


void RedPos_NOMID()
{
  AllianceSet = true;
  chassis.pid_drive_set(-22_in ,127);
  pros::delay(800);
  mobile.set_value(true);
  pros::delay(80);
  chassis.pid_turn_set(-129_deg ,120); //chassis.pid_turn_set(129_deg ,120);
  chassis.pid_wait();
  chassis.pid_drive_set(11_in, 127);
  chassis.pid_wait_until(2_in);
  mobile.set_value(false);
  chassis.pid_wait_until(5_in);
  targetValueLB = 10000;
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-14_in, 120);
  pros::delay(750);
  targetValueLB = 4000;
  mobile.set_value(true);
  pros::delay(100);
  chassis.pid_turn_set(-90_deg ,120); //  chassis.pid_turn_set(90_deg ,120);
  chassis.pid_wait();
  intake.move_voltage(12000);
  chassis.pid_drive_set(14_in, 120);
  chassis.pid_wait_quick_chain();
  chassis.pid_swing_set(ez::RIGHT_SWING, -10_deg, 120, -5); // chassis.pid_swing_set(ez::LEFT_SWING, 10_deg, 120, -5);
  chassis.pid_wait();
  chassis.pid_drive_set(14_in, 120);
  chassis.pid_wait_quick_chain();
}




void BluePos_NOMID_Rush()
{
  AllianceSet = false;
  pros::Task intakedt(IntakeDetector);
  // Drive to MOGO and score PRELOAD
  chassis.pid_drive_set(38_in, 127);
  chassis.pid_wait_until(5_in);
  doinker.set_value(true);
  chassis.pid_wait_until(32_in);
  doinker.set_value(false); 
  chassis.pid_wait_until(35_in);
  pros::delay(20);
  chassis.pid_drive_set(-25_in ,120);
  chassis.pid_wait_until(-17_in);
  doinker.set_value(true);
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(-100_deg, 120);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-28_in, 120);
  chassis.pid_wait_quick_chain();

  pros::delay(500000);

  // Swing to ring 
  chassis.pid_swing_set(ez::RIGHT_SWING, -90_deg, 100,-45);
  chassis.pid_wait_quick_chain(); 
  // Start intake 
  pros::Task CS(IntakeCS); 
  chassis.pid_drive_set(28_in, 120);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-5_in, 60);
  chassis.pid_wait_quick_chain();
  // Swing to Corner
  chassis.pid_swing_set(ez::RIGHT_SWING, -165_deg, 100,5);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(17_in, 120);
  chassis.pid_wait_quick_chain();
  // Extend Doinker
  doinker.set_value(true);  
  chassis.pid_drive_set(12_in, 120);
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(-215_deg, 100);
  chassis.pid_wait();
  doinker.set_value(false);
  chassis.pid_turn_set(-180_deg, 100);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(10_in, 120);
  chassis.pid_wait_quick_chain();
  chassis.pid_swing_set(ez::RIGHT_SWING, -130_deg, 100,5);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-10_in, 120);
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(-190_deg, 100);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(17_in, 120);
  chassis.pid_wait_quick_chain();
  chassis.pid_swing_set(ez::RIGHT_SWING, -130_deg, 100,5);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-39_in, 120);
  chassis.pid_wait_quick_chain();

}


void RedPos_NOMID_Rush()
{
  AllianceSet = true;
  chassis.pid_drive_set(33_in, 127);
  // chassis.pid_wait(); 
  pros::delay(1100);
  chassis.pid_swing_set(ez::LEFT_SWING, 48_deg, 100, -25); // chassis.pid_swing_set(ez::RIGHT_SWING, -48_deg, 100, -25);
  chassis.pid_wait_until(15_deg); // chassis.pid_wait_until(-15_deg);
  targetValueLB = 10000;
  chassis.pid_wait();
  targetValueLB = 4000;
  chassis.pid_drive_set(-17_in ,127);
  pros::delay(900);
  mobile.set_value(true);
  pros::delay(50);
  chassis.pid_swing_set(ez::LEFT_SWING, 90_deg, 100,-45); // chassis.pid_swing_set(ez::RIGHT_SWING, -90_deg, 100,-45);
  pros::delay(500);
  pros::Task CS(IntakeCS);
  chassis.pid_drive_set(28_in, 120);
  pros::delay(900);
  chassis.pid_turn_set(15_deg, 100);
  pros::delay(500);
  chassis.pid_drive_set(-14_in, 110);
  pros::delay(800);
  chassis.pid_swing_set(ez::RIGHT_SWING, 100_deg, 100, 5); // chassis.pid_swing_set(ez::RIGHT_SWING, -165_deg, 100,5);
  chassis.pid_wait_quick_chain();
  doinker.set_value(true);
  pros::delay(100);
  chassis.pid_drive_set(10_in, 110);
  pros::delay(900);
  chassis.pid_turn_set(60_deg, 110);
  pros::delay(900);
  doinker.set_value(false);
  chassis.pid_turn_set(90_deg, 110);
  pros::delay(900);
  chassis.pid_drive_set(10_in, 110);
  pros::delay(900);
  chassis.pid_swing_set(ez::RIGHT_SWING, 140_deg, 100, 5); // chassis.pid_swing_set(ez::RIGHT_SWING, -165_deg, 100,5);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-9_in, 110);
  pros::delay(900);
  chassis.pid_turn_set(80_deg, 110);
  pros::delay(900);
  chassis.pid_drive_set(16_in, 60);
  pros::delay(800);
}

#pragma endregion AWP
#pragma region Elims


void Ellims_5rings_Blue() 
{
  AllianceSet = false;
  targetValueLB = 5500;
  chassis.pid_swing_set(ez::LEFT_SWING, 30_deg, 90, 5);
  chassis.pid_wait();
  intake.move_voltage(12000);
  pros::delay(1000);
  intake.move_voltage(0);
  chassis.pid_turn_set(-72_deg, 90);/////////////////////70
  chassis.pid_wait();
  chassis.pid_drive_set(6_in, 100);///9
  chassis.pid_wait();
  targetValueLB = 16000;
  pros::delay(500);
  targetValueLB = 4000;
  chassis.pid_turn_set(-60_deg, 90);
  chassis.pid_wait();
  chassis.pid_drive_set(-40_in, 100);
  chassis.pid_wait(); 
  mobile.set_value(true);
  pros::delay(100);
  chassis.pid_turn_set(180_deg, 90);
  chassis.pid_wait();
  intake.move_voltage(12000);
  chassis.pid_drive_set(17_in, 70);//20
  chassis.pid_wait();
  chassis.pid_drive_set(-17_in, 70);//20
  chassis.pid_wait();
  chassis.pid_turn_set(135_deg, 90);
  chassis.pid_wait(); 
  chassis.pid_drive_set(18_in, 70);//20
  chassis.pid_wait();
  chassis.pid_swing_set(ez::LEFT_SWING, 180_deg, 90, 5);
  chassis.pid_wait();
  chassis.pid_drive_set(13_in, 70);//20
  chassis.pid_wait();
  pros::delay(500);
  intake.move_voltage(0);
  chassis.drive_set(-127, -20);
  pros::delay(400);
  chassis.drive_set(0, 0);
  pros::delay(200);
  chassis.drive_set(-70, -127);
  pros::delay(800); //1700 IT WAS
  chassis.drive_set(0, 0);

}
void Ellims_5rings_Red()
{
  AllianceSet = true;
  targetValueLB = 5500;

  // Change swing to RIGHT_SWING and adjust the angle for the left side
  chassis.pid_swing_set(ez::RIGHT_SWING, -30_deg, 90, 5); 
  chassis.pid_wait();

  intake.move_voltage(12000); // Activate intake
  pros::delay(1000);          // Wait for intake to process objects
  intake.move_voltage(0);     // Stop intake

  // Change turn angle to positive for the left side
  chassis.pid_turn_set(70_deg, 90); 
  chassis.pid_wait();

  chassis.pid_drive_set(6_in, 100); // Move forward 6 inches
  chassis.pid_wait();

  targetValueLB = 16000; // Adjust motor target value
  pros::delay(500);

  targetValueLB = 4000; // Reduce motor target value

  // Change turn angle to positive for the left side
  chassis.pid_turn_set(60_deg, 90); 
  chassis.pid_wait();

  chassis.pid_drive_set(-40_in, 100); // Move backward 40 inches
  chassis.pid_wait();

  mobile.set_value(true); // Activate mobile goal mechanism
  pros::delay(100);

  // Change turn angle to -180 for the left side
  chassis.pid_turn_set(-180_deg, 90); 
  chassis.pid_wait();

  intake.move_voltage(12000); // Activate intake
  chassis.pid_drive_set(17_in, 70); // Move forward 17 inches
  chassis.pid_wait();

  chassis.pid_drive_set(-17_in, 70); // Move backward 17 inches
  chassis.pid_wait();

  // Change turn angle to -135 for the left side
  chassis.pid_turn_set(-135_deg, 90); 
  chassis.pid_wait();

  chassis.pid_drive_set(18_in, 70); // Move forward 18 inches
  chassis.pid_wait();

  // Change swing to RIGHT_SWING and adjust the angle for the left side
  chassis.pid_swing_set(ez::RIGHT_SWING, -180_deg, 90, 5); 
  chassis.pid_wait();

  chassis.pid_drive_set(11_in, 70); // Move forward 13 inches
  chassis.pid_wait();

  pros::delay(500); // Wait to stabilize

  intake.move_voltage(0); // Stop intake

  // Adjust drive commands for the left side
  chassis.drive_set(-20, -127); // Turn left while reversing
  pros::delay(400);             
  chassis.drive_set(0, 0);      // Stop robot

  pros::delay(200); // Short pause

  chassis.drive_set(-127, -70); // Turn left with a sharper turn
  pros::delay(800);             
  chassis.drive_set(0, 0);      // Stop robot
}







void Elims_6rings_BLUE()
{
  AllianceSet = false;
  // TAKE MOGO
  chassis.pid_drive_set(-25_in, 120);
   
 //chassis.pid_wait_quick_chain(); 
 chassis.pid_wait_until(-24);
  mobile.set_value(true);
  pros::delay(100);
  chassis.pid_wait_quick_chain(); 
  // AUTON LINE RINGS
  chassis.pid_turn_set(-140_deg, 85);
  chassis.pid_wait_quick_chain();
  intake.move_voltage(120000);
  // chassis.pid_drive_set(12_in,110);
  chassis.pid_drive_set(19_in,120);
  //chassis.pid_wait_quick_chain();
  chassis.pid_wait_quick_chain(); 
  chassis.pid_swing_set(ez::LEFT_SWING, -90_deg, 80, 0);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(12_in,40);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-5_in,120);
  chassis.pid_wait_quick_chain();
  chassis.pid_swing_set(ez::LEFT_SWING, -50_deg, 127, 0);
  //chassis.pid_wait_quick();
  chassis.pid_wait_quick_chain(); 
  // MID RING
  chassis.pid_turn_set(12_deg, 90);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(25_in, 120);
  chassis.pid_wait_until(8_in);
  intake.move_voltage(0);
  chassis.pid_wait_until(17_in);
  pros::Task intakeControl2(IntakeCS);
  pros::delay(500);
  chassis.pid_turn_set(-45_deg, 90);
  chassis.pid_wait_quick();
 
  //CORNER RINGS
  chassis.pid_drive_set(21_in,120);
  chassis.pid_wait_quick_chain();
  //chassis.pid_wait_quick_chain();
  chassis.drive_set(85, 85);
  pros::delay(500);


  // blue 1
  chassis.pid_drive_set(-2.8_in,45);
  chassis.pid_wait_quick_chain();
  chassis.pid_wait_quick_chain();
  chassis.drive_set(45, 45);
  pros::delay(700);
  chassis.drive_set(0, 0);
  pros::delay(200);


  // red 1 (discard)
  chassis.pid_drive_set(-3_in,45);
  chassis.pid_wait_quick_chain();
  pros::delay(600);
  chassis.drive_set(45, 45);
  pros::delay(700);
  chassis.drive_set(0, 0);
  pros::delay(200);


  //blue 2
  chassis.pid_drive_set(-3_in,45);
  chassis.pid_wait_quick_chain();
  pros::delay(400);
  chassis.drive_set(45, 45);
  pros::delay(15000);
  chassis.drive_set(0, 0);
  pros::delay(200);

  chassis.pid_drive_set(-15_in,120);
  chassis.pid_wait_quick_chain();  
}














void Elims_6rings_RED()
{
  AllianceSet = true;
  // TAKE MOGO
  chassis.pid_drive_set(-21_in, 120);
  pros::delay(1200);  
 //chassis.pid_wait_quick_chain(); 
 mobile.set_value(true);
  pros::delay(100);

  // AUTON LINE RINGS
  chassis.pid_turn_set(140_deg, 85);
  chassis.pid_wait_quick_chain();
  intake.move_voltage(120000);
  // chassis.pid_drive_set(12_in,110);
  chassis.pid_drive_set(18.5_in,120);
  //chassis.pid_wait_quick_chain();
  pros::delay(1450);  
  chassis.pid_swing_set(ez::RIGHT_SWING, 90_deg, 80, 0);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(7_in,120);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-5_in,120);
  chassis.pid_wait_quick_chain();
  chassis.pid_swing_set(ez::RIGHT_SWING, 50_deg, 127, 0);
  //chassis.pid_wait_quick();
  pros::delay(400);  
  // MID RING
  chassis.pid_turn_set(-8_deg, 90);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(28_in, 120);
  chassis.pid_wait_until(8_in);
  intake.move_voltage(0);
  chassis.pid_wait_until(17_in);
  pros::Task intakeControl2(IntakeCS);
  pros::delay(500);
  chassis.pid_turn_set(40_deg, 90);
  chassis.pid_wait_quick();
  //CORNER RINGS
  chassis.pid_drive_set(22_in,120);
  pros::delay(1050);
  //chassis.pid_wait_quick_chain();
  chassis.drive_set(85, 85);
  pros::delay(500);


  // RED 1
  chassis.pid_drive_set(-2.8_in,45);
  chassis.pid_wait_quick_chain();
  pros::delay(400);
  chassis.drive_set(45, 45);
  pros::delay(700);
  chassis.drive_set(0, 0);
  pros::delay(200);


  // BLUE 1 (discard)
  chassis.pid_drive_set(-3_in,45);
  chassis.pid_wait_quick_chain();
  pros::delay(600);
  chassis.drive_set(45, 45);
  pros::delay(700);
  chassis.drive_set(0, 0);
  pros::delay(200);


  //RED 2
  chassis.pid_drive_set(-3_in,45);
  chassis.pid_wait_quick_chain();
  pros::delay(400);
  chassis.drive_set(45, 45);
  pros::delay(700);
  chassis.drive_set(0, 0);
  pros::delay(200);

  chassis.pid_drive_set(-15_in,120);
  chassis.pid_wait_quick_chain();  
  
}


#pragma endregion Elims

#pragma region Constants


void default_constants() {
  chassis.pid_turn_behavior_set(shortest);
  chassis.pid_heading_constants_set(10, 0, 20);
  chassis.pid_drive_constants_set(14, 0, 160);///9/70
  // chassis.pid_drive_constants_backward_set(10, 0.001, 80);
  chassis.pid_turn_constants_set(5, 0, 45);//2.30 /0.04 //20
  chassis.pid_swing_constants_set(5, 0, 45);//

  chassis.pid_turn_exit_condition_set(80_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_swing_exit_condition_set(80_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_drive_exit_condition_set(80_ms, 1_in, 250_ms, 3_in, 500_ms, 500_ms);

  chassis.pid_turn_chain_constant_set(3_deg);
  chassis.pid_swing_chain_constant_set(5_deg);
  chassis.pid_drive_chain_constant_set(3_in);

  chassis.slew_drive_constants_set(7_in, 80);
}





#pragma endregion Constants
#pragma region examples

///
// Drive Example
///
void drive_example() {
  // The first parameter is target inches
  // The second parameter is max speed the robot will drive at
  // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
  // for slew, only enable it when the drive distance is greater than the slew distance + a few inches

  /*chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();*/

  chassis.pid_drive_set(-24_in, DRIVE_SPEED);
  chassis.pid_wait();
/*
  chassis.pid_drive_set(-12_in, DRIVE_SPEED);
  chassis.pid_wait();*/
}

///
// Turn Example
///
void turn_example() {
  // The first parameter is the target in degrees
  // The second parameter is max speed the robot will drive at


  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();
}

///
// Combining Turn + Drive
///
void drive_and_turn() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Wait Until and Changing Max Speed
///
void wait_until_change_speed() {
  // pid_wait_until will wait until the robot gets to a desired position

  // When the robot gets to 6 inches slowly, the robot will travel the remaining distance at full speed
  chassis.pid_drive_set(24_in, 30, true);
  chassis.pid_wait_until(6_in);
  chassis.pid_speed_max_set(DRIVE_SPEED);  // After driving 6 inches at 30 speed, the robot will go the remaining distance at DRIVE_SPEED
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  // When the robot gets to -6 inches slowly, the robot will travel the remaining distance at full speed
  chassis.pid_drive_set(-24_in, 30, true);
  chassis.pid_wait_until(-6_in);
  chassis.pid_speed_max_set(DRIVE_SPEED);  // After driving 6 inches at 30 speed, the robot will go the remaining distance at DRIVE_SPEED
  chassis.pid_wait();
}

///
// Swing Example
///
void swing_example() {
  // The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
  // The second parameter is the target in degrees
  // The third parameter is the speed of the moving side of the drive
  // The fourth parameter is the speed of the still side of the drive, this allows for wider arcs

  chassis.pid_swing_set(ez::LEFT_SWING, 45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, 0_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, 45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::LEFT_SWING, 0_deg, SWING_SPEED, 45);
  chassis.pid_wait();
}

///
// Motion Chaining
///
void motion_chaining() {
  // Motion chaining is where motions all try to blend together instead of individual movements.
  // This works by exiting while the robot is still moving a little bit.
  // To use this, replace pid_wait with pid_wait_quick_chain.
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  // Your final motion should still be a normal pid_wait
  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Auto that tests everything
///
void combining_movements() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, -45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Interference example
///
void tug(int attempts) {
  for (int i = 0; i < attempts - 1; i++) {
    // Attempt to drive backward
    printf("i - %i", i);
    chassis.pid_drive_set(-12_in, 127);
    chassis.pid_wait();

    // If failsafed...
    if (chassis.interfered) {
      chassis.drive_sensor_reset();
      chassis.pid_drive_set(-2_in, 20);
      pros::delay(1000);
    }
    // If the robot successfully drove back, return
    else {
      return;
    }
  }
}

// If there is no interference, the robot will drive forward and turn 90 degrees.
// If interfered, the robot will drive forward and then attempt to drive backward.
void interfered_example() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  if (chassis.interfered) {
    tug(3);
    return;
  }

  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();
}

// . . .
// Make your own autonomous functions here!
// . . .'


#pragma endregion examples