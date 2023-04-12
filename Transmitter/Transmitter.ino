extern "C" {
#include "aes.h"
#include "hmac.h"
#include "present.h"
}

// Global variables for data
// It is assumed that the data is 1 byte and only 1 AES block is required
uint8_t plainText;
uint8_t cipherText[AES_BLOCKLEN];
uint8_t HMAC[HMAC_SHA1_HASH_SIZE];

// Global variables for CAN transmission
#define MESSAGE_ID_1 0x056
#define MESSAGE_ID_2 0x057
#define MESSAGE_ID_3 0x058
#define MESSAGE_ID_4 0x059
#define MESSAGE_ID_5 0x060

int messageIds[5] = {
  MESSAGE_ID_1, MESSAGE_ID_2,
  MESSAGE_ID_3, MESSAGE_ID_4, MESSAGE_ID_5
};

void setup() {
  Serial.begin(9600);
  initSensor();
  initEncrypt();
  initCAN();
}

void loop() {
  sense(&plainText);
  encryptData(&plainText, cipherText);
  computeHMAC(cipherText, HMAC);
  sendData(cipherText, HMAC, messageIds);
}
