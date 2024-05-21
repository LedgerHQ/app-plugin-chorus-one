/*******************************************************************************
 *   Plugin Boilerplate
 *   (c) 2023 Ledger
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 ********************************************************************************/

#pragma once

#include <string.h>
#include "eth_plugin_interface.h"

// All possible selectors of your plugin.
// EDIT THIS: Enter your selectors here, in the format X(NAME, value)
// A Xmacro below will create for you:
//     - an enum named selector_t with every NAME
//     - a map named SELECTORS associating each NAME with it's value
#define SELECTORS_LIST(X)                        \
    X(STAKEWISE_DEPOSIT, 0xf9609f08)             \
    X(STAKEWISE_BURN_OS_TOKEN, 0x066055e0)       \
    X(STAKEWISE_ENTER_EXIT_QUEUE, 0x8ceab9aa)    \
    X(STAKEWISE_CLAIM_EXITED_ASSETS, 0x8697d2c2) \
    X(STAKEWISE_LIQUIDATE_OS_TOKEN, 0x2999ad3f)  \
    X(STAKEWISE_MINT_OS_TOKEN, 0x201b9eb5)       \
    X(STAKEWISE_REDEEM, 0x7bde82f2)              \
    X(STAKEWISE_REDEEM_OS_TOKEN, 0x43e82a79)

// Xmacro helpers to define the enum and map
// Do not modify !
#define TO_ENUM(selector_name, selector_id)  selector_name,
#define TO_VALUE(selector_name, selector_id) selector_id,

// This enum will be automatically expanded to hold all selector names.
// The value SELECTOR_COUNT can be used to get the number of defined selectors
// Do not modify !
typedef enum selector_e {
    SELECTORS_LIST(TO_ENUM) SELECTOR_COUNT,
} selector_t;

// This array will be automatically expanded to map all selector_t names with the correct value.
// Do not modify !
extern const uint32_t SELECTORS[SELECTOR_COUNT];

// Enumeration used to parse the smart contract data.
// EDIT THIS: Adapt the parameter names here.
typedef enum {
    RECEIVER = 0,  // Address
    REFERRER,
    OS_TOKEN_SHARES,
    VAULT_SHARES,
    POSITION_TICKET,
    TIMESTAMP,
    EXIT_QUEUE_INDEX,
    OWNER,
    // PATH_OFFSET,
    // PATH_LENGTH,
    UNEXPECTED_PARAMETER,
} parameter;

// Shared global memory with Ethereum app. Must be at most 5 * 32 bytes.
typedef struct context_s {
    // For display.
    // `vault_shares` also used as `positionTicket` due to size constrains.
    uint8_t vault_shares[INT256_LENGTH];
    uint8_t receiver[ADDRESS_LENGTH];
    // `referrer` also used as `owner`.
    uint8_t referrer[ADDRESS_LENGTH];
    uint8_t os_token_shares[INT128_LENGTH];
    uint8_t timestamp[INT256_LENGTH];
    uint8_t exit_queue_index[INT256_LENGTH];

    // For parsing data.
    uint8_t next_param;  // Set to be the next param we expect to parse.
    // uint16_t offset;     // Offset at which the array or struct starts.
    // bool go_to_offset;   // If set, will force the parsing to iterate through parameters until
    //                      // `offset` is reached.

    // For both parsing and display.
    selector_t selectorIndex;
} context_t;

// Check if the context structure will fit in the RAM section ETH will prepare for us
// Do not remove!
ASSERT_SIZEOF_PLUGIN_CONTEXT(context_t);
