#include <eth_plugin_interface.h>

const char HEX_CHARS[] = "0123456789ABCDEF";

void byte_to_hex(char *dst, uint8_t byte) {
    dst[0] = HEX_CHARS[(byte >> 4) & 0x0F];
    dst[1] = HEX_CHARS[byte & 0x0F];
}

void display_first_and_last_bytes(ethQueryContractUI_t *msg,
                                  uint8_t *data,
                                  int array_size,
                                  int first_last_size) {
    char *next_ptr = msg->msg;
    strlcpy(next_ptr, "0x", sizeof(msg->msg));
    next_ptr += 2;
    for (int i = 0; i < first_last_size; ++i) {
        byte_to_hex(next_ptr, data[i]);
        next_ptr += 2;
    }
    if (first_last_size <= 1) {
        // Can display just the first byte.
        return;
    }
    strlcpy(next_ptr, "...", sizeof(msg->msg));
    next_ptr += 3;
    for (int i = 0; i < first_last_size; ++i) {
        byte_to_hex(next_ptr, data[array_size - first_last_size + i]);
        next_ptr += 2;
    }
}
