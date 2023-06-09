# Konami4PlayerFreePlayHelper
An arduino sketch to help you if you have buttons hard wired to coin mechs to give Konami 4 player fighting games a free play mode.

## Problem
4 player Konami arcade games like The Simpsons, X-Men, and Teenage Mutant Ninja Turtles don't have a free play option. Many home arcade enthusiasts wire buttons up to the coin mechs to simulate a coin going in. The reason this doesn't work is because kids can't help but spam the coin button and add 99 lives to their character. Then they drop out or get bored and spam 99 lives onto another character. Then you end up with a character that nobody is there to control and no way to drop them out of the game. I've tried telling the children "Only press the coin in button when you die", but the satisfying sound and feeling of spamming the button is too great.

## Solution
This is an Arduino sketch that takes an input pin (attached to the coin mech button) and writes to an output pin (to the coin mech itself), but after the button is lifted there's an 8 second timer before the button will register being pressed again. This makes it impossible to spam the button rapidly. Kids will actually play the game and forget about spamming lives (in theory). It does this for 4 pairs of pins. If you flash this onto a 5V arduino you can wire up vcc, ground, and the 4 input and output pins. Exact pin numbers are constants at the top of the .ino file. 

Feel free to clone this repo and change the pins or the delay time (or anything else you want). This was originally designed for an Arduino Nano Pro and the pins line up nicely there.

## tldr
This sketch disables a button for a period of time after you press it.
