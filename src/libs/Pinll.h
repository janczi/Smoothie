struct pina{ 
unsigned int mask; 
void * pio;
unsigned char id; 
unsigned char type; 
unsigned char attr; 
};

class Pinll{
public:
	char port;
	char pin;
	struct pina pina;
//	Pinll();
	Pinll(char port_a, char pin_a);
	void SetInput();
	void SetOutput();
	bool Get();
	void Set();
	void Clear();



};
