#include "RF24Knot.h"
#include "TangleNet.h"
RF24Knot RF24KnotInstance;
extern LogWeaver LogWeaverInstance;
const uint32_t pipes[2] PROGMEM = { 0x1F5F5F, 0xE5C10A };

RF24Knot::RF24Knot(void):RF24(0,0) {
}
void RF24Knot::setParent(TangleNet *_parent) { 
	parent=_parent;
}
void RF24Knot::setupTangleNet(void) {
	setAddressSize(3);
	printDetails();
	openReadingPipe(0,pipes[0]);
	openReadingPipe(1,pipes[1]);
	openReadingPipe(2,pipes[1]+1);
	openReadingPipe(3,pipes[1]+2);
	openReadingPipe(4,pipes[1]+3);
	openReadingPipe(5,pipes[1]+4);
	printDetails();
	DEBUG_PRINTLN("Address size:");
	DEBUG_PRINTLN(getAddressSize());
}
