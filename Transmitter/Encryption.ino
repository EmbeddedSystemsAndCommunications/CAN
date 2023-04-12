struct AES_ctx context;
uint8_t key[16] = {
  0x2D, 0xC6, 0x0D, 0xE1, 0x9E, 0x32, 0x8B, 0x39,
  0x62, 0x7B, 0x5A, 0xF6, 0x2E, 0x03, 0x75, 0x80
};
uint8_t paddedPlainText[AES_BLOCKLEN];

void initEncrypt() {
  AES_init_ctx(&context, key);  
}

// Pad the data to AES Block length
void padData(uint8_t* plainText, uint8_t* paddedPlainText) {
  size_t originalLength = 1;
  size_t paddedLength = (originalLength / AES_BLOCKLEN + 1) * AES_BLOCKLEN;
  uint8_t paddingValue = paddedLength - originalLength;

  for (size_t index = 0; index < originalLength; index++)
    paddedPlainText[index] = plainText[index];
  for (size_t index = originalLength; index < paddedLength; index++)
    paddedPlainText[index] = paddingValue;
}

// Encrypt the data
void encryptData(uint8_t* plainText, uint8_t* cipherText) {
  // Pad the data if required
  padData(plainText, paddedPlainText);
  
  Serial.print(" Encrypted data : ");
  for (size_t index = 0; index < AES_BLOCKLEN; index++)
    cipherText[index] = paddedPlainText[index];
  AES_ECB_encrypt(&context, cipherText);
  for (size_t index = 0; index < AES_BLOCKLEN; index++)
    Serial.print(cipherText[index], HEX);
}