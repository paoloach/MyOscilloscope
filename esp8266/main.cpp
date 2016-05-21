#include "espressif/esp_common.h"
#include "esp/uart.h"
#include "mbedtls/net.h"

#include <string.h>
#include <unistd.h>

#include "FreeRTOS.h"
#include "sched.h"
#include "task.h"

#include "espressif/esp_common.h"

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "lwip/netdb.h"
#include "lwip/dns.h"

#include "ssid_config.h"
#include "spi.h"
#include "gpio-local.h"

#include "stream.h"


#define DATA_SIZE 10240
extern "C"{
  void user_init(void);
  uint8_t data[DATA_SIZE];
  uint8_t * writeData=data;
  uint8_t * dataRead=data;
  int dataLen=0;
}

void gpio_output_set(uint32_t  set_mask, uint32_t  clear_mask, uint32_t  enable_mask, uint32_t  disable_mask)
{
    GPIO_REG_WRITE(GPIO_OUT_W1TS_ADDRESS, set_mask);
    GPIO_REG_WRITE(GPIO_OUT_W1TC_ADDRESS, clear_mask);
    GPIO_REG_WRITE(GPIO_ENABLE_W1TS_ADDRESS, enable_mask);
    GPIO_REG_WRITE(GPIO_ENABLE_W1TC_ADDRESS, disable_mask);
}

void readData(){
    printf("Start read SPI\n");
  SET_PERI_REG_MASK(SPI_CMD(HSPI), SPI_USR);
    
  uint16_t temp = READ_PERI_REG(SPI_W0(HSPI)) >> 16;
  printf("Read SPI: %04X\n", temp);
  if (writeData == data+DATA_SIZE){
      writeData =data;
  }
  if (writeData == dataRead && dataLen >0){
    dataRead++;
    if (dataRead == data + DATA_SIZE){
      dataRead = data;
    }
  } else {
    dataLen++;
  }
  *writeData = temp & 0xFF;
  writeData++;
  
  if (writeData == data+DATA_SIZE){
      writeData =data;
  }
  if (writeData == dataRead && dataLen >0){
    dataRead++;
    if (dataRead == data + DATA_SIZE){
      dataRead = data;
    }
  } else {
    dataLen++;
  }
  *writeData = (temp >> 8) & 0xFF;
  writeData++;
}

void syntReadData(){
    static int countIns=0;
    if (countIns < 2049){
        countIns++;
        if (writeData == data+DATA_SIZE){
            writeData =data;
        }
        if (writeData == dataRead && dataLen >0){
            dataRead++;
            if (dataRead == data + DATA_SIZE){
                dataRead = data;
            }
        } else {
            dataLen++;
        }
        *writeData = countIns;
        countIns++;
        writeData++;
        
        if (writeData == data+DATA_SIZE){
            writeData =data;
        } 
        if (writeData == dataRead && dataLen > 0){
            dataRead++;
            if (dataRead == data + DATA_SIZE){
                dataRead = data;
            }
        } else {
            dataLen++;
        }
        *writeData = countIns;
        writeData++;

        mbedtls_net_usleep(1000);
    } 
 
}

void spi_task(void *pvParameters){
  spi_init_gpio(HSPI,SPI_CLK_USE_DIV);
  spi_clock(HSPI,8,10 );
  spi_rx_byte_order(HSPI,SPI_BYTE_ORDER_HIGH_TO_LOW);
  CLEAR_PERI_REG_MASK(SPI_USER(HSPI), SPI_USR_MOSI|SPI_USR_MISO|SPI_USR_COMMAND|SPI_USR_ADDR|SPI_USR_DUMMY);
  SET_PERI_REG_MASK(SPI_USER(HSPI), SPI_USR_MISO);
  WRITE_PERI_REG(SPI_USER1(HSPI), (15&SPI_USR_MISO_BITLEN)<<SPI_USR_MISO_BITLEN_S);

  PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO2_U, FUNC_GPIO2);
  GPIO_OUTPUT_SET(GPIO_ID_PIN(2), 1);
  gpio_enable(4,GPIO_INPUT);

  while(true){
      writeToStream();
      if (gpio_read(4)){
        readData();
       }
//      syntReadData();
  }
}



void user_init(void){
    uart_set_baud(0, 115200);
    printf("SDK version:%s\n", sdk_system_get_sdk_version());

//    struct sdk_station_config config = {
//        .ssid = WIFI_SSID,
//        .password = WIFI_PASS,
//    };

    struct sdk_station_config config;
    strcpy((char*)config.ssid, WIFI_SSID);
    strcpy((char*)config.password , WIFI_PASS);
    sdk_wifi_set_opmode(STATION_MODE);
    sdk_wifi_station_set_config(&config);

    xTaskCreate(&spi_task, (signed char *)"SPI_task", 1024, NULL, 2, NULL);
    initStream();
}
