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
		uint8_t myAddr;
		uint8_t linkID[3];
	public:
		RF24Knot(void);
		void setParent(TangleNet *_parent);
		bool checkAvailable(void);	
		void setupTangleNet(void);
		void setupMyAddr(void);
		void sendPacket(uint8_t *packet);
		void smile(bool initial=false);

};
void regularSmile(void);
#endif
