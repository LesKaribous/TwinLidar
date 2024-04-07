#pragma once
#include "utils/geometry.h"
#include "utils/commandHandler.h"
#include <Arduino.h>

void registerCommands();

void command_enable(const args_t& args);
void command_disable(const args_t& args);
void command_status(const args_t& args); //Display all status
void command_status(const args_t& args); //Display single status
void command_debug(const args_t& args); //Display all status
void command_debug(const args_t& args); //Display single status

//Terminal
void command_help(const args_t& args);
void command_print(const args_t& args);