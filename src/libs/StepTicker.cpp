/*  
      This file is part of Smoothie (http://smoothieware.org/). The motion control part is heavily based on Grbl (https://github.com/simen/grbl).
      Smoothie is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
      Smoothie is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
      You should have received a copy of the GNU General Public License along with Smoothie. If not, see <http://www.gnu.org/licenses/>. 
*/



using namespace std;
#include <vector>
#include "libs/Module.h"
#include "libs/Kernel.h"
#include "StepTicker.h"
#include "libs/Hook.h"
extern "C" {
#include <math.h>
#include <board.h>
#include <irq/irq.h>
#include <tc/tc.h>
}
StepTicker* global_step_ticker;


extern "C" void TC1_IrqHandler (void){
    volatile unsigned int dummy;
    // Clear status bit to acknowledge interrupt
    if(AT91C_BASE_TC1->TC_SR & AT91C_TC_CPCS){  // If interrupt register set for register C
        global_step_ticker->tick(); 
    }

    if(AT91C_BASE_TC1->TC_SR & AT91C_TC_CPBS){  // If interrupt register set for register B
        global_step_ticker->reset_tick();
    }
    dummy = AT91C_BASE_TC1->TC_SR;
    
}



StepTicker::StepTicker(){
    global_step_ticker = this;
    AT91C_BASE_TC1->TC_RB = 0;
    
}

void StepTicker::set_frequency( int frequency ){
    this->frequency = 1.0*frequency;
    unsigned int div;
    unsigned int tcclks;

    // Enable peripheral clock
    AT91C_BASE_PMC->PMC_PCER = 1 << AT91C_ID_TC1;

    // Configure TC for a 4Hz frequency and trigger on RC compare
    TC_FindMckDivisor(frequency, BOARD_MCK, &div, &tcclks);
    TC_Configure(AT91C_BASE_TC1, tcclks | AT91C_TC_CPCTRG);
    AT91C_BASE_TC1->TC_RC = (BOARD_MCK / div) / frequency; // timerFreq / desiredFreq
    this->div=div;
    // Configure and enable interrupt on RC compare
    IRQ_ConfigureIT(AT91C_ID_TC1, 0, TC1_IrqHandler);
    AT91C_BASE_TC1->TC_IER = AT91C_TC_CPCS;
    IRQ_EnableIT(AT91C_ID_TC1);
    //TC_Start(AT91C_BASE_TC1);
    
    
}

void StepTicker::set_reset_delay( double seconds ){
    AT91C_BASE_TC1->TC_RB = int(floor(double(BOARD_MCK/(this->div))*( seconds )));  // SystemCoreClock/divisor = Timer increments in a second
    AT91C_BASE_TC1->TC_IER = AT91C_TC_CPCS|AT91C_TC_CPBS;
    TC_Start(AT91C_BASE_TC1);

}

void StepTicker::tick(){
    
    for (int i=0; i<this->hooks.size(); i++){ 
        this->hooks.at(i)->call();
    }
}

void StepTicker::reset_tick(){
    for (int i=0; i<this->reset_hooks.size(); i++){ 
        this->reset_hooks.at(i)->call();
    }
}


