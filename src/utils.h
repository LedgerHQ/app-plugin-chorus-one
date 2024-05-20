#pragma once

void display_eth_address(ethQueryContractUI_t *msg, uint8_t *address);
void display_uint_decimal(ethQueryContractUI_t *msg, uint8_t *number, size_t size);
void copy_parameter_with_offset(uint8_t* dst, const uint8_t* parameter, uint8_t offset, uint8_t dst_size);