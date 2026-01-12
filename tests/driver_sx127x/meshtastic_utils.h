/*
 * Copyright (C) 2025 Université Grenoble Alpes
 */

/*
 * Utils for the Meshtastic
 *
 */

#ifndef MODULES_MESHTASTIC_UTILS_INCLUDE_MESHTASTIC_UTILS_H_
#define MODULES_MESHTASTIC_UTILS_INCLUDE_MESHTASTIC_UTILS_H_

#include <stdint.h>
#include <stdbool.h>

struct __attribute__((__packed__)) MeshtasticHeader
{
	uint32_t destination_id; // The destination's unique NodeID. 0xFFFFFFFF for broadcast. Little Endian.
	uint32_t source_id; //  The sender's unique NodeID. Little Endian.
	uint32_t packet_id; // The sending node's unique packet ID for this packet. Little Endian.

	uint8_t hope_start: 3;  // 0:2 original HopLimit
	uint8_t from_mqtt: 1;   // 3:3 ViaMQTT (packet came via MQTT)
	uint8_t want_ack: 1;    // 4:4
	uint8_t hop_limit: 3;   // 5:7

	uint8_t channel_hash; // Channel hash. Used as hint for decryption for the receiver.

	uint8_t next_hop; // Next-hop used for relaying
	uint8_t relay_node; // Relay node of the current transmission

	uint8_t pb_payload[237]; // Max. 237 bytes (excl. protobuf overhead)
};

typedef struct MeshtasticHeader MeshtasticHeader_t;

/** Check Size */
bool meshtastic_check_valid_frame_size(const uint8_t *frame_buffer, const uint8_t frame_size);

/** Get Destination Id */
uint32_t meshtastic_get_destination_id(const uint8_t *frame_buffer, const uint8_t frame_size);

/** Get Source Id */
uint32_t meshtastic_get_source_id(const uint8_t *frame_buffer, const uint8_t frame_size);

/** Get Packet Id */
uint32_t meshtastic_get_packet_id(const uint8_t *frame_buffer, const uint8_t frame_size);

/** Get Hop Limit */
uint8_t meshtastic_get_hop_limit(const uint8_t *frame_buffer, const uint8_t frame_size);

/** Get Hope Start */
uint8_t meshtastic_get_hope_start(const uint8_t *frame_buffer, const uint8_t frame_size);

/** Is From MQTT */
bool meshtastic_is_from_mqtt(const uint8_t *frame_buffer, const uint8_t frame_size);

/** Is Want Ack */
bool meshtastic_is_want_ack(const uint8_t *frame_buffer, const uint8_t frame_size);

/** Get Channel Hash */
uint8_t meshtastic_get_channel_hash(const uint8_t *frame_buffer, const uint8_t frame_size);

/** Get Protobuf Payload */
void meshtastic_get_pb_payload(const uint8_t *frame_buffer, const uint8_t frame_size, uint8_t *payload, uint8_t* payload_size);

/** Print payload */
void meshtastic_printf(const uint8_t *frame_buffer, const uint8_t frame_size);

#endif /* MODULES_MESHTASTIC_UTILS_INCLUDE_MESHTASTIC_UTILS_H_ */