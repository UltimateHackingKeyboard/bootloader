#ifndef __WORMHOLE_H__
#define __WORMHOLE_H__

// Includes:

    #include <stdint.h>

// Macros:

    #define WORMHOLE_MAGIC_NUMBER 0x3b04cd9e94521f9a
    #define IS_WORMHOLE_OPEN (Wormhole.magicNumber == WORMHOLE_MAGIC_NUMBER)

// Typedefs:

    typedef enum {
        EnumerationMode_Bootloader,
        EnumerationMode_BusPal,
        EnumerationMode_NormalKeyboard,
        EnumerationMode_CompatibleKeyboard,
    } enumeration_mode_t;

    typedef struct {
      uint64_t magicNumber;
      uint8_t enumerationMode;
      uint32_t timeoutMs;
    } wormhole_t;

// Variables:

    extern wormhole_t __attribute__ ((section (".noinit"))) Wormhole;

#endif
