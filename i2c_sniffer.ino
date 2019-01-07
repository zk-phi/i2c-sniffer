#include <stdbool.h>

#define SDA_PIN 1
#define SCL_PIN 2

typedef enum { WAITING, SYNC, CONNECTED } i2c_status_t;

i2c_status_t status = STOP;

uint8_t buffer;
uint8_t cursor;

void main (void) {
  pinMode(SDA_PIN, INPUT);
  pinMode(SCL_PIN, INPUT);
  Serial.begin(9600);
}

void loop (void) {
  if (digitalRead(SCL_PIN)) {
    if (status == SYN) {
      if (cursor == 7) {
        if (!digitalRead(SDA_PIN)) {
          Serial.writeln(" [ACK]");
          cursor == 0;
        }
      } else {
        buffer |= digitalRead(SDA_PIN) << (cursor++);
        if (cursor == 7) Serial.write(buffer);
      }
    }
  }

  while (digitalRead(SCL_PIN)) {
  }
}
