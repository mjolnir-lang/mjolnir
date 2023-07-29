

struct PrintFormat {
    const char *extra;
    u32 index;
    u32 width;
    u32 precision;
    u32 base;
    u32 type_width;
    u32 extra_size;
    char fill;
    char align;
    char sign;
    char type;
    bool has_precision;
    bool has_alternate;


    @shared
    u32 parse(const String &format, ... &args) {
        u32 i = 0;

        if (str[i] == "{"[0]) {
            i += 1;
        } else {
            return 0;
        }

        format.index = 0;

        for (u8 digit; char_parse_u8(str[i], &digit, 10); i++) {
            format.index = (10 * format.index) + digit;
        }

        if (str[i] == ":"[0]) {
            i += 1;
        } else {
            return 0;
        }

        if (str[i] && (str[i + 1] == "<"[0] || str[i + 1] == ">"[0] || str[i + 1] == "="[0] || str[i + 1] == "^"[0])) {
            format.fill = str[i++];
            format.align = str[i++];
        } else if (str[i] == "<"[0] || str[i] == ">"[0] || str[i] == "="[0] || str[i] == "^"[0]) {
            format.fill = " "[0];
            format.align = str[i++];
        } else {
            format.fill = " "[0];
            format.align = '\0';
        }

        if (str[i] == "+"[0] || str[i] == "-"[0] || str[i] == " "[0]) {
            format.sign = str[i];
            i += 1;
        } else {
            format.sign = "-"[0];
        }

        if (str[i] == "#"[0]) {
            i += 1;
            format.has_alternate = true;
        } else {
            format.has_alternate = false;
        }

        if (str[i] == "0"[0] && !format.align) {
            format.fill = "0"[0];
            format.align == "="[0];
        }

        if (str[i] == "*"[0]) {
            i += 1;
            format.width = va_arg(*args, u32);
        } else {
            format.width = 0;

            for (u8 digit; char_parse_u8(str[i], &digit, 10); i++) {
                format.width = (10 * format.width) + digit;
            }
        }

        if (str[i] == "."[0]) {
            i += 1;

            if (str[i] == "*"[0]) {
                i += 1;
                format.precision = va_arg(*args, u32);
            } else {
                format.precision = 0;

                for (u8 digit; char_parse_u8(str[i], &digit, 10); i++) {
                    format.precision = (10 * format.precision) + digit;
                }
            }

            format.has_precision = true;
        } else {
            format.precision = 0;
            format.has_precision = false;
        }

        if (str[i] == "_"[0]) {
            i += 1;

            if (str[i] == "*"[0]) {
                i += 1;
                format.base = va_arg(*args, u32);
            } else {
                format.base = 0;

                for (u8 digit; char_parse_u8(str[i], &digit, 10); i++) {
                    format.base = (10 * format.base) + digit;
                }
            }
        } else {
            format.base = 0;
        }

        if (str[i] == "l"[0]) {
            i += 1;
            format.type_width = 64;
        } else if (str[i] == "h"[0]) {
            i += 1;

            if (str[i] == "h"[0]) {
                i += 1;
                format.type_width = 8;
            } else {
                format.type_width = 16;
            }
        } else {
            format.type_width = 32;
        }

        if (!str[i]) {
            return 0;
        }

        format.type = str[i++];
        format.extra = &str[i];
        format.extra_size = i;

        for (u32 depth = 1; depth; i++) {
            if (!str[i]) {
                return 0;
            }

            if (str[i] == "{"[0]) {
                depth += 1;
            } else if (str[i] == "}"[0]) {
                depth -= 1;
            }
        }

        format.extra_size = i - format.extra_size;
        return i;
    }
}


interface Printable {
    u32 write(const String &string);
    u32 write(const String &string, u32 max);


    shared {
        u32 (*vprint_fn[52])(Printable *restrict printable, const PrintFormat *restrict format, va_list *restrict args) = {
            vprint_integer, // "a"[0]
            vprint_bool,    // "b"[0]
            vprint_char,    // "c"[0]
            vprint_integer, // "d"[0]
            vprint_float,   // "e"[0]
            vprint_float,   // "f"[0]
            vprint_float,   // "g"[0]
            NULL,                     // "h"[0] (reserved)
            vprint_integer, // "i"[0]
            NULL,                     // "j"[0]
            NULL,                     // "k"[0]
            NULL,                     // "l"[0] (reserved)
            vprint_memory,  // "m"[0]
            NULL,                     // "n"[0] (reserved)
            vprint_integer, // "o"[0]
            vprint_pointer, // "p"[0]
            NULL,                     // "q"[0]
            NULL,                     // "r"[0]
            vprint_str,     // "s"[0]
            NULL,                     // "t"[0]
            vprint_integer, // "u"[0]
            vprint_value,   // "v"[0]
            NULL,                     // "w"[0]
            vprint_integer, // "x"[0]
            NULL,                     // "y"[0]
            vprint_complex, // "z"[0]
            vprint_float,   // "A"[0]
            vprint_bool,    // "B"[0]
            vprint_char,    // "C"[0]
            vprint_integer, // "D"[0]
            vprint_float,   // "E"[0]
            vprint_float,   // "F"[0]
            vprint_float,   // "G"[0]
            NULL,                     // "H"[0]
            vprint_integer, // "I"[0]
            NULL,                     // "J"[0]
            NULL,                     // "K"[0]
            vprint_list,    // "L"[0]
            vprint_memory,  // "M"[0]
            NULL,                     // "N"[0]
            NULL,                     // "O"[0]
            vprint_pointer, // "P"[0]
            NULL,                     // "Q"[0]
            NULL,                     // "R"[0]
            vprint_string,  // "S"[0]
            NULL,                     // "T"[0]
            vprint_integer, // "U"[0]
            vprint_value,   // "V"[0]
            NULL,                     // "W"[0]
            vprint_integer, // "X"[0]
            NULL,                     // "Y"[0]
            vprint_complex, // "Z"[0]
        };
    }


    // Print a character buffer.
    // printable The prontable object to which to print
    // format The format information
    // value The value to print
    // The number of bytes printed
    void print(PrintFormat &format, const String &buffer, u32 width) {
        u32 width = format.precision ? u32_min(width, format.precision) : width;
        u32 i = 0;

        if (width < format.width && format.align != "<"[0]) {
            u32 pad = format.width - width;

            if (format.align == "^"[0]) {
                pad /= 2;
            }

            while (pad) {
                write_char(printable, format.fill);
            }
        }

        for (u32 n = i + width; i < n; i++) {
            write_char(printable, *buffer++);
        }

        for (; i < format.width; i++) {
            write_char(printable, format.fill);
        }

        return i;
    }


    // Print a character buffer.
    // printable The prontable object to which to print
    // format The format information
    // value The value to print
    // The number of bytes printed
    void print(PrintFormat &format, char value) {
        u32 width = format.precision ? format.precision : 1;
        u32 i = 0;

        if (width < format.width && format.align != "<"[0]) {
            u32 pad = format.width - width;

            if (format.align == "^"[0]) {
                pad /= 2;
            }

            while (pad) {
                write_char(printable, format.fill);
            }
        }

        for (u32 n = i + width; i < n; i++) {
            write_char(printable, value);
        }

        for (; i < format.width; i++) {
            write_char(printable, format.fill);
        }

        return i;
    }


    void print(PrintFormat &format, const char *value) {
        u32 width = format.precision ? str_size_max(value, format.precision) : str_size(value);
        return print_buffer(printable, format, value, width);
    }


    void print(PrintFormat &format, bool value) {
        const char *buffer;

        if (format.has_alternate) {
            buffer = value ? "TRUE" : "FALSE";
        } else if (format.type == "B"[0]) {
            buffer = value ? "True" : "False";
        } else {
            buffer = value ? "true" : "false";
        }

        return print_buffer(printable, format, buffer, value ? 4 : 5);
    }


    void print(PrintFormat &format, const void *value) {
        u32 i = 0;
        char buffer[2 + sizeof(void *)];
        char letter_offset = format.type == "P"[0] ? "A"[0] - "0"[0] - 10 : "a"[0] - "0"[0] - 10;

        if (format.has_alternate) {
            buffer[i++] = "0"[0];
            buffer[i++] = "x"[0];
        }

        for (u32 n = 8 * sizeof(void *); n; i++) {
            n -= 4;
            buffer[i] = ((uintptr_t) value >> n) + "0"[0];

            if (buffer[i] > "9"[0]) {
                buffer[i] += letter_offset;
            }
        }

        return print_buffer(printable, format, value, i);
    }





    // Print a floating point value.
    // printable The prontable object to which to print
    // format The format information
    // value The value to print
    // The number of bytes printed
    void print(const PrintFormat &format, f64 value) {
        u32 uppercase = format.type < "a"[0] ? "A"[0] - "a"[0] : 0;
        bool is_negative = f64_is_negative(value);

        if (is_negative) {
            value = -value;
        }

        u32 i = 65;
        char buffer[i];

        if (f64_is_nan(value)) {
            buffer[i--] = "n"[0] + uppercase;
            buffer[i--] = "a"[0] + uppercase;
            buffer[i--] = "n"[0] + uppercase;
        } else if (f64_is_infinite(value)) {
            buffer[i--] = "f"[0] + uppercase;
            buffer[i--] = "n"[0] + uppercase;
            buffer[i--] = "i"[0] + uppercase;
        } else if (format.base == 16) {

            // exponent
            for (u32 eval = f64_exponent(value); eval; eval >>= 4) {
                buffer[i--] = (eval & 0xFU) + uppercase;
            }

            buffer[i--] = "p"[0] + uppercase;

            // fraction
            for (u32 fval = f64_mantissa(value); fval; fval >>= 4) {
                buffer[i--] = (fval & 0xFU) + uppercase;
            }

            buffer[i--] = "."[0];

            // integer
            buffer[i--] = f64_is_normal(value) ? "1"[0] : "0"[0];
            buffer[i--] = "x"[0];
            buffer[i--] = "0"[0];
        } else {
            bool is_scientific = (format.type == "E"[0] || format.type == "e"[0]);

            if (format.type == "G"[0] || format.type == "g"[0]) {
                u32 scientific_width = 0;
                u32 fixedpoint_width = 0;
                is_scientific = scientific_width > fixedpoint_width;
            }

            // adjust
            // round

            if (is_scientific) {

                // exponent
                u32 eval = 0;

                do {
                    buffer[i--] = (eval % 10) + "0"[0];
                } while (eval /= 10);

                buffer[i--] = "e"[0] + uppercase;
            }

            // fraction
            u64 fval = 0;

            do {
                buffer[i--] = (fval % 10) + "0"[0];
            } while (fval /= 10);

            // integer
            u64 ival = 0;

            do {
                buffer[i--] = (ival % 10) + "0"[0];
            } while (ival /= 10);
        }

        // Print the value.
        PrintFormat fmt = {
            width = format.width;
            align = format.align;
            fill = format.fill;
        };

        // Print the sign.
        if (is_negative) {
            if (fmt.align == "="[0]) {
                fmt.align = ">"[0];

                if (fmt.width > 0) {
                    fmt.width -= 1;
                }

                write_char(printable, "-"[0]);
            } else {
                buffer[i--] = "-"[0];
            }
        }

        return print_buffer(printable, format, buffer, 65 - i);
    }






























    void vprint_char(PrintFormat &format, ... &args) {
        if (!format.align) {
            format.align = "<"[0];
        }

        return print_char(printable, format, va_arg(*args, u32));
    }


    void vprint_str(PrintFormat &format, ... &args) {
        if (!format.align) {
            format.align = "<"[0];
        }

        return print_str(printable, format, va_arg(*args, const char *));
    }


    void vprint_bool(PrintFormat &format, ... &args) {
        if (!format.align) {
            format.align = "<"[0];
        }

        return print_bool(printable, format, va_arg(*args, u32));
    }


    void vprint_pointer(PrintFormat &format, ... &args) {
        if (!format.align) {
            format.align = "<"[0];
        }

        return print_bool(printable, format, va_arg(*args, u32));
    }


    void vprint_memory(PrintFormat &format, ... &args) {
        return print_memory(printable, format, va_arg(*args, u32), va_arg(*args, const u8 *), va_arg(*args, u32));
    }


    void vprint_integer(PrintFormat &format, ... &args) {
        if (!format.align) {
            format.align = ">"[0];
        }

        if (format.type == "o"[0]) {
            format.base = 8;
        } else if (format.type == "X"[0] || format.type == "x"[0]) {
            format.base = 16;
        }

        return print_integer(printable, format, format.type_width == 64 ? va_arg(*args, u64) : va_arg(*args, u32));
    }


    void vprint_float(PrintFormat &format, ... &args) {
        if (!format.align) {
            format.align = ">"[0];
        }

        return print_float(printable, format, va_arg(*args, double));
    }


    void vprint_value(PrintFormat &format, ... &args) {
        if (!format.align) {
            format.align = ">"[0];
        }

        return print_value(printable, format, va_arg(*args, double), bias);
    }






    void print(const String &format, ... args) {
        u32 i = 0;

        while (*format) {

            // Copy litteral characters from the format string.
            if (*format != "{"[0]) {
                print(inst, *format++);
                i += 1;
                continue;
            }

            format += 1;

            // Check for a litteral "{"[0] character.
            if (*format == "{"[0]) {
                print(inst, *format++);
                i += 1;
                continue;
            }

            // Parse the alignment flag from the format string.
            PrintFormat fmt;
            u32 n;

            if (print_format_parse(&fmt, format, &n, args)) {
                return RESULT_FAILURE;
            }

            format += n;

            if (fmt.type == "n"[0]) {
                *va_arg(*args, u32 *) = i;
            } else if (type < 52) {

                // Custom format function.
                if (va_arg(*args, format_print_f)(this, print, &fmt, args)) {
                    return RESULT_FAILURE;
                }
            }
        }

        return RESULT_SUCCESS;
    }
}
