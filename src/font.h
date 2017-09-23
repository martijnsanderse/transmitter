#ifndef FONT_H
#define FONT_H

#define CHAR_WIDTH 5
#define CHAR_HEIGHT 8

const unsigned char font[96*5] = { // char, ascii table position: 
    0x00,0x00,0x00,0x00,0x00, // space    32
    0x00,0x00,0xbe,0x00,0x00, // ! 
    0x00,0x07,0x00,0x07,0x00, // "        
    0x48,0xfc,0x48,0xfc,0x48, // #        35
    0x48,0x54,0xfe,0x54,0x24, // $ 
    0x88,0x54,0x28,0x50,0xa8, // % 
    0x6c,0x92,0x92,0xac,0x40, // & 
    0xa0,0x00,0x07,0x00,0x00, // '
    0x00,0x7c,0x82,0x01,0x00, // (        40
    0x00,0x01,0x82,0x7c,0x00, // )
    0x28,0x10,0x7c,0x10,0x28, // *
    0x10,0x10,0x7c,0x10,0x10, // +
    0x00,0x00,0x80,0x00,0x00, // ,
    0x10,0x10,0x10,0x10,0x10, // -        45
    0x00,0x00,0x80,0x00,0x00, // .
    0x00,0xc0,0x30,0x0c,0x03, // /
    0x7c,0x82,0x92,0x82,0x7c, // 0
    0x00,0x84,0xfe,0x80,0x00, // 1
    0xc4,0xa2,0x92,0x92,0x8c, // 2        50
    0x44,0x82,0x92,0x92,0x6c, // 3
    0x30,0x28,0x24,0xfe,0x20, // 4
    0x5e,0x92,0x92,0x92,0x62, // 5
    0x78,0x94,0x92,0x92,0x60, // 6
    0x02,0x82,0x62,0x1a,0x06, // 7        55
    0x6c,0x92,0x92,0x92,0x6c, // 8
    0x0c,0x92,0x92,0x52,0x3c, // 9
    0x00,0x00,0x48,0x00,0x00, // :
    0x00,0x80,0x48,0x00,0x00, // ;
    0x10,0x10,0x28,0x28,0x44, // <        60
    0x28,0x28,0x28,0x28,0x28, // =
    0x44,0x28,0x28,0x10,0x10, // >
    0x04,0x02,0xa2,0x12,0x0c, // ?
    0x7c,0x82,0xba,0xba,0xa2, // @
    0xfc,0x38,0x26,0x38,0xc0, // A        65
    0xfe,0x92,0x92,0x92,0x6c, // B
    0x7c,0x82,0x82,0x82,0x44, // C
    0xfe,0x82,0x82,0x44,0x38, // D
    0xfe,0x92,0x92,0x92,0x82, // E
    0xfe,0x12,0x12,0x12,0x02, // F        70
    0x7c,0x82,0x82,0x92,0xf4, // G
    0xfe,0x10,0x10,0x10,0xfe, // H
    0x00,0x82,0xfe,0x82,0x00, // I
    0x80,0x80,0x82,0x82,0x7e, // J
    0xfe,0x10,0x28,0x44,0x82, // K        75
    0xfe,0x80,0x80,0x80,0x80, // L
    0xfe,0x18,0x60,0x18,0xfe, // M
    0xfe,0x06,0x38,0xc0,0xfe, // N
    0x7c,0x82,0x82,0x82,0x7c, // O
    0xfe,0x12,0x12,0x12,0x0c, // P        80
    0x7c,0x82,0x82,0xc2,0xfc, // Q
    0xfe,0x12,0x12,0x12,0xec, // R
    0x4c,0x92,0x92,0x92,0x64, // S
    0x02,0x02,0xfe,0x02,0x02, // T
    0x7e,0x80,0x80,0x80,0x7e, // U        85
    0x0e,0x30,0xc0,0x30,0x0e, // V
    0x1e,0xe0,0x1c,0xe0,0x1e, // W
    0xc6,0x28,0x10,0x28,0xc6, // X
    0x0e,0x10,0xf0,0x10,0x0e, // Y
    0xc2,0xa2,0x92,0x8a,0x86, // Z        90
    0x00,0xff,0x01,0x01,0x00, // [
    0x03,0x0c,0x30,0xc0,0x00, // "\"
    0x00,0x01,0x01,0xff,0x00, // ]
    0x08,0x04,0x02,0x04,0x08, // ^
    0x00,0x00,0x00,0x00,0x00, // _        95
    0x00,0x00,0x02,0x04,0x00, // `
    0x40,0xa8,0xa8,0xa8,0xf0, // a
    0xff,0x88,0x88,0x88,0x70, // b
    0x70,0x88,0x88,0x88,0x88, // c
    0x70,0x88,0x88,0x88,0xff, // d       100
    0x70,0xa8,0xa8,0xa8,0xb0, // e
    0x08,0xfe,0x09,0x09,0x01, // f
    0x70,0x88,0x88,0x88,0xf0, // g
    0xff,0x08,0x08,0x08,0xf0, // h
    0x00,0x08,0xfa,0x00,0x00, // i       105
    0x00,0x00,0x08,0xfa,0x00, // j
    0x00,0xff,0x20,0x50,0x88, // k
    0x00,0x01,0xff,0x00,0x00, // l
    0xf8,0x08,0xf0,0x08,0xf0, // m
    0xf8,0x08,0x08,0x08,0xf0, // n       110
    0x70,0x88,0x88,0x88,0x70, // o
    0xf8,0x88,0x88,0x88,0x70, // p
    0x70,0x88,0x88,0x88,0xf8, // q
    0xf8,0x10,0x08,0x08,0x10, // r
    0x90,0xa8,0xa8,0xa8,0x48, // s       115
    0x00,0x7e,0x88,0x88,0x80, // t
    0x78,0x80,0x80,0x80,0xf8, // u
    0x18,0x60,0x80,0x60,0x18, // v
    0x38,0xc0,0x30,0xc0,0x38, // w
    0x88,0x50,0x20,0x50,0x88, // x       120
    0x78,0x80,0x80,0x80,0xf8, // y
    0x88,0xc8,0xa8,0x98,0x88, // z
    0x00,0x10,0xee,0x01,0x00, // {
    0x00,0x00,0xff,0x00,0x00, // |
    0x00,0x01,0xee,0x10,0x00, // }       125
    0x20,0x10,0x10,0x20,0x20, // ~
    0x00,0x00,0x00,0x00,0x00
};

#endif // FONT_H