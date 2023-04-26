/*
 * BlinkAgent.h
 *
 * Active agent to run as task and blink and LED on the given GPIO pad
 *
 *  Created on: 15 Aug 2022
 *      Author: jondurrant
 */

#ifndef BLINKAGENT_H_
#define BLINKAGENT_H_

#include <string>

#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "Agent.h"


class Screen: public Agent {
public:
	/***
	 * Constructor
	 * 
	 */
	Screen(std::string input);

	/***
	 * Destructor
	 */
	virtual ~Screen();

	enum Pin {
    A           = 12,
    B           = 13,
    C           = 14,
    D           = 15,
    E           = 11,
    UP          = 15, // alias for D
    DOWN        = 11, // alias for E
    USER        = 23,
    CS          = 17,
    CLK         = 18,
    MOSI        = 19,
    DC          = 20,
    RESET       = 21,
    BUSY        = 26,
    VBUS_DETECT = 24,
    LED         = 25,
    BATTERY     = 29,
    ENABLE_3V3  = 10
};



protected:

	/***
	 * Run loop for the agent.
	 */
	virtual void run();


	/***
	 * Get the static depth required in words
	 * @return - words
	 */
	virtual configSTACK_DEPTH_TYPE getMaxStackSize();

	//GPIO PAD for LED;  TODO - remove
	uint8_t xLedPad = 0;

	std::string text_to_display;

	SemaphoreHandle_t xSem = NULL;

};


#endif /* BLINKAGENT_H_ */
