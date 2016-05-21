#include "lwip/err.h"
#include "lwip/sys.h"
#include "lwip/mem.h"
#include "lwip/memp.h"
#include "lwip/pbuf.h"
#include "lwip/tcp.h"

#include "stream.h"
#include "config.h"

#define DATA_SIZE 10240
extern "C"{
  extern uint8_t data[DATA_SIZE];
  extern uint8_t * writeData;
  extern uint8_t * dataRead;
  extern int dataLen;
}

static struct tcp_pcb * tcpPcb;
static struct tcp_pcb * connectedPCB=NULL;;
static bool sending=false;


static err_t  newConnection(void *arg, struct tcp_pcb *newpcb, err_t err);
static err_t recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err);
static err_t sent(void *arg, struct tcp_pcb *tpcb, u16_t len);


void initStream(void) {
    err_t error;
    tcpPcb = tcp_new();
  
    error =  tcp_bind(tcpPcb, IP_ADDR_ANY, STREAM_PORT);
    if (error != ERR_OK){
        printf("tcp_bind error: %d\n", error);
        return;
    }

    struct tcp_pcb * tcpPcbl = tcp_listen(tcpPcb);
    if (tcpPcbl == NULL){
        printf("tcp_listern error: not enough memory !\n");
        return;
    }

    tcpPcb = tcpPcbl;
    printf("PCB listen: %p\n", tcpPcb);

    tcp_accept(tcpPcb, newConnection);
    tcp_sent(tcpPcb, sent);
}

void writeToStream(void){
    if (sending ){
        return;
    }
    if (connectedPCB != NULL){
        err_t error;
        uint16_t maxSize = tcp_sndbuf(tcpPcb);
        if (maxSize > 1024){
            maxSize = 1024;
        }
        if (dataLen > maxSize){ 
            printf("send %d data\n", maxSize);
            if (writeData < dataRead){
                uint16_t available = (data+DATA_SIZE) - dataRead;
                if (available < maxSize){
                    maxSize = available;
                }
                error =  tcp_write(connectedPCB, dataRead, maxSize,0);
                
            } else {
                error =  tcp_write(connectedPCB, dataRead, maxSize,0);
            }
            dataLen -= maxSize;
            if (error == ERR_OK){
                sending=true;
            }
        }
    }
}

static err_t sent(void *arg, struct tcp_pcb *tpcb, u16_t len){
    printf("sent %d data\n", len);
    dataRead+=len;
    if (dataRead == (data+DATA_SIZE)){
        dataRead = data;
    }
    sending=false;
    return ERR_OK;
}

static err_t  newConnection(void *arg, struct tcp_pcb *newpcb, err_t err) {
    err_t error;

    printf("new connection: %p\n", newpcb);
    if (connectedPCB != NULL){
        printf("too many connections\n" );
        error = tcp_close(newpcb);
        if (error != ERR_OK){
            printf("Unable to close the connection: %d\n", error);
        }
    }
    connectedPCB = newpcb;
    tcp_sent(newpcb, sent);
    tcp_recv(newpcb,recv );
    tcp_accepted(newpcb);
    return ERR_OK;
}

static err_t recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err){
    if (p == NULL){
        printf("connection close: %p\n", tpcb);
       // tcp_close(tcpPcb);
        connectedPCB = NULL;
    } else {
        tcp_recved(tcpPcb, p->len);
        pbuf_free(p);
    }
    return ERR_OK;
    
}


