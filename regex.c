//
// Created by istas on 30.05.2021.
//

#include "regex.h"


bool engine_init(struct RegexEngine *engine) {
    engine->index = 0;
    engine->state = State_0;
    engine->colon_counter = 0;
    engine->dot_counter = 0;
    engine->is_not_ip = true;
    engine->is_three_digit = false;
    engine->is_found = false;
    engine->is_error = false;
    engine->double_colon_required = false;
    return true;
}

bool engine_reset(struct RegexEngine *engine) {
    engine_init(engine);
    return true;
}


void engine_tick(struct RegexEngine *engine) {
    switch (engine->state) {
        case State_Complete: {
            engine_reset(engine);
            engine->is_found = true;
            break;
        }
        case State_Error: {
            engine->is_error = true;
            break;
        }
        case State_0: {
            if (symbol_1) {
                engine->state = State_1;
            } else if (symbol_2) {
                engine->state = State_5;
            } else if (symbol_0_to_9) {
                engine->state = State_8;
            } else if (engine->is_not_ip) {
                if (symbol_f) {
                    engine->state = State_9;
                } else if (symbol_0_to_9_or_Aa_to_Ff) {
                    engine->state = State_13;
                }
            } else {
                engine->state = State_Error;
            }
            break;
        }
        case State_1: {
            if (symbol_0_to_9) {
                engine->state = State_2;
            } else if (symbol_dot) {
                engine->state = State_4;
                engine->dot_counter++;
                engine->is_not_ip = false;
            } else if (engine->dot_counter == 3) {
                engine->state = State_Complete;
            } else if ((engine->is_not_ip) && (engine->colon_counter < 4)) {
                if (symbol_0_to_9_or_Aa_to_Ff) {
                    engine->state = State_13;
                } else if (symbol_colon) {
                    engine->state = State_17;
                    engine->colon_counter++;
                }
            } else {
                engine->state = State_Error;
            }
            break;
        }
        case State_2: {
            if (symbol_0_to_9) {
                engine->state = State_3;
                engine->is_three_digit = true;
            } else if (symbol_dot) {
                engine->state = State_4;
                engine->dot_counter++;
                engine->is_not_ip = false;
            } else if ((engine->is_not_ip) && (engine->colon_counter < 4)) {
                if (symbol_0_to_9_or_Aa_to_Ff) {
                    engine->state = State_14;
                } else if (symbol_colon) {
                    engine->state = State_17;
                    engine->colon_counter++;
                }
            } else if (engine->dot_counter == 3) {
                engine->state = State_Complete;
            } else {
                engine->state = State_Error;
            }
            break;
        }
        case State_3: {
            if (symbol_dot) {
                engine->state = State_4;
                engine->dot_counter++;
                engine->is_not_ip = false;
            } else if (engine->dot_counter == 3) {
                engine->state = State_Complete;
            } else if ((engine->is_not_ip) && (engine->colon_counter < 4)) {
                if (symbol_0_to_9_or_Aa_to_Ff) {
                    if (engine->is_three_digit) {
                        engine->state = State_15;
                        engine->is_three_digit = false;
                    } else {
                        engine->state = State_14;
                    }
                } else if (symbol_colon) {
                    engine->state = State_17;
                    engine->colon_counter++;
                }
            } else {
                engine->state = State_Error;
            }
            break;
        }
        case State_4: {
            if (engine->dot_counter <= 3) {
                engine->index--;
                engine->state = State_0;
                engine->is_not_ip = false; /*Т.к. в это состояние можно придти только если нашли точку*/
            } else {
                engine->state = State_Error;
            }
            break;
        }
        case State_5: {
            if (symbol_0_to_4) {
                engine->state = State_2;
            } else if (symbol_5) {
                engine->state = State_6;
            } else if (symbol_0_to_9) {
                engine->state = State_3;
            } else if (symbol_dot) {
                engine->state = State_4;
                engine->dot_counter++;
                engine->is_not_ip = false;
            } else if (engine->dot_counter == 3) {
                engine->state = State_Complete;
            } else if ((engine->is_not_ip) && (engine->colon_counter < 4)) {
                if (symbol_0_to_9_or_Aa_to_Ff) {
                    engine->state = State_13;
                } else if (symbol_colon) {
                    engine->state = State_17;
                    engine->colon_counter++;
                }
            } else {
                engine->state = State_Error;
            }
            break;
        }
        case State_6: {
            if (symbol_0_to_5) {
                engine->state = State_7;
                if (engine->dot_counter == 3) {
                    engine->state = State_Complete;
                }
            } else if (symbol_dot) {
                engine->state = State_4;
                engine->dot_counter++;
                engine->is_not_ip = false;
            } else if (engine->dot_counter == 3) {
                //if (symbol_0_to_9) {
                //engine->state = State_Error;
                //} else
                engine->state = State_Complete;
            } else if ((engine->is_not_ip) && (engine->colon_counter < 4)) {
                if (symbol_0_to_9_or_Aa_to_Ff) {
                    engine->state = State_14;
                } else if (symbol_colon) {
                    engine->state = State_17;
                    engine->colon_counter++;
                }
            } else {
                engine->state = State_Error;
            }
            break;
        }
        case State_7: {
            if (symbol_dot) {
                engine->state = State_4;
                engine->dot_counter++;
                engine->is_not_ip = false;
            } else if (engine->dot_counter == 3) {
                engine->state = State_Complete;
            } else if ((engine->is_not_ip) && (engine->colon_counter < 4)) {
                if (symbol_0_to_9_or_Aa_to_Ff) {
                    engine->state = State_15;
                } else if (symbol_colon) {
                    engine->state = State_17;
                    engine->colon_counter++;
                }
            } else {
                engine->state = State_Error;
            }
            break;
        }
        case State_8: {
            if (symbol_0_to_9) {
                engine->state = State_3;
            } else if (symbol_dot) {
                engine->state = State_4;
                engine->dot_counter++;
                engine->is_not_ip = false;
            } else if (engine->dot_counter == 3) {
                engine->state = State_Complete;
            } else if ((engine->is_not_ip) && (engine->colon_counter < 4)) {
                if (symbol_0_to_9_or_Aa_to_Ff) {
                    engine->state = State_14;
                } else if (symbol_colon) {
                    engine->state = State_17;
                    engine->colon_counter++;
                }
            } else {
                engine->state = State_Error;
            }
            break;
        }
        case State_9: {
            if (symbol_f) {
                engine->state = State_10;
            } else if (symbol_0_to_9_or_Aa_to_Ff) {
                engine->state = State_13;
            } else {
                engine->state = State_Error;
            }
            break;
        }
        case State_10: {
            if (symbol_f) {
                engine->state = State_11;
            } else if (symbol_0_to_9_or_Aa_to_Ff) {
                engine->state = State_14;
            } else {
                engine->state = State_Error;
            }
            break;
        }
        case State_11: {
            if (symbol_f) {
                engine->state = State_12;
            } else if (symbol_0_to_9_or_Aa_to_Ff) {
                engine->state = State_15;
            } else {
                engine->state = State_Error;
            }
            break;
        }
        case State_12: {
            if (symbol_f) {
                engine->state = State_12;
            } else if (symbol_colon) {
                engine->state = State_18;
                engine->colon_counter++;
            } else {
                engine->state = State_Error;
            }
            break;
        }
        case State_13: {
            engine->double_colon_required = true;
            if (symbol_0_to_9_or_Aa_to_Ff) {
                engine->state = State_14;
            } else if (symbol_colon) {
                engine->state = State_17;
                engine->colon_counter++;
            } else {
                engine->state = State_Error;
            }
            break;
        }
        case State_14: {
            engine->double_colon_required = true;
            if (symbol_0_to_9_or_Aa_to_Ff) {
                engine->state = State_15;
            } else if (symbol_colon) {
                engine->state = State_17;
                engine->colon_counter++;
            } else {
                engine->state = State_Error;
            }
            break;
        }
        case State_15: {
            engine->double_colon_required = true;
            if (symbol_0_to_9_or_Aa_to_Ff) {
                engine->state = State_16;
            } else if (symbol_colon) {
                engine->state = State_17;
                engine->colon_counter++;
            } else {
                engine->state = State_Error;
            }
            break;
        }
        case State_16: {
            engine->double_colon_required = true;
            if (symbol_colon) {
                engine->state = State_17;
                engine->colon_counter++;
            } else {
                engine->state = State_Error;
            }
            break;
        }
        case State_17: {
            if (symbol_colon) {
                engine->state = State_23;
            } else if (engine->double_colon_required == false) {
                if (symbol_1) {
                    engine->state = State_1;
                } else if (symbol_2) {
                    engine->state = State_5;
                } else if (symbol_0_to_9) {
                    engine->state = State_8;
                }
            } else if ((engine->colon_counter < 4) && (symbol_0_to_9_or_Aa_to_Ff)) {
                engine->state = State_13;
            } else {
                engine->state = State_Error;
            }
            break;
        }
        case State_18: {
            if (symbol_0) {
                engine->state = State_19;
            } else if (symbol_1) {
                engine->state = State_1;
            } else if (symbol_2) {
                engine->state = State_5;
            } else if (symbol_0_to_9) {
                engine->state = State_8;
            } else if ((engine->colon_counter < 4) && (symbol_0_to_9_or_Aa_to_Ff)) {
                engine->state = State_13;
            } else if (symbol_colon) {
                engine->state = State_17;
                engine->colon_counter++;
            } else {
                engine->state = State_Error;
            }
            break;
        }
        case State_19: {
            if (symbol_0) {
                engine->state = State_20;
            } else if (symbol_colon) {
                engine->state = State_17;
                engine->colon_counter++;
            } else if (symbol_dot) {
                engine->state = State_4;
                engine->dot_counter++;
            } else {
                engine->state = State_Error;
            }
            break;
        }
        case State_20: {
            if (symbol_0) {
                engine->state = State_21;
            } else if (symbol_colon) {
                engine->state = State_17;
                engine->colon_counter++;
            } else {
                engine->state = State_Error;
            }
            break;
        }
        case State_21: {
            if (symbol_0) {
                engine->state = State_22;
            } else if (symbol_colon) {
                engine->state = State_17;
                engine->colon_counter++;
            } else {
                engine->state = State_Error;
            }
            break;
        }
        case State_22: {
            if (symbol_colon) {
                engine->state = State_17;
                engine->colon_counter++;
            } else {
                engine->state = State_Error;
            }
            break;
        }
        case State_23: {
            engine->is_not_ip = false;
            if (symbol_1) {
                engine->state = State_1;
            } else if (symbol_2) {
                engine->state = State_5;
            } else if (symbol_0_to_9) {
                engine->state = State_8;
            } else {
                engine->state = State_Error;
            }
            break;
        }
    }
    engine->index++;
}

