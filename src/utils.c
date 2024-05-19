#include <eth_plugin_interface.h>


const char HEX_CHARS[] = "0123456789ABCDEF";

void byte_to_hex(char *dst, uint8_t byte) {
    dst[0] = HEX_CHARS[(byte >> 4) & 0x0F];
    dst[1] = HEX_CHARS[byte & 0x0F];
}

void display_eth_address(ethQueryContractUI_t *msg, uint8_t * address) {
    char* next_ptr = msg->msg;
    strcpy(next_ptr, "0x");
    next_ptr += 2;
    for (int i = 0; i < 3; ++i) {
        byte_to_hex(next_ptr, address[i]);
        next_ptr += 2;
    }
    strcpy(next_ptr, "...");
    next_ptr += 3;
    for (int i = 0; i < 3; ++i) {
        byte_to_hex(next_ptr, address[ADDRESS_LENGTH-3 + i]);
        next_ptr += 2;
    }
}

void display_uint128_decimal(ethQueryContractUI_t *msg, uint8_t *number) {
    char buffer[40] = {0};
    int buffer_index = 39;
    buffer[buffer_index] = '\0';

    uint8_t temp_number[16];
    memcpy(temp_number, number, 16);
    int temp_index;
    uint8_t carry;
    do {
        carry = 0;
        for (int i = 0; i < 16; i++) {
            uint16_t value = (carry << 8) + temp_number[i];
            temp_number[i] = value / 10;
            carry = value % 10;
        }
        buffer[--buffer_index] = carry + '0';
        
        temp_index = 0;
        while (temp_index < 16 && temp_number[temp_index] == 0) {
            temp_index++;
        }
    } while (temp_index < 16);

    strcpy(msg->msg, &buffer[buffer_index]);
}