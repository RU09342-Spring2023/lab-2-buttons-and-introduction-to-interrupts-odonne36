## Intro

The code in the occupancy detector file is a program that acts as an alarm system for a room. 

## Armed State

The system starts out in an armed state that is indicated by a green LED blinking every second. If there is a person in the room
(indicated by a button press), the system now moves into the next state.

## Alert State

If the system detects a person (button press) then it will go into the alert state. This is indicated by the red led blinking and the green led
turned off. There are two ways to get out of this state: if the system determines that after 10 seconds there is still a person in the room (button still held down)
the system goes into the alarm state. If the system doesn't detect a person after the 10 seconds, it resets everything and goes back to the armed state.

## Alarm State

If the alarm is triggered, then the red led is constantly on and the original button will no longer work. The only way to get out of
this state is to press the other button which resets the system and goes back to the armed state.