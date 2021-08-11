
#include "mbed.h"
#include "rtos/ThisThread.h"

#include <chrono>
#include <stdio.h>
#include <string.h>

using namespace std::chrono;

extern "C" void HardFault_Handler(void);

int main(void) {

    for(int i = 3; i > 0; i--) {
        printf("crashing in %i...\r\n", i);
        rtos::ThisThread::sleep_for(1s);
    }
    
    HardFault_Handler();

}

extern "C" {

void mbed_error_reboot_callback(mbed_error_ctx *error_context)
{
    printf("resetting error count (was %d)\r\n", error_context->error_reboot_count);
    mbed_reset_reboot_error_info();
}

}
