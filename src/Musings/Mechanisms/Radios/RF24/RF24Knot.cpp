#include "RF24Knot.h"
#ifdef TANGLENET_RF24
RF24Knot RF24KnotInstance;
RF24Knot::RF24Knot(void):RF24(0,0) {

}
RF24Knot::setPins(uint8_t _cepin, uint8_t _cspin) { 
	ce_pin = _cepin;
	csn_pin = _cspin;
}
#endif
