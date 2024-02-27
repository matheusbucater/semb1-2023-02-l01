/****************************************************************************
 * main.c
 *
 *   Authors: Daniel Pereira de Carvalho <daniel.carvalho@ufu.br>
 *            Marcelo Barros de Almeida  <marcelo.barros@ufu.br>
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <stdint.h>

 /****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define SRAM_START  0x20000000U                  /* Inicio da SRAM CORTEX-M */
#define SRAM_SIZE   (128U * 1024U)               /* Tam. SRAM STM32F411 128K */
#define SRAM_END    ((SRAM_START) + (SRAM_SIZE)) /* Final da SRAM STM32F411 */

#define STACK_START SRAM_END                     /* Inicio da Stack */

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

int main(void);

/* Prototipos de funcoes para as System Exceptions */

void reset_handler              (void);
void nmi_handler                (void) __attribute__ ((weak, alias("default_handler")));
void hardfault_handler          (void) __attribute__ ((weak, alias("default_handler")));
void memmanage_handler          (void) __attribute__ ((weak, alias("default_handler")));
void busfault_handler           (void) __attribute__ ((weak, alias("default_handler")));
void usagefault_handler         (void) __attribute__ ((weak, alias("default_handler")));
void svc_handler                (void) __attribute__ ((weak, alias("default_handler")));
void debugmon_handler           (void) __attribute__ ((weak, alias("default_handler")));
void pendsv_handler             (void) __attribute__ ((weak, alias("default_handler")));
void systick_handler            (void) __attribute__ ((weak, alias("default_handler")));
void WWDG_handler               (void) __attribute__ ((weak, alias("default_handler")));
void EXTI21_handler             (void) __attribute__ ((weak, alias("default_handler")));
void EXT22_handler              (void) __attribute__ ((weak, alias("default_handler")));
void FLASH_handler              (void) __attribute__ ((weak, alias("default_handler")));
void RCC_handler                (void) __attribute__ ((weak, alias("default_handler")));
void exti0_handler              (void) __attribute__ ((weak, alias("default_handler")));
void exti1_handler              (void) __attribute__ ((weak, alias("default_handler")));
void exti2_handler              (void) __attribute__ ((weak, alias("default_handler")));
void exti3_handler              (void) __attribute__ ((weak, alias("default_handler")));
void exti4_handler              (void) __attribute__ ((weak, alias("default_handler")));
void dma1_stream0_handler       (void) __attribute__ ((weak, alias("default_handler")));
void dma1_stream1_handler       (void) __attribute__ ((weak, alias("default_handler")));
void dma1_stream2_handler       (void) __attribute__ ((weak, alias("default_handler")));
void dma1_stream3_handler       (void) __attribute__ ((weak, alias("default_handler")));
void dma1_stream4_handler       (void) __attribute__ ((weak, alias("default_handler")));
void dma1_stream5_handler       (void) __attribute__ ((weak, alias("default_handler")));
void dma1_stream6_handler       (void) __attribute__ ((weak, alias("default_handler")));
void adc_handler                (void) __attribute__ ((weak, alias("default_handler")));
void exit9_5_handler            (void) __attribute__ ((weak, alias("default_handler")));
void tim1_brk_tim9_handler      (void) __attribute__ ((weak, alias("default_handler")));
void tim1_up_tim10_handler      (void) __attribute__ ((weak, alias("default_handler")));
void tim1_trg_com_tim11_handler (void) __attribute__ ((weak, alias("default_handler")));
void tim1_cc_handler            (void) __attribute__ ((weak, alias("default_handler")));
void tim2_handler               (void) __attribute__ ((weak, alias("default_handler")));
void tim3_handler               (void) __attribute__ ((weak, alias("default_handler")));
void tim4_handler               (void) __attribute__ ((weak, alias("default_handler")));
void i2c1_ev_handler            (void) __attribute__ ((weak, alias("default_handler")));
void i2c1_er_handler            (void) __attribute__ ((weak, alias("default_handler")));
void i2c2_ev_handler            (void) __attribute__ ((weak, alias("default_handler")));
void i2c2_er_handler            (void) __attribute__ ((weak, alias("default_handler")));
void spi1_handler               (void) __attribute__ ((weak, alias("default_handler")));
void spi2_handler               (void) __attribute__ ((weak, alias("default_handler")));
void usart1_handler             (void) __attribute__ ((weak, alias("default_handler")));
void usart2_handler             (void) __attribute__ ((weak, alias("default_handler")));
void exti15_10_handler          (void) __attribute__ ((weak, alias("default_handler")));
void exti17_handler             (void) __attribute__ ((weak, alias("default_handler")));
void exti18_handler             (void) __attribute__ ((weak, alias("default_handler")));
void dma1_stream7_handler       (void) __attribute__ ((weak, alias("default_handler")));
void sdio_handler               (void) __attribute__ ((weak, alias("default_handler")));
void tim5_handler               (void) __attribute__ ((weak, alias("default_handler")));
void spi3_handler               (void) __attribute__ ((weak, alias("default_handler")));
void dma2_stream0_handler       (void) __attribute__ ((weak, alias("default_handler")));
void dma2_stream1_handler       (void) __attribute__ ((weak, alias("default_handler")));
void dma2_stream2_handler       (void) __attribute__ ((weak, alias("default_handler")));
void dma2_stream3_handler       (void) __attribute__ ((weak, alias("default_handler")));
void dma2_stream4_handler       (void) __attribute__ ((weak, alias("default_handler")));
void otg_fs_handler             (void) __attribute__ ((weak, alias("default_handler")));
void dma2_stream5_handler       (void) __attribute__ ((weak, alias("default_handler")));
void dma2_stream6_handler       (void) __attribute__ ((weak, alias("default_handler")));
void dma2_stream7_handler       (void) __attribute__ ((weak, alias("default_handler")));
void usart6_handler             (void) __attribute__ ((weak, alias("default_handler")));
void i2c3_ev_handler            (void) __attribute__ ((weak, alias("default_handler")));
void i2c3_er_handler            (void) __attribute__ ((weak, alias("default_handler")));
void fpu_handler                (void) __attribute__ ((weak, alias("default_handler")));
void spi4_handler               (void) __attribute__ ((weak, alias("default_handler")));
void spi5_handler               (void) __attribute__ ((weak, alias("default_handler")));

 /****************************************************************************
 * External Data
 ****************************************************************************/

/* Variaveis exportadas pelo linker script */

extern uint32_t _sdata;     /* Inicio da secao .data */
extern uint32_t _edata;     /* Fim da secao .data */
extern uint32_t _la_data;   /* Origem da secao .data na FLASH */

extern uint32_t _sbss;      /* Inicio da secao .bss */
extern uint32_t _ebss;      /* Fim da secao .bss */

/****************************************************************************
 * Private Data
 ****************************************************************************/

/* Tabela de Vetores de Interrupção */

uint32_t vectors[] __attribute__((section(".isr_vectors"))) =
{
  STACK_START,                            /* 0x0000 0000 */
  (uint32_t)reset_handler,                /* 0x0000 0004 */
  (uint32_t)nmi_handler,                  /* 0x0000 0008 */
  (uint32_t)hardfault_handler,            /* 0x0000 000c */
  (uint32_t)memmanage_handler,            /* 0x0000 0010 */
  (uint32_t)busfault_handler,             /* 0x0000 0014 */
  (uint32_t)usagefault_handler,           /* 0x0000 0018 */
  0,                                      /* 0x0000 001c */
  0,                                      /* 0x0000 0020 */
  0,                                      /* 0x0000 0024 */
  0,                                      /* 0x0000 0028 */
  (uint32_t)svc_handler,                  /* 0x0000 002c */
  (uint32_t)debugmon_handler,             /* 0x0000 0030 */
  0,                                      /* 0x0000 0034 */
  (uint32_t)pendsv_handler,               /* 0x0000 0038 */
  (uint32_t)systick_handler,              /* 0x0000 003c */
  (uint32_t)WWDG_handler,
  (uint32_t)EXTI21_handler,
  (uint32_t)EXT22_handler,
  (uint32_t)FLASH_handler,
  (uint32_t)RCC_handler,
  (uint32_t)exti0_handler,
  (uint32_t)exti1_handler,
  (uint32_t)exti2_handler,
  (uint32_t)exti3_handler,
  (uint32_t)exti4_handler,
  (uint32_t)dma1_stream0_handler,
  (uint32_t)dma1_stream1_handler,
  (uint32_t)dma1_stream2_handler,
  (uint32_t)dma1_stream3_handler,
  (uint32_t)dma1_stream4_handler,
  (uint32_t)dma1_stream5_handler,
  (uint32_t)dma1_stream6_handler,
  (uint32_t)adc_handler,
  (uint32_t)exit9_5_handler,
  (uint32_t)tim1_brk_tim9_handler,
  (uint32_t)tim1_up_tim10_handler,
  (uint32_t)tim1_trg_com_tim11_handler,
  (uint32_t)tim1_cc_handler,
  (uint32_t)tim2_handler,
  (uint32_t)tim3_handler,
  (uint32_t)tim4_handler,
  (uint32_t)i2c1_ev_handler,
  (uint32_t)i2c1_er_handler,
  (uint32_t)i2c2_ev_handler,
  (uint32_t)i2c2_er_handler,
  (uint32_t)spi1_handler,
  (uint32_t)spi2_handler,
  (uint32_t)usart1_handler,
  (uint32_t)usart2_handler,
  (uint32_t)exti15_10_handler,
  (uint32_t)exti17_handler,
  (uint32_t)exti18_handler,
  (uint32_t)dma1_stream7_handler,
  (uint32_t)sdio_handler,
  (uint32_t)tim5_handler,
  (uint32_t)spi3_handler,
  (uint32_t)dma2_stream0_handler,
  (uint32_t)dma2_stream1_handler,
  (uint32_t)dma2_stream2_handler,
  (uint32_t)dma2_stream3_handler,
  (uint32_t)dma2_stream4_handler,
  (uint32_t)otg_fs_handler,
  (uint32_t)dma2_stream5_handler,
  (uint32_t)dma2_stream6_handler,
  (uint32_t)dma2_stream7_handler,
  (uint32_t)usart6_handler,
  (uint32_t)i2c3_ev_handler,
  (uint32_t)i2c3_er_handler,
  (uint32_t)fpu_handler,
  (uint32_t)spi4_handler,
  (uint32_t)spi5_handler,
};

/****************************************************************************
 * Private Functions
 ****************************************************************************/

void reset_handler(void)
{
  uint32_t i; 

  /* Copia a secao .data para a RAM */
   
  uint32_t size = (uint32_t)&_edata - (uint32_t)&_sdata;
  uint8_t *pDst = (uint8_t*)&_sdata;                      /* SRAM */
  uint8_t *pSrc = (uint8_t*)&_la_data;                    /* FLASH */
  
  for(i = 0; i < size; i++)
  {
    *pDst++ = *pSrc++;
  }

  /* Preenche a secao .bss com zero */

  size = (uint32_t)&_ebss - (uint32_t)&_sbss;
  pDst = (uint8_t*)&_sbss;
  for(i = 0 ; i < size; i++)
  {
    *pDst++ = 0;
  }

  /* Chama a funcao main() */

  main();
}

void default_handler(void)
{
  while(1){};
}
