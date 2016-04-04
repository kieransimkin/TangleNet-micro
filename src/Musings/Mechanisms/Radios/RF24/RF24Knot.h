#ifdef TANGLENET_RF24
#include "RF24PacketShape.h"
#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>

#ifndef __RF24_H__
#error You must include RF24 in your project to use RF24 Radio
#endif
class RF24Knot : public RF24 {
	private:
	public:
		RF24Knot(void);
		void setPins(uint8_t _cepin, uint8_t _cspin);
		void setupTangleNet(void);

};
#endif
