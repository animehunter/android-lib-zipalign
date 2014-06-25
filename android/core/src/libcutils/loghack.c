#include <stdio.h>
#include <stdarg.h>

/* For non-android OS */
#ifndef HAVE_ANDROID_OS
int __android_log_print(int prio, const char *tag,  const char *fmt, ...)
{
    va_list args;
    va_start (args, fmt);
    vfprintf (stdout, fmt, args);
    va_end (args);
    return 0;
}

void __android_log_assert(const char *cond, const char *tag, const char *fmt, ...)
{
    if(cond)
    {
        va_list args;
        va_start (args, fmt);
        vfprintf (stdout, fmt, args);
        va_end (args);
    }
}
#endif