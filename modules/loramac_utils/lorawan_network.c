/*
 * Copyright (C) 2020 Didier Donsez
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     pkg_semtech_loramac
 * @{
 *
 * @file
 * @brief       Utility functions for Semtech LoRaMac library.
 *
 * @author      Didier Donsez <didier.donsez@univ-grenoble-alpes.fr>
 *
 * @}
 */

#define ENABLE_DEBUG (1)
#include "debug.h"

#include "inttypes.h"

#include "net/loramac.h"
#include "semtech_loramac.h"

#include <string.h>

// See https://www.thethingsnetwork.org/docs/lorawan/prefix-assignments/

#define DEVADDR_MASK_NETID1								(0xFE000000)
#define DEVADDR_MASK_NETID3								(0xFFFE0000)
#define DEVADDR_MASK_NETID6								(0xFFFFFC00)


// Experimental NetID 1 (00000000 - 01FFFFFF)
#define DEVADDR_BASE_EXPERIMENTAL						(0x00000000)
// Experimental NetID 1 (02000000 - 03FFFFFF)
#define DEVADDR_BASE_EXPERIMENTAL1						(0x02000000)

// CampusIoT NetId 6 (FC00AC00 - FC00AFFF)
#define DEVADDR_BASE_UGA								(0xFC00AC00)

// TTN NetID 1 (26000000 - 27FFFFFF)
#define DEVADDR_BASE_TTN								(0x26000000)
// Actility NetID 1 (04000000 - 05FFFFFF)
#define DEVADDR_BASE_ACTILITY							(0x04000000)
// Orange NetID 1 (1E000000 - 1FFFFFFF)
#define DEVADDR_BASE_ORANGE								(0x1E000000)

// Bouygues Telecom (now Netmore) NetID 1 (0E000000 - 0FFFFFFF)
#define DEVADDR_BASE_BOUYGUES_TELECOM					(0x0E000000)
// Netmore NetID 3 (E0040000 - E005FFFF)
#define DEVADDR_BASE_NETMORE3					        (0xE0040000)
// Netmore NetID 6 (FC004800 - FC004BFF)
#define DEVADDR_BASE_NETMORE6					        (0xFC004800)

// Requea NetId 6 (FC006800 - FC006BFF)
#define DEVADDR_BASE_REQUEA								(0xFC006800)


// Swisscom NetID 1 (08000000 - 09FFFFFF)
#define DEVADDR_BASE_SWISSCOM							(0x08000000)
// KPN NetID 1 (2A000000 - 2BFFFFFF)
#define DEVADDR_BASE_KPN								(0x2A000000)
// Digita NetID 3 (E0020000 - E003FFFF)
#define DEVADDR_BASE_DIGITA								(0xE0020000)

// Cisco Systems NetID 1 (2A000000 - 2BFFFFFF)
#define DEVADDR_BASE_CISCO_SYSTEMS						(0x2A000000)
// TATA Communication NetID 1(22000000 - 23FFFFFF)
#define DEVADDR_BASE_TATA_COMMUNICATIONS				(0x22000000)

// Lacuna NetId 6 (FC00A000 - FC00A3FF)
#define DEVADDR_BASE_LACUNA								(0xFC00A000)
// Hiber NetId 6 (FC008400 - FC0087FF)
#define DEVADDR_BASE_HIBER								(0xFC008400)

// Multitech NetID 1 (2E000000 - 2FFFFFFF)
#define DEVADDR_BASE_MULTITECH							(0x2E000000)
// Schneider Electric NetID 3 (E02E0000 - E02FFFFF)
#define DEVADDR_BASE_SCHNEIDER_ELECTRIC					(0xE02E0000)
// Kerlink NetID 1 (24000000 - 25FFFFFF)
#define DEVADDR_BASE_KERLINK							(0x24000000)

// Birdz NetID 3 (E04E0000 - E04FFFFF)
#define DEVADDR_BASE_BIRDZ							    (0xE04E0000)
// Birdz NetID 3 (E0560000 - E057FFFF)
#define DEVADDR_BASE_AMAZON							    (0xE0560000)

// Eutelsat S.A. NetID 3 (E05C0000 - E05DFFFF)
#define DEVADDR_BASE_EUTELSAT							(0xE05C0000)

// Andorra Telecom NetID 3 (FC00A400 - FC00A7FF)
#define DEVADDR_BASE_ANDORRA_TELECOM					(0xE05C0000)

// Afnic NetID 6 (FC00BC00 - FC00BFFF)
#define DEVADDR_BASE_AFNIC					            (0xFC00BC00)


#define IS_BELONGING_TO_NETWORK(devaddr,devaddr_subnet,devaddr_mask) ( devaddr_subnet == ( devaddr & devaddr_mask ))


#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))

typedef struct lorawan_network {

	/*
	 * @brief Subnet of the DevAddr
	 */
	uint32_t devaddr_subnet;

	/*
	 * @brief Mask of the DevAddr
	 */
	uint32_t devaddr_mask;

	/*
	 * @brief Name of the network
	 */
	char* name;

	// TODO add char* region;


} lorawan_network_t;

// TODO complete the list with https://www.thethingsnetwork.org/docs/lorawan/prefix-assignments/

static const lorawan_network_t lorawan_networks[] = {
		{ DEVADDR_BASE_EXPERIMENTAL, DEVADDR_MASK_NETID1, "Experimental"},
		{ DEVADDR_BASE_EXPERIMENTAL1, DEVADDR_MASK_NETID1, "Experimental1"},
		{ DEVADDR_BASE_ACTILITY, DEVADDR_MASK_NETID1, "Actility"},
		{ DEVADDR_BASE_TTN, DEVADDR_MASK_NETID1, "The Things Network"},
		{ DEVADDR_BASE_ORANGE, DEVADDR_MASK_NETID1, "Orange"},

		{ DEVADDR_BASE_BOUYGUES_TELECOM, DEVADDR_MASK_NETID1, "Bouygues Telecom (now Netmore)"},
		{ DEVADDR_BASE_NETMORE3, DEVADDR_MASK_NETID3, "Netmore"},
		{ DEVADDR_BASE_NETMORE6, DEVADDR_MASK_NETID6, "Netmore"},

		{ DEVADDR_BASE_KERLINK, DEVADDR_MASK_NETID1, "Kerlink"},
		{ DEVADDR_BASE_CISCO_SYSTEMS, DEVADDR_MASK_NETID1, "Cisco Systems"},
		{ DEVADDR_BASE_TATA_COMMUNICATIONS, DEVADDR_MASK_NETID1, "Tata Communications"},
		{ DEVADDR_BASE_MULTITECH, DEVADDR_MASK_NETID1, "Mulitech"},

		{ DEVADDR_BASE_SCHNEIDER_ELECTRIC, DEVADDR_MASK_NETID3, "Schneider Electric"},

		{ DEVADDR_BASE_BIRDZ, DEVADDR_MASK_NETID3, "Birdz"},
		{ DEVADDR_BASE_AMAZON, DEVADDR_MASK_NETID3, "Amazon"},
		{ DEVADDR_BASE_ANDORRA_TELECOM, DEVADDR_MASK_NETID3, "Andorra Telecom"},

		{ DEVADDR_BASE_AFNIC, DEVADDR_MASK_NETID6, "Afnic"},

		{ DEVADDR_BASE_EUTELSAT, DEVADDR_MASK_NETID3, "Eutelsat S.A."},
		{ DEVADDR_BASE_LACUNA, DEVADDR_MASK_NETID6, "Lacuna Space"},
		{ DEVADDR_BASE_HIBER, DEVADDR_MASK_NETID6, "Hiber"},
		{ DEVADDR_BASE_REQUEA, DEVADDR_MASK_NETID6, "Requea"},
        
		{ DEVADDR_BASE_UGA, DEVADDR_MASK_NETID6, "Université Grenoble Alpes"}
};

const char* loramac_utils_get_lorawan_network(const uint32_t devaddr) {
	// TODO Special case for Helium

	for(unsigned int i=0; i < NELEMS(lorawan_networks); i++) {
		const lorawan_network_t* ln = lorawan_networks + i;
		if (IS_BELONGING_TO_NETWORK(devaddr,ln->devaddr_subnet, ln->devaddr_mask)) {
			return ln->name;
		}
	}

	return "Unknown";
}

