extern "C"{
#include <board.h>
#include <pio/pio.h>
}
#include "libs/Pinll.h"
_AT91S_PIO* ports[]={AT91C_BASE_PIOA,AT91C_BASE_PIOB,AT91C_BASE_PIOC}; 
char ios[]={AT91C_ID_PIOA,AT91C_ID_PIOB,AT91C_ID_PIOC}; 

Pinll::Pinll(char port_a, char pin_a){
	this->port=port_a;
	this->pin=pin_a;
	this->pina.mask=1<<pin_a;
	this->pina.pio=ports[port_a];
	this->pina.id=ios[port_a];
	this->pina.type=PIO_INPUT;
	this->pina.attr=PIO_PULLUP;
	PIO_Configure((const Pin*)(&(this->pina)),1);
}
void Pinll::SetInput(){
	this->pina.type=PIO_INPUT;
	PIO_Configure((const Pin*)(&(this->pina)),1);

}
void Pinll::SetOutput(){
	this->pina.type=PIO_OUTPUT_0;
	PIO_Configure((const Pin*)(&(this->pina)),1);
}
bool Pinll::Get(){
	return PIO_Get((const Pin*)(&(this->pina)));
}
void Pinll::Set(){
	PIO_Set((const Pin *)(&(this->pina)));
}
void Pinll::Clear(){
	PIO_Clear((const Pin *)(&(this->pina)));
}
