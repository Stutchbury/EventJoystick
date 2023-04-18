/**
 * A basic example of using the EventJoystick library.
 */
#include <EventJoystick.h>

/**
 * Instantiate an EventJoystick.
 * Must be analog pins
 */
EventJoystick ej1(A0,A1);


/**
 * A function to handle the 'changed' event for either
 * the x or y axis.
 * Can be called anything but requires EventJoystick& 
 * as its only parameter.
 */
void onEj1Changed(EventJoystick& ej) {
  Serial.print("ej1 changed. X position: ");
  Serial.print(ej.x.position());
  Serial.print(", Y position: ");
  Serial.println(ej.y.position());
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(500);
  Serial.println("EventJoystick Basic Example");

  /**
   * EventJoystick will attempt to set the start value for X & Y 
   * when instatiated but on some microcontrollers, analogRead is
   * not setup in time.
   * If yu are not seing positve and negative values for each axis, 
   * uncomment the following two lines:
   */
  //ej1.x.setStartValue(analogRead(A0));
  //ej1.y.setStartValue(analogRead(A1));

  ej1.setNumIncrements(50);
  //Link the event(s) you require to your function
  ej1.setChangedHandler(onEj1Changed);
   
}

void loop() {
  // put your main code here, to run repeatedly:
  /**
   * You must call update() for every defined EventJoystick.
   * This will read the state of the both axis in the
   * EventJoystick and fire the appropriate events.
   */
  ej1.update();
}
