#include <eth_plugin_interface.h>


const char HEX_CHARS[] = "0123456789ABCDEF";

void byte_to_hex(char *dst, uint8_t byte) {
    dst[0] = HEX_CHARS[(byte >> 4) & 0x0F];
    dst[1] = HEX_CHARS[byte & 0x0F];
}

void displayEthAddress(ethQueryContractUI_t *msg, uint8_t * address) {
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
