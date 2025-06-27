#include <stdio.h>
#include <string.h>
#include "microsui/sign.h"
#include "microsui/cryptography.h"
#include "microsui/utils.h"
#include "constants.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define BLINK_GPIO GPIO_NUM_8

void app_main() {
    gpio_reset_pin(BLINK_GPIO);
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
    vTaskDelay(pdMS_TO_TICKS(2500));
    gpio_set_level(BLINK_GPIO, 0);
    printf("\n\n\n\t\t--- MicroSui: Blank ESP32 Template Project ---\n");

    /*
    *
    *   Please insert your code here.
    * 
    *   Below you will find a small implementation with the main functions of Microsui. 
    *   You can eliminate or edit it if you need it.
    *   Also, remember that there are more examples available for ESP32 in the 
    *   `/examples` folder of this repository
    * 
    */

    printf("\n\n\t\tGenerating Signature from Message!\n");
    // private_key_bech32 is defined in constants.c
    uint8_t private_key[32];
    const char* msg_hex = "48656c6c6f2053756921"; // Hello Sui! in hexa
    uint8_t sui_sig[97];
    char sui_sig_hex[195]; // 2 hex chars per byte + null terminator
    // 1- Decoding the Bech32 private key to bytes (MicroSui functions uses 32 bytes private keys)
    microsui_decode_sui_privkey(private_key_bech32, private_key);
    // 2- Generating Signature from the message and private key
    microsui_sign_message(sui_sig, msg_hex, private_key);
    // 3- Printing the Sui Signature in hex format
    bytes_to_hex(sui_sig, 97, sui_sig_hex); // 97 bytes is the length of a Sui Signature
    printf("\n\t Sui Signature (97 bytes): %s\n", sui_sig_hex);

    while (1) {
        gpio_set_level(BLINK_GPIO, 0);
        vTaskDelay(pdMS_TO_TICKS(500));
        gpio_set_level(BLINK_GPIO, 1);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}