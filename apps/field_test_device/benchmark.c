


#define ENABLE_DEBUG (1)
#include "debug.h"

#include "benchmark.h"

#include "xtimer.h"
#include <time.h>

#include <string.h>

#include "net/loramac.h"
#include "semtech_loramac.h"
#include "loramac_utils.h"
#include "app_clock.h"

#include <random.h>

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))
#endif

/**
 * @See https://github.com/Lora-net/LoRaMac-node/blob/master/src/mac/LoRaMacTypes.h#L335
*/
static const uint8_t _pwd_dbm_to_id[] = {
    0, 0,
    0 /* 2 dBm */, 0,
    1 /* 4 dBm */, 1,
    2 /* 6 dBm */, 2,
    3 /* 8 dBm */, 3,
    4 /* 10 dBm */, 4,
    5 /* 12 dBm */, 5,
    6 /* 14 dBm */
};




// Count the number of elements in an array.
//#define CNT(array) (uint8_t)(sizeof(array) / sizeof(*array))

#define PAYLOAD_LEN	256

static uint8_t payload[PAYLOAD_LEN];

// Encode message data to the payload.
unsigned int encode_benchmark(uint8_t *payload, unsigned int len, uint8_t power, uint8_t dr)
{

	// reset the payload
	memset(payload,0,PAYLOAD_LEN);

	if(len < sizeof(2 * sizeof(uint8_t))) {
		return 0;
	}

	unsigned int i = 0;

	// Encode txpower.
	payload[i++] = power;
    // Encode datarate.
	payload[i++] = dr;

	// TODO add FCNT, RSSI, LSNR of the last downlink.

	return i;
}

void benchmark_start(semtech_loramac_t *loramac, struct benchmark_t benchmark, unsigned int (*encode_sensors)(uint8_t*, const unsigned int)) {

    // Start benchmark
    DEBUG("[ftd] Start benchmark\n");


    /* set ADR flag */
    semtech_loramac_set_adr(loramac, benchmark.adr);

    uint8_t port = benchmark.min_port;
    uint32_t cpt = 0;
    while (1)
    {
        port = benchmark.min_port + ((port + 1 - benchmark.min_port) % (benchmark.max_port - benchmark.min_port));

        int i;
        uint8_t dr;
        uint8_t power;
        uint8_t size;

        DEBUG("[ftd] New benchmark sequence: port=%d\n", port);
        app_clock_print_rtc();

        for( i=0 ; i < benchmark.drpwsz_sequence_nb  ; i++) {

        	cpt++;

            dr = benchmark.drpwsz_sequence[3*i];
            power = benchmark.drpwsz_sequence[3*i+1];
            size = benchmark.drpwsz_sequence[3*i+2];

            // TODO uint32_t devaddr = devaddrs[cpt%ARRAYSIZE(devaddrs)];
            uint32_t devaddr = benchmark.devaddr + (cpt%benchmark.nb_virtual_devices);

        	DEBUG("[ftd] Send @ devaddr=%8lx port=%d dr=%d txpower=%d size=%d\n", devaddr, port, dr, power, size);

        	unsigned int len = encode_benchmark(payload, size, power, dr);

        	len = encode_sensors(payload + len, size - len);

            // WARNING : If LORAMAC_TX_CNF, the firmware is blocked when the network server does not confirmed the message
            //semtech_loramac_set_tx_mode(loramac, benchmark.txconfirmed ? LORAMAC_TX_CNF : LORAMAC_TX_UNCNF);

            /* send the LoRaWAN message */
        	if(dr == 0xff) {
        	    semtech_loramac_set_adr(loramac, true);
        	} else {
        	    semtech_loramac_set_adr(loramac, false);
        		semtech_loramac_set_dr(loramac, dr);
        	}

            semtech_loramac_set_tx_port(loramac, port);

            if(power < ARRAY_SIZE(_pwd_dbm_to_id)){
                semtech_loramac_set_tx_power(loramac, _pwd_dbm_to_id[power]);
            } else {
                semtech_loramac_set_tx_power(loramac, 6); // 14 dBm
            }

            semtech_loramac_set_devaddr(loramac, (uint8_t*)&devaddr);

            uint8_t ret = semtech_loramac_send(loramac, payload, size);

            uint32_t uplink_counter = semtech_loramac_get_uplink_counter(loramac);

            if (ret != SEMTECH_LORAMAC_TX_DONE) {
                DEBUG("[ftd] ERROR: Cannot send payload: ret code: %d (%s)\n", ret, loramac_utils_err_message(ret));
            } else {
            	DEBUG("[ftd] Tx Done ret=%d fcnt=%ld\n", ret, uplink_counter);
            }

            xtimer_sleep(*benchmark.tx_period);

#if LORAMAC_LINK_CHECK == 1
            // schedule LORAMAC_LINK_CHECK
            if(cpt%LORAMAC_LINK_CHECK_PERIOD == 0) {
                semtech_loramac_request_link_check(loramac);
            }
#endif

#if APP_CLOCK_SYNC == 1
            // send a APP_TIME_REQ request every APP_TIME_REQ_PERIOD message
            if(cpt%APP_TIME_REQ_PERIOD == 0) {
            	// keep the current MAC configuration
                //semtech_loramac_set_tx_mode(loramac, LORAMAC_TX_CNF);
            	app_clock_send_app_time_req(loramac);
            	xtimer_sleep(*benchmark.tx_period);
            }
#endif
        }

        /* sleep tx_period secs */
        // TODO introduire un alea de quelques secondes dans la tx_period pour éviter que des endpoints qui redémarrent ensemble se brouillent les uns les autres.
        // TODO verifier que la tx_period est compatible avec le DC (sinon, le Tx retourne le code=13)
        xtimer_usleep(*benchmark.tx_period * 1000000 + random_uint32_range (0, NEXT_BENCHMARK_RANDOM * 1000000));

    }

    /* this should never be reached */
    return;
}
