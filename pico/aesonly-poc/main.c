#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "hardware/clocks.h"
#include "tinyaes/aes.h"

/** @brief Function for outputting usage info to the serial port.
*/
static void help(void)
{
    printf("Usage:\r\n");
    printf("p: Print configuration\r\n");
    printf("n: Enter tiny_aes_128 mode\r\n");
    printf("   p: Enter plaintext\r\n");
    printf("   k: Enter key\r\n");
    printf("   e: Encrypt\r\n");
    printf("   n: Set number of repetitions\r\n");
    printf("   r: Run repeated encryption\r\n");
    printf("   q: Quit tiny_aes_128 mode\r\n");
}

void print_config()
{
    clock_hw_t *clock = &clocks_hw->clk[clk_sys];
    printf("clk_sys_freq=%d MHz\n", clock_get_hz(clk_sys) / 1000000);
    printf("clk_sys_ctrl=0x%x\n", clock->ctrl);
}

/*
 * @brief Function to read 16 integers from the serial line and to write them in
 * to a bytearray
 */
void read_128(uint8_t* in){
    int tmp;
    for(int i=0;i<16;i++){
        scanf("%d",&tmp);
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
    printf("%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\r\n",
           out[ 0],out[ 1],out[ 2],out[ 3],
           out[ 4],out[ 5],out[ 6],out[ 7],
           out[ 8],out[ 9],out[10],out[11],
           out[12],out[13],out[14],out[15]);
}

/*
 * @brief Function to handle tiny_aes_128 attacks
 */
void tiny_aes_128_mode(){
    printf("Entering tiny_aes_128 mode\r\n");
    uint8_t control;
    bool exit = false;
    uint8_t key[16] = {0};
    uint8_t in[16] = {0};
    uint8_t out[16] = {0};
    uint32_t num_repetitions = 1;


    while(!exit){
        scanf("%c",&control);
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
                scanf("%lu", &num_repetitions);
                printf("Setting number of repetitions to %ld\r\n", num_repetitions);
                break;
            case 'r':           /* repeated encryption */
                for (uint32_t i = 0; i < num_repetitions; ++i) {
                    for(uint32_t j = 0; j < 0xff; j++);
                    AES128_ECB_encrypt(in, key, out);
                }
                printf("Done\r\n");
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
    printf("Exiting tiny_aes_128 mode\r\n");
}

int main() {
    stdio_init_all();

    // initialize CYW43 driver architecture
    if (cyw43_arch_init()) {
        printf("failed to initialise cyw43_arch\n");
        return -1;
    }

    printf("RF Test\r\n");

    while (true)
    {
        uint8_t control;
        scanf("%c",&control);
        switch (control)
        {
            case 'p':
                print_config();
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
    return 0;
}
