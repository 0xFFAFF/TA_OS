#include <taos.h>
#include <types.h>
#include <io.h>
#include <string.h>
#include <console.h>

char msg[] = "hello TAOS!!!";
char buf[1024];
void kernel_init()
{
    console_init();
    console_write(msg, sizeof(msg));
    return;
}