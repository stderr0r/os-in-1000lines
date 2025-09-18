#include "common.h"

void putchar(char c);

void printf(const char *fmt, ...) {
    va_list vargs;
    va_start(vargs, fmt);

    while (*fmt) {
        if (*fmt == '%') {
            fmt++;
            switch (*fmt) {
            case '\0':
                putchar('%');
                goto end;
            case '%':
                putchar('%');
                break;
            case 's':
                const char *s = va_arg(vargs, const char *);
                while (*s) {
                    putchar(*s);
                    s++;
                }
                break;
            case 'x': {
                unsigned value = va_arg(vargs, unsigned);
                for (int i = 7; i >= 0; i--) {
                    putchar("0123456789abcdef"[(value >> (4 * i)) & 0xf]);
                }
                break;
            }
            case 'd': {
                unsigned value = va_arg(vargs, unsigned);
                if (value >= (1 << 31)) {
                    putchar('-');
                    value = -value;
                }
                if (value == 0) {
                    putchar('0');
                    break;
                }
                char buf[10];
                int i = 0;
                while (value) {
                    buf[i++] = ('0' + (value % 10));
                    value /= 10;
                }
                while (i--) putchar(buf[i]);
                break;
            }
            }
        } else {
            putchar(*fmt);
        }
        fmt++;
    }
    end:
        va_end(vargs);

}

void *memcpy(void *dst, const void *src, size_t n) {
    uint8_t *d = (uint8_t * ) dst;
    const uint8_t *s = (const uint8_t * ) src;
    while (n--) *d++ = *s++;
    return dst;
}

void *memset(void *buf, char c, size_t n) {
    uint8_t *p = (uint8_t *) buf;
    while (n--) *p++ = c;
    return buf;
}

char *strcpy(char *dst, const char *src) {
    char *d = dst;
    while (*src) *d++ = *src++;
    *d = '\0';
    return dst;
}

char *strcpy_s(char *dst, size_t dst_size, const char *src) {
    char *d = dst;
    size_t left = dst_size;
    while (left > 1 && *src) {
        *d++ = *src++;
        --left;
    }
    *d = '\0';
    return dst;
}

int strcmp(const char *s1, const char *s2) {
    while (*s1 && *s2) {
        if (*s1 != s2) break;
        s1++; s2++;
    }
}
