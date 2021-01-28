#include "game.h"

// eeprom缓存
uint8 *eeprom_buf;

// "2048" 字模(32x32)
code const uint8 str_2048[] = {
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0xF0,0x00,0x00,0x38,0x78,
    0x00,0x00,0x70,0x38,0x00,0x00,0xF0,0x38,0x00,0x00,0xF0,0x78,0x00,0x00,0xF0,0x78,
    0x00,0x00,0x00,0xF0,0x00,0x00,0x00,0xE0,0x00,0x00,0x01,0xC0,0x00,0x00,0x03,0x80,
    0x00,0x00,0x07,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x70,0x00,
    0x00,0x00,0xE0,0x00,0x00,0x01,0x80,0x00,0x00,0x03,0x01,0x80,0x00,0x0E,0x03,0x00,
    0x00,0x1C,0x06,0x00,0x00,0x3F,0xFE,0x00,0x00,0x3F,0xFC,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*２*/
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0xE0,0x00,0x00,0x1C,0x70,
    0x00,0x00,0x38,0x70,0x00,0x00,0x70,0x70,0x00,0x00,0x60,0x70,0x00,0x00,0xE0,0x70,
    0x00,0x00,0xE0,0x70,0x00,0x01,0xC0,0xE0,0x00,0x01,0xC0,0xE0,0x00,0x03,0x80,0xE0,
    0x00,0x03,0x81,0xC0,0x00,0x03,0x81,0xC0,0x00,0x07,0x03,0xC0,0x00,0x07,0x03,0x80,
    0x00,0x07,0x03,0x80,0x00,0x07,0x07,0x00,0x00,0x0F,0x07,0x00,0x00,0x0E,0x0E,0x00,
    0x00,0x06,0x1C,0x00,0x00,0x07,0x38,0x00,0x00,0x03,0xF0,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*０*/
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0xE0,
    0x00,0x00,0x01,0xE0,0x00,0x00,0x03,0xE0,0x00,0x00,0x07,0xC0,0x00,0x00,0x0F,0xC0,
    0x00,0x00,0x1B,0xC0,0x00,0x00,0x33,0x80,0x00,0x00,0x67,0x80,0x00,0x00,0xC7,0x00,
    0x00,0x01,0x87,0x00,0x00,0x03,0x0F,0x00,0x00,0x06,0x0E,0x00,0x00,0x0C,0x0E,0x00,
    0x00,0x1F,0xFF,0xC0,0x00,0x3F,0xFF,0xC0,0x00,0x00,0x1C,0x00,0x00,0x00,0x3C,0x00,
    0x00,0x00,0x38,0x00,0x00,0x00,0x7C,0x00,0x00,0x03,0xFF,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*４*/
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0xF0,0x00,0x00,0x1C,0x38,
    0x00,0x00,0x38,0x38,0x00,0x00,0x70,0x38,0x00,0x00,0xF0,0x38,0x00,0x00,0xF0,0x70,
    0x00,0x00,0xF0,0x60,0x00,0x00,0xF1,0xC0,0x00,0x00,0x7F,0x80,0x00,0x00,0x3E,0x00,
    0x00,0x00,0x7F,0x00,0x00,0x01,0xCF,0x80,0x00,0x03,0x87,0xC0,0x00,0x07,0x03,0xC0,
    0x00,0x0E,0x03,0xC0,0x00,0x0C,0x03,0xC0,0x00,0x0C,0x03,0x80,0x00,0x0C,0x07,0x00,
    0x00,0x0E,0x0E,0x00,0x00,0x07,0xBC,0x00,0x00,0x01,0xE0,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*８*/
};

void readToBuf(){
    eeprom_buf = (uint8 *)&gd_2048;
    eeprom_read(0, eeprom_buf, sizeof(gd_2048));
}

void updateBuf(){
    eeprom_sector_erase(0);
    eeprom_buf = (uint8 *)&gd_2048;
    eeprom_write(0, eeprom_buf, sizeof(gd_2048));
}
