#include <stdio.h>
#include "regex.h"

int main() {
    struct RegexEngine engine;
    engine_init(&engine);
    scanf("%s", engine.line);
    int err_index = 0;
    while (engine.is_found != true && engine.index < 255) {
        engine_tick(&engine);
        if (engine.is_error) {
            engine_reset(&engine);
            err_index++;
            engine.index = err_index;
            //printf("%s\n", "ERROR");
            //break;
            }
        }
    if (engine.is_found) {
        printf("%s\n", "REGEX FOUND");
    } else printf("%s\n", "ERROR");
    return 0;
}

/*
УСПЕХ
aa:aa::9.9.63.9
ffff:0000:255.255.24.9
aa:aa::9.9.6.9
afea:aac::29.253.63.69
ffff:00:253.54.7.5
ffff:00:0.0.0.0
ffff:23.53.5.6
ffff:125.0.0.25
99.9.9.9
ffff:ffff::9.9.9.9
1337::9.9.9.9
ffff:0:0.9.9.9
ffff:0::9.9.9.9
ffff:0000:1230::9.9.9.9
ffff:0000::255.255.24.9
ffff:0000:255.255.24.9
ffff:125.0.0.255
ffff:ffff::9.9.9.25

ОШИБКА
ffff:125.0.0.256
fe:aa:3.3.3.3
aa:ff::0.0.256.256
ffff:0:465.56.2.2
*/