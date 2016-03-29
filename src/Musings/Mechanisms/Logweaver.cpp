#include "LogWeaver.h"
#include "arduino.h"
size_t LogWeaver::write(uint8_t character) { /*blahblah is the name of your class*/
/*Code to display letter when given the ASCII code for it*/
	Serial.write(character);
}
void LogWeaver::printf(const char *format, ...)
   {
   char buf[PRINTF_BUF];
   va_list ap;
        va_start(ap, format);
        vsnprintf(buf, sizeof(buf), format, ap);
        for(char *p = &buf[0]; *p; p++) // emulate cooked mode for newlines
        {
                if(*p == '\n')
                        write('\r');
                write(*p);
        }
        va_end(ap);
   }
#ifdef F // check to see if F() macro is available
void LogWeaver::printf(const __FlashStringHelper *format, ...)
   {
   char buf[PRINTF_BUF];
   va_list ap;
        va_start(ap, format);
#ifdef __AVR__
        vsnprintf_P(buf, sizeof(buf), (const char *)format, ap); // progmem for AVR
#else
        vsnprintf(buf, sizeof(buf), (const char *)format, ap); // for the rest of the world
#endif
        for(char *p = &buf[0]; *p; p++) // emulate cooked mode for newlines
        {
                if(*p == '\n')
                        write('\r');
                write(*p);
        }
        va_end(ap);
   }
#endif
void LogWeaver::vli_print(uint8_t *vli, unsigned int size) {
    for(unsigned i=0; i<size; ++i) {
        printf("%02X ", (unsigned)vli[i]);
    }
}

