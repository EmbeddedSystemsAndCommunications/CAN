#define HMAC_KEY_LEN 24

uint8_t keyHMAC[HMAC_KEY_LEN] = {
  0x23, 0xAB, 0x5F, 0x8C, 0xE1, 0x9A, 0x3E, 0x71,
  0xD4, 0x4B, 0xBC, 0xE9, 0xF1, 0xA0, 0x81, 0xFF,
  0xAF, 0x62, 0x17, 0xFE, 0xC3, 0x8A, 0x06, 0x50
};

void computeHMAC(uint8_t* message, uint8_t* output) {
  hmac_sha1(
    keyHMAC, HMAC_KEY_LEN,
    message, 16,
    output);
  Serial.print(" MAC : ");
  for (size_t index = 0; index < HMAC_SHA1_HASH_SIZE; index++)
    Serial.print(output[index], HEX);
}

bool equal(uint8_t* HMAC1, uint8_t* HMAC2) {
  for (size_t index = 0; index < HMAC_SHA1_HASH_SIZE; index++) {
    if (HMAC1[index] != HMAC2[index])
      return false;
  }
  return true;
}