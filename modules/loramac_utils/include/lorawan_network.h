/*
 * Copyright (C) 2020-2023 UGA LIG
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
 * @brief       Utility functions for LoRaWAN
 *
 * @author      Didier Donsez <didier.donsez@univ-grenoble-alpes.fr>
 *
 * @}
 */

#ifndef LORAWAN_NETWORK_H
#define LORAWAN_NETWORK_H

#include <inttypes.h>

#ifdef __cplusplus
extern "C"
{
#endif

    const char* loramac_utils_get_lorawan_network(const uint32_t devaddr);

#ifdef __cplusplus
extern "C"
}
#endif

#endif
