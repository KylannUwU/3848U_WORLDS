/*
This Source Code Form is subject to the terms of the Mozilla Public
License, v. 2.0. If a copy of the MPL was not distributed with this
file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include "EZ-Template/sdcard.hpp"

#include <filesystem>

#include "EZ-Template/auton_selector.hpp"
#include "liblvgl/llemu.hpp"
#include "pros/colors.hpp"
#include "pros/llemu.hpp"
#include "pros/misc.h"
#include "EZ-Template/util.hpp"

namespace ez::as {
AutonSelector auton_selector{};

void auto_sd_update() {
  // If no SD card, return
  if (!ez::util::SD_CARD_ACTIVE) return;

  FILE* usd_file_write = fopen("/usd/auto.txt", "w");
  std::string cp_str = std::to_string(auton_selector.auton_page_current);
  char const* cp_c = cp_str.c_str();
  fputs(cp_c, usd_file_write);
  fclose(usd_file_write);
}

void auton_selector_initialize() {
  // If no SD card, return
  if (!ez::util::SD_CARD_ACTIVE) return;

  FILE* as_usd_file_read;
  // If file exists...
  if ((as_usd_file_read = fopen("/usd/auto.txt", "r"))) {
    char a_buf[10];
    fread(a_buf, 1, 10, as_usd_file_read);
    ez::as::auton_selector.auton_page_current = std::stof(a_buf);
    fclose(as_usd_file_read);
  }
  // If file doesn't exist, create file
  else {
    auto_sd_update();  // Writing to a file that doesn't exist creates the file
    printf("Created auto.txt\n");
  }

  if (ez::as::auton_selector.auton_page_current > ez::as::auton_selector.auton_count - 1 || ez::as::auton_selector.auton_page_current < 0) {
    ez::as::auton_selector.auton_page_current = 0;
    ez::as::auto_sd_update();
  }
}

void page_up() {
  if (auton_selector.auton_page_current == auton_selector.auton_count - 1)
    auton_selector.auton_page_current = 0;
  else
    auton_selector.auton_page_current++;
  auto_sd_update();
  auton_selector.selected_auton_print();
}

void page_down() {
  if (auton_selector.auton_page_current == 0)
    auton_selector.auton_page_current = auton_selector.auton_count - 1;
  else
    auton_selector.auton_page_current--;
  auto_sd_update();
  auton_selector.selected_auton_print();
}

void taskSelector()
{
    while(true)
  {
     if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)) 
      ez::as::page_down(); 
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) 
      ez::as::page_up(); 
  
   pros::delay(20);  
  }
}

bool auton_selector_running2 = false;

// Define los puertos para los bumper switches
pros::ADIDigitalIn bumper_next('C');  // Cambiar al siguiente autónomo
pros::ADIDigitalIn bumper_prev('D');  // Cambiar al anterior autónomo

void check_bumpers() {
  while (auton_selector_running2) {
    if (bumper_next.get_new_press()) { // Si el bumper de "siguiente" es presionado
      ez::as::page_up();
      ez::as::auton_selector.selected_auton_print();
      //pros::lcd::print(0, "Autónomo seleccionado: %s", ez::as::auton_selector.get_selected_auton().c_str());
    }

    if (bumper_prev.get_new_press()) { // Si el bumper de "anterior" es presionado
      ez::as::page_down();
      ez::as::auton_selector.selected_auton_print();
      //pros::lcd::print(0, "Autónomo seleccionado: %s", ez::as::auton_selector.get_selected_auton().c_str());
    }

    pros::delay(20); // Retraso para evitar lecturas duplicadas
  }
}



void initialize() {
  // Initialize auto selector and LLEMU
  pros::lcd::initialize();
 //pros::lcd::shutdown();
  //pros::lcd::set_background_color(COLOR_GOLD);
  ez::as::auton_selector_initialize();
  pros::screen::set_pen(0x00FF0000);
  pros::screen::fill_rect(0, 0, 480, 240);
  // Callbacks for auto selector
  ez::as::auton_selector.selected_auton_print();
 pros::lcd::register_btn0_cb(ez::as::page_down);
  pros::lcd::register_btn2_cb(ez::as::page_up);
  auton_selector_running2 = true;

  // Iniciar una tarea para monitorear los bumpers
  pros::Task bumper_task(check_bumpers);
    // Mostrar el primer autónomo
  ez::as::auton_selector.selected_auton_print();



  auton_selector_running = true;
}


void shutdown() {
  pros::lcd::shutdown();
  pros::lcd::register_btn0_cb(nullptr);
  pros::lcd::register_btn2_cb(nullptr);

  auton_selector_running = false;
}

bool enabled() { return auton_selector_running; }

bool turn_off = false;

// Using a button to control the lcd
pros::adi::DigitalIn* limit_switch_left = nullptr;
pros::adi::DigitalIn* limit_switch_right = nullptr;
pros::Task limit_switch_task(ez::as::limitSwitchTask);
void limit_switch_lcd_initialize(pros::adi::DigitalIn* right_limit, pros::adi::DigitalIn* left_limit) {
  if (!left_limit && !right_limit) {
    delete limit_switch_left;
    delete limit_switch_right;
    if (pros::millis() <= 100)
      turn_off = true;
    return;
  }
  turn_off = false;
  limit_switch_right = right_limit;
  limit_switch_left = left_limit;
  limit_switch_task.resume();
}

void limitSwitchTask() {
  while (true) {
    if (limit_switch_right && limit_switch_right->get_new_press())
      ez::as::page_up();
    else if (limit_switch_left && limit_switch_left->get_new_press())
      ez::as::page_down();

    if (pros::millis() >= 500 && turn_off)
      limit_switch_task.suspend();

    pros::delay(50);
  }
}
}  // namespace ez::as