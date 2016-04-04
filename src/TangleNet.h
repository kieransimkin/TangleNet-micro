#ifndef _TangleNet_h
#define _TangleNet_h

#include "Musings/Mechanisms/uECC/uECC.h"
#ifdef TANGLENET_RF24
	#include "Musings/Mechanisms/Radios/RF24/RF24Knot.h"
#endif

#ifdef DEBUG
 #include "Musings/Mechanisms/LogWeaver.h"
 LogWeaver LogWeaverInstance;
 #define DEBUG_PRINTF(...) LogWeaverInstance.printf(__VA_ARGS__)
 #define DEBUG_VLI_PRINT(x,y) LogWeaverInstance.vli_print(x,y)
 #define DEBUG_PRINT(x) LogWeaverInstance.print(x)
 #define DEBUG_PRINTLN(x) LogWeaverInstance.println(x)
#else
 #define DEBUG_PRINTF(...)
 #define DEBUG_VLI_PRINT(x,y) 
 #define DEBUG_PRINT(x) 
 #define DEBUG_PRINTLN(x) 
#endif

void setFatalError(void);
class RF24Knot; // forward decl
 extern RF24Knot RF24KnotInstance;

class TangleNet {
	private:
		uint8_t sequence;
		uint8_t ecdsaPrivate[uECC_BYTES];
		uint8_t ecdsaPublic[uECC_BYTES+1];
		char* name;
		RF24Knot *RF24Radio;

	protected:
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
#endif
