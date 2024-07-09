#pragma once

void display_first_and_last_bytes(ethQueryContractUI_t *msg,
                                  uint8_t *address,
                                  int array_offset,
                                  int first_last_size);
bool compare_last_n_bytes(const uint8_t *parameter, const uint8_t *expected_bytes, size_t n);
