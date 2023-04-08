
#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "dump.h"
#include "hardware/spi.h"

const int CHUNK_SIZE = 20;
const int OFFSET = 0; //debug

void cs(int on) {

    gpio_put(CS, on == 1 ? true : false);
}



void spi_r(uint8_t cmd, uint32_t addr, uint8_t *buf, int len) {

    uint8_t address[3];

    for(int i = 0 ; i < 3 ; ++i)
        address[i] = (addr>>(16-(i*8))) &0xff;




    cs(0);
    sleep_ms(100);
 //   spi_write_read_blocking(spi0, &addr, &buf,len);


    spi_write_blocking(spi0,&cmd,1);

    spi_write_blocking(spi0,&address[0],1);
    spi_write_blocking(spi0,&address[1],1);
    spi_write_blocking(spi0,&address[2],1);

    spi_read_blocking(spi0,0,&buf,len);

    cs(1);
    
}

void readJEDEC() {

	char addr = 0x9f;
    uint8_t read[4];
    cs(0);
    sleep_ms(100);
    spi_write_blocking(spi0,&addr,1);
    spi_read_blocking(spi0,0,&read,4);
    cs(1);

 printf("\nJEDEC\nManufacturer ID: 0x%x\nDevice ID: 0x%x\nSize: 0x%x\n",  read[0], read[1], read[2]);
 
}

void readPage() {

                          //  printf("\n\n");


    uint8_t buf[CHUNK_SIZE];

        for(int j =0 ; j < CHUNK_SIZE; ++j)
            buf[j] = 0;


    for(int j =0 ; j < 0x40000; ++j) {

        spi_r(0x03,(j*(CHUNK_SIZE-5))+OFFSET,buf,CHUNK_SIZE);

        //                                printf("\n\n");

        for(int i = 0; i < CHUNK_SIZE-5; i++) {

            printf("%02x",buf[i]);
        }
        printf("\n");


    }

    while(1)
        printf("end\n");


}


int main() {

    stdio_init_all();


    gpio_set_function(SCK,GPIO_FUNC_SPI);
    gpio_set_function(MOSI,GPIO_FUNC_SPI);
    gpio_set_function(MISO,GPIO_FUNC_SPI);
    gpio_set_function(CS,GPIO_FUNC_SPI);

    gpio_init(CS);
    gpio_set_dir(CS, GPIO_OUT);

    cs(1);


    spi_init(spi0,2000000);
    spi_set_format(spi0, 8,SPI_CPOL_1,SPI_CPHA_1,SPI_MSB_FIRST);



        sleep_ms(5000);
      //  readJEDEC(); 

      //        printf("end\n");


       readPage();


    
}