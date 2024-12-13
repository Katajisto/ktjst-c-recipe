#ifndef BZ4X
#define BZ4X
#include <math.h>
#include <sys/types.h>
#include "stdlib.h"
#include "math.h"
#include "stdio.h"
#include "string.h"

/*
Beyond Zipped 4 Xhannels
The depth implementation is currently a meme, pls fix.
*/

unsigned char* Bz4xEncode(float* rgbafloats, u_int32_t width, u_int32_t height, int* size);
unsigned char* Bz4xDecode(unsigned char* bz4xfile, int insize, int* outsize, int* width, int* height);

#ifdef BZ4X_IMPLEMENTATION

int _bz4x_max(int a, int b) {
    if(a < b) return b;
    return a;
}

int _bz4x_min(int a, int b) {
    if(a > b) return b;
    return a;
}

int _bz4x_clamp(int a, int l, int u) {
    if(a < l) return l;
    if(a > u) return u;
    return a;
}

typedef struct ColorRGB {
    float r;
    float g;
    float b;
} _bz4x_ColorRGB;

_bz4x_ColorRGB _bz4x_r9g9b9e5_to_rgb(uint rgbe)
{
    int ri; int gi; int bi; int ei;
    ri = rgbe & 0x1FF;
    gi = rgbe>>9 & 0x1FF;
    bi = rgbe>>18 & 0x1FF;
    ei = rgbe>>27 & 0x1FF;

    float rf; float gf; float bf;
    rf = ri * (1.0f / 512.0f) * exp2(ei-16);
    bf = bi * (1.0f / 512.0f) * exp2(ei-16);
    gf = gi * (1.0f / 512.0f) * exp2(ei-16);

    return (_bz4x_ColorRGB) {.r = rf, .g = gf, .b = bf};
}
u_int32_t _bz4x_rgb_to_r9g9b9e5(float r, float g, float b)
{
    int riexp; int giexp; int biexp;
    frexp(r, &riexp);
    frexp(g, &giexp);
    frexp(b, &biexp);
    int e = _bz4x_clamp(_bz4x_max(riexp, _bz4x_max(giexp, biexp)), -16, 15);
    int ri; int gi; int bi;
    ri = _bz4x_clamp(floor(r * exp2(-e) * 512.0f), 0, 511);
    gi = _bz4x_clamp(floor(g * exp2(-e) * 512.0f), 0, 511);
    bi = _bz4x_clamp(floor(b * exp2(-e) * 512.0f), 0, 511);
    return ri|(gi<<9)|(bi<<18)|((e+16)<<27);
}

unsigned char* Bz4xEncode(float* rgbafloats, u_int32_t width, u_int32_t height, int* size) {
    int sz = sizeof(char) * width * height * 6 + 8;
    unsigned char* file = (unsigned char*)malloc(sz);
    (*size) = sz;
    int cursor = 0;

    
    memcpy(&file[cursor], &width, 4);
    cursor += 4;
    memcpy(&file[cursor], &height, 4);
    cursor += 4;
    
    for(int i = 0; i < width * height; i++) {
        float r = rgbafloats[i * 4 + 0];
        float g = rgbafloats[i * 4 + 1];
        float b = rgbafloats[i * 4 + 2];
        float a = rgbafloats[i * 4 + 3];
        u_int32_t rgb = _bz4x_rgb_to_r9g9b9e5(r, g, b);
        memcpy(&file[cursor], &rgb, 4);
        cursor += 4;
        u_int16_t depth = round(a * 10.0);
        memcpy(&file[cursor], &depth, 2);
        cursor += 2;
    }
    return file;
}

unsigned char* Bz4xDecode(unsigned char* bz4xfile, int insize, int* outsize, int* width, int* height) {
    int cursor = 0;
    u_int32_t w;
    u_int32_t h;
    memcpy(&w, &bz4xfile[cursor], 4);
    cursor += 4;
    memcpy(&h, &bz4xfile[cursor], 4);
    cursor += 4;

    (*width) = w;
    (*height) = h;

    int size = sizeof(float) * w * h * 4;
    (*outsize) = size;
    float* outbuf = (float*)malloc(size);
    int outcursor = 0;
    
    while(cursor < insize) {
        u_int32_t color;
        u_int16_t depth;
        memcpy(&color, &bz4xfile[cursor], 4);
        cursor += 4;
        memcpy(&depth, &bz4xfile[cursor], 2);
        cursor += 2;
        _bz4x_ColorRGB col = _bz4x_r9g9b9e5_to_rgb(color);
        outbuf[outcursor] = col.r; outcursor++;
        outbuf[outcursor] = col.g; outcursor++;
        outbuf[outcursor] = col.b; outcursor++;
        outbuf[outcursor] = depth / 10.0; outcursor++;
    }
    return (unsigned char*)outbuf;
}

#endif
#endif
