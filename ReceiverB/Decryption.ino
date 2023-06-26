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
uint8_t paddedDecodedText[AES_BLOCKLEN];

void initDecrypt() {
  AES_init_ctx(&context, key);
}

uint8_t removePadding(uint8_t* paddedDecodedText) {
  return paddedDecodedText[0];
}

uint8_t decryptData(uint8_t* cipherText) {
  // Do the PRESENT Decryption
  uint8_t AEScipherText[AES_BLOCKLEN];  
  present_decrypt(cipherText, presentKey1, AEScipherText);
  present_decrypt(cipherText + 8, presentKey2, AEScipherText + 8);
  
  // Do the AES Decryption
  for (size_t index = 0; index < AES_BLOCKLEN; index++)
    paddedDecodedText[index] = AEScipherText[index];
  AES_ECB_decrypt(&context, paddedDecodedText);

  // Remove padding
  uint8_t decodedText = decodedText = removePadding(paddedDecodedText);
  Serial.println(" Decoded data : " + String(decodedText));
  return decodedText;
}