/*
    This file is a part of the wiringBone library
    Copyright (C) 2015 Abhraneel Bera

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 3 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
    USA
*/

// Standard header files
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <errno.h>
#include <sys/time.h>

#include "CommonDefines.h"
#include "CLOCK.h"

static uint64_t startMillis, startMicros;

void startClock()
{
  struct timeval timeValue;

  gettimeofday(&timeValue, NULL);

  startMillis = (uint64_t)timeValue.tv_sec * (uint64_t)1000    + (uint64_t)(timeValue.tv_usec / 1000);
  startMicros = (uint64_t)timeValue.tv_sec * (uint64_t)1000000 + (uint64_t)(timeValue.tv_usec);
}

void delay(uint32_t duration)
{
  struct timeval currentTime, delayLength, endTime;

  gettimeofday(&currentTime, NULL);

  delayLength.tv_sec  = duration / 1000;
  delayLength.tv_usec = (duration % 1000) * 1000;  

  timeradd(&currentTime, &delayLength, &endTime);

  while(timercmp(&currentTime, &endTime, <))
  gettimeofday(&currentTime, NULL);
}

void delayMicroseconds(uint32_t duration)
{
  struct timeval currentTime, delayLength, endTime;

  gettimeofday(&currentTime, NULL);

  delayLength.tv_sec  = duration / 1000000;
  delayLength.tv_usec = duration % 1000000;  

  timeradd(&currentTime, &delayLength, &endTime);

  while(timercmp(&currentTime, &endTime, <))
  gettimeofday(&currentTime, NULL);
}

uint32_t millis()
{
  struct timeval currentTime;

  gettimeofday(&currentTime,  NULL);

  return((uint32_t)( ((uint64_t)currentTime.tv_sec * (uint64_t)1000 + (uint64_t)(currentTime.tv_usec / 1000)) - startMillis));
}

uint32_t micros()
{
  struct timeval currentTime;

  gettimeofday(&currentTime,  NULL);

  return((uint32_t)( ((uint64_t)currentTime.tv_sec * (uint64_t)1000000 + (uint64_t)currentTime.tv_usec) - startMicros));
}

//added by fkb 16/11/22

void delayMillis(uint32_t duration){
    delay(duration);
}

void delayMicros(uint32_t duration){
    delayMicroseconds(duration);
}

uint32_t millisFromStart(){
  return millis();
}

uint32_t microsFromStart(){
  return micros();
}


/*string timeFromInternet(){
#if defined(WIRE) || defined(WIFI)
  FILE *fp;
  char buf[20];
  // assume the system time synchronizes with the Internet time
  fp = popen("sudo date -u \"+\%Y/\%m/\%d %H:%M:%S\"", "r");
  fgets(buf, sizeof(buf),fp);
  pclose(fp);
  string res(buf, strlen(buf));
  return res;
#else
  string res("Internet is not available!!");
  return res;
#endif
}





string tl_time_Int2String(int val){
    char buf[10];
    sprintf(buf, "%d", val);
    string res(buf, strlen(buf));
    return res;
}

string timeFromGPS(){
#ifdef GPS
    date_time temp = TL_GPS.timeData();
    string str;
    str = str + tl_time_Int2String(temp.year) + "/" + tl_time_Int2String(temp.month) + '/' + tl_time_Int2String(temp.day) + " " + tl_time_Int2String(temp.hour) + ":" + tl_time_Int2String(temp.minute) + ":" + tl_time_Int2String(temp.second);
    return str;
#else
    string res("GPS is not available!!");
    return res;
#endif
}*/
