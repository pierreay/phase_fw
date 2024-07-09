/**
  ******************************************************************************
  * @file    UART/UART_TwoBoards_ComPolling/Src/main.c 
  * @author  MCD Application Team
  * @brief   This sample code shows how to use UART HAL API to transmit
  *          and receive a data buffer with a communication process based on
  *          polling transfer. 
  *          The communication is done using 2 Boards.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "aes.h"
#include "string.h"
#include "stdbool.h"
#include "stdlib.h"
#include "stdio.h"

/** @addtogroup STM32L1xx_HAL_Examples
  * @{
  */

/** @addtogroup UART_TwoBoards_ComPolling
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define AUTOAES_TWAIT 150
#define AUTOAES_ITER 350
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* UART handler declaration */
UART_HandleTypeDef UartHandle;

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void Error_Handler(void);
static void HAL_User_Init(void);
static void UART_write(char *);
static char UART_getc();

static void tiny_aes_128_mode();
static void auto_mode(void);
static void help(void);
static void read_128(uint8_t *);
static void write_128(uint8_t *);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  HAL_User_Init();

  // UART_write("Init OK\r\n");

  /* Infinite loop */
  while (1)
  {
    char control;
    control = UART_getc();
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
}

/*
 * @brief Function to handle tiny_aes_128 attacks
 */
static void tiny_aes_128_mode() {
    UART_write("Entering tiny_aes_128 mode\r\n");
    bool exit = false;
    uint8_t key[16] = {0};
    uint8_t in[16] = {0};
    uint8_t out[16] = {0};
    uint32_t num_repetitions = 1;

    char outBuf[16];

    while(!exit){
        char control = UART_getc();
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
                HAL_Delay(1000);
                AES128_ECB_encrypt(in,key,out);
                break;
            case 'n':           /* set number of repetitions */
                num_repetitions = 0;
                for(int i=3; i>=0; i--)
                  num_repetitions |= UART_getc() << (8*i);
                snprintf(outBuf, sizeof(outBuf), "%lu", num_repetitions);
                UART_write("Setting number of repetitions to ");
                UART_write(outBuf);
                UART_write("\r\n");
                break;
              
            case 'r':           /* repeated encryption */
                for (uint32_t i = 0; i < num_repetitions; ++i) {
                    for(uint32_t j = 0; j < 0xff; j++);
                    AES128_ECB_encrypt(in, key, out);
                }
                UART_write("Done\r\n");
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
    UART_write("Exiting tiny_aes_128 mode\r\n");
}

/*
 * @brief Function to read 16 bytes from the serial line and to write them in
 * to a bytearray
 */
static void read_128(uint8_t *in) {
    int tmp = 0;
    // Read 16 bytes
    for(int i = 0; i < 16; i++) {
        int tmp0 = 0;
        int tmp1 = 0;
        int tmp2 = 0;
        // Read 3 ASCII digits
        for(int j = 0; j < 3; j++) {
            // NOTE: Simulate atoi()
            tmp = UART_getc() - 48;

            // DBG
            /* char outBuf[16]; */
            /* snprintf(outBuf, sizeof(outBuf), "%d", tmp); */
            /* UART_write(outBuf); */
            /* UART_write(" "); */

            // If CR (carrier ret, \r) or SPACE:
            if (tmp == -35 || tmp == -16) {
                break;
            }

            // Put digit w.r.t. its power.
            if (j == 0) {
                tmp0 = tmp;
            }
            else if (j == 1) {
                tmp1 = tmp0;
                tmp0 = tmp;
            }
            else if (j == 2) {
                tmp2 = tmp1;
                tmp1 = tmp0;
                tmp0 = tmp;
            }
        }

        // Compute number based on separate digits.
        tmp = tmp2 * 100 + tmp1 * 10 + tmp0;

        // DBG
        /* char outBuf[16]; */
        /* snprintf(outBuf, sizeof(outBuf), "%d", tmp); */
        /* UART_write(outBuf); */
        /* UART_write(" "); */

        // Save it inside byte array.
        in[i] = (uint8_t)tmp;    
    }
}

/*
 * @brief Function to write a byte array as 16 bytes to the serial line
 */
static void write_128(uint8_t *out){
    char outBuf[16];
    for(int i=0; i<16; i++){
      snprintf(outBuf, sizeof(outBuf), "%d", out[i]);
      UART_write(outBuf);
      UART_write(" ");
    }
    UART_write("\r\n");
}

static void help(void)
{
    UART_write("Usage:\r\n");
    UART_write("a: Start automatic mode (Wait/AES)\r\n");
    UART_write("n: Enter tiny_aes_128 mode\r\n");
    UART_write("   p: Enter plaintext\r\n");
    UART_write("   k: Enter key\r\n");
    UART_write("   e: Encrypt\r\n");
    UART_write("   o: Output encryption result\r\n");
    UART_write("   n: Set number of repetitions\r\n");
    UART_write("   r: Run repeated encryption\r\n");
    UART_write("   q: Quit tiny_aes_128 mode\r\n");
}

static void auto_mode() {
  UART_write("Automatic mode \r\n");
  uint8_t key[16] = {0};
  uint8_t in_buf[16] = {0};
  uint8_t out_buf[16] = {0};
  while (1) {
    // Wait
    BSP_LED_Off(LED2);
    UART_write("Start waiting...\r\n");
    HAL_Delay(AUTOAES_TWAIT);
    BSP_LED_On(LED2);
    // AES
    UART_write("Start encrypting...\r\n");
    for (uint32_t i = 0; i < AUTOAES_ITER; i++) {
      AES128_ECB_encrypt(in_buf, key, out_buf);
      HAL_Delay(1);
    }
  }
}

static void UART_write(char *txBuf) {
  HAL_UART_Transmit(&UartHandle, (uint8_t *)txBuf, strlen(txBuf), 500);
}

static char UART_getc() {
  HAL_StatusTypeDef ret;
  char c;
  
  while((ret  = HAL_UART_Receive(&UartHandle, (uint8_t *)&c, 1, 0xFFFFFFFF)) 
              == HAL_TIMEOUT) {
    if(ret != HAL_OK) Error_Handler();
  }

  return c;
}


static void HAL_User_Init() {
    /* STM32F103xB HAL library initialization:
       - Configure the Flash prefetch
       - Systick timer is configured by default as source of time base, but user 
         can eventually implement his proper time base source (a general purpose 
         timer for example or other time source), keeping in mind that Time base 
         duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and 
         handled in milliseconds basis.
       - Set NVIC Group Priority to 4
       - Low Level Initialization
     */
  HAL_Init();

  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};

  /* Enable HSE Oscillator and Activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType      = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState            = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState        = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource       = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL          = RCC_PLL_MUL6;
  RCC_OscInitStruct.PLL.PLLDIV          = RCC_PLL_DIV3;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /* Set Voltage scale1 as MCU will run at 32MHz */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  
  /* Poll VOSF bit of in PWR_CSR. Wait until it is reset to 0 */
  while (__HAL_PWR_GET_FLAG(PWR_FLAG_VOS) != RESET) {};

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
  clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }

  /* Initialize BSP Led for LED2 */
  BSP_LED_Init(LED2);

  /*##-1- Configure the UART peripheral ######################################*/
  /* Put the USART peripheral in the Asynchronous mode (UART Mode) */
  /* UART configured as follows:
      - Word Length = 8 Bits
      - Stop Bit = One Stop bit
      - Parity = None
      - BaudRate = 9600 baud
      - Hardware flow control disabled (RTS and CTS signals) */
  UartHandle.Instance        = USARTx;
  UartHandle.Init.BaudRate   = 9600;
  UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
  UartHandle.Init.StopBits   = UART_STOPBITS_1;
  UartHandle.Init.Parity     = UART_PARITY_NONE;
  UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
  UartHandle.Init.Mode       = UART_MODE_TX_RX;
  if(HAL_UART_DeInit(&UartHandle) != HAL_OK)
  {
    Error_Handler();
  }  
  if(HAL_UART_Init(&UartHandle) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief  UART error callbacks
  * @param  UartHandle: UART handle
  * @note   This example shows a simple way to report transfer error, and you can
  *         add your own implementation.
  * @retval None
  */
void HAL_UART_ErrorCallback(UART_HandleTypeDef *UartHandle)
{
    Error_Handler();
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void Error_Handler(void)
{
  /* Turn LED2 on */
  BSP_LED_On(LED2);
  while(1)
  {
    /* Error if LED2 is slowly blinking (1 sec. period) */
    BSP_LED_Toggle(LED2); 
    HAL_Delay(1000); 
  }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/**
  * @}
  */
