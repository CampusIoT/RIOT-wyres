/*
 * Copyright (C) 2025-2026 Université Grenoble Alpes
 */

/*
 * Utils for the LoRa Mini Mesh
 *
 */

#ifndef LORA_MINI_MESH_H
#define LORA_MINI_MESH_H

#include <inttypes.h>
#include <stdbool.h>

#define LORAWAN_PHYPAYLOAD_LEN					(256U)

#define LORAWAN_MTYPE_PROPRIETARY				(0b111)
#define LORAMESH_TYPE_ADVERT					(0b00001)
#define LORAMESH_TYPE_GROUP						(0b00010)
#define LORAMESH_TYPE_DIRECT					(0b00011)


// Payload
#define LORAMESH_PAYLOAD_TYPE_RAW				(0b000)
#define LORAMESH_PAYLOAD_TYPE_TEXT				(0b001)
#define LORAMESH_PAYLOAD_TYPE_TEXT_UNISHOX2		(0b001)
#define LORAMESH_PAYLOAD_TYPE_IMAGE_AEIC_SE		(0b001)
#define LORAMESH_PAYLOAD_TYPE_PING				(0b001)
#define LORAMESH_PAYLOAD_TYPE_TRACEROUTE		(0b001)
#define LORAMESH_PAYLOAD_TYPE_NEIGHBOUR			(0b001)
#define LORAMESH_PAYLOAD_TYPE_LPP				(0b001)



advert, text, text_unishox2, image_aeic_se, lpp, raw, ping, traceroute, neighbour

/**
 * MeshLoRa MHDR
 */
struct __attribute__((packed)) LoRaMiniMesh_MHDR {
	
	uint8_t hop :3;

	uint8_t payload_type :5;

	uint8_t rfu :5;

	uint8_t mtype :3;
};


typedef struct LoRaMiniMesh_MHDR LoRaMiniMesh_MHDR_t;


/**
 * MeshLoRa Advert
 */
struct __attribute__((packed)) LoRaMiniMesh_Advert {

	uint8_t hop :3;

	uint8_t payload_type :5;

	uint8_t rfu :5;

	uint8_t mtype :3;

	// 

	uint32_t timestamp; // used at frame counter

	uint8_t pubkey[32];

	uint8_t fieldsflags;

	// location
	// name

	// MIC self-signed with public key is appended to the message
};


typedef struct LoRaMiniMesh_Advert LoRaMiniMesh_Advert_t;



/**
 * MeshLoRa Group
 */
struct __attribute__((packed)) LoRaMiniMesh_Group {

	uint8_t hop :3;

	uint8_t payload_type :5;

	uint8_t rfu :5;

	uint8_t mtype :3;

	// 

	uint16_t src_prefix;

	uint8_t payload[LORAWAN_PHYPAYLOAD_LEN - 14U];

	// MIC is appended to the message
};


typedef struct LoRaMiniMesh_Group LoRaMiniMesh_Group_t;




/**
 * MeshLoRa Uplink
 */
struct __attribute__((packed)) LoRaMiniMesh_Uplink {

	uint8_t hop_count :3;

	uint8_t payload_type :2;

	uint8_t mtype :3;

	uint16_t datarate :4;

	uint16_t uplink_id :12;

	uint8_t rssi;

	uint8_t snr :6;

	uint8_t rfu :2;

	uint8_t channel;

	uint32_t relay_id;

	uint8_t lora_mini_mesh_phypayload[LORAWAN_PHYPAYLOAD_LEN - 14U];

};

typedef struct LoRaMiniMesh_Uplink LoRaMiniMesh_Uplink_t;

/**
 * MeshLoRa Downlink
 */
struct __attribute__((packed)) LoRaMiniMesh_Downlink {

	uint8_t hop_count :3;

	uint8_t payload_type :2;

	uint8_t mtype :3;

	uint16_t downlink_datarate :4;

	uint16_t uplink_id :12;

	uint32_t delay :4;

	uint32_t tx_power :4;

	uint32_t downlink_frequency :24;

	uint32_t relay_id;

	uint8_t lora_mini_mesh_phypayload[LORAWAN_PHYPAYLOAD_LEN - 15U];

};

typedef struct LoRaMiniMesh_Downlink LoRaMiniMesh_Downlink_t;

/**
 * MeshLoRa Relay Heartbeat
 */
struct __attribute__((packed)) LoRaMiniMesh_RelayHeartbeat {

	uint8_t hop_count :3;

	uint8_t payload_type :2;

	uint8_t mtype :3;

	uint32_t timestamp;

	uint32_t relay_id;

	uint8_t relay_path[28U];

};

typedef struct LoRaMiniMesh_RelayHeartbeat LoRaMiniMesh_RelayHeartbeat_t;

/**
 * MeshLoRa Stats (Extension proposal)
 */
struct __attribute__((packed)) LoRaMiniMesh_Stats {

	unsigned int mtype :3;

	unsigned int payload_type :2;

	unsigned int hop_count :3;

	uint32_t relay_id;

	uint16_t stats_id; // LSB of uint32_t

	uint16_t uptime; // LSB of uint32_t

	uint16_t rx; // Number of frames since boot. LSB of uint32_t

	uint16_t rx_ok; // Number of frames (CRC_OK) since boot. LSB of uint32_t

	uint16_t rx_relay; // Number of relayed frames (uplink) since boot. LSB of uint32_t

	uint16_t tx; // Number of tx frames since boot. LSB of uint32_t

	uint16_t tx_relay; // Number of relayed tx frames (downlink) since boot. LSB of uint32_t
};

typedef struct LoRaMiniMesh_Stats LoRaMiniMesh_Stats_t;

/** Check valid mesh frame */
bool lora_mini_mesh_check_valid_frame(const uint8_t *frame_buffer,
		const uint8_t size);

/** Get Type */
uint8_t lora_mini_mesh_get_type(const uint8_t *frame_buffer, const uint8_t size);

/** Get frame MIC */
uint32_t lora_mini_mesh_get_mic(const uint8_t *frame_buffer, const uint8_t size);

/** Check frame MIC */
bool lora_mini_mesh_check_mic(const uint8_t *frame_buffer, const uint8_t size,
		const uint8_t *aes_key);

/** Is LoRa Mesh Join Frame */
bool lora_mini_mesh_is_uplink(const uint8_t *frame_buffer, const uint8_t size);

/** Is LoRa Mesh Join Frame */
bool lora_mini_mesh_is_downlink(const uint8_t *frame_buffer, const uint8_t size);

/** Is LoRa Mesh Relay Heartbeat */
bool lora_mini_mesh_is_relay_heartbeat(const uint8_t *frame_buffer,
		const uint8_t size);

/** get hop count */
bool lora_mini_mesh_get_hop_count(const uint8_t *frame_buffer, const uint8_t size);

/** Get Relay Id */
uint32_t lora_mini_mesh_get_relay_id(const uint8_t *frame_buffer,
		const uint8_t size);

/** get SNR as encoded value */
uint8_t lora_mini_mesh_get_snr_u(const float snr);

/** get SNR as float */
float lora_mini_mesh_get_snr_f(const uint8_t snr);

/** get the channel from the frequency */
uint8_t lora_mini_mesh_get_channel(const uint32_t freq_hz, const uint32_t* frequency_plan, const uint32_t frequency_plan_len);

/** Get LoRaWAN PhyPayload */
const uint8_t* lora_mini_mesh_get_payload(const uint8_t *frame_buffer,
		const uint8_t size, uint8_t *lorawan_phypayload_size);

/** Get LoRaWAN PhyPayload size */
uint8_t lora_mini_mesh_get_payload_size(const uint8_t *frame_buffer,
		const uint8_t size);

void lora_mini_mesh_printf_uplink(const uint8_t *frame_buffer, const uint8_t size);

void lora_mini_mesh_printf_downlink(const uint8_t *frame_buffer, const uint8_t size);

void lora_mini_mesh_printf_relay_heartbeat(const uint8_t *frame_buffer,
		const uint8_t size);

void lora_mini_mesh_printf_frame(const uint8_t *frame_buffer, const uint8_t size);

bool lora_mini_mesh_build_uplink(uint8_t *frame_buffer, uint8_t *size,
		const uint8_t hop_count, const uint16_t uplink_id,
		const uint8_t datarate, const float rssi, const float snr,
		const uint8_t channel, const uint32_t relay_id,
		const uint8_t *phypayload, const uint8_t phypayload_size,
		const uint8_t *signing_key);

#endif
