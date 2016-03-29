#include "Print.h"
#include <stddef.h>
#include <stdarg.h>
#define PRINTF_BUF 80 // define the tmp buffer size (change if desired)


class LogWeaver : public Print { 
	virtual size_t write(uint8_t);
	public:
	void printf(const char *format, ...);
#ifdef F // check to see if F() macro is available
   	void printf(const __FlashStringHelper *format, ...);
#endif	
	void vli_print(uint8_t *vli, unsigned int size);
};
