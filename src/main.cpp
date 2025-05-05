#include "main.h"


using pros::E_MOTOR_BRAKE_HOLD;

// USE TO CHANGE COLOR SORTING, IF DEFINED, RED RINGS ONLY SCORE
//#define RED 1
//

ez::Drive chassis(
    // These are your drive motors, the first motor is used for sensing!
    {
        -12,
        -11,
        -13,
    },  // Left Chassis Ports (negative port will reverse it!)
    {
        19,
        18,
        20,
    },  // Right Chassis Ports (negative port will reverse it!)

    1,     // IMU Port
    3.25,  // Wheel Diameter (Remember, 4" wheels without screw holes are actually 4.125!)
    450);  // Wheel RPM

ez::tracking_wheel horiz_tracker(17, 2, 1.25);


bool mobileToggle = false;
bool doinkerToggle = false;
bool flagMode = false;
bool autonStarted = false;
bool autonIsDone = false;
unsigned long toggleStartTime = 0;

const double KpLB = 5.0; // Ganancia proporcional
const double KiLB = 0.0; // Ganancia integral
const double KdLB = 0.0; // Ganancia derivativa

double integralValueLB = 0.0; 
double previousErrorLB = 0.0;
int targetValueLB = 4000; 

void controlMotor() 
{
    int encoderValue = rotationSensor.get_position(); 
    double error = targetValueLB - encoderValue;
    integralValueLB += error;
    double derivative = error - previousErrorLB;
    double output = KpLB * error + KiLB * integralValueLB + KdLB * derivative;
    if (output > 12000) output = 12000;
    else if (output < -12000) output = -12000;
    ladybrown.move_voltage(static_cast<int>(output));
    previousErrorLB = error;
}

void myTaskFunctionAuton() 
{
    while (!autonIsDone)
     {
        controlMotor();
        pros::delay(20);
    }
}




void myTaskFunctionDrive() 
{
    while (autonIsDone)
     {
        controlMotor();
        pros::delay(20);
    }
}




void initialize() 
{
    //AutonSelector auton_selector;
    //pros::Task controltask(controller_navigation);



  //ODOM SETUP
  chassis.odom_tracker_back_set(&horiz_tracker);
  chassis.odom_turn_bias_set(0.8);
  chassis.pid_odom_angular_constants_set(8, 0.0, 75);
  chassis.pid_odom_boomerang_constants_set(10, 0.0, 60);

  
  ez::ez_template_print();
  intake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  opt2.set_led_pwm(100);
  
  pros::delay(500);
  chassis.opcontrol_curve_buttons_toggle(true);  // Enables modifying the controller curve with buttons on the joysticks
  chassis.opcontrol_drive_activebrake_set(0);    // Sets the active brake kP. We recommend ~2.  0 will disable.
  chassis.opcontrol_curve_default_set(0, 0);     // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)
  
  // Set the drive to your own constants from autons.cpp!
  default_constants();
  
  // These are already defaulted to these buttons, but you can change the left/right curve buttons here!
  // chassis.opcontrol_curve_buttons_left_set(pros::E_CONTROLLER_DIGITAL_LEFT, pros::E_CONTROLLER_DIGITAL_RIGHT);  // If using tank, only the left side is used.
  // chassis.opcontrol_curve_buttons_right_set(pros::E_CONTROLLER_DIGITAL_Y, pros::E_CONTROLLER_DIGITAL_A);

  // Autonomous Selector using LLEMU
  ez::as::auton_selector.autons_add({



        Auton("TEST \n\n RED", soloAWP_Red_NEW),
      // Auton("Blue POS NO MID\n\n BLUE", BluePos_NOMID),      
   
      
      Auton("RED\n\n NEG CORNER", AWP_RedNeg),              // Working
      Auton("RED\n\n NEG NO AWS", AWP_BluePos),             // Working
      
      Auton("RED\n\n POSITIVE AWP", AWP_RedPos),            // Working
      Auton("RED\n\n POSITIVE NO MID", RedPos_NOMID), 
      
      Auton("RED\n\n SOLO AWP", soloAWP_Red_NEW),
      
      Auton("RED \n\n ELIM6RING", Elims_6rings_RED),       
      
      Auton("BLUE\n\n NEG CORNER", AWP_BlueNeg),            // Working
      Auton("BLUE\n\n NEG NO AWS", AWP_RedPos),             // Working
      
      Auton("BLUE\n\n POSITIVE AWP", AWP_BluePos),          // Working
      Auton("BLUE\n\n POSITIVE NO MID", BluePos_NOMID),     // Working
      
      Auton("BLUE\n\n SOLO AWP", soloAWP_Blue_NEW),
      
      Auton("BLUE \n\n ELIM6RING", Elims_6rings_BLUE),       
      


     // Auton("SKILLS \n\n SkillAuton", AWP_BlueNeg),
      // Auton("SOLO AWP Left\n\nSOLO AWP Left", soloAWP_LeftSide),
      // Auton("SOLO AWP Right\n\nSOLO AWP Right", soloAWP_RightSide),
      // Auton("Ellims 5 RED \n\nRED SIDE", Ellims_5rings_Red),
      // Auton("Ellims 5 BLUE\n\nBLUE SIDE", Ellims_5rings_Blue),
      // Auton("JustInCase Left\n\n 2 Rings", JustInCaseLeft),
      // Auton("JustInCase Right\n\n 2 Rings", JustInCaseRight),
      // Auton("SKILLS \n\n SkillAuton", Skills),
  });

  // Initialize chassis and auton selector
  chassis.initialize();
  ez::as::initialize();

  master.rumble(".");
    
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() 
{

}


void competition_initialize() 
{
  
  // . . .
}

void autonomous() 
{
  autonStarted = true;
  chassis.pid_targets_reset();                // Resets PID targets to 0
  chassis.drive_imu_reset();                  // Reset gyro position to 0
  chassis.drive_sensor_reset();               // Reset drive sensors to 0
  chassis.drive_brake_set(pros ::E_MOTOR_BRAKE_HOLD);  // Set motors to hold.  This helps autonomous consistency
  ladybrown.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  intake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  pros::Task myTask(myTaskFunctionAuton);
  ez::as::auton_selector.selected_auton_call();  // Calls selected auton from autonomous selector
  myTask.remove();
}



void opcontrol() 
{

  bool isSorting = false;
         
   int hue_detect_pos = 0;

  if(autonStarted)
    autonIsDone = true;


  pros::Task myTask(myTaskFunctionDrive);
    pros::motor_brake_mode_e_t driver_preference_brake = MOTOR_BRAKE_COAST;
  chassis.drive_brake_set(driver_preference_brake);
  ladybrown.set_brake_mode(E_MOTOR_BRAKE_HOLD);
 // intake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
 // opt1.set_led_pwm(100);
 // opt2.set_led_pwm(100);
 // pros::delay(300);
  static int last_stop_time = 0;
  static int hue_detect_time = 0;
  static bool is_paused = false;

  while (true) 
  {

    pros::lcd::clear_line(0);
    pros::lcd::clear_line(1);
    pros::lcd::clear_line(2);
    //master.clear_line(1);

    if(isSorting)
      master.print(1, 0, "Sort    ");
    else
      master.print(1, 0, "NO SORT    ");
    

    //master.clear_line(1);
    pros::lcd::print(1, "COLOR RIGHT: %.2f ",  opt2.get_hue());
    //pros::lcd::print(2, "Chassis %.2f ",  chassis.get));

    if (!pros::competition::is_connected()) 
    {
      if (master.get_digital_new_press(DIGITAL_X))
        chassis.pid_tuner_toggle();

      if (master.get_digital(DIGITAL_B) && master.get_digital(DIGITAL_DOWN)) 
      {
        autonomous();
        chassis.drive_brake_set(driver_preference_brake);
      }

      chassis.pid_tuner_iterate();  // Allow PID Tuner to iterate
    }

    chassis.opcontrol_tank();  // Tank control

    
   // COLOR SORT //
   if(master.get_digital_new_press(DIGITAL_UP))
   isSorting = !isSorting;

    if(master.get_digital(DIGITAL_R1) && master.get_digital(DIGITAL_R2))
      intake.move_voltage(-12000); // -8000

    

     
    else if(master.get_digital(DIGITAL_R1) &&  !master.get_digital(DIGITAL_R2) )
    {
         int current_time = pros::millis();

    bool optStatement = AllianceSet  ? opt2.get_hue() > 220.0 : opt2.get_hue() < 30.0  ;
    
    if (optStatement && isSorting)  // No Blues Detect: 100.0* // 200.0 // **150.0
    
    // No Reds Detect: 30.0* // 45.0 
    
    {
      // // Si el motor no está en pausa, configurar el inicio del temporizador
      //   if (hue_detect_time == 0) {
      //       hue_detect_time = current_time;
      //   }
      int current_pos = intake.get_position(); 
      int currentdist = opt1.get_distance();
      int threshold = 100;



      if (hue_detect_pos == 0) 
        hue_detect_pos = current_pos;

      if (current_pos - hue_detect_pos <= 230) 
        intake.move_voltage(12000); 


        else 
        {
          intake.move_voltage(-12000); 
          pros::delay(100);
          intake.move_voltage(0); 
          pros::delay(100);
          hue_detect_pos = 0;
        }


        
        // // Primera etapa: mantener el motor encendido durante 100 ms
        // if (abs(current_time - hue_detect_time) <= 100) { // 70 // *100
        //     intake.move_voltage(12000); // Motor activo
        // }
        // // Segunda etapa: detener el motor por 300 ms
        // else if (abs(current_time - hue_detect_time) <= 200) {
        //     intake.move_voltage(0); // *0
        //     pros::delay(50);
        //     intake.move_voltage(-12000); // *0
        //     pros::delay(100);
        //     // wait pause just for intake and flip these two and test as well

        //   //  intake.move_voltage(-12000); // *iniyan added
        //   // intake.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);// Motor detenido
        //    // is_paused = true; // Activar el estado de pausa
        // }
        // // Reiniciar después de la pausa
        // else {
        //     hue_detect_time = 0; // Reiniciar el temporizador
        //    // is_paused = false; // Salir de pausa
        // }
    } 
    
    
    
    
    else {
        // Si el HUE no es menor que 10, reiniciar todo
        hue_detect_time = 0;
        is_paused = false;
        intake.move_voltage(12000); // Motor sigue funcionando normalmente
    }
      flagMode = false;
    }



///////////////////////////////////////////////////




    else if(master.get_digital(DIGITAL_R2)  && !master.get_digital(DIGITAL_R1) )
    {
      intake.move_voltage(12000);
      flagMode = true;
    }
    else if(master.get_digital(DIGITAL_L1) && flagMode == true)	
      intake.move_voltage(-2000);
    else
      intake.move_voltage(0);

    if(flagMode == true)
      targetValueLB = 5650;
    else
      targetValueLB = 4000;

    if(master.get_digital(DIGITAL_L1) && rotationSensor.get_position() < 16500 && flagMode == true)
      ladybrown.move_voltage(8000); 
    else if((master.get_digital(DIGITAL_R2)  || master.get_digital(DIGITAL_L2))  && flagMode == true)
      controlMotor();
    else
    { 
      if( flagMode == false)
        controlMotor();
      else
        ladybrown.move_voltage(0); 
    }


    if(master.get_digital_new_press(DIGITAL_L1)  && flagMode == false)
      mobileToggle = !mobileToggle;
    if(mobileToggle)
      mobile.set_value(false);
    else if(!mobileToggle) 
      mobile.set_value(true); 




    if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) // && !flagMode)
    {
        doinkerToggle = !doinkerToggle;
        toggleStartTime = pros::millis(); 
    }
    if (doinkerToggle && pros::millis() - toggleStartTime > 5000) 
        doinkerToggle = false; 

    if(doinkerToggle)
      doinker.set_value(true);
    else if(!doinkerToggle) 
      doinker.set_value(false); 

    pros::delay(10);
  }
}