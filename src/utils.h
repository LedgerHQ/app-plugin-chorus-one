#pragma once

void display_eth_address(ethQueryContractUI_t *msg, uint8_t *address);
void display_uint128_decimal(ethQueryContractUI_t *msg_struct, uint8_t *os_shares);
void copy_parameter_with_offset(uint8_t* dst, const uint8_t* parameter, uint8_t offset, uint8_t dst_size);