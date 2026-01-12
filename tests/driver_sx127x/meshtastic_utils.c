/*
 * Copyright (C) 2025 Université Grenoble Alpes
 */

/*
 * Utils for the Meshtastic
 *
 */
#include <string.h>
#include <stdio.h>

#include "meshtastic_utils.h"

/** Check Size */
bool meshtastic_check_valid_frame_size(const uint8_t *frame_buffer, const uint8_t frame_size) {
	(void)frame_buffer;
	return frame_size >= 16;
}

/** Get Destination Id */
uint32_t meshtastic_get_destination_id(const uint8_t *frame_buffer, const uint8_t frame_size) {
	(void)frame_size;
	return ((MeshtasticHeader_t*)frame_buffer)->destination_id;
}

/** Get Source Id */
uint32_t meshtastic_get_source_id(const uint8_t *frame_buffer, const uint8_t frame_size) {
	(void)frame_size;
	return ((MeshtasticHeader_t*)frame_buffer)->source_id;
}

/** Get Packet Id */
uint32_t meshtastic_get_packet_id(const uint8_t *frame_buffer, const uint8_t frame_size) {
	(void)frame_size;
	return ((MeshtasticHeader_t*)frame_buffer)->packet_id;
}

/** Get Hop Limit */
uint8_t meshtastic_get_hop_limit(const uint8_t *frame_buffer, const uint8_t frame_size) {
	(void)frame_size;
	return ((MeshtasticHeader_t*)frame_buffer)->hop_limit;
}

/** Get Hope Start */
uint8_t meshtastic_get_hope_start(const uint8_t *frame_buffer, const uint8_t frame_size) {
	(void)frame_size;
	return ((MeshtasticHeader_t*)frame_buffer)->hope_start;
}

/** Is From MQTT */
bool meshtastic_is_from_mqtt(const uint8_t *frame_buffer, const uint8_t frame_size) {
	(void)frame_size;
	return ((MeshtasticHeader_t*)frame_buffer)->from_mqtt == 1;
}

/** Is Want Ack */
bool meshtastic_is_want_ack(const uint8_t *frame_buffer, const uint8_t frame_size) {
	(void)frame_size;
	return ((MeshtasticHeader_t*)frame_buffer)->want_ack == 1;
}

/** Get Channel Hash */
uint8_t meshtastic_get_channel_hash(const uint8_t *frame_buffer, const uint8_t frame_size) {
	(void)frame_size;
	return ((MeshtasticHeader_t*)frame_buffer)->channel_hash;
}

/** Get Protobuf Payload */
void meshtastic_get_pb_payload(const uint8_t *frame_buffer, const uint8_t frame_size, uint8_t *payload, uint8_t* payload_size) {
	*payload_size = frame_size - 16;
	memcpy(payload, ((MeshtasticHeader_t*)frame_buffer)->pb_payload, *payload_size);
}

/** Print payload */
void meshtastic_printf(const uint8_t *frame_buffer, const uint8_t frame_size) {
	if(frame_size < 16) {
		printf("too short for a meshtastic frame\n");
		return;
	}

	const MeshtasticHeader_t*  m = (MeshtasticHeader_t*)frame_buffer;

	printf("destination_id: %8lx\n", m->destination_id);
	printf("source_id:      %8lx\n", m->source_id);
	printf("packet_id:      %8lx\n", m->packet_id);

	printf("hop_limit:      %d\n", m->hop_limit);
	printf("hope_start:     %d\n", m->hope_start);
	printf("from_mqtt:      %s\n", m->from_mqtt == 1 ? "true" : "false");
	printf("want_ack:       %s\n", m->want_ack == 1 ? "true" : "false");

	printf("channel_hash:   %2x\n", m->channel_hash);
	printf("pb_payload:     ");

	for (uint8_t j = 0; j < frame_size - 16; j++) {
		printf("%02X ", m->pb_payload[j]);
	}
	printf("\n");

	// TODO display encrypted protobuf payload
}


