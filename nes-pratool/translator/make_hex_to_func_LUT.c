#include <stdio.h>
#include "../src/cpu.h"

int main() {
    char *hex_func[256];
    int i;

    for (i = 0; i < 256; i++) {
        hex_func[i] = "dum\0";
    }
    
    hex_func[0x6D] = "adc\0";
    hex_func[0x7D] = "adc\0";
    hex_func[0x79] = "adc\0";
    hex_func[0x69] = "adc\0";
    hex_func[0x61] = "adc\0";
    hex_func[0x71] = "adc\0";
    hex_func[0x65] = "adc\0";
    hex_func[0x75] = "adc\0";
    hex_func[0x2D] = "and\0";
    hex_func[0x3D] = "and\0";
    hex_func[0x39] = "and\0";
    hex_func[0x29] = "and\0";
    hex_func[0x21] = "and\0";
    hex_func[0x31] = "and\0";
    hex_func[0x25] = "and\0";
    hex_func[0x35] = "and\0";
    hex_func[0x0E] = "asl\0";
    hex_func[0x1E] = "asl\0";
    hex_func[0x0A] = "asl\0";
    hex_func[0x06] = "asl\0";
    hex_func[0x16] = "asl\0";
    hex_func[0x90] = "bcc\0";
    hex_func[0xB0] = "bcs\0";
    hex_func[0xF0] = "beq\0";
    hex_func[0x2C] = "bit\0";
    hex_func[0x24] = "bit\0";
    hex_func[0x30] = "bmi\0";
    hex_func[0xD0] = "bne\0";
    hex_func[0x10] = "bpl\0";
    //hex_func[0x00] = "brk\0";
    hex_func[0x50] = "bvc\0";
    hex_func[0x70] = "bvs\0";
    hex_func[0x18] = "clc\0";
    hex_func[0xD8] = "cld\0";
    hex_func[0x58] = "cli\0";
    hex_func[0xB8] = "clv\0";
    hex_func[0xCD] = "cmp\0";
    hex_func[0xDD] = "cmp\0";
    hex_func[0xD9] = "cmp\0";
    hex_func[0xC9] = "cmp\0";
    hex_func[0xC1] = "cmp\0";
    hex_func[0xD1] = "cmp\0";
    hex_func[0xC5] = "cmp\0";
    hex_func[0xD5] = "cmp\0";
    hex_func[0xEC] = "cpx\0";
    hex_func[0xE0] = "cpx\0";
    hex_func[0xE4] = "cpx\0";
    hex_func[0xCC] = "cpy\0";
    hex_func[0xC0] = "cpy\0";
    hex_func[0xC4] = "cpy\0";
    hex_func[0xCE] = "dec\0";
    hex_func[0xDE] = "dec\0";
    hex_func[0xC6] = "dec\0";
    hex_func[0xD6] = "dec\0";
    hex_func[0xCA] = "dex\0";
    hex_func[0x88] = "dey\0";
    /*hex_func[0x4D] = "eor\0";
    hex_func[0x5D] = "eor\0";
    hex_func[0x59] = "eor\0";
    hex_func[0x49] = "eor\0";
    hex_func[0x41] = "eor\0";
    hex_func[0x51] = "eor\0";
    hex_func[0x45] = "eor\0";
    hex_func[0x55] = "eor\0";*/
    hex_func[0xEE] = "inc\0";
    hex_func[0xFE] = "inc\0";
    hex_func[0xE6] = "inc\0";
    hex_func[0xF6] = "inc\0";
    hex_func[0xE8] = "inx\0";
    //hex_func[0xC8] = "iny\0";
    hex_func[0x4C] = "jmp\0";
    hex_func[0x6C] = "jmp\0";
    hex_func[0x20] = "jsr\0";
    hex_func[0xAD] = "lda\0";
    hex_func[0xBD] = "lda\0";
    hex_func[0xB9] = "lda\0";
    hex_func[0xA9] = "lda\0";
    hex_func[0xA1] = "lda\0";
    hex_func[0xB1] = "lda\0";
    hex_func[0xA5] = "lda\0";
    hex_func[0xB5] = "lda\0";
    hex_func[0xAE] = "ldx\0";
    hex_func[0xBE] = "ldx\0";
    hex_func[0xA2] = "ldx\0";
    hex_func[0xA6] = "ldx\0";
    hex_func[0xB6] = "ldx\0";
    hex_func[0xAC] = "ldy\0";
    hex_func[0xBC] = "ldy\0";
    hex_func[0xA0] = "ldy\0";
    hex_func[0xA4] = "ldy\0";
    hex_func[0xB4] = "ldy\0";
    hex_func[0x4E] = "lsr\0";
    hex_func[0x5E] = "lsr\0";
    hex_func[0x4A] = "lsr\0";
    hex_func[0x46] = "lsr\0";
    hex_func[0x56] = "lsr\0";
    hex_func[0x09] = "ora\0";
    hex_func[0x05] = "ora\0";
    hex_func[0x15] = "ora\0";
    hex_func[0x0D] = "ora\0";
    hex_func[0x1D] = "ora\0";
    hex_func[0x19] = "ora\0";
    hex_func[0x01] = "ora\0";
    hex_func[0x11] = "ora\0";
    hex_func[0xEA] = "nop\0";
    hex_func[0x48] = "pha\0";
    hex_func[0x08] = "php\0";
    hex_func[0x68] = "pla\0";
    hex_func[0x28] = "plp\0";
    /*hex_func[0x2E] = "rol\0";
    hex_func[0x3E] = "rol\0";
    hex_func[0x2A] = "rol\0";
    hex_func[0x26] = "rol\0";
    hex_func[0x36] = "rol\0";
    hex_func[0x6E] = "ror\0";
    hex_func[0x7E] = "ror\0";
    hex_func[0x6A] = "ror\0";
    hex_func[0x66] = "ror\0";
    hex_func[0x76] = "ror\0";
    hex_func[0x40] = "rti\0";
    hex_func[0x60] = "rts\0";*/
    hex_func[0xE9] = "sbc\0";
    hex_func[0xE5] = "sbc\0";
    hex_func[0xF5] = "sbc\0";
    hex_func[0xED] = "sbc\0";
    hex_func[0xFD] = "sbc\0";
    hex_func[0xF9] = "sbc\0";
    hex_func[0xE1] = "sbc\0";
    hex_func[0xF1] = "sbc\0";
    hex_func[0x38] = "sec\0";
    //hex_func[0xF8] = "sed\0";
    //hex_func[0x78] = "sei\0";
    hex_func[0x8D] = "sta\0";
    hex_func[0x9D] = "sta\0";
    hex_func[0x99] = "sta\0";
    hex_func[0x81] = "sta\0";
    hex_func[0x91] = "sta\0";
    hex_func[0x85] = "sta\0";
    hex_func[0x95] = "sta\0";
    hex_func[0x86] = "stx\0";
    hex_func[0x96] = "stx\0";
    hex_func[0x8E] = "stx\0";
    /*hex_func[0x84] = "sty\0";
    hex_func[0x94] = "sty\0";
    hex_func[0x8C] = "sty\0";*/
    //hex_func[0xAA] = "tax\0";
    hex_func[0xA8] = "tay\0";
    //hex_func[0xBA] = "tsx\0";
    hex_func[0x8A] = "txa\0";
    //hex_func[0x9A] = "txs\0";
    hex_func[0x98] = "tya\0";
    //hex_func[0xCB] = "wai\0";

    for (i = 0; i < sizeof(hex_func)/sizeof(hex_func[0])-1; i++) {
        if ((i+1) % 16 == 0) {
            printf("%s,\n", hex_func[i]);
        } else {
            printf("%s, ", hex_func[i]);
        }
    }
    printf("%s\n", hex_func[i]);

    return 0;
}
