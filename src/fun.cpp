// Copyright 2022 UNN-IASR
#include "fun.h"

#include <locale>
#include <cctype>
#include <cwctype>
#include <cmath>
#include <cstdlib>
#include <climits>

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

        int c = (unsigned char)*letter;

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
    unsigned int words = 0;
    const char *letter = str - 1;
    enum state_enum {
        ST_OUTSIDE,
        ST_INVALID_WORD,
        ST_WORD
    } state = ST_OUTSIDE;

    // Чтобы пропускать только латинский алфавит
    std::locale c_locale("C");

    while (*++letter) {
        enum char_category {
            CAT_SPACE,
            CAT_LATIN_UPPERCASE,
            CAT_LATIN_LOWERCASE,
            CAT_OTHER
        } category = CAT_OTHER;

        char c = *letter;

        if (isspace(c, c_locale)) {
            category = CAT_SPACE;
        } else if (isalpha(c, c_locale)) { // Является буквой
            if (isupper(c, c_locale)) {
                category = CAT_LATIN_UPPERCASE;
            } else if (islower(c, c_locale)) {
                category = CAT_LATIN_LOWERCASE;
            }
        }

        switch (state) {
            case ST_OUTSIDE:
                switch (category) {
                case CAT_LATIN_UPPERCASE:
                    state = ST_WORD;
                    words++;
                    break;
                case CAT_LATIN_LOWERCASE:
                case CAT_OTHER:
                    state = ST_INVALID_WORD;
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
                case CAT_LATIN_UPPERCASE:
                case CAT_OTHER:
                    state = ST_INVALID_WORD;
                    words--;
                    break;
                default:
                    break;
                }
                break;
            default:
                break;
        }
    }

    return words;
}

unsigned int faStr3(const char *str) {
    std::wstring wstr;
    unsigned int words = 0;
    unsigned int total_letters = 0;
    enum state_enum {
        ST_OUTSIDE,
        ST_WORD
    } state = ST_OUTSIDE;

    // Перевести const char* в wstring для отображения
    // корректной длины UTF-8 кириллических слов
    {
        const char* old_loc_str = setlocale(0, NULL);
        setlocale(LC_ALL, "");
        mbtowc(NULL, NULL, 0);
        const char *str_ptr = str;
        wchar_t wc = L'\0';
        int ret = 0;
        do {
            ret = mbtowc(&wc, str_ptr, MB_LEN_MAX);
            if (ret > 0) {
                wstr += wc;
                str_ptr += ret;
            }
        } while (ret > 0);

        setlocale(LC_ALL, old_loc_str);
    }

    for (auto const & c : wstr) {
        enum char_category {
            CAT_SPACE,
            CAT_NONSPACE
        } category = CAT_NONSPACE;

        if (iswspace(c)) {
            category = CAT_SPACE;
        }

        switch (state) {
            case ST_OUTSIDE:
                switch (category) {
                case CAT_NONSPACE:
                    state = ST_WORD;
                    words++;
                    total_letters++;
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
                case CAT_NONSPACE:
                    total_letters++;
                    break;
                default:
                    break;
                }
                break;
            default:
                state = ST_OUTSIDE;
                break;
        }
    }

    double average_length =
                    words ? static_cast<double>(total_letters) / words : 0;

    return std::round(average_length);
}
