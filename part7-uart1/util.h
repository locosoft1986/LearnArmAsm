#ifndef __UTIL_H__
#define __UTIL_H__


typedef __builtin_va_list va_list;
#define va_start(ap, np) __builtin_va_start(ap, np)
#define va_end(ap) __builtin_va_end(ap)
#define va_arg(ap, ty) __builtin_va_arg(ap, ty)

char* numberk(char* str, unsigned int n, int base);

char* strcopyk(char* buf, char* str);

void vsprintfk(char* buf, const char* fmt, va_list args);

void printfk(const char* fmt, ...);

#endif