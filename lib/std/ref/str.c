#include <dust/str.h>
#include <dust/common.h>

#include <errno.h>
#include <stdlib.h>


extern inline u32 str_size(const char *str);
extern inline u32 str_size_max(const char *str, u32 max);

extern inline void str_to_upper(char *str);
extern inline void str_to_upper_max(char *str, u32 max);
extern inline void str_to_lower(char *str);
extern inline void str_to_lower_max(char *str, u32 max);

extern inline void str_fill(char *str, char ch);
extern inline void str_fill_max(char *str, char ch, u32 max);


extern inline void str_copy(char *restrict str, const char *restrict other);


extern inline void str_copy_max(char *restrict str, const char *restrict copy, u32 max);


u32 str_hash(const char *str) {
    u32 hash = 5381;

    for (u32 i = 0; str[i]; i++) {
        hash = (33 * hash) + str[i];
    }

    return hash;
}


u32 str_hash_max(const char *str, u32 max) {
    u32 hash = 5381;

    for (u32 i = 0; i < max && str[i]; i++) {
        hash = (33 * hash) + str[i];
    }

    return hash;
}


result_t str_find_char(const char *restrict str, u32 *restrict index, char ch) {
    for (u32 i = 0; str[i]; i++) {
        if (str[i] == ch) {
            *index = i;
            return RESULT_SUCCESS;
        }
    }

    return RESULT_FAILURE;
}


result_t str_find_char_max(const char *restrict str, u32 *restrict index, char ch, u32 max) {
    for (u32 i = 0; i < max && str[i]; i++) {
        if (str[i] == ch) {
            *index = i;
            return RESULT_SUCCESS;
        }
    }

    return RESULT_FAILURE;
}


result_t str_find_chars(const char *restrict str, u32 *restrict index, const char *restrict chars) {
    for (u32 i = 0; str[i]; i++) {
        for (const char *ch = chars; *ch; ch++) {
            if (str[i] == *ch) {
                *index = i;
                return RESULT_SUCCESS;
            }
        }
    }

    return RESULT_FAILURE;
}


result_t str_find_chars_max(const char *restrict str, u32 *restrict index, const char *restrict chars, u32 max) {
    for (u32 i = 0; i < max && str[i]; i++) {
        for (const char *ch = chars; *ch; ch++) {
            if (str[i] == *ch) {
                *index = i;
                return RESULT_SUCCESS;
            }
        }
    }

    return RESULT_FAILURE;
}


result_t str_find_str(const char *restrict str, u32 *restrict index, const char *restrict substr) {
    for (u32 i = 0; *str; i++, str++) {
        for (u32 j = 0;; j++) {
            if (!substr[j]) {
                *index = i;
                return RESULT_SUCCESS;
            }

            if (str[j] != substr[j]) {
                break;
            }
        }
    }

    return RESULT_FAILURE;
}


result_t str_find_str_max(const char *restrict str, u32 *restrict index, const char *restrict substr, u32 max) {
    for (u32 i = 0; i < max && *str; i++, str++) {
        for (u32 j = 0; i + j < max; j++) {
            if (!substr[j]) {
                *index = i;
                return RESULT_SUCCESS;
            }

            if (str[j] != substr[j]) {
                break;
            }
        }
    }

    return RESULT_FAILURE;
}


result_t str_find_strs(const char *restrict str, u32 *restrict index, const char **restrict substrs) {
    for (u32 i = 0; *str; i++, str++) {
        for (const char *substr = substrs; substr; substr++) {
            for (u32 j = 0;; j++) {
                if (!substr[j]) {
                    *index = i;
                    return RESULT_SUCCESS;
                }

                if (str[j] != substr[j]) {
                    break;
                }
            }
        }
    }

    return RESULT_FAILURE;
}


result_t str_find_strs_max(const char *restrict str, u32 *restrict index, const char **restrict substrs, u32 max) {
    for (u32 i = 0; i < max && *str; i++, str++) {
        for (const char *substr = substrs; substr; substr++) {
            for (u32 j = 0; i + j < max; j++) {
                if (!substr[j]) {
                    *index = i;
                    return RESULT_SUCCESS;
                }

                if (str[j] != substr[j]) {
                    break;
                }
            }
        }
    }

    return RESULT_FAILURE;
}










i32 str_compare(const char *restrict str, const char *restrict other) {
    u32 i = 0;
    for (; str[i] && other[i] && str[i] == other[i]; i++);
    return other[i] - str[i];
}


extern inline bool str_is_equ(const char *str, const char *other);
extern inline bool str_is_neq(const char *str, const char *other);
extern inline bool str_is_les(const char *str, const char *other);
extern inline bool str_is_leq(const char *str, const char *other);
extern inline bool str_is_gtr(const char *str, const char *other);
extern inline bool str_is_geq(const char *str, const char *other);


i32 str_compare_max(const char *restrict str, const char *restrict other, u32 max) {
    u32 i = 0;
    for (; i < max && str[i] && other[i] && str[i] == other[i]; i++);
    return other[i] - str[i];
}


extern inline bool str_is_equ_max(const char *str, const char *other, u32 max);
extern inline bool str_is_neq_max(const char *str, const char *other, u32 max);
extern inline bool str_is_les_max(const char *str, const char *other, u32 max);
extern inline bool str_is_leq_max(const char *str, const char *other, u32 max);
extern inline bool str_is_gtr_max(const char *str, const char *other, u32 max);
extern inline bool str_is_geq_max(const char *str, const char *other, u32 max);



















result_t parse_format_parse(ParseFormat *format, const char *str, u32 *size, va_list *args) {
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


result_t print_format_parse(PrintFormat *format, const char *str, u32 *size, va_list *args) {
    u32 i = 0;

    if (str[i] == '{') {
        ;
    }

    if (str[i] == ':') {
        ;
    }

    // Parse the format alignment with fill.
    if (str[i] && (str[i + 1] == '<' || str[i + 1] == '>' || str[i + 1] == '=' || str[i + 1] == '^')) {
        format->fill = str[i++];
        format->align = str[i++];
    } else {
        format->fill = ' ';

        // Parse the format alignment only.
        if (str[i] == '<' || str[i] == '>' || str[i] == '=' || str[i] == '^') {
            format->align = str[i];
        } else {
            format->align = 0;
        }
    }

    // Parse the number prefix from the format string.
    if ((format->has_prefix = str[i] == '#')) {
        format += 1;
    }

    // Parse the zero-padding from the format string.
    if (!format->align && str[i] == '0') {
        i += 1;
        format->fill = '0';
        format->align = '=';
    }

    // Parse the format width from the format string.
    format->width = 0;

    if (str[i] == '*') {
        i += 1;
        format->width = va_arg(*args, u32);
    } else for (; char_is_digit(str[i]); i++) {
        format->width = (10 * format->width) + str[i] - '0';
    }

    // Parse the number precision from the format string.
    format->precision = 0;

    if (str[i] == '.') {
        i += 1;

        if (str[i] == '*') {
            i += 1;
            format->precision = va_arg(*args, u32);
        } else for (; char_is_digit(str[i]); i++) {
            format->precision = (10 * format->precision) + str[i] - '0';
        }
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
















u32 str_parse(const char *restrict str, const char *restrict format, va_list *args) {
    u32 i = 0;
    return i;
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
static result_t str_parse_number(const char *restrict str, const char *restrict format, va_list *args) {
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


result_t str_parse_i32(const char *restrict str, u32 *restrict num, i32 *restrict value, u32 base) {
    i64 val;
    result_t res = str_parse_i64(str, num, &val, base);

    if (val < I32_MIN) {
        *value = I32_MIN;
        return RESULT_FAILURE;
    }

    if (val > I32_MAX) {
        *value = I32_MAX;
        return RESULT_FAILURE;
    }
}














static result_t str_print_buffer(char *restrict str, u32 max, PrintFormat *restrict format, const char *buffer, u32 width) {
    u32 width = format->precision ? u32_min(width, format->precision) : width;
    u32 i = 0;

    if (width < format->width && format->align != '<') {
        u32 pad = format->width - width;

        if (format->align == '^') {
            pad /= 2;
        }

        while (u32_min(max, pad)) {
            str[i++] = format->fill;
        }
    }

    for (u32 n = u32_min(max, i + width); i < n; i++) {
        str[i] = *buffer++;
    }

    for (; i < u32_min(max, format->width); i++) {
        str[i] = format->fill;
    }

    return i;
}











static result_t str_print_char(char *restrict str, u32 max, PrintFormat *restrict format, char value) {
    u32 width = format->precision ? format->precision : 1;
    u32 i = 0;

    if (width < format->width && format->align != '<') {
        u32 pad = format->width - width;

        if (format->align == '^') {
            pad /= 2;
        }

        while (u32_min(max, pad)) {
            str[i++] = format->fill;
        }
    }

    for (u32 n = u32_min(max, i + width); i < n; i++) {
        str[i] = value;
    }

    for (; i < u32_min(max, format->width); i++) {
        str[i] = format->fill;
    }

    return i;
}


static result_t str_print_str(char *restrict str, u32 max, PrintFormat *restrict format, const char *value) {
    u32 width = format->precision ? str_size_max(value, format->precision) : str_size(value);
    return str_print_buffer(str, max, format, value, width);
}


static result_t str_print_bool(char *restrict str, u32 max, PrintFormat *restrict format, bool value) {
    const char *buffer;

    if (format->type == 'B') {
        buffer = value ? "True" : "False";
    } else {
        buffer = value ? "true" : "false";
    }

    return str_print_buffer(str, max, format, buffer, value ? 4 : 5);
}


static result_t str_print_pointer(char *restrict str, u32 max, PrintFormat *restrict format, const void *value) {
    u32 i = 0;
    char buffer[2 + sizeof(void *)];
    char letter_offset = format->type == 'P' ? 'A' - '0' - 10 : 'a' - '0' - 10;

    if (format->has_prefix) {
        buffer[i++] = '0';
        buffer[i++] = 'x';
    }

    for (u32 n = 8 * sizeof(void *); n; i++) {
        n -= 4;
        buffer[i] = ((uintptr_t) value >> n) + '0';

        if (buffer[i] > '9') {
            buffer[i] += letter_offset;
        }
    }

    return str_print_buffer(str, max, format, value, i);
}


static result_t str_print_memory(char *restrict str, u32 max, PrintFormat *restrict format, u32 address, const void *values, u32 size) {
    u32 address_size = address + size > 0xFFFFU ? 4 : 2;
    u32 type_size = format->type_width / 8;
    u32 cols = 16 / type_size;
    u32 mask = endian_is_little ? type_size - 1 : 0;
    u32 i = 0;
    u32 buffer_size = address_size + cols + 52;
    char buffer[buffer_size];
    char letter_offset = format->type == 'M' ? 'A' - '0' - 10 : 'a' - '0' - 10;
    char *string_view = NULL;

    for (u32 address = a;;) {
        if (string_view) {
            string_view = &buffer[buffer_size - 16];
        }

        for (u32 col = 0; col < cols; col++) {
            buffer[i] = ' ';

            if (n < 0 || n > size) {
                for (u32 j = 0; j < type_size; j++) {
                    if (string_view) {
                        string_view[i++] = ' ';
                    }

                    buffer[i++] = ' ';
                    buffer[i++] = ' ';
                }
            } else {
                for (u32 j = 0; j < type_size; j++) {
                    u8 value = values[n + (j ^ mask)];

                    if (string_view) {
                        string_view[col ^ mask] = char_is_print(value) ? value : '.';
                    }

                    buffer[i] = (value >> 4) + '0';

                    if (buffer[i] > '9') {
                        buffer[i] += letter_offset;
                    }

                    i += 1;
                    buffer[i] = (value & 0xFU) + '0';

                    if (buffer[i] > '9') {
                        buffer[i] += letter_offset;
                    }

                    i += 1;
                }
            }
        }

        if (string_view) {
            buffer[i++] = ' ';
            buffer[i++] = ' ';
        }

        if (i < max) {
            buffer[i++] = '\n';
        }
    }

    return i - 1;
}


static result_t str_print_number(char *restrict str, u32 max, const char *restrict format, va_list *args) {
    bool is_negative = value < 0;
    u64 val = is_negative ? -value : value; // TODO: handle MIN value.
    u32 i = 65;
    char digits[i + 1];
    digits[i--] = '\0';

    do {
        digits[i] = (val % base) + '0';

        if (digits[i] > '9') {
            digits[i] += uppercase ? ('A' - '0' - 10) : ('a' - '0' - 10);
        }

        val /= base;
        i -= 1;
    } while (val);

    // Print the sign.
    if (is_negative) {
        digits[i--] = '-';
    }

    u32 req = 65 - i;

    if (req > max) {
        //lib_error("Insufficient space!");
        str_copy_max(*str, digits, max);
        return RESULT_FAILURE;
    }

    // Print the integer magnitude.
    str_copy(*str, digits);
    return RESULT_SUCCESS;
}


















static result_t str_vprint_char(char *restrict str, u32 max, PrintFormat *restrict format, va_list *args) {
    if (!format->align) {
        format->align = '<';
    }

    return str_print_char(str, max, format, va_arg(*args, u32));
}


static result_t str_vprint_str(char *restrict str, u32 max, PrintFormat *restrict format, va_list *args) {
    if (!format->align) {
        format->align = '<';
    }

    return str_print_str(str, max, format, va_arg(*args, const char *));
}


static result_t str_vprint_bool(char *restrict str, u32 max, PrintFormat *restrict format, va_list *args) {
    if (!format->align) {
        format->align = '<';
    }

    return str_print_bool(str, max, format, va_arg(*args, u32));
}


static result_t str_vprint_pointer(char *restrict str, u32 max, PrintFormat *restrict format, va_list *args) {
    if (!format->align) {
        format->align = '<';
    }

    return str_print_bool(str, max, format, va_arg(*args, u32));
}


static result_t str_vprint_memory(char *restrict str, u32 max, PrintFormat *restrict format, va_list *args) {
    return str_print_memory(str, max, format, va_arg(*args, u32), va_arg(*args, const u8 *), va_arg(*args, u32));
}


static result_t str_vprint_integer(char *restrict str, u32 max, PrintFormat *restrict format, va_list *args) {
    if (!format->align) {
        format->align = '>';
    }

    if (format->type == 'o') {
        format->base = 8;
    } else if (format->type == 'X' || format->type == 'x') {
        format->base = 16;
    }

    if (format->type_width == 64) {
        return str_print_integer64(str, max, format, va_arg(*args, u64));
    }

    return str_print_integer32(str, max, format, va_arg(*args, u32));
}


static result_t str_vprint_float(char *restrict str, u32 max, PrintFormat *restrict format, va_list *args) {
    if (!format->align) {
        format->align = '>';
    }

    return str_print_bool(str, max, format, va_arg(*args, double));
}


static result_t str_vprint_value(char *restrict str, u32 max, PrintFormat *restrict format, va_list *args) {
    if (!format->align) {
        format->align = '>';
    }

    return str_print_value(str, max, format, va_arg(*args, double), bias);
}








result_t str_vprint(char *restrict str, u32 max, const char *restrict format, va_list *args) {
    u32 rem = max; // The remaining space in the string.
    u32 idx = 0; // The format argument index.
    u32 i = 0;

    while (*format) {

        // Copy litteral characters from the format string.
        if (*format != '{') {
            str[i++] = *format++;
            continue;
        }

        format += 1;

        // Check for a litteral '{' character.
        if (*format == '{') {
            str[i++] = *format++;
            continue;
        }

        // Parse the alignment flag from the format string.
        PrintFormat fmt;
        u32 n;

        if (print_format_parse(&fmt, format, &n, args)) {
            return RESULT_FAILURE;
        }

        format += n;

        if (fmt.type == 'n') {
            *va_arg(*args, u32 *) = i;
        } else if (type < 52) {

            // Custom format function.
            str_print_fn_f str_print_fn = va_arg(*args, str_print_fn_f *);
            if (str_print_fn(&str[i], max - i, &fmt, args)) {
                return RESULT_FAILURE;
            }
        } else {
            lib_bug("Invalid format specifier for custom type! ({:c})", fmt.type);
        }
    }

    return RESULT_SUCCESS;
}




result_t str_print(char *restrict str, u32 max, const char *restrict format, ...) {
    va_list args;
    va_start(args, format);
    result_t res = str_vprint(str, max, format, args);
    va_end(args);
    return res;
}
