extern "C" {
#include "aes.h"
#include "hmac.h"
#include "present.h"
}

// Global variables for data
// It is assumed that the data is 1 byte and only 1 AES block is required
uint8_t receivedHMAC[HMAC_SHA1_HASH_SIZE];
uint8_t computedHMAC[HMAC_SHA1_HASH_SIZE];
uint8_t cipherText[AES_BLOCKLEN];
uint8_t decodedText;

void setup() {
  Serial.begin(9600);
  initCAN();
  initDecrypt();
  initDisplay();
}

void loop() {
  receiveData(cipherText, receivedHMAC);
  computeHMAC(cipherText, computedHMAC);
  if (equal(receivedHMAC, computedHMAC))
    decryptData(cipherText, &decodedText);
  else
    Serial.println(" Data not received completely");
  // displayInLED(decodedText);
  delay(100);
}