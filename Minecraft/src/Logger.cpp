#include <cstdarg>
#include <string>

#include "Logger.h"

void Logger::Log(const char* format, ...)
{
	va_list args;
	va_start(args, format);

	int len = _vscprintf(format, args) + 1;
	char* message = new char[len];
	vsprintf(message, format, args);

	va_end(args);
}
