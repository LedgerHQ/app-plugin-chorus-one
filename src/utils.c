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
    strcpy(next_ptr, "0x");
    next_ptr += 2;
    for (int i = 0; i < first_last_size; ++i) {
        byte_to_hex(next_ptr, data[i]);
        next_ptr += 2;
    }
    if (first_last_size <= 1) {
        // Can display just the first byte.
        return;
    }
    strcpy(next_ptr, "...");
    next_ptr += 3;
    for (int i = 0; i < first_last_size; ++i) {
        byte_to_hex(next_ptr, data[array_size - first_last_size + i]);
        next_ptr += 2;
    }
}

void display_uint_decimal(ethQueryContractUI_t *msg, uint8_t *number, size_t size) {
    char buffer[80] = {0};
    int buffer_index = sizeof(buffer) - 1;
    buffer[buffer_index] = '\0';

    uint8_t temp_number[32] = {0};
    memcpy(temp_number, number, size);

    size_t temp_index;
    uint8_t carry;

    do {
        carry = 0;
        for (size_t i = 0; i < size; i++) {
            uint16_t value = (carry << 8) + temp_number[i];
            temp_number[i] = value / 10;
            carry = value % 10;
        }
        buffer[--buffer_index] = carry + '0';

        // Remove zeros
        temp_index = 0;
        while (temp_index < size && temp_number[temp_index] == 0) {
            temp_index++;
        }
    } while (temp_index < size);

    strcpy(msg->msg, &buffer[buffer_index]);
}
