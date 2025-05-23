#ifndef SIGN_H
#define SIGN_H

int microsui_sign_offline(uint8_t signature[97], const char* message_hex, const uint8_t private_key[32]);

void print_hex(const char* label, const uint8_t *data, size_t len);

#endif