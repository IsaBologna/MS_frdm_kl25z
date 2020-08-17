/**
 * @file main.cpp
 * Example use of nRF24L01+ library by Owen Edwards
 *  https://os.mbed.com/users/Owen/code/nRF24L01P_Hello_World/
 *
 * @author Isabella Bologna
 * @date Jul 2020
 * 
 * @section LICENSE
 *
 * @copyright mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 * 
 * @copydoc main.cpp https://os.mbed.com/users/Owen/code/nRF24L01P_Hello_World/
 * @copydoc nRF24L01P.cpp
 */

#include "mbed.h"
#include "nRF24L01P.h"

// The nRF24L01+ supports transfers from 1 to 32 bytes (some boards may not handle many bytes)
#define TRANSFER_SIZE   4 

#define WAIT_TIME_MS 500 // macro for generic delay time, in milisseconds

/*** Pins definitions***/
#define MOSI    PTD2
#define MISO    PTD3
#define SCK     PTC5
#define CS      PTD0
#define CE      PTD5
#define IRQ     PTA13

DigitalOut red(LED_RED); 

nRF24L01P my_nrf24l01p(MOSI, MISO, SCK, CS, CE, IRQ); // module instance

int main() {

    //!
    char txData[TRANSFER_SIZE], rxData[TRANSFER_SIZE];
    int txDataCnt = 0;
    int rxDataCnt = 0;

    my_nrf24l01p.powerUp();

    // Display the (default) setup of the nRF24L01+ chip
    printf( "nRF24L01+ Frequency    : %d MHz\r\n",  my_nrf24l01p.getRfFrequency() );
    printf( "nRF24L01+ Output power : %d dBm\r\n",  my_nrf24l01p.getRfOutputPower() );
    printf( "nRF24L01+ Data Rate    : %d kbps\r\n", my_nrf24l01p.getAirDataRate() );
    printf( "nRF24L01+ TX Address   : 0x%010llX\r\n", my_nrf24l01p.getTxAddress() );
    printf( "nRF24L01+ RX Address   : 0x%010llX\r\n", my_nrf24l01p.getRxAddress() );

    printf( "Type keys to test transfers:\r\n  (transfers are grouped into %d characters)\r\n", TRANSFER_SIZE );

    my_nrf24l01p.setTransferSize( TRANSFER_SIZE );

    my_nrf24l01p.setReceiveMode();
    my_nrf24l01p.enable();
    //! 
    
    while (true) {
        red = !red; // toggle LED
        thread_sleep_for(WAIT_TIME_MS); // delay, compatible with thread
    }
}
