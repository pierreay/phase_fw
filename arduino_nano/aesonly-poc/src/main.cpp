#include <Arduino.h>
#include "aes.h"
/** @brief Function for outputting usage info to the serial port.
*/
static void help(void)
{
    Serial.print("Usage:\r\n");
    Serial.print("a: Start automatic mode (Wait/AES)\r\n");
    Serial.print("n: Enter tiny_aes_128 mode\r\n");
    Serial.print("   p: Enter plaintext\r\n");
    Serial.print("   k: Enter key\r\n");
    Serial.print("   e: Encrypt\r\n");
    Serial.print("   n: Set number of repetitions\r\n");
    Serial.print("   r: Run repeated encryption\r\n");
    Serial.print("   q: Quit tiny_aes_128 mode\r\n");
}


int read_int() {
    // Read byte.
    int bread = 0;
    // Final read number.
    int bfinal = 0;
    while (true) {
        // Wait until at least one byte is available.
        while (!(Serial.available() > 0));
        // Read one byte.
        bread = Serial.read();
        // If carriage return or space, then break.
        if (bread == 13 || bread == 10 || bread == 32 ) {
            break;
        }
        // Increment int order at each digit.
        bfinal *= 10;
        // Put converted read byte (from ASCII number to desired int).
        bfinal += (bread - 48);
    }
    return bfinal;
}

/*
 * @brief Function to read 16 integers from the serial line and to write them in
 * to a bytearray
 */
void read_128(uint8_t* in){
    int tmp;
    for(int i=0;i<16;i++){
        tmp = read_int();
        in[i] = (uint8_t)tmp;    
    }
    /* NOTE: DEBUG: */
    /*scanf("%hhd %hhd %hhd %hhd %hhd %hhd %hhd %hhd %hhd %hhd %hhd %hhd %hhd %hhd %hhd %hhd",*/
           /*&in[ 0],&in[ 1],&in[ 2],&in[ 3],*/
           /*&in[ 4],&in[ 5],&in[ 6],&in[ 7],*/
           /*&in[ 8],&in[ 9],&in[10],&in[11],*/
           /*&in[12],&in[13],&in[14],&in[15]);*/
}

/*
 * @brief Function to write a byte array as 16 integers to the serial line
 */
void write_128(uint8_t* out){
    for(int i=0;i<16;i++){
      Serial.print(out[i], DEC);
      Serial.print(" ");
    }
    Serial.print("\r\n");
}

/*
 * @brief Function to automatically perform tiny_aes_128 attacks
 */
void auto_mode(){
    printf("Automatic mode \r\n");
    uint8_t key[16] = {0};
    uint8_t in[16] = {0};
    uint8_t out[16] = {0};
    while (true) {
        // Wait
        Serial.print("Start waiting...\r\n");
        delay(1000);
        // AES
        Serial.print("Start encrypting...\r\n");
        for (uint32_t i = 0; i < 5000; i++) {
            AES128_ECB_encrypt(in, key, out);
        }
    }
}
/*
 * @brief Function to handle tiny_aes_128 attacks
 */
void tiny_aes_128_mode(){
    Serial.print("Entering tiny_aes_128 mode\r\n");
    uint8_t control;
    bool exit = false;
    uint8_t key[16] = {0};
    uint8_t in[16] = {0};
    uint8_t out[16] = {0};
    uint32_t num_repetitions = 1;


    while(!exit){
        while (!(Serial.available() > 0));
        char control = Serial.read();
        switch(control){
            case 'p':
                read_128(in);
                write_128(in); // dbg
                break;
            case 'k':
                read_128(key);
                write_128(key); // dbg
                break;
            case 'e':
                AES128_ECB_encrypt(in,key,out);
                break;
            case 'n':           /* set number of repetitions */
                num_repetitions = read_int();
                Serial.print("Setting number of repetitions to ");
                Serial.print(num_repetitions, DEC);
                Serial.print("\r\n");
                break;
            case 'r':           /* repeated encryption */
                for (uint32_t i = 0; i < num_repetitions; ++i) {
                    for(uint32_t j = 0; j < 0xff; j++);
                    AES128_ECB_encrypt(in, key, out);
                }
                Serial.print("Done\r\n");
                break;
            case 'o':
                write_128(out);
                break;
            case 'q':
                exit = true;
                break;
            default:
                break;
        }
    }
    Serial.print("Exiting tiny_aes_128 mode\r\n");
}


void setup();

void loop();

int incomingByte = 0; // for incoming serial data

void setup() {
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
}

void loop() {
    uint8_t control;
    while (!(Serial.available() > 0));
    control = Serial.read();
    switch (control)
    {
        case 'a':
            auto_mode();
            break;
        case 'n':
            tiny_aes_128_mode();
            break;

        case 'h':
            help();
            break;

        default:
            // No implementation needed
            break;
    }
}


