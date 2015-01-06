#include "leds.h"

bitPtr led0;
bitPtr led1;
bitPtr led2;
bitPtr led3;
bitPtr led4;
bitPtr led5;
bitPtr led6;
bitPtr led7;
bitPtr led0_tris;
bitPtr led1_tris;
bitPtr led2_tris;
bitPtr led3_tris;
bitPtr led4_tris;
bitPtr led5_tris;
bitPtr led6_tris;
bitPtr led7_tris;

void ledsInit() {
    bitSet(led0_tris, 0);
    bitSet(led1_tris, 0);
    bitSet(led2_tris, 0);
    bitSet(led3_tris, 0);
    bitSet(led4_tris, 0);
    bitSet(led5_tris, 0);
    bitSet(led6_tris, 0);
    bitSet(led7_tris, 0);
}

void ledSet(uint8_t led, bool state) {
    switch (led) {
        case 0:
            bitSet(led0, state);
            break;
        case 1:
            bitSet(led1, state);
            break;
        case 2:
            bitSet(led2, state);
            break;
        case 3:
            bitSet(led3, state);
            break;
        case 4:
            bitSet(led4, state);
            break;
        case 5:
            bitSet(led5, state);
            break;
        case 6:
            bitSet(led6, state);
            break;
        case 7:
            bitSet(led7, state);
            break;
        default:
            break;
    }
}

void ledToggle(uint8_t led) {
    switch (led) {
        case 0:
            bitSet(led0, !bitGet(led0));
            break;
        case 1:
            bitSet(led1, !bitGet(led1));
            break;
        case 2:
            bitSet(led2, !bitGet(led2));
            break;
        case 3:
            bitSet(led3, !bitGet(led3));
            break;
        case 4:
            bitSet(led4, !bitGet(led4));
            break;
        case 5:
            bitSet(led5, !bitGet(led5));
            break;
        case 6:
            bitSet(led6, !bitGet(led6));
            break;
        case 7:
            bitSet(led7, !bitGet(led7));
            break;
        default:
            break;
    }
}

void ledSetAll(uint8_t value) {
    ledSet(0, value & 0b00000001);
    ledSet(1, value & 0b00000010);
    ledSet(2, value & 0b00000100);
    ledSet(3, value & 0b00001000);
    ledSet(4, value & 0b00010000);
    ledSet(5, value & 0b00100000);
    ledSet(6, value & 0b01000000);
    ledSet(7, value & 0b10000000);
}
