#include "MomentaryButton.h"


MomentaryButton::MomentaryButton(int inputPin)
	: wasClosed(false), pin(inputPin), holdReported(false)
{}

void MomentaryButton::setup()
{
	pinMode(pin, INPUT);
	digitalWrite(pin, HIGH);
}

void MomentaryButton::check()
{
	unsigned long currentTimeMillis = millis();
	boolean isClosed = (digitalRead(pin) == LOW);

	if (isClosed != wasClosed)
	{
		if (isClosed)
		{
			closeTimeMillis = currentTimeMillis;
		}
		else
		{
			holdReported = false;
		}
	}

	clicked = held = false;
	boolean overHoldThreshold =
		(currentTimeMillis - closeTimeMillis) >= HOLD_THRESHOLD;
	if (isClosed && overHoldThreshold)
	{
		held = true;
	}
	else if (!isClosed && wasClosed && !overHoldThreshold)
	{
		clicked = true;
	}

	wasClosed = isClosed;
}

boolean MomentaryButton::wasClicked() {
	return clicked;
}

boolean MomentaryButton::wasHeld() {
	if (held && !holdReported)
	{
        	holdReported = true;
        	return held;
	}
	else
	{
        	return false;
	}
}

// Getters
        int MomentaryButton::getPin(){return pin;}
        unsigned long MomentaryButton::getCloseTimeMillis(){return closeTimeMillis;}
//        boolean MomentaryButton::getWasHeld(){return wasHeld;}
        boolean MomentaryButton::getWasClosed(){return wasClosed;}
        boolean MomentaryButton::getHeld(){return held;}
        boolean MomentaryButton::getClicked(){return clicked;}
        unsigned long MomentaryButton::getHoldThreshold(){return HOLD_THRESHOLD;}
        unsigned long MomentaryButton::getBounceThreshold(){return 50;}
// Setters
        void MomentaryButton::setCloseTimeMillis(unsigned long value){closeTimeMillis = value;}
//        void MomentaryButton::setWasHeld(boolean value){wasHeld = value;}
        void MomentaryButton::setWasClosed(boolean value){wasClosed = value;}
        void MomentaryButton::setHeld(boolean value){held = value;}
        void MomentaryButton::setClicked(boolean value){clicked = value;}




