#pragma once

#ifndef ARCANECORE_HPP
#define ARCANECORE_HPP

#include <Arduino.h>

#include "robotControl.hpp"
#include "GameController.hpp"
#include "WirelessController.hpp"

String ssid = "The Wifi";
String password = "ThePassword";
String url = "ws:\\192.168.1.75:8000";

RobotControl robot;
GameController game;
WirelessController wireless(ssid, password, url);

Queue * gameQueue;

hw_timer_t * timer = NULL;
char in;
volatile bool complete;

std::array<int8_t, 2> startPos;
std::array<int8_t, 2> endPos;

void IRAM_ATTR stepperISR();
void timerInit();

#endif