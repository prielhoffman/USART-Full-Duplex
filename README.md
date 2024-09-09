# USART Full-Duplex Communication Implementation

## Overview

This repository contains an implementation of a Full-Duplex communication scheme using USART (Universal Synchronous/Asynchronous Receiver Transmitter). The project involves two main functions for transmitting (`usart_tx()`) and receiving (`usart_rx()`) data between devices over separate clock and data channels. This implementation ensures continuous data exchange without using busy waiting or sleep/delay mechanisms.

## Implementation Details

### Communication Scheme

Each device in the USART communication system has its own channels:

- **Clock Channel**: Synchronizes the bits transmitted on the data channel. 
  - Implementation-wise, it is a constant “0101…” stream from the transmitter to the receiver. 
  - Each bit lasts for `BIT_TIME` (1/50 seconds), resulting in a clock frequency of 50Hz.

- **Data Channel**: Transmits data serially (bit by bit) between the boards.
  - Data is written (sent to the channel) when the clock channel rises and is read when the clock falls.

### Functions

Two functions handle the transmission and reception of data:

1. **`usart_tx()`**: This function is responsible for sending data and clock signals to the other device. 
   - The function works with 1 Byte (8 bits) of data, sending the Least Significant Bit (LSB) first.
   - The implementation should allow for flexibility in the number of bits (up to 12 bits) by using `#define` directives.
   - After transmitting the data, the transmitter will wait for a random amount of time before sending the next data. 
   - Note: No sleep, delay, while, or for loops are allowed in this function to prevent busy waiting.

2. **`usart_rx()`**: This function reads the clock pin to check if a transmission is in progress. 
   - If a transmission is detected, it reads the data pin when the clock falls from '1' to '0'.
   - The function is designed to avoid "Busy Waiting."

### Usage

The USART communication should run indefinitely in a loop, alternating between sending and receiving data. A typical implementation might look like this:

```c
void loop() {
    usart_tx();
    usart_rx();
}
```

### Important Notes
The implementation avoid busy waiting techniques such as using while, for, sleep, or delay.

### How to Use
1.Clone the Repository:

```bash
git clone https://github.com/your-username/usart-full-duplex.git
cd usart-full-duplex
```

2. Compile and Upload to the Device:
* Use your preferred IDE or toolchain to compile the code.
* Upload the compiled binary to your microcontroller or device.

3. Run the Code:
* After uploading, the devices will begin communicating using the 'usart_tx()' and 'usart_rx()' functions in a continuous loop.
