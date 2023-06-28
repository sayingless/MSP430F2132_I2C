#include <msp430.h>

void setupDigitalOscillator() {
  DCOCTL = 0;
  DCOCTL = CALDCO_1MHZ;
  BCSCTL1 = CALBC1_1MHZ;
}

void initializeI2C() {
  P3SEL = BIT1;
  P3SEL |= BIT2;
  UCB0CTL1 |= UCSWRST;
  UCB0CTL0 |= (UCMST | UCSYNC | UCMODE_3);
  UCB0CTL1 |= (UCSSEL_2 | UCSWRST);
  UCB0BR0 = 10;
  UCB0BR1 = 0;
  UCB0CTL1 &= ~UCSWRST;
}

void I2CStartSend(char slaveAddress) {
  UCB0I2CSA = slaveAddress;
  UCB0CTL1 |= UCTR + UCTXSTT;
}

void I2CWrite(char command) {
  while ((IFG2 & UCB0TXIFG) != B0TXPending);
  UCB0TXBUF = command;
  while ((IFG2 & UCB0TXIFG) != B0TXPending);
  UCB0CTL1 |= UCTXSTP;
  while (UCB0CTL1 & UCTXSTP);
}

char I2CRead(char slaveAddress) {
  UCB0I2CSA = slaveAddress;
  UCB0CTL1 &= ~UCTR;  // Set read mode
  UCB0CTL1 |= UCTXSTT;  // Send start condition
  while (UCB0CTL1 & UCTXSTT);  // Wait for start condition is sent
  UCB0CTL1 |= UCTXSTP;  // Send stop condition
  while (UCB0CTL1 & UCTXSTP); // Make sure stop condition is sent
  while((IFG2 & UCB0RXIFG) != B0RXPending);  // Wait until data can be read
  char readValue = B0_RECEIVE_BUFFER;  // Read data
  return readValue;
}

void I2CStop() {
  UCB0CTL1 |= UCTXSTP;
  while (UCB0CTL1 & UCTXSTP);
}

int main(void) {
	WDTCTL = WDTPW + WDTHOLD; // Stop WDT
	setupDigitalOscillator();
  initializeI2C();

	while (1) {
    // Trap CPU
	}
}
