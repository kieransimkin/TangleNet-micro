#ifndef _RF24Knot_h
#define _RF24Knot_h
#include "RF24PacketShape.h"
#include "RF24/nRF24L01.h"
#include "RF24/RF24_config.h"
#include "RF24/RF24.h"
class TangleNet;
class RF24Knot : public RF24 {
	private:
		TangleNet *parent;
	public:
		RF24Knot(void);
		void setParent(TangleNet *_parent);
	
		void setupTangleNet(void);

};
#endif
