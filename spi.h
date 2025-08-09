#include "pico/stdlib.h"

#include "hardware/spi.h"
#include "hardware/irq.h"
#include "pico/bootrom.h"

#define SCK     2
#define MOSI    3
#define MISO    4
#define CS      5

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;


void cs(int on) {

    gpio_put(CS, on == 1 ? true : false);
}

void init_spi() {

    gpio_set_function(SCK,GPIO_FUNC_SPI);
    gpio_set_function(MOSI,GPIO_FUNC_SPI);
    gpio_set_function(MISO,GPIO_FUNC_SPI);
    gpio_set_function(CS,GPIO_FUNC_SPI);

    gpio_init(CS);
    gpio_set_dir(CS, GPIO_OUT);

    cs(1);


    spi_init(spi0,400000);
    spi_set_format(spi0, 8,SPI_CPOL_1,SPI_CPHA_1,SPI_MSB_FIRST);
}



void spi_read_byte_slow(u8 * addr_bytes, u8 * buf) {
    u8 cmd = 0x03;


    cs(0);
    sleep_us(1);
    spi_write_blocking(spi0,&cmd,1);
    spi_write_blocking(spi0,addr_bytes,3);
    spi_read_blocking(spi0,0,buf,1);
    cs(1);
}

void readJEDEC() {

	char cmd = 0x9f;
    uint8_t read[3];
    cs(0);
    sleep_us(1);
    spi_write_blocking(spi0,&cmd,1);
    spi_read_blocking(spi0,0,&read,3);
    cs(1);

 printf("\nJEDEC\nManufacturer ID: 0x%x\nDevice ID: 0x%x\nSize: 0x%x\n",  read[0], read[1], read[2]);

 
 
}
