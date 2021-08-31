//
// Created by istas on 30.05.2021.
//

#ifndef REGEX_AUTOMATA_REGEX_H
#define REGEX_AUTOMATA_REGEX_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(__cplusplus)
extern  "C" {
#endif

#define symbol_f engine->line[engine->index] == 'f'
#define symbol_dot engine->line[engine->index] == '.'
#define symbol_colon engine->line[engine->index] == ':'
#define symbol_0 engine->line[engine->index] == '0'
#define symbol_1 engine->line[engine->index] == '1'
#define symbol_2 engine->line[engine->index] == '2'
#define symbol_5 engine->line[engine->index] == '5'
#define symbol_0_to_4 engine->line[engine->index] >= 48 && engine->line[engine->index] <= 52
#define symbol_0_to_5 engine->line[engine->index] >= 48 && engine->line[engine->index] <= 53
#define symbol_0_to_9 engine->line[engine->index] >= 48 && engine->line[engine->index] <= 57
#define symbol_0_to_9_or_Aa_to_Ff symbol_0_to_9 \
|| (engine->line[engine->index] >= 65 && engine->line[engine->index] <= 70) \
|| (engine->line[engine->index] >= 97 && engine->line[engine->index] <= 102)


enum RegexState{
    State_0, State_1, State_2, State_3,
    State_4, State_5, State_6, State_7,
    State_8, State_9, State_10, State_11,
    State_12, State_13, State_14,State_15,
    State_16, State_17, State_18,State_19,
    State_20, State_21, State_22, State_23,
    State_Complete, State_Error
};


struct RegexEngine {
    enum RegexState state;
    int colon_counter;
    int dot_counter;
    int is_error;
    bool double_colon_required;
    bool is_not_ip;
    bool is_three_digit;
    int index;
    char line[255];
    bool is_found;

};

bool engine_init(struct RegexEngine *engine);
void engine_tick(struct RegexEngine *engine);
bool engine_reset(struct RegexEngine *engine);

#if defined(__cplusplus)
}
#endif


#endif //REGEX_AUTOMATA_REGEX_H
