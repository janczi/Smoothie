extern "C"{
#include <board.h>
#include <pio/pio.h>
}
char ports[]={AT91C_BASE_PIOA,AT91C_BASE_PIOB,AT91C_BASE_PIOC}; 
char ios[]={AT91C_ID_PIOA,AT91C_ID_PIOB,AT91C_ID_PIOC}; 

Pinll::Pinll(){
}
Pinll::Pinll(char port_a, char pin_a){
	this->port=port_a;
	this->pin=pin_a;
	this->pina={1<<pin_a,ports[port_a],ios[port_a],PIO_INPUT, PIO_PULLUP};
	PIO_Configure(&(this->pina),1);
}
void Pinll::SetInput(){
	this->pina.type=PIO_INPUT;
	PIO_Configure(&(this->pina),1);

}
void Pinll::SetOutput(){
	this->pina.type=PIO_OUTPUT_0;
	PIO_Configure(&(this->pina),1);
}
bool Pinll::Get(){
	return PIO_Get(&(this->pina));
}
void Pinll::Set(){
	PIO_Set(&(this->pina));
}
void Pinll::Clear(){
	PIO_Clear(&(this->pina));
}
