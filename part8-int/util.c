#include "util.h"
#include "rpi-aux.h"


#define OUTPUT_BUFFER_LENGTH (512)

char* numberk(char* str, unsigned int n, int base)
{
	register char* p;
	char strbuf[36];
	p = &strbuf[36];
	*--p = '0';

	if(n == 0)
	{
		*--p = 0;
	}
	else
	{
		do
		{
			*--p = "0123456789ABCDEF"[n % base];
		} while( n /= base );
	}

	while(*p != 0)
	{
		*str++ = *p++;
	}

	return str;
}

char* strcopyk(char* buf, char* str)
{
	while(*str)
	{
		*buf = *str;
		++buf;
		++str;
	}

	return buf;
}

void vsprintfk(char* buf, const char* fmt, va_list args)
{
	char* p = buf;
	va_list next_arg = args;

	while(*fmt)
	{
		if(*fmt != '%')
		{
			*p++ = *fmt++;
			continue;
		}


		++fmt;

		switch(*fmt)
		{
			case 'x':
			{
				p = numberk(p, va_arg(next_arg, unsigned int), 16);
				++fmt;
				break;
			}
			case 'd':
			{
				p = numberk(p, va_arg(next_arg, unsigned int), 10);
				++fmt;
				break;
			}
			case 's':
			{
				p = strcopyk(p, (char*) va_arg(next_arg, unsigned int));
				++fmt;
				break;
			}
			default:
			{
				break;
			}
		}
	}

	*p = 0;

	return;
}


void aux_write(void* buf)
{
	char* p = buf;

	while(*p)
	{
		AuxMiniUartWrite(*p);
		++p;
	}
}


void printfk(const char* fmt, ...)
{
	char buf[OUTPUT_BUFFER_LENGTH];
	va_list ap;
	va_start(ap, fmt);

	vsprintfk(buf, fmt, ap);

	aux_write(buf);

	va_end(ap);

	return;
}


char kgetc()
{
	return AuxMiniUartRead();
}

void kputc(char c)
{
	AuxMiniUartWrite(c);
}