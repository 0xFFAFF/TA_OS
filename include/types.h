#ifndef _TAOS_TYPES_H
#define _TAOS_TYPES_H

#define EOF -1
#define NULL ((void *)0)
#define EOS '\0'

#define bool _Bool
#define true 1
#define false 0

#define _packed __attribute__((packed)) //用于定义特殊的结构体

typedef unsigned int size_t;

typedef char int8;
typedef short int16;
typedef int int32;
typedef long long int64;

typedef char u8;
typedef short u16;
typedef int u32;
typedef long long u64;

#endif