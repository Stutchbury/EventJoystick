/**
 *
 * GPLv2 Licence https://www.gnu.org/licenses/old-licenses/gpl-2.0.txt
 * 
 * Copyright (c) 2023 Philip Fletcher <philip.fletcher@stutchbury.com>
 * 
 */


#include "EventJoystick.h"


EventJoystick::EventJoystick(byte analogX, byte analogY)
  : x(analogX), y(analogY) {
  x.setStartValue(analogRead(analogX));
  y.setStartValue(analogRead(analogY));
  setCentreBoundary(200);
}
EventJoystick::EventJoystick() {
  enable(false,false);
}


void EventJoystick::update() {
  x.update();
  y.update();
  if ( x.hasChanged() || y.hasChanged() ) {
    if (changed_cb != NULL) changed_cb(*this);
  }
  if ( idleFired && (!x.isIdle() || !y.isIdle() ) ) {
    idleFired = false;
  }
  if ( !idleFired && x.isIdle() && y.isIdle() ) {
    if (enabled() ) {
      if (idle_cb != NULL) idle_cb(*this);
    }
    idleFired = true; //We don't want the idle to fire after re-enabling
  }
}

void EventJoystick::setChangedHandler(EventJoystickCallback f) { changed_cb = f; }

void EventJoystick::setIdleHandler(EventJoystickCallback f) { idle_cb = f; }

void EventJoystick::setNumIncrements(uint8_t numIncr /*=10*/) {
  x.setNumIncrements(numIncr);
  y.setNumIncrements(numIncr);
}

void EventJoystick::setNumNegativeIncrements(uint8_t numIncr /*=10*/) {
  x.setNumNegativeIncrements(numIncr);
  y.setNumNegativeIncrements(numIncr);
}

void EventJoystick::setNumPositiveIncrements(uint8_t numIncr /*=10*/) {
  x.setNumPositiveIncrements(numIncr);
  y.setNumPositiveIncrements(numIncr);
}

void EventJoystick::setCentreBoundary(uint16_t width /*=200*/) {
  x.setStartBoundary(width);
  y.setStartBoundary(width);
}

void EventJoystick::setOuterBoundary(uint16_t width /*=100*/) {
  x.setEndBoundary(width);
  y.setEndBoundary(width);
}

void EventJoystick::setIdleTimeout(unsigned int timeoutMs) {
  x.setIdleTimeout(timeoutMs);
  y.setIdleTimeout(timeoutMs);
}


bool EventJoystick::hasChanged() {
  return x.hasChanged() || y.hasChanged();
}

unsigned int EventJoystick::userId() { return _userId; }

unsigned int EventJoystick::userState() { return _userState; }

bool EventJoystick::enabled() { return x.enabled() && y.enabled(); }

void EventJoystick::enable(bool e, bool allowRead) { 
  x.enable(e, allowRead);
  y.enable(e, allowRead);
}


bool EventJoystick::isIdle() {
  //Return true if idle (whether idle callback defined or not)
  return x.isIdle() && y.isIdle();
}

void EventJoystick::setRateLimit(uint16_t ms) {
  x.setRateLimit(ms);
  y.setRateLimit(ms);
}

