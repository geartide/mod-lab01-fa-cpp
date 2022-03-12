// Copyright 2022 UNN-IASR
#include "fun.h"

#include <cctype>

unsigned int faStr1(const char *str) {
    unsigned int words = 0;
    const char *letter = str - 1;
    enum state_enum { ST_OUTSIDE, ST_INVALID_WORD, ST_WORD } state = ST_OUTSIDE;

    while (*++letter) {
        enum char_category {
            CAT_SPACE,
            CAT_DIGIT,
            CAT_LETTER
        } category = CAT_SPACE;

        int c = *letter;

        if (isspace(c)) {
            category = CAT_SPACE;
        } else if (isdigit(c)) {
            category = CAT_DIGIT;
        } else if (isalpha(c)) {
            category = CAT_LETTER;
        }

        switch (state) {
        case ST_OUTSIDE:
            switch (category) {
            case CAT_DIGIT:
                state = ST_INVALID_WORD;
                break;
            case CAT_LETTER:
                state = ST_WORD;
                words++;
                break;
            default:
                break;
            }
            break;
        case ST_INVALID_WORD:
            switch (category) {
            case CAT_SPACE:
                state = ST_OUTSIDE;
                break;
            default:
                break;
            }
            break;
        case ST_WORD:
            switch (category) {
            case CAT_SPACE:
                state = ST_OUTSIDE;
                break;
            case CAT_DIGIT:
                state = ST_INVALID_WORD;
                words--;
                break;
            default:
                break;
            }
            break;
        default:
            state = ST_OUTSIDE;
            letter--;
            break;
        }
    }

    return words;
}

unsigned int faStr2(const char *str) {
    return 0;
}

unsigned int faStr3(const char *str) {
    return 0;
}
