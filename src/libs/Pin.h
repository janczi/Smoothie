#ifndef PIN_H
#define PIN_H

//#include "mbed.h" //Required for LPC_GPIO* . can probably be found in one othe the files mbed.h includes. TODO
//#include "../gcc4mbed/external/mbed/LPC1768/LPC17xx.h"
#include "libs/Kernel.h"
#include "libs/utils.h"
#include <string>
#include <cstring>
#include <cstdlib>
#include "libs/Pinll.h"
class Pin{
    public:
        Pin(){ }

        Pin* from_string(std::string value){
            char port = atoi(value.substr(0,1).c_str()); 
            this->inverting = ( value.find_first_of("!")!=string::npos ? true : false );
            char pinnum  = atoi( value.substr(2, value.size()-2-(this->inverting?1:0)).c_str() );
            this->pin=new Pinll(port,pinnum);
            return this;
        }

        inline Pin*  as_output(){
            this->pin->SetOutput();
            return this;
        }  

        inline Pin*  as_input(){
            this->pin->SetInput();
            return this;
        }  

        inline bool get(){
            if( this->inverting ){
               return ~(( this->pin->Get() ) & 1);
            }else{
               return  (( this->pin->Get() ) & 1);
            }
        }

        inline void set(bool value){
            // TODO : This should be bitmath 
            if( this->inverting ){ value = !value; }
            if( value ){
                this->pin->Set();
            }else{
                this->pin->Clear();
            }        
        }

        bool inverting; 
        Pinll *pin;
};




#endif
