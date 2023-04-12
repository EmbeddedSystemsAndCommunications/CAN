#ifndef __PRESENT_H__
#define __PRESENT_H__

#include <stdint.h>

// Public functions
void present_encrypt(const uint8_t *plain, const uint8_t *key, uint8_t *ans);
void present_decrypt(const uint8_t *cipher, const uint8_t *key, uint8_t *ans);

#endif  // for __PRESENT_H__
