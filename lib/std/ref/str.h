///
/// C String
///
#ifndef DUST_STR_H
#define DUST_STR_H

#include <dust/print.h>
#include <dust/parse.h>
#include <dust/char.h>
#include <dust/common.h>


/// \brief Return true if the string is empty.
/// \param this The string to process
/// \param max The maximum number of characters to process
/// \return true if the string is empty
///         false if the string contains characters
inline bool str_is_empty(const char *this) {
    return *this == '\0';
}


/// \brief Clear the string.
/// \param this The string to clear
inline void str_clear(char *this) {
    *this = '\0';
}


/// \brief Return the length of the string.
/// \param this The string to process
/// \return The number of characters in the string
inline u32 str_size(const char *this) {
    u32 i = 0;
    for (; this[i]; i++);
    return i;
}


/// \brief Return the length of the string up to a maximum number of
/// characters.
/// \param this The string to process
/// \param max The maximum number of characters to process
/// \return The number of characters in the string
inline u32 str_size_max(const char *this, u32 max) {
    u32 i = 0;
    for (; i < max && this[i]; i++);
    return i;
}


/// \brief Convert all alphabet characters in the string to uppercase.
/// \param this The string to process
inline void str_to_upper(char *this) {
    for (; *this; this++) {
        if (char_is_lower(*this)) {
            *this -= 'a' - 'A';
        }
    }
}


/// \brief Convert all alphabet characters in the string to uppercase.
/// \param this The string to process
/// \param max The maximum number of characters to process
inline void str_to_upper_max(char *this, u32 max) {
    for (u32 i = 0; i < max && this[i]; i++) {
        if (char_is_lower(*this)) {
            *this -= 'a' - 'A';
        }
    }
}


/// \brief Convert all alphabet characters in the string to lowercase.
/// \param this The string to process
inline void str_to_lower(char *this) {
    for (; *this; this++) {
        if (char_is_upper(*this)) {
            *this += 'a' - 'A';
        }
    }
}


/// \brief Convert all alphabet characters in the string to lowercase.
/// \param this The string to process
/// \param max The maximum number of characters to process
inline void str_to_lower_max(char *this, u32 max) {
    for (u32 i = 0; i < max && this[i]; i++) {
        if (char_is_upper(*this)) {
            *this += 'a' - 'A';
        }
    }
}


/// \param this The string to process
inline void str_fill(char *this, char ch) {
    for (; *this; this++) {
        *this = ch;
    }
}


/// \param this The string to fill
/// \param max The maximum number of characters to process
inline void str_fill_max(char *this, char ch, u32 max) {
    for (u32 i = 0; i < max && this[i]; i++) {
        this[i] = ch;
    }
}


/// \brief Copy all characters from the first string to the second.
/// \param this The string from which to read
/// \param other The string to which to write
/// \return The number of characters copied
inline u32 str_copy(char *restrict this, const char *restrict other) {
    u32 i = 0;
    for (; (this[i] = other[i]); i++);
    return i;
}


/// \brief Copy up to max characters from the first string to the second.
/// \param this The string from which to read
/// \param other The string to which to write
/// \param max The maximum number of characters to copy
/// \return The number of characters copied
inline u32 str_copy_max(char *restrict this, const char *restrict other, u32 max) {
    u32 i = 0;
    for (; i < max && (this[i] = other[i]); i++);
    this[i] = '\0';
    return i;
}


/// \brief Compute the hash of the string.
/// \param this The string to process
/// \param max The maximum number of characters to process
u32 str_hash(const char *this);


/// \brief Compute the hash of the string up to the given number of characters.
/// \param this The string to process
/// \param max The maximum number of characters to process
u32 str_hash_max(const char *this, u32 max);


///
/// String Searching
///


/// \brief Get the index of the first given character in the string.
/// \param this The string to search
/// \param index The index of the character if found, unchanged otherwise
/// \param ch The character for which to search
/// \return RESULT_SUCCESS if the character has been found
///         RESULT_FAILURE if the character was not found
result_t str_find_char(const char *restrict this, u32 *restrict index, char ch);


/// \brief Get the index of the first given character in the string.
/// \param this The string to search
/// \param index The index of the character if found, unchanged otherwise
/// \param ch The character for which to search
/// \param max The maximum number of characters to process
/// \return RESULT_SUCCESS if the character has been found
///         RESULT_FAILURE if the character was not found
result_t str_find_char_max(const char *restrict this, u32 *restrict index, char ch, u32 max);


/// \brief Get the index of the first of any of the given characters in the
/// string.
/// \param this The string to search
/// \param index The index of the character if found, unchanged otherwise
/// \param chars The characters for which to search
/// \return RESULT_SUCCESS if a character has been found
///         RESULT_FAILURE if a character was not found
result_t str_find_chars(const char *restrict this, u32 *restrict index, const char *restrict chars);


/// \brief Get the index of the first of any of the given characters in the
/// string.
/// \param this The string to search
/// \param index The index of the character if found, unchanged otherwise
/// \param chars The characters for which to search
/// \param max The maximum number of characters to process
/// \return RESULT_SUCCESS if a character has been found
///         RESULT_FAILURE if a character was not found
result_t str_find_chars_max(const char *restrict this, u32 *restrict index, const char *restrict chars, u32 max);


/// \brief Get the index of the first given substring in the string.
/// \param this The string to search
/// \param index The index of the substring if found, unchanged otherwise
/// \param substr The substring for which to search
/// \return RESULT_SUCCESS if the substring has been found
///         RESULT_FAILURE if the substring was not found
result_t str_find_str(const char *restrict this, u32 *restrict index, const char *restrict substr);


/// \brief Get the index of the first given substring in the string.
/// \param this The string to search
/// \param index The index of the substring if found, unchanged otherwise
/// \param substr The substring for which to search
/// \param max The maximum number of characters to process
/// \return RESULT_SUCCESS if the substring has been found
///         RESULT_FAILURE if the substring was not found
result_t str_find_str_max(const char *restrict this, u32 *restrict index, const char *restrict substr, u32 max);


/// \brief Get the index of the first given substring in the string.
/// \param this The string to search
/// \param index The index of the substring if found, unchanged otherwise
/// \param substrs The NULL terminated list of substrings for which to search
/// \return RESULT_SUCCESS if a substring has been found
///         RESULT_FAILURE if a substring was not found
result_t str_find_strs(const char *restrict this, u32 *restrict index, const char **restrict substrs);


/// \brief Get the index of the first given substring in the string.
/// \param this The string to search
/// \param max The maximum number of characters to process
/// \param index The index of the substring if found, unchanged otherwise
/// \param substrs The NULL terminated list of substrings for which to search
/// \return RESULT_SUCCESS if a substring has been found
///         RESULT_FAILURE if a substring was not found
result_t str_find_strs_max(const char *restrict this, u32 *restrict index, const char **restrict substrs, u32 max);


void str_replace_char(char *restrict this, char ch, char value) {
    for (; *this; this++) {
        if (*this == ch) {
            *this = value;
        }
    }
}


void str_replace_chars(char *restrict this, const char *restrict chars, char value) {
    for (; *this; this++) {
        for (const char *ch = chars; *ch; ch++) {
            if (*this == *ch) {
                *this = value;
                break;
            }
        }
    }
}


void str_replace_chars_list(char *restrict this, const char *restrict chars, const char *restrict values) {
    for (; *this; this++) {
        for (u32 j = 0; chars[j]; j++) {
            if (*this == chars[j]) {
                *this = values[j];
                break;
            }
        }
    }
}


///
/// String Comparison
///


/// Compares two strings. Returns the ordinal difference between 'string' and 'other'.
// Returns:
//  u8 -  0 if 'this' == 'other'
//             1 if 'this' >  'other'
//            -1 if 'this' <  'other'
i32 str_compare(const char *restrict this, const char *restrict other);


/// \brief Test if the first string is equal to the other.
/// \param this The first string
/// \param other The second string
/// \return true if the first string is equal to the second string
inline bool str_is_equ(const char *this, const char *other) {
    return str_compare(this, other) == 0;
}


/// \brief Test if the first string is not equal to the other.
/// \param this The first string
/// \param other The second string
/// \return true if the first string is not equal to the second string
inline bool str_is_neq(const char *this, const char *other) {
    return str_compare(this, other) != 0;
}


/// \brief Test if the first string is less than the other.
/// \param this The first string
/// \param other The second string
/// \return true if the first string is less than the second string
inline bool str_is_les(const char *this, const char *other) {
    return str_compare(this, other) < 0;
}


/// \brief Test if the first string is less than or equal to the other.
/// \param this The first string
/// \param other The second string
/// \return true if the first string is less than or equal to the second string
inline bool str_is_leq(const char *this, const char *other) {
    return str_compare(this, other) <= 0;
}


/// \brief Test if the first string is greater than the other.
/// \param this The first string
/// \param other The second string
/// \return true if the first string is greater than the second string
inline bool str_is_gtr(const char *this, const char *other) {
    return str_compare(this, other) > 0;
}


/// \brief Test if the first string is greater than or equal to the other.
/// \param this The first string
/// \param other The second string
/// \return true if the first string is greater than or equal to the second string
inline bool str_is_geq(const char *this, const char *other) {
    return str_compare(this, other) >= 0;
}


i32 str_compare_max(const char *restrict this, const char *restrict other, u32 max);


/// \brief Test if the first string is equal to the other.
/// \param this The first string
/// \param other The second string
/// \param max The maximum number of characters to test
/// \return true if the first string is equal to the second string
inline bool str_is_equ_max(const char *this, const char *other, u32 max) {
    return str_compare_max(this, other, max) == 0;
}


/// \brief Test if the first string is not equal to the other.
/// \param this The first string
/// \param other The second string
/// \param max The maximum number of characters to test
/// \return true if the first string is not equal to the second string
inline bool str_is_neq_max(const char *this, const char *other, u32 max) {
    return str_compare_max(this, other, max) != 0;
}


/// \brief Test if the first string is less than the other.
/// \param this The first string
/// \param other The second string
/// \param max The maximum number of characters to test
/// \return true if the first string is less than the second string
inline bool str_is_les_max(const char *this, const char *other, u32 max) {
    return str_compare_max(this, other, max) < 0;
}


/// \brief Test if the first string is less than or equal to the other.
/// \param this The first string
/// \param other The second string
/// \param max The maximum number of characters to test
/// \return true if the first string is less than or equal to the second string
inline bool str_is_leq_max(const char *this, const char *other, u32 max) {
    return str_compare_max(this, other, max) <= 0;
}


/// \brief Test if the first string is greater than the other.
/// \param this The first string
/// \param other The second string
/// \param max The maximum number of characters to test
/// \return true if the first string is greater than the second string
inline bool str_is_gtr_max(const char *this, const char *other, u32 max) {
    return str_compare_max(this, other, max) > 0;
}


/// \brief Test if the first string is greater than or equal to the other.
/// \param this The first string
/// \param other The second string
/// \param max The maximum number of characters to test
/// \return true if the first string is greater than or equal to the second string
inline bool str_is_geq_max(const char *this, const char *other, u32 max) {
    return str_compare_max(this, other, max) >= 0;
}


///
result_t str_vparse(const char *restrict this, const char *restrict format, va_list *args);


///
inline result_t str_parse(const char *restrict this, const char *restrict format, ...) {
    va_list args;
    va_start(args, format);
    result_t res = str_vparse(this, format, &args);
    va_end(args);
    return res;
}


///
result_t str_vprint(char *restrict this, u32 max, const char *restrict format, va_list *args);


///
inline result_t str_print(char *restrict this, u32 max, const char *restrict format, ...) {
    va_list args;
    va_start(args, format);
    result_t res = str_vprint(this, max, format, &args);
    va_end(args);
    return res;
}


#endif
