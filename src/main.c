#include <stdio.h>
#include <string.h>
#include "microsui/sign.h"
#include "microsui/utils.h"
#include "constants.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define BLINK_GPIO GPIO_NUM_8

// Original msg in HEX generated with `await tx.build({ client });` in Mysten Typescript SDK
const char* msg_hex = "00000200080065cd1d0000000000202e3d52393c9035afd1ef38abd7fce2dad71f0e276b522fb274f4e14d1df974720202000101000001010300000000010100d79a4c7a655aa80cf92069bbac9666705f1d7181ff9c2d59efbc7e6ec4c3379d0180dc491e55e7caabfcdd1b0f538928d8d54107b9c1def3ed0baa3aa5106ba8674f0dd01400000000204b7e9da00f30cd1edf4d40710213c15a862e1fc175f2edb2b2c870c8559d65cdd79a4c7a655aa80cf92069bbac9666705f1d7181ff9c2d59efbc7e6ec4c3379de80300000000000040ab3c000000000000";

void app_main() {
    gpio_reset_pin(BLINK_GPIO);
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
    vTaskDelay(pdMS_TO_TICKS(2500));
    gpio_set_level(BLINK_GPIO, 0);
    printf("\n\n\n\t\t\t --- ESP32 OFFLINE SIGN DEMO ---\n");

    printf("\n\n\t\tGenerating Sign from Message!\n");
    vTaskDelay(pdMS_TO_TICKS(500));
    printf("\n\tOriginal Message: %s\n", msg_hex);
    vTaskDelay(pdMS_TO_TICKS(1300));

    // Generating the Sui Signature from the message and private key (private_key is in constant.h)
    uint8_t sui_sig[97];
    microsui_sign_message(sui_sig, msg_hex, private_key);

    // Printing the Sui Signature in hex format
    char sui_sig_hex[195]; // 2 hex chars per byte + null terminator
    bytes_to_hex(sui_sig, 97, sui_sig_hex); // 97 bytes is the length of a Sui Signature
    printf("\n\t Sui Signature (97 bytes): %s\n", sui_sig_hex);

    printf("\n\n\t SIGNATURE must be sended to the Gateway to be broadcasted to the Sui Network...\n");

    while (1) {
        gpio_set_level(BLINK_GPIO, 0);
        vTaskDelay(pdMS_TO_TICKS(500));
        gpio_set_level(BLINK_GPIO, 1);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
    
}