#include "Musings/Mechanisms/uECC/uECC.h"
#include "Musings/Mechanisms/LogWeaver.h"


#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>


class TangleNet {
	private:
		uint8_t sequence;
		uint8_t ecdsaPrivate[uECC_BYTES];
		uint8_t ecdsaPublic[uECC_BYTES+1];
		char* name;
		RF24 *radio;

	protected:
		LogWeaver log;
		void generateKey(void);
		int RNG(uint8_t *p_dest, unsigned p_size);
#ifdef __AVR__
		int RNG_AVR(uint8_t *p_dest, unsigned p_size);
#endif
		bool ensureRandomSeeded(void);
		void _init(void);

	public:
		
		TangleNet(void);
		TangleNet(uint8_t sequence, uint8_t* ecdsaPrivate);
		TangleNet(uint8_t sequence, uint8_t* ecdsaPrivate, char* name);
		void begin(void);
#ifdef __AVR__
		void setRandomNoiseSource(uint8_t pin);
#endif
		void addRF24Communication(uint8_t _cepin, uint8_t _cspin);
		void loadFromEEPROM(void);
		void loadFromEEPROM(uint8_t offset);
		void saveToEEPROM(void);
		void saveToEEPROM(uint8_t offset);
		bool available(void);
		void dumpLocalKnot(void);


};
