/*
 * Screen.cpp
 *
 *  Created on: 15 Aug 2022
 *      Author: jondurrant
 */

#include "Screen.h"

#include "stdio.h"

//includes from screen demo
#include <string.h>
#include <math.h>
#include <vector>
#include <cstdlib>

#include "drivers/uc8151/uc8151.hpp"
#include "libraries/pico_graphics/pico_graphics.hpp"
#include "button.hpp"


using namespace pimoroni;


//Screen Delay
#define DELAY			portTICK_PERIOD_MS(3000) 

UC8151* uc8151;
PicoGraphics_Pen1BitY* graphics;

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

/***
 * Constructor
 * 
 */
Screen::Screen() {

    uc8151 = new UC8151(296, 128, ROTATE_0);
    graphics = new PicoGraphics_Pen1BitY(uc8151->width, uc8151->height, nullptr);

    Button button_a(Pin::A);
    Button button_b(Pin::B);
    Button button_c(Pin::C);
    Button button_d(Pin::D);
    Button button_e(Pin::E);

    xSem = xSemaphoreCreateBinary( );
	if (xSem == NULL){
		printf("ERROR could not create semaphore\n");
	} else {
		xSemaphoreGive(xSem);
	}

}

/***
 * Destructor
 */
Screen::~Screen() {

    delete uc8151;
    delete graphics;

	if (xSem != NULL){
		vSemaphoreDelete(xSem);
	}

}



 bool Screen::WriteToScreen(std::string text_to_display){

	if (xSemaphoreTake(xSem, 0) == pdTRUE){

        graphics->set_pen(0);
        graphics->clear();
        graphics->set_pen(15); 
        graphics->set_font("bitmap8");

		graphics->text(text_to_display, {0, 0}, 296);
		uc8151->update(graphics);

		//vTaskDelay(DELAY);

		xSemaphoreGive(xSem);

		return true;

	}

	return false;
 }
