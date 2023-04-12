#include <SPI.h>
#include <mcp2515.h>

#define CAN_MESSAGE_LENGTH 8
#define MCP2515_CS_PIN 53
#define DELAY 500
struct can_frame CANMessage;
MCP2515 mcp2515(MCP2515_CS_PIN);

void initCAN() {
  SPI.begin();
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();
}

void sendData(uint8_t* data, uint8_t* MAC, int* messageIds) {
  // Since data is 16 bytes, it needs to be split in 2 parts and sent to the node
  // Send the first frame
  CANMessage.can_id = messageIds[0];
  CANMessage.can_dlc = CAN_MESSAGE_LENGTH;
  for (size_t index = 0; index < CAN_MESSAGE_LENGTH; index++)
    CANMessage.data[index] = data[index];
  mcp2515.sendMessage(&CANMessage);

  delay(DELAY);

  // Send the second frame
  CANMessage.can_id = messageIds[1];
  CANMessage.can_dlc = CAN_MESSAGE_LENGTH;
  for (size_t index = 0; index < CAN_MESSAGE_LENGTH; index++)
    CANMessage.data[index] = data[CAN_MESSAGE_LENGTH + index];
  mcp2515.sendMessage(&CANMessage);

  delay(DELAY);

  // Now send the MAC since MAC is 20 bytes, it has to be sent in 3 frames
  // Send the first MAC frame
  CANMessage.can_id = messageIds[2];
  CANMessage.can_dlc = CAN_MESSAGE_LENGTH;
  for (size_t index = 0; index < CAN_MESSAGE_LENGTH; index++)
    CANMessage.data[index] = MAC[index];
  mcp2515.sendMessage(&CANMessage);

  delay(DELAY);

  // Send the second MAC frame
  CANMessage.can_id = messageIds[3];
  CANMessage.can_dlc = CAN_MESSAGE_LENGTH;
  for (size_t index = 0; index < CAN_MESSAGE_LENGTH; index++)
    CANMessage.data[index] = MAC[CAN_MESSAGE_LENGTH + index];
  mcp2515.sendMessage(&CANMessage);

  delay(DELAY);

  // Send the third MAC frame
  CANMessage.can_id = messageIds[4];
  CANMessage.can_dlc = 4;
  for (size_t index = 0; index < 4; index++)
    CANMessage.data[index] = MAC[2 * CAN_MESSAGE_LENGTH + index];
  mcp2515.sendMessage(&CANMessage);

  delay(DELAY);
}
