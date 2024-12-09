/*
 * Copyright (C) 2017 Inria
 *               2017 Inria Chile
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     tests
 *
 * @file
 * @brief       Semtech LoRaMAC test application
 *
 * @author      Alexandre Abadie <alexandre.abadie@inria.fr>
 * @author      Jose Alamos <jose.alamos@inria.cl>
 */

#include <stdio.h>

#ifdef MODULE_SEMTECH_LORAMAC_RX
#include "thread.h"
#include "msg.h"
#endif

#include "shell.h"
#include "semtech_loramac.h"

#include "xtimer.h"
#include "periph/adc.h"
#include "periph/gpio.h"

#include "lpsxxx.h"
#include "lpsxxx_params.h"

#define ADC_IN_USE 			ADC_LINE(0)
#define ADC_RES				ADC_RES_12BIT

#define LPP_CHANNEL 4

extern semtech_loramac_t loramac;

#ifdef MODULE_SEMTECH_LORAMAC_RX

#define FPORT_REBOOT            (30U)
#define FPORT_SONG              (33U)

static void _reboot(const uint32_t delay) {
    printf("Rebooting in %ld sec\n", delay);
    // TODO
}

static void _play_song(const char* song) {
    printf("Playing song: %s\n", song);
    // TODO

}

#define LORAMAC_RECV_MSG_QUEUE                   (4U)
static msg_t _loramac_recv_queue[LORAMAC_RECV_MSG_QUEUE];
static char _recv_stack[THREAD_STACKSIZE_DEFAULT];


static void *_wait_recv(void *arg)
{
    msg_init_queue(_loramac_recv_queue, LORAMAC_RECV_MSG_QUEUE);

    (void)arg;
    while (1) {
        /* blocks until something is received */
        switch (semtech_loramac_recv(&loramac)) {
            case SEMTECH_LORAMAC_RX_DATA:
                loramac.rx_data.payload[loramac.rx_data.payload_len] = 0;
                const uint8_t fport = loramac.rx_data.port;
                printf("Data received: %s, port: %d\n",
                (char *)loramac.rx_data.payload, fport);

                switch(fport) {
                 case FPORT_REBOOT: {
                    uint32_t delay = (uint8_t)(loramac.rx_data.payload[0] & 0xFF);
                    _reboot(delay);
                    break;
                }
               case FPORT_SONG: {
                    _play_song((char *)loramac.rx_data.payload);
                    break;
                }
                default: {
                    break;
                }
                }
                break;
            case SEMTECH_LORAMAC_RX_LINK_CHECK:
                printf("Link check information:\n"
                   "  - Demodulation margin: %d\n"
                   "  - Number of gateways: %d\n",
                   loramac.link_chk.demod_margin,
                   loramac.link_chk.nb_gateways);
                break;

            case SEMTECH_LORAMAC_RX_CONFIRMED:
                puts("Received ACK from network");
                break;

            case SEMTECH_LORAMAC_TX_SCHEDULE:
                puts("The Network Server has pending data");
                break;

            default:
                break;
        }
    }
    return NULL;
}
#endif


static int send_lpp_payload(uint8_t* payload_buf,uint16_t payload_len)
{
    uint8_t cnf = LORAMAC_TX_UNCNF;  /* Default: confirmable */
    uint8_t port = 10; /* Default: 2 */
    /* handle optional parameters */

    semtech_loramac_set_tx_mode(&loramac, cnf);
    semtech_loramac_set_tx_port(&loramac, port);

    switch (semtech_loramac_send(&loramac,  payload_buf, payload_len)) {

        case SEMTECH_LORAMAC_NOT_JOINED:
            puts("Cannot send: not joined");
            return 1;

        case SEMTECH_LORAMAC_DUTYCYCLE_RESTRICTED:
            puts("Cannot send: dutycycle restriction");
            return 1;

        case SEMTECH_LORAMAC_BUSY:
            puts("Cannot send: MAC is busy");
            return 1;

        case SEMTECH_LORAMAC_TX_ERROR:
            puts("Cannot send: error");
            return 1;

        case SEMTECH_LORAMAC_TX_CNF_FAILED:
            puts("Fail to send: no ACK received");
            return 1;
    }

    puts("LPP payload sent with success");
    return 0;
}


// SHELL_COMMAND(loramac_txhex, "Send hextring message", _loramac_txhex_handler);






int main(void)
{
#ifdef MODULE_SEMTECH_LORAMAC_RX
    thread_create(_recv_stack, sizeof(_recv_stack),
                  THREAD_PRIORITY_MAIN - 1, 0, _wait_recv, NULL, "recv thread");
#endif
    lpsxxx_t lps22;

    uint8_t lpp_payload[64];

    uint16_t luminosity = 0;
    uint16_t pres;
    int16_t temp;

    int ret;

    printf("============ TP Info 5 ================\n\n\r");

    semtech_loramac_set_dr(&loramac,5);
    semtech_loramac_set_adr(&loramac,true); //permet de gérer automatiquement le data rate

    //On reessaye de Join tant que ca marche pas
    while(ret != SEMTECH_LORAMAC_JOIN_SUCCEEDED){
        printf("Joining LoRa infrastructure ...\r\n");
        ret = semtech_loramac_join(&loramac,LORAMAC_JOIN_OTAA);
        if(ret != SEMTECH_LORAMAC_JOIN_SUCCEEDED){
            printf("Join failed, retrying in 10 seconds ...\n\r");
            xtimer_msleep(10000);
        }
    }

    printf("Join succesfull !\n\r");

    //Initialize Light sensor
    LED_GREEN_ON;
	xtimer_sleep(1);
	LED_RED_OFF;
	xtimer_sleep(1);
	LED_RED_OFF;
	xtimer_sleep(1);
	LED_GREEN_OFF;
	xtimer_sleep(1);

	LIGHT_SENSOR_SUPPLY_ON;
    if (adc_init(ADC_IN_USE) < 0) {
        printf("\r\nInitialization of ADC_LINE(%u) failed\r\n", ADC_IN_USE);

        return 1;
    }
    else {
        printf("\r\nSuccessfully initialized ADC_LINE(%u)\r\n", ADC_IN_USE);
    }

    //Initialyze lps22
    printf("Initializing %s sensor\n", LPSXXX_SAUL_NAME);
    if (lpsxxx_init(&lps22, &lpsxxx_params[0]) != LPSXXX_OK) {
        puts("Initialization failed");
        return 1;
    }

    while(1){
        //get luminosity
        luminosity = (uint16_t)adc_sample(ADC_IN_USE,ADC_RES);

        //get temp and pressure
        lpsxxx_enable(&lps22);
        xtimer_sleep(1); /* wait a bit for the measurements to complete */

        lpsxxx_read_temp(&lps22, &temp);
        lpsxxx_read_pres(&lps22, &pres);
        lpsxxx_disable(&lps22);

        int temp_abs = temp / 100;
        int centi_temp = temp - (temp_abs * 100);
        

        printf("Pressure value: %ihPa - Temperature: %2i.%02i°C\n",
               pres, temp_abs, centi_temp);
            
        printf("ADC_LINE(%u): raw value: %.4i, percent: %.2d %% \r\n", ADC_IN_USE, luminosity, luminosity*100/4096);
        
        temp /= 10;
        pres *= 10;

        //format the string to LPP (Data channel, Data type, Data payload)
        lpp_payload[0] = LPP_CHANNEL;
        lpp_payload[1] = 101; //illuminance
        lpp_payload[2] = luminosity >> 8;
        lpp_payload[3] = luminosity & 0xFF;
        lpp_payload[4] = LPP_CHANNEL;
        lpp_payload[5] = 103; //temperature
        lpp_payload[6] = temp >> 8;
        lpp_payload[7] = temp & 0xFF;
        lpp_payload[8] = LPP_CHANNEL;
        lpp_payload[9] = 115; //pressure
        lpp_payload[10] = pres >> 8;
        lpp_payload[11] = pres & 0xFF;

        
 

        //send payload
        send_lpp_payload(lpp_payload,12);
        
        printf("Sending next payload in 30 seconds ...\n\n\r");
        xtimer_msleep(30000);
    }
}
