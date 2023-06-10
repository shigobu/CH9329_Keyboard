#include "CH9329_Keyboard.h"

#define USART0_BAUD_RATE(BAUD_RATE) ((float)(F_CPU * 64 / (16 * (float)BAUD_RATE)) + 0.5)

const int button = PIN_PA1;
uint8_t reportData[KEY_REPORT_DATA_LENGTH] = {};

void USART0_init(void) {
  PORTA.DIR &= ~PIN7_bm;
  PORTA.DIR |= PIN6_bm;
  USART0.BAUD = (uint16_t)USART0_BAUD_RATE(CH9329_DEFAULT_BAUDRATE);
  USART0.CTRLB |= USART_TXEN_bm;
}

void USART0_sendValue(uint8_t c) {
  while (!(USART0.STATUS & USART_DREIF_bm)) {
    ;
  }
  USART0.TXDATAL = c;
}

void USART0_sendValue(uint8_t* c, size_t length) {
  for (size_t i = 0; i < length; i++ ) {
    USART0_sendValue(c[i]);
  }
}

void setup() {
  USART0_init();
  CH9329_Keyboard.begin();

  pinMode(button, INPUT_PULLUP);
  delay(5000);
}

void loop() {
  if (digitalRead(button) == LOW) {
    size_t length = 0;
    CH9329_Keyboard.press('w');
    length = CH9329_Keyboard.getReportData(reportData, KEY_REPORT_DATA_LENGTH);
    USART0_sendValue(reportData, length);

    CH9329_Keyboard.release('w');
    length = CH9329_Keyboard.getReportData(reportData, KEY_REPORT_DATA_LENGTH);
    USART0_sendValue(reportData, length);
    while (digitalRead(button) == LOW);
  }
}
