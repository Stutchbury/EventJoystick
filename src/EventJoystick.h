/**
 * Based on the EventAnalog library, this is an event based library for 
 * analog joysticks - slice an analog range of each axis into configurable 
 * number of increments and a callback will be fired on each change of increment.
 * Effective noise reduction built in.
 * Also has an idle timeout callback.
 * 
 * Use EventButton to register event for the joystick button.
 * 
 * GPLv2 Licence https://www.gnu.org/licenses/old-licenses/gpl-2.0.txt
 * 
 * Copyright (c) 2023 Philip Fletcher <philip.fletcher@stutchbury.com>
 * 
 */

#include "Arduino.h"

#include <EventAnalog.h>

#ifndef EventJoystick_h
#define EventJoystick_h

#if defined(ARDUINO_ARCH_ESP32) || defined(ESP8266) || defined(CORE_TEENSY)
  #include <functional>
#endif

class EventJoystick {

  protected:

    #if defined(ARDUINO_ARCH_ESP32) || defined(ESP8266) || defined(CORE_TEENSY)
      typedef std::function<void(EventJoystick &btn)> EventJoystickCallback;
    #else
      typedef void (*EventJoystickCallback)(EventJoystick &);
    #endif

  public:

    EventAnalog x;
    EventAnalog y;

    /**
     * Construct a joystick
     */
    EventJoystick(byte analogX, byte analogY);

    EventJoystick();

    void update();


    /** ***************************************************
     * set joystick callback handlers
     */

    /**
     */
    void setChangedHandler(EventJoystickCallback f);
    /**
     */
    void setIdleHandler(EventJoystickCallback f);
    
    /** ***************************************
     *  joystick setup
     */

    /**
     * @brief Split the analog range of both axis into this number of slices.
     * A changed callback will be fire each time the increment changes. 
     * You can also set increments on individial axis after this has 
     * been called.
     * @param numIncr 
     */
    void setNumIncrements(uint8_t numIncr=10);

    /**
     * @brief Normally increments are set with setNumIncrements but
     * you can also set the negative and positive sides individually.
     * 
     * @param numIncr 
     */
    void setNumNegativeIncrements(uint8_t numIncr=10);
    /**
     * @brief Normally increments are set with setNumIncrements but
     * you can also set the negative and positive sides individually.
     * 
     * @param numIncr 
     */
    void setNumPositiveIncrements(uint8_t numIncr=10);

    void setCentreBoundary(uint16_t width=200);
    void setOuterBoundary(uint16_t width=100);

    /**
     * Set the idle timeout in ms (default 10000)
     * Note: this sets the idle timeout for both EventAnalog axis.
     * You can override them individually after setting this.
     */
    void setIdleTimeout(unsigned int timeoutMs);

    /**
     * Set an identifier, ignored by library (not unique, defaults to 0)
     * Useful when calling a common handler.
     * Note: Does not set the EventAnalog userId
     */
    void setUserId(unsigned int id);

    /**
     * Set the user state. Slight function creep but useful.
     * For use by implementor, ignored by library
     * eg ON, OFF, INACTIVE etc
     * Note: Does not set the EventAnalog userState
     */
    void setUserState(unsigned int s);


    /**
     * @brief Returns true of the position of either EventAnalog
     * axis has changed since previous update()
     * 
     * @return true 
     * @return false 
     */
    bool hasChanged();

    /**
     * Get the identifier (not unique, defaults to 0)
     */
    unsigned int userId();

    /**
     * Get the user state.
     */
    unsigned int userState();


    /**
     * Returns true if enabled or if either of the EventAnalg axis are enabled
     */
    bool enabled();

    /**
     * Set enabled to true (default) or false
     * This will enable/disable all event callbacks.
     * If allowRead is set to true, will still do analogRead
     * to allow manual setting of max negative/positive values without
     * firing callbacks
     * This is applied to both EventAnalog axis.
     */
    void enable(bool e=true, bool allowRead=false);

    /**
     * @brief Return true if no activity on both EventAnalog
     * axis for  longer than setIdleTimeout - irrespective of 
     * whether the idle (or changed) callback has been fired
     * 
     * @return true 
     * @return false 
     */
    bool isIdle();
    
    void setRateLimit(uint16_t ms);


  protected:
    
    //Encoder
    EventJoystickCallback changed_cb = NULL;
    EventJoystickCallback idle_cb = NULL;

  private:
    unsigned int _userId = 0;
    unsigned int _userState = 0;
    bool idleFired = false;



};

#endif


