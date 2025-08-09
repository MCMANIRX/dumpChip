#include <stdio.h>
#include <string.h>


#include "spi.h"





u8 str[100] = {0};
u8 str_idx = 0;


bool marker_found(char *marker) {
    int pos = 0;  // correct characters received so far
    for(int i = 0 ; i < str_idx; ++i){
    char c= str[i];

    if (c == -1) return false;  // shortcut for a common case
    if (c == marker[pos]) {
        pos++;
       // putchar(pos+'0');                      // count a correct character
        if (marker[pos] == '\0') {  // we got the complete string
            pos = 0;                // reset for next time
            return true;            // report success

        }
    } else if (c == marker[0]) {
        pos = 1;        // we have the initial character again
    } else {
        pos = 0;        // we received a wrong character
    }
    }
    return false;
}



void read_byte_from_address() {

    // convert hex string to u32
    int idx = 0;
    char c = '\0';

    u32 addr = 0;
    str_idx-=2; // set str ptr

    for(int i = 0; i < str_idx; ++i){
        c = str[i];
        addr+=  (c - (c > 0x39 ? 0x37 : 0x30))* pow(16,str_idx-(i+1));
    }

    addr&=0x0fffff; // mask


    //convert address to bytes for spi fcns
    u8 addr_bytes[3];
    for(int i = 0 ; i < 3 ; ++i)
        addr_bytes[i] = (addr>>(16-(i*8))) &0xff;

    //error checking
    int checks = 0;
    u8 r0,r1;

    while(checks<4) {

        spi_read_byte_slow(addr_bytes,&r0);
        spi_read_byte_slow(addr_bytes,&r1);
        checks++;
        if(r0 != r1){
            checks = 0;
            sleep_us(1);
            printf("ERR %02x %02x\n",r0,r1);
        }

            }

   //export to python
   printf("%02x\n",r0);
    
}


void console() {
    str_idx =0;

    while(1){


        u8 in = getchar();

        if(in){
            //putchar(in);
            str[str_idx++]  = in;

            if(in == 0xd){

                //putchar('\n');
                if(marker_found("bootrom"))
                    reset_usb_boot(0,0);
                
                else if(marker_found("h"))
                    read_byte_from_address();
                
                else if(marker_found("jedec")) //debug
                    readJEDEC();

               
                str_idx = 0;


                }

            }
            
            else if(in == 0x8 && str_idx>0)
                str_idx -=1;

        }


    }


int main() {

    stdio_init_all();

    init_spi();

    console();





    
}