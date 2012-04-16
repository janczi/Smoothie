/*  
      This file is part of Smoothie (http://smoothieware.org/). The motion control part is heavily based on Grbl (https://github.com/simen/grbl).
      Smoothie is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
      Smoothie is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
      You should have received a copy of the GNU General Public License along with Smoothie. If not, see <http://www.gnu.org/licenses/>. 
*/

#include <string>
#include <cstring>
#include <stdarg.h>
using std::string;
#include "libs/Module.h"
extern "C"{
#include "libs/samserial.h"
}
#include "libs/Kernel.h"
#include "libs/nuts_bolts.h"
#include "SerialConsole.h"
#include "libs/RingBuffer.h"
#include "libs/SerialMessage.h"
#include "libs/StreamOutput.h"

SerialConsole *console;

// Serial reading module
// Treats every received line as a command and passes it ( via event call ) to the command dispatcher. 
// The command dispatcher will then ask other modules if they can do something with it
SerialConsole::SerialConsole( const char* rx_pin, const char* tx_pin, int baud_rate ){
    //this->serial = new  Serial( rx_pin, tx_pin );
    //this->serial->baud(baud_rate);
}  

// Called when the module has just been loaded
extern "C"{
void serialcallback(unsigned char c){
	console->on_serial_char_received(c);
}
}

void SerialConsole::on_module_loaded() {
    console=this;
    setcallback(&serialcallback);
    // We want to be called every time a new char is received
    //this->serial->attach(this, &SerialConsole::on_serial_char_received, Serial::RxIrq);
    // We only call the command dispatcher in the main loop, nowhere else
    this->register_for_event(ON_MAIN_LOOP);
}
        
// Called on Serial::RxIrq interrupt, meaning we have received a char
void SerialConsole::on_serial_char_received(char received){

	//ccprintf("new char: \n");
        //On newline, we have received a line, else concatenate in buffer
        if( received == '\r' ){ return; }
        this->buffer.push_back(received); 
}
        
// Actual event calling must happen in the main loop because if it happens in the interrupt we will loose data
void SerialConsole::on_main_loop(void * argument){
    int index=this->find_char('\n');
    if( index>-1 ){
        char *recv=(char *)malloc((index+1)*sizeof(char));
	recv[index]='\0';
        int i=0;
	char c='\0';
        while(c!='\n'){
	   this->buffer.pop_front(c);           
           recv[i]=c;
	   ++i;   
        }
	struct SerialMessage message; 
        message.message = string(recv);
	free(recv);
	message.stream = this;
        this->kernel->call_event(ON_CONSOLE_LINE_RECEIVED, &message ); 
    }
}


int SerialConsole::printf(const char* format, ...){
    va_list args;
    int result; 
    va_start (args, format);
    char buf[128];
    result = vsprintf(buf,format, args);
    ccprintf(buf);
    va_end (args);
    printf_impl(buf);
    return result;
}


bool SerialConsole::has_char(char letter){
    int index = this->buffer.head;
    while( index != this->buffer.tail ){
        if( this->buffer.buffer[index] == letter ){
            return true;
        }
        index = this->buffer.next_block_index(index);
    }
    return false;
}

int SerialConsole::find_char(char letter){
    int index = this->buffer.head;
    while( index != this->buffer.tail ){
        if( this->buffer.buffer[index] == letter ){
            return index;
        }
        index = this->buffer.next_block_index(index);
    }
    return -1;
}
