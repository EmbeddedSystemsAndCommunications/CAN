struct AES_ctx context;
uint8_t key[16] = {
  0x2D, 0xC6, 0x0D, 0xE1, 0x9E, 0x32, 0x8B, 0x39,
  0x62, 0x7B, 0x5A, 0xF6, 0x2E, 0x03, 0x75, 0x80
};
uint8_t presentKey1[10] = {
  0x9F, 0x72, 0xAB, 0x5E, 0xF8,
  0x0F, 0xAB, 0x57, 0xE2, 0x9A
};
uint8_t presentKey2[10] = {
  0x34, 0xE6, 0xC7, 0x8D, 0x11,
  0x2A, 0xFF, 0x81, 0x3E, 0x6D  
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
  
  // Do the AES encryption
  uint8_t AEScipherText[AES_BLOCKLEN];
  for (size_t index = 0; index < AES_BLOCKLEN; index++)
    AEScipherText[index] = paddedPlainText[index];
  AES_ECB_encrypt(&context, AEScipherText);
  
  // Do the PRESENT Encryption
  present_encrypt(AEScipherText, presentKey1, cipherText);
  present_encrypt(AEScipherText + 8, presentKey2, cipherText + 8);
  
  Serial.print(" Encrypted data : ");
  for (size_t index = 0; index < AES_BLOCKLEN; index++)
    Serial.print(cipherText[index], HEX);
}