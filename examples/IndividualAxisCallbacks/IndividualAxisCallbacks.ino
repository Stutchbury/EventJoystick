/**
 * An example of using the EventJoystick library with callbacks for induvidual axis.
 */
#include <EventJoystick.h>

/**
 * Instantiate an EventJoystick.
 * Must be analog pins
 */
EventJoystick ej1(A0,A1);

/**
 * A function to handle the X axis 'changed' event
 * Can be called anything but requires EventAnalog& 
 * as its only parameter.
 * Note: Here we are specifying an EventAnalog type
 * not an EventJoystick.
 */
void onEj1XChanged(EventAnalog& ej) {
  Serial.print("ej1 changed. X position: ");
  Serial.println(ej.position());
}

/**
 * A function to handle the Y axis 'changed' event
 * Can be called anything but requires EventAnalog& 
 * as its only parameter.
 * Note: Here we are specifying an EventAnalog type
 * not an EventJoystick.
 */
void onEj1YChanged(EventAnalog& ej) {
  Serial.print("ej1 changed. Y position: ");
  Serial.println(ej.position());
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(500);
  Serial.println("EventJoystick Individual Axis Callback Example");

  /**
   * EventJoystick will attempt to set the start value for X & Y 
   * when instantiated but on some microcontrollers, analogRead is
   * not setup in time.
   * If yu are not seing positve and negative values for each axis, 
   * uncomment the following two lines:
   */
  //ej1.x.setStartValue(analogRead(A0));
  //ej1.y.setStartValue(analogRead(A1));

  //Link the event(s) you require to your function
  /**
   * Here we are setting the changed handlers on the individual axis.
   */
  ej1.x.setChangedHandler(onEj1XChanged);
  ej1.y.setChangedHandler(onEj1YChanged);
   
}

void loop() {
  // put your main code here, to run repeatedly:
  /**
   * You must call update() for every defined EventJoystick.
   * This will read the state of the both axis in the
   * EventJoystick and fire the appropriate events.
   * Do not call the individual axis update() method.
   */
  ej1.update();
}
