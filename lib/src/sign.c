#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "monocypher/monocypher.h"
#include "compact25519/compact_ed25519.h"

void hex_to_bytes(const char* hex_str, uint8_t* bytes, size_t bytes_len) {
    for (size_t i = 0; i < bytes_len; i++) {
        sscanf(hex_str + 2*i, "%2hhx", &bytes[i]);  // Convert 2 hex chars to 1 byte
    }
}

void print_hex(const char* label, const uint8_t* data, size_t len) {
    printf("%s (%zu bytes): ", label, len);
    for (size_t i = 0; i < len; i++) {
        printf("%02x", data[i]);
    }
    printf("\n\n");
}


size_t build_message_with_intent(uint8_t *tx_bytes, size_t tx_len, uint8_t *output) {
    size_t offset = 0;

    // Setting Intent
    output[offset++] = 0x00; // scope: 0x00 is TransactionData (we need this in this case)
    output[offset++] = 0x00; // version: V0
    output[offset++] = 0x00; // appId: Sui

    // Copying tx_bytes in output
    memcpy(output + offset, tx_bytes, tx_len);
    offset += tx_len;

    return offset; // Total length of messageWithIntent
}

int microsui_sign_offline(uint8_t sui_sig[97], const char* message_hex, const uint8_t private_key[32]) {
    // 1. Convert the HEX message to binary bytes
    size_t msg_len = strlen(message_hex) / 2;  // 2 hex chars = 1 byte
    uint8_t* message = (uint8_t*)malloc(msg_len);
    hex_to_bytes(message_hex, message, msg_len);

    uint8_t private_key_cp[32];
    memcpy(private_key_cp, private_key, 32);

    // 2. Generate public key
    uint8_t public_key[32];
    uint8_t secret_key[64];
    crypto_ed25519_key_pair(secret_key, public_key, private_key_cp);

    // 3. Generate digest using BLAKE2b with the message whit the intent
    uint8_t message_with_intent[512];
    uint8_t message_with_intent_len = build_message_with_intent(message, msg_len, message_with_intent);
    uint8_t digest[32];
    crypto_blake2b(digest, 32, message_with_intent, message_with_intent_len);

    // 4. Sign the digest using Ed25519 with the private key and public key
    uint8_t ed25519_signature[64];
    compact_ed25519_sign(ed25519_signature, secret_key, digest, 32);

    // 5. Build Sui signature
    sui_sig[0] = 0x00;  // Ed25519 Scheme
    memcpy(sui_sig + 1, ed25519_signature, 64);
    memcpy(sui_sig + 65, public_key, 32);

    free(message);
    return 0;
}