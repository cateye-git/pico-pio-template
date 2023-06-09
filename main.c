#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"    // for clock_get_hz() in our PIO helper function

// generated by pioasm from `ledcontol.pio`
#include "ledcontrol.pio.h"


int main () {
    // initialise the `stdio` library so that we can use printf() etc
    stdio_init_all ();

    // decide which PIO we want to use (the RP2040 has two of them)
    PIO pio = pio0;

    // add the assembled instructions to the PIO shared memory
    uint offset = pio_add_program (pio, &ledcontrol_program);

    // claim a free state machine on the PIO
    uint sm = pio_claim_unused_sm (pio, true);

    // use our helper function to configure and start the state machine
    ledcontrol_init (pio, sm, offset, PICO_DEFAULT_LED_PIN, 1e6);

    // control the LED by sending data to the state machine's TX FIFO
    while (true) {
        puts ("LED on");
        pio_sm_put_blocking (pio, sm, 1);
        sleep_ms (500);

        puts ("LED off");
        pio_sm_put_blocking (pio, sm, 0);
        sleep_ms (1000);
    }
}
