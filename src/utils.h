#pragma once

void display_first_and_last_bytes(ethQueryContractUI_t *msg, uint8_t *address, int array_offset, int first_last_size);
void display_uint_decimal(ethQueryContractUI_t *msg, uint8_t *number, size_t size);
void display_hexa(ethQueryContractUI_t *msg, uint8_t *data, size_t length);