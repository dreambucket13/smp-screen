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


//Blink Delay
#define DELAY			500

UC8151* uc8151;
PicoGraphics_Pen1BitY* graphics;

/***
 * Constructor
 * 
 */
Screen::Screen(std::string input) {
	text_to_display = input;

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
	stop();
}


 /***
  * Main Run Task for agent
  */
 void Screen::run(){

    	graphics->set_pen(0);
		graphics->clear();
		graphics->set_pen(15); //was 1
		graphics->set_font("bitmap8");

	while (true) { // Loop forever
		

	if (xSemaphoreTake(xSem, 0) == pdTRUE){

        graphics->clear();
		graphics->text(text_to_display, {0, 0}, 296);
		uc8151->update(graphics);
        printf("%s on Core %d\n", pName, getCore());

		xSemaphoreGive(xSem);

	}



	}

 }

/***
 * Get the static depth required in words
 * @return - words
 */
configSTACK_DEPTH_TYPE Screen::getMaxStackSize(){
	return 150;
}
