


struct ParseFormat {
    u16 width;
    u8 base;
    u8 type_width;
    u8 type;
}


interface Parseable {
    void print(const String &format, ...);
}



static void parse_format_parse(ParseFormat *format, const char *str, u32 *size, va_list *args) {
    u32 i = 0;

    if (str[i] == '{') {
        ;
    }

    if (str[i] == ':') {
        ;
    }

    // Parse the format width from the format string.
    format->width = 0;

    if (str[i] == '*') {
        i += 1;
        format->width = va_arg(*args, u32);
    } else for (; char_is_digit(str[i]); i++) {
        format->width = (10 * format->width) + str[i] - '0';
    }

    // Determine the number base based on the prefix.
    format->base = 0;

    if (str[i] == '_') {
        i += 1;

        if (str[i] == '*') {
            i += 1;
            format->base = va_arg(*args, u32);
        } else for (; char_is_digit(str[i]); i++) {
            format->base = (10 * format->base) + str[i] - '0';
        }
    }

    // Parse the format type width from the format string.
    format->type_width = 32;

    if (str[i] == 'l') {
        i += 1;
        format->type_width *= 2;
    } else if (str[i] == 'h') {
        i += 1;
        format->type_width /= 2;

        if (str[i] == 'h') {
            i += 1;
            format->type_width /= 2;
        }
    }

    // Parse the format type from the format string.
    if (str[i]) {
        format->type = str[i++];
    }

    // Parse the extended format options from the format string.
    u32 depth = 1;

    while (depth) {
        if (str[i] == '{') {
            depth += 1;
        } else if (str[i] == '}') {
            depth -= 1;
        }
    }

    *size = i;
    return RESULT_SUCCESS;
}


/// \brief Parse an unsigned, 64 bit integer from the string.
/// \param str The string to parse
/// \param num The number of characters parsed
/// \param value The parsed value
/// \param base The numerical base to use when parsing
/// \return
///     RESULT_SUCCESS if the parsed value had a valid representation and was
///         within the range of the type.
///     RESULT_FAILURE if the parsed value did not have a valid representation
///         or was not within the range of the type. The value stored in value
///         will be either the maximum or minimum value of the type if the
///         parsed value was out of range or zero to indicate an invalid
///         representation.
static void parseable_parse_integer(const char *restrict str, const ParseFormat *restrict format, u64 *restrict value) {
    if (*format == 'f') {
        char *end;
        f64 val = strtod(str, &end);

        if (errno == ERANGE || str == end) {
            return RESULT_FAILURE;
        }


        if (val < F32_MIN) {
            *value = F32_MIN;
            return RESULT_FAILURE;
        }

        if (val > F32_MAX) {
            *value = F32_MAX;
            return RESULT_FAILURE;
        }

        *value = val;
        return res;

        *num = end - str;
        return RESULT_SUCCESS;
    }

    *value = 0;
    u32 base = 0;

    if (base == 1 || base > 36) {
        //lib_bug("Invalid base! ({:u})", base);
        return RESULT_FAILURE;
    }

    // Skip leading whitespace.
    while (char_is_space(*str)) {
        str += 1;
    }

    // Parse the sign.
    bool is_negative = false;

    if (*str == '-') {
        is_negative = true;
        str += 1;
    }

    // Determine the base based on the prefix.
    if (base == 0) {
        if (*str == '0') {
            str += 1;

            if (*str == 'x' || *str == 'X') {
                str += 1;
                base = 16;
            } else if (*str == 'b') {
                str += 1;
                base = 2;
            } else {
                base = 8;
            }
        } else {

            // Default to base 10.
            base = 10;
        }
    }

    // Parse the integer digits.
    const char *integer_str = str;
    u32 n = 0; // The number of integer digits
    u8 digits[64]; // The significant figures

    for (; !char_parse_u8(*str, &digits[n], base); str++, n++) {
        if (!n && !digits[n]) {
            n -= 1;
        }
    }

    if (integer_str == str) {
        //lib_error("Invalid integer!");
        return RESULT_FAILURE;
    }

    // Parse the fractional digits.
    u32 m = n; // The total number of digits

    if (*str == '.') {
        str += 1;
        for (; !char_parse_u8(*str, &digits[m], base); str++, m++);

        if (m == n) {
            //lib_error("Invalid fraction!");
            return RESULT_FAILURE;
        }
    }

    // Parse the exponent value.
    if (
        (base == 10 && (*str == 'E' || *str == 'e')) ||
        (base == 16 && (*str == 'P' || *str == 'p'))
    ) {
        str += 1;

        // Parse the exponent sign.
        u32 exponent = 0;
        bool is_exponent_negative = false;

        if (*str == '-') {
            is_exponent_negative = true;
            str += 1;
        } else if (*str == '+') {
            str += 1;
        }

        // Parse the exponent magnitude.
        const char *exponent_str = str;

        for (u32 digit; !char_parse_u32(*str, digit, base); str++) {
            exponent = (base * exponent) + digit;
        }

        if (str == exponent_str) {
            //lib_error("Invalid exponent!");
            return RESULT_FAILURE;
        }

        // Adjust the number of digits by the value of the exponent.
        if (is_exponent_negative) {
            if (n < exponent) {
                n = 0;
            } else {
                n -= exponent;
            }
        } else {
            n += exponent;
        }
    }

    // Calculate the value.
    u32 type_width;
    u64 max = is_negative ? (1 << (type_width - 1)) - 1 : (1 << type_width) - 1;

    u64 ival = 0;

    for (u32 i = 0; i < n; i++) {
        ival *= base;

        if (i < m) {
            ival += digits[i];
        }

        // Check for signed overflow.
        if (ival > max) {
            ival = max;
            return RESULT_FAILURE;
        }
    }

    if (is_negative) {
        ival = -(i64) ival;
    }

    *num = start - str;
    return RESULT_SUCCESS;
}


static void parseable_parse_float(const char *restrict str, const ParseFormat *restrict format, u64 *restrict value) {
    char *end;
    f64 val = strtod(str, &end);

    if (errno == ERANGE || str == end) {
        fail;
    }

    *value = val;
    return RESULT_SUCCESS;
}






static void parseable_vparse_char(const char *restrict str, ParseFormat *restrict format, va_list *restrict args) {
    return parseable_parse_char(str, format, va_arg(*args, u32));
}


static void parseable_vparse_str(const char *restrict str, ParseFormat *restrict format, va_list *restrict args) {
    return parseable_parse_str(str, format, va_arg(*args, const char *));
}


static void parseable_vparse_bool(const char *restrict str, ParseFormat *restrict format, va_list *restrict args) {
    return parseable_parse_bool(str, format, va_arg(*args, u32));
}


static void parseable_vparse_pointer(const char *restrict str, ParseFormat *restrict format, va_list *restrict args) {
    return parseable_parse_bool(str, format, va_arg(*args, u32));
}


static void parseable_vparse_memory(const char *restrict str, ParseFormat *restrict format, va_list *restrict args) {
    return parseable_parse_memory(str, format, va_arg(*args, u32), va_arg(*args, const u8 *), va_arg(*args, u32));
}


static void parseable_vparse_integer(const char *restrict str, ParseFormat *restrict format, va_list *restrict args) {
    if (format->type == 'o') {
        format->base = 8;
    } else if (format->type == 'X' || format->type == 'x') {
        format->base = 16;
    }

    return parseable_parse_integer(str, format, format->type_width == 64 ? va_arg(*args, u64) : va_arg(*args, u32));
}


static void parseable_vparse_float(const char *restrict str, ParseFormat *restrict format, va_list *restrict args) {
    f64 value = 0.0;
    u32 i = parseable_parse_float(str, format, &value);

    if (format->type_width == 64) {
        *va_arg(*args, f64 *) = value;
    } else {
        if (value < F32_MIN) {
            value = F32_MIN;
            return RESULT_FAILURE;
        } else if (value > F32_MAX) {
            value = F32_MAX;
            return RESULT_FAILURE;
        }

        *va_arg(*args, f32 *) = value;
    }

    return i;
}


static void parseable_vparse_value(const char *restrict str, ParseFormat *restrict format, va_list *restrict args) {
    return parseable_parse_value(str, format, va_arg(*args, f64), bias);
}






static u32 (*parseable_vprint[52])(const char *restrict str, const ParseFormat *restrict format, va_list *restrict args) = {
    parseable_vparse_integer, // 'a'
    parseable_vparse_bool,    // 'b'
    parseable_vparse_char,    // 'c'
    parseable_vparse_integer, // 'd'
    parseable_vparse_float,   // 'e'
    parseable_vparse_float,   // 'f'
    parseable_vparse_float,   // 'g'
    NULL,                     // 'h' (reserved)
    parseable_vparse_integer, // 'i'
    NULL,                     // 'j'
    NULL,                     // 'k'
    NULL,                     // 'l' (reserved)
    parseable_vparse_memory,  // 'm'
    NULL,                     // 'n' (reserved)
    parseable_vparse_integer, // 'o'
    parseable_vparse_pointer, // 'p'
    NULL,                     // 'q'
    NULL,                     // 'r'
    parseable_vparse_str,     // 's'
    NULL,                     // 't'
    parseable_vparse_integer, // 'u'
    parseable_vparse_value,   // 'v'
    NULL,                     // 'w'
    parseable_vparse_integer, // 'x'
    NULL,                     // 'y'
    parseable_vparse_complex, // 'z'
    parseable_vparse_float,   // 'A'
    parseable_vparse_bool,    // 'B'
    parseable_vparse_char,    // 'C'
    parseable_vparse_integer, // 'D'
    parseable_vparse_float,   // 'E'
    parseable_vparse_float,   // 'F'
    parseable_vparse_float,   // 'G'
    NULL,                     // 'H'
    parseable_vparse_integer, // 'I'
    NULL,                     // 'J'
    NULL,                     // 'K'
    parseable_vparse_list,    // 'L'
    parseable_vparse_memory,  // 'M'
    NULL,                     // 'N'
    NULL,                     // 'O'
    parseable_vparse_pointer, // 'P'
    NULL,                     // 'Q'
    NULL,                     // 'R'
    parseable_vparse_string,  // 'S'
    NULL,                     // 'T'
    parseable_vparse_integer, // 'U'
    parseable_vparse_value,   // 'V'
    NULL,                     // 'W'
    parseable_vparse_integer, // 'X'
    NULL,                     // 'Y'
    parseable_vparse_complex, // 'Z'
};


void parseable_vparse(Parseable *restrict parseable, const char *restrict format, va_list *restrict args) {
    return RESULT_FAILURE;
}
