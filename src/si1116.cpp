/**
  @file si1116.cpp

  @authors Diode IoT Inc. <info@diodeiot.com>

  @authors Kadir Sevil <kadir.sevil@diodeiot.com>

  @copyright Copyright (c) 2021-2022 Diode Iot Inc. All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "si1116.h"

#define ARRLEN(x) ((sizeof(x)) / (sizeof(*x)))

#define GET_STATE(x, y) ((!x) != (!y))

SI1116 si1116;

const int SI1116::led[1][2] = {{2, HIGH}};

const int SI1116::button[1][2] = {{0, LOW}};

const int SI1116::ch_lookup[16][2] = {{22, LOW},
                                      {21, LOW},
                                      {19, LOW},
                                      {18, LOW},
                                      {5, LOW},
                                      {17, LOW},
                                      {16, LOW},
                                      {4, LOW},
                                      {23, LOW},
                                      {13, LOW},
                                      {32, LOW},
                                      {33, LOW},
                                      {25, LOW},
                                      {26, LOW},
                                      {27, LOW},
                                      {14, LOW}};

SI1116::SI1116(void)
{
}

SI1116::~SI1116(void)
{
}

void SI1116::init(unsigned long debounce_time)
{
  this->debounce_time = debounce_time;

  previous_steady_state = digitalRead(button[0][0]);
  last_steady_state = previous_steady_state;
  last_fickle_state = previous_steady_state;
  last_debounce_time = 0;

  digitalWrite(led[0][0], GET_STATE(led[0][1], LOW));
  pinMode(led[0][0], OUTPUT);

  pinMode(button[0][0], INPUT);

  for(int i = 0; i < ARRLEN(ch_lookup); i++)
  {
    digitalWrite(ch_lookup[i][0], GET_STATE(ch_lookup[i][1], LOW));
    pinMode(ch_lookup[i][0], OUTPUT);
  }
}

void SI1116::deinit(void)
{
  pinMode(led[0][0], INPUT);

  pinMode(button[0][0], INPUT);

  for(int i = 0; i < ARRLEN(ch_lookup); i++)
  {
    pinMode(ch_lookup[i][0], INPUT);
  }
}

void SI1116::loop(void)
{
  unsigned long current_time = millis();

  int current_state = digitalRead(button[0][0]);

  if(current_state != last_fickle_state)
  {
    last_debounce_time = current_time;
    last_fickle_state = current_state;
  }

  if((current_time - last_debounce_time) >= debounce_time)
  {
    previous_steady_state = last_steady_state;
    last_steady_state = current_state;
  }
}

void SI1116::ledSet(int state)
{
  digitalWrite(led[0][0], GET_STATE(led[0][1], state));
}

void SI1116::ledOn(void)
{
  ledSet(1);
}

void SI1116::ledOff(void)
{
  ledSet(0);
}

bool SI1116::isButtonPressed(void)
{
  return previous_steady_state == HIGH && last_steady_state == LOW;
}

bool SI1116::isButtonReleased(void)
{
  return previous_steady_state == LOW && last_steady_state == HIGH;
}

void SI1116::setRelay(int chNum, int state)
{
  if(chNum < 1 || chNum > ARRLEN(ch_lookup))
  {
    return;
  }

  digitalWrite(ch_lookup[chNum - 1][0], GET_STATE(ch_lookup[chNum - 1][1], state));
}

int SI1116::getRelay(int chNum)
{
  if(chNum < 1 || chNum > ARRLEN(ch_lookup))
  {
    return -1;
  }

  return GET_STATE(ch_lookup[chNum - 1][1], digitalRead(ch_lookup[chNum - 1][0]));
}

void SI1116::allOnRelay(void)
{
  for(int i = 0; i < ARRLEN(ch_lookup); i++)
  {
    digitalWrite(ch_lookup[i][0], GET_STATE(ch_lookup[i][1], HIGH));
  }
}

void SI1116::allOffRelay(void)
{
  for(int i = 0; i < ARRLEN(ch_lookup); i++)
  {
    digitalWrite(ch_lookup[i][0], GET_STATE(ch_lookup[i][1], LOW));
  }
}

void SI1116::openRelay1(void)
{
  setRelay(1, HIGH);
}

void SI1116::closeRelay1(void)
{
  setRelay(1, LOW);
}

int SI1116::getRelay1(void)
{
  return getRelay(1);
}

void SI1116::openRelay2(void)
{
  setRelay(2, HIGH);
}

void SI1116::closeRelay2(void)
{
  setRelay(2, LOW);
}

int SI1116::getRelay2(void)
{
  return getRelay(2);
}

void SI1116::openRelay3(void)
{
  setRelay(3, HIGH);
}

void SI1116::closeRelay3(void)
{
  setRelay(3, LOW);
}

int SI1116::getRelay3(void)
{
  return getRelay(3);
}

void SI1116::openRelay4(void)
{
  setRelay(4, HIGH);
}

void SI1116::closeRelay4(void)
{
  setRelay(4, LOW);
}

int SI1116::getRelay4(void)
{
  return getRelay(4);
}

void SI1116::openRelay5(void)
{
  setRelay(5, HIGH);
}

void SI1116::closeRelay5(void)
{
  setRelay(5, LOW);
}

int SI1116::getRelay5(void)
{
  return getRelay(5);
}

void SI1116::openRelay6(void)
{
  setRelay(6, HIGH);
}

void SI1116::closeRelay6(void)
{
  setRelay(6, LOW);
}

int SI1116::getRelay6(void)
{
  return getRelay(6);
}

void SI1116::openRelay7(void)
{
  setRelay(7, HIGH);
}

void SI1116::closeRelay7(void)
{
  setRelay(7, LOW);
}

int SI1116::getRelay7(void)
{
  return getRelay(7);
}

void SI1116::openRelay8(void)
{
  setRelay(8, HIGH);
}

void SI1116::closeRelay8(void)
{
  setRelay(8, LOW);
}

int SI1116::getRelay8(void)
{
  return getRelay(8);
}

void SI1116::openRelay9(void)
{
  setRelay(9, HIGH);
}

void SI1116::closeRelay9(void)
{
  setRelay(9, LOW);
}

int SI1116::getRelay9(void)
{
  return getRelay(9);
}

void SI1116::openRelay10(void)
{
  setRelay(10, HIGH);
}

void SI1116::closeRelay10(void)
{
  setRelay(10, LOW);
}

int SI1116::getRelay10(void)
{
  return getRelay(10);
}

void SI1116::openRelay11(void)
{
  setRelay(11, HIGH);
}

void SI1116::closeRelay11(void)
{
  setRelay(11, LOW);
}

int SI1116::getRelay11(void)
{
  return getRelay(11);
}

void SI1116::openRelay12(void)
{
  setRelay(12, HIGH);
}

void SI1116::closeRelay12(void)
{
  setRelay(12, LOW);
}

int SI1116::getRelay12(void)
{
  return getRelay(12);
}

void SI1116::openRelay13(void)
{
  setRelay(13, HIGH);
}

void SI1116::closeRelay13(void)
{
  setRelay(13, LOW);
}

int SI1116::getRelay13(void)
{
  return getRelay(13);
}

void SI1116::openRelay14(void)
{
  setRelay(14, HIGH);
}

void SI1116::closeRelay14(void)
{
  setRelay(14, LOW);
}

int SI1116::getRelay14(void)
{
  return getRelay(14);
}

void SI1116::openRelay15(void)
{
  setRelay(15, HIGH);
}

void SI1116::closeRelay15(void)
{
  setRelay(15, LOW);
}

int SI1116::getRelay15(void)
{
  return getRelay(15);
}

void SI1116::openRelay16(void)
{
  setRelay(16, HIGH);
}

void SI1116::closeRelay16(void)
{
  setRelay(16, LOW);
}

int SI1116::getRelay16(void)
{
  return getRelay(16);
}