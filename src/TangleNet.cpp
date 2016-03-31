#include "TangleNet.h"
#include "arduino.h"
TangleNet::TangleNet(void) {
	_init();
	sequence=0;
	ecdsaPrivate[0]=0;
	ecdsaPrivate[1]=0;
	ecdsaPrivate[2]=0;
}
TangleNet::TangleNet(uint8_t sequence, uint8_t* ecdsaPrivate) {
	_init();
}
TangleNet::TangleNet(uint8_t sequence, uint8_t* ecdsaPrivate, char* name) {
	_init();
}
void TangleNet::_init(void) {
	uECC_set_rng((uECC_RNG_Function) &TangleNet::RNG);
}
void TangleNet::begin(void) {
	if (ecdsaPrivate[0]==0 && ecdsaPrivate[1]==0 && ecdsaPrivate[2]==0) {
		generateKey();
	}
}
void TangleNet::generateKey(void) {
	uint8_t longKey[uECC_BYTES*2];
	if (!ensureRandomSeeded()) { 
		log.println("Can't generate a key, you must seed the random number generator first, or provider your own random number generator function");
		return;
  	}

	if (!uECC_make_key(longKey, ecdsaPrivate)) { 
		log.println("make key failed");
	}
	uECC_compress(longKey, ecdsaPublic);
	log.println("Made key?");
}
bool TangleNet::ensureRandomSeeded(void) { 
	log.print(random());
	return true;
}
int TangleNet::RNG(uint8_t *p_dest, unsigned p_size)
{
  while(p_size--)
  {
    *p_dest = (uint8_t)random();
    p_dest++;
  }
  return 1;
}
void TangleNet::addRF24Communication(uint8_t _cepin, uint8_t _cspin) {

}
bool TangleNet::available(void) {

}
void TangleNet::loadFromEEPROM(void) {

}
void TangleNet::loadFromEEPROM(uint8_t offset) {

}
void TangleNet::dumpLocalKnot(void) {
	log.printf("Sequence: %d", sequence);
	log.vli_print(ecdsaPrivate,uECC_BYTES);
}
#ifdef __AVR__
void TangleNet::setRandomNoiseSource(uint8_t pin){
	uECC_set_rng((uECC_RNG_Function) &TangleNet::RNG_AVR);
}
int TangleNet::RNG_AVR(uint8_t *dest, unsigned size) {
  // Use the least-significant bits from the ADC for an unconnected pin (or connected to a source of 
  // random noise). This can take a long time to generate random data if the result of analogRead(0) 
  // doesn't change very frequently.
  while (size) {
    uint8_t val = 0;
    for (unsigned i = 0; i < 8; ++i) {
      int init = analogRead(0);
      int count = 0;
      while (analogRead(0) == init) {
        ++count;
      }
      
      if (count == 0) {
         val = (val << 1) | (init & 0x01);
      } else {
         val = (val << 1) | (count & 0x01);
      }
    }
    *dest = val;
    ++dest;
    --size;
 }
  return 1;
}
#endif
