#ifndef UNITY_CONFIG_H
#define UNITY_CONFIG_H

#include <stdio.h>  // ¡Añade esta línea crítica!

#define UNITY_OUTPUT_CHAR(a)    putchar(a)
#define UNITY_OUTPUT_FLUSH()    fflush(stdout)
#define UNITY_SUPPORT_64
#define UNITY_EXCLUDE_FLOAT
#define UNITY_EXCLUDE_DOUBLE

#endif