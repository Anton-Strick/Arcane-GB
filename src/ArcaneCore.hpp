#pragma once

#ifndef ARCANECORE_HPP
#define ARCANECORE_HPP

#include <Arduino.h>
#include <WiFi.h>
#include <WebSocketsClient.h>

#include "robotControl.hpp"
#include "GameController.hpp"
#include "WirelessController.hpp"

String ssid = "The Wifi";
String password = "ThePassword";
String url = "192.168.1.75";
//String url = "agbackend.herokuapp.com";

RobotControl robot;
GameController game;
WirelessController wireless(ssid, password, url);

WebSocketsClient webSocket;

hw_timer_t * timer = NULL;
char in;
volatile bool complete;

void IRAM_ATTR stepperISR();
void timerInit();
void socketEventRecieved(WStype_t type, uint8_t * payload, size_t length);

#endif