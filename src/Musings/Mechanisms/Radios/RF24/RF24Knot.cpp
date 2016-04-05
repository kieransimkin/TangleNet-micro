#include "RF24Knot.h"
#include "TangleNet.h"

RF24Knot RF24KnotInstance;
extern LogWeaver LogWeaverInstance;
const uint32_t pipes[2] PROGMEM = { 0x1F5F5F, 0xE5C10A };

RF24Knot::RF24Knot(void):RF24(9,10) {
}
void RF24Knot::setParent(TangleNet *_parent) { 
	parent=_parent;
}
void RF24Knot::setupTangleNet(void) {
  	setPayloadSize(32);
	//disableCRC();
	setCRCLength(RF24_CRC_8);
	setAddressSize(3);
	setAutoAck(false);
	setChannel(76);
	//setDataRate(RF24_2MBPS);
	setDataRate(RF24_250KBPS);
	setPALevel(RF24_PA_MAX);
	myAddr = 0;
	linkID[0] = random(0,255);
	linkID[1] = random(0,255);
	linkID[2] = random(0,255);
	openReadingPipe(0,pipes[0]);
	openReadingPipe(1,pipes[1]);
	openReadingPipe(2,pipes[1]+1);
	openReadingPipe(3,pipes[1]+2);
	openReadingPipe(4,pipes[1]+3);
	openReadingPipe(5,pipes[1]+4);
	printDetails();
	startListening();
	smile(true);
	Alarm.timerRepeat(10, regularSmile);
	DEBUG_PRINTLN("Address size:");
	DEBUG_PRINTLN(getAddressSize());
}
void regularSmile(void) { 
	RF24KnotInstance.smile(false);
}
void RF24Knot::smile(bool initial) {
	uint8_t data[32];
	RF24Packet *packet = (RF24Packet *) data;
	RF24MSG_Smile *smile = (RF24MSG_Smile *) packet->Payload;
	packet->MessageType = MSG_TYPE_SMILE;
	packet->Sequence = parent->getSequence();
	if (initial) { 
		packet->Flags = MSG_FLAG_BEGIN | MSG_FLAG_END | MSG_FLAG_ECHO;
	} else {
	       packet->Flags = MSG_FLAG_BEGIN | MSG_FLAG_END; 	
	}
	memcpy(packet->KnotLinkID, linkID, 3);
       	memcpy(smile->ecdsaPublic, parent->ecdsaPublic, uECC_BYTES+1);
	sendPacket(data);
	DEBUG_PRINTLN("Doing smile");
		
}	
void RF24Knot::sendPacket(uint8_t *packet) {
	stopListening();
       	setupMyAddr();
	write(packet, 32);
	startListening();
}
bool RF24Knot::checkAvailable(void) { 
	uint8_t data[sizeof(RF24Packet)];
	RF24Packet *packet = (RF24Packet *) data;
	if (testRPD()) {
		DEBUG_PRINTLN("Carrier detected");

	}
	if (available()) { 
		DEBUG_PRINTLN("Got Packet");
		read(data, 32);
		DEBUG_PRINTLN(packet->MessageType);
		DEBUG_PRINTLN(packet->Sequence);
		DEBUG_PRINTLN(packet->Flags);
				
	}
}
void RF24Knot::setupMyAddr(void) { 
	switch (myAddr) { 
		case 0:
			openWritingPipe(pipes[0]);
			break;
		case 1:
			openWritingPipe(pipes[1]);
			break;
		case 2:
			openWritingPipe(pipes[1]+1);
			break;
		case 3:
			openWritingPipe(pipes[1]+2);
			break;
		case 4:
			openWritingPipe(pipes[1]+3);
			break;
		case 5:
			openWritingPipe(pipes[1]+4);
			break;
	}
}
