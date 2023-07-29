///
/// Dynamic String
///
/// The String object uses heap memory to store NULL terminated strings.
/// Strings are created with string_init(), string_from_str(), or string_copy()
/// The primary operations for strings are apending, inserting, removing, and
/// finding characters and substrings.
///
/// Other operations include resizeing the capacity of the string for
/// preallocation.
///
#ifndef DUST_STRING_H
#define DUST_STRING_H

#include <dust/str.h>
#include <dust/memory.h>
#include <dust/parse.h>
#include <dust/print.h>
#include <dust/common.h>


/// \brief A string.
typedef struct string {
    char *str;     // The C string.
    u32 capacity;  // The allocated capacity (Does not include the null terminator)
    u32 size;      // The size of the string (Does not include the null terminator)
} String;


/// \brief Initialize a string.
/// \param this The string to initialize
/// \param capacity The initial capacity of the string
result_t string_init(String *this, u32 capacity);


/// \brief Initialize a string from a C string.
/// \param this The string to initialize
/// \param str The string to copy
result_t string_from_str(String *restrict this, const char *restrict str);


/// \brief Initialize a string from a C string.
/// \param this The string to initialize
/// \param str The string to copy
result_t string_from_str_max(String *restrict this, const char *restrict str, u32 max);


/// \brief Initialize a string from another string.
/// \param this The string to initialize
/// \param other The string to copy
result_t string_copy(String *restrict this, const String *restrict other);


/// \brief Free the string.
/// \param this The string to free
inline void string_free(String *this) {
    memory_free(this->str);
}


/// \brief Check if the string is empty.
/// \param this The string to test
/// \return true if the string is empty
///         false if the string is not empty
inline bool string_is_empty(const String *this) {
    return this->size == 0;
}


/// \brief Check if the string is empty.
/// \param this The string to test
/// \return true if the string is empty
///         false if the string is not empty
inline u32 string_space(const String *this) {
    return this->capacity - this->size;
}


/// \brief Clear the string.
/// \param this The string to clear
inline void string_clear(String *this) {
    this->str[0] = '\0';
    this->size = 0;
}


/// \brief Return the length of the string.
/// \param str The string to process
/// \return The number of characters in the string
inline u32 string_size(const String *this) {
    return this->size;
}


/// \brief Return the length of the string up to a maximun number of
/// characters.
/// \param str The string to process
/// \param max The maximum number of characters to process
/// \return The number of characters in the string
inline u32 string_size_max(const String *this, u32 max) {
    return u32_min(this->size, max);
}


/// \brief Increase the capacity of the string.
/// \param this The string to resize
/// \param size The minimum size
inline result_t string_resize(String *this, u32 size) {
    if (size <= this->capacity) {
        return RESULT_SUCCESS;
    }

    u32 capacity = this->capacity + 1;

    do {
        capacity *= 2;
    } while (capacity <= size);

    BUBBLE(memory_reallocate(&this->str, capacity));
    this->capacity = capacity - 1;
    this->size = size;
    return RESULT_SUCCESS;
}


/// \brief Swap the values of two strings.
/// \param this The first string
/// \param other The second string
void string_swap(String *restrict this, String *restrict other) {
    ptr_swap(&this->str, &other->str);
    u32_swap(&this->capacity, &other->capacity);
    u32_swap(&this->size, &other->size);
}


/// \brief Append a string to the string.
/// \param this The string to which to append
/// \param buffer The string to append
result_t string_append(String *restrict this, const char *restrict buffer, u32 size);


/// \brief Append a character to the string.
/// \param this The string to which to append
/// \param ch The character to append
result_t string_append_char(String *this, char ch);


/// \brief Append a string to the string.
/// \param this The string to which to append
/// \param str The string to append
result_t string_append_str(String *restrict this, const char *restrict str);


/// \brief Append a string to the string.
/// \param this The string to which to append
/// \param str The string to append
result_t string_append_str_max(String *restrict this, const char *restrict str, u32 max);


/// \brief Append a string to the string.
/// \param this The string to which to append
/// \param other The string to append
result_t string_append_string(String *restrict this, const String *restrict other);


/// \brief Insert a character into the string at an index.
/// \param this The string to modify
/// \param index The index at which to insert the character
/// \param ch The character to insert
/// \return RESULT_SUCCESS if the character has been inserted successfully;
///         RESULT_FAILURE if the character could not be inserted
result_t string_insert_char(String *this, u32 index, char ch);


/// \brief Insert a string into the string at an index.
/// \param this the string to process
/// \param index The index at which to insert the string
/// \param str The string to insert
result_t string_insert_str(String *restrict this, u32 index, const char *restrict str);


/// \brief Insert a string into the string at an index.
/// \param this the string to process
/// \param index The index at which to insert the string
/// \param other The string to insert
result_t string_insert_string(String *restrict this, u32 index, const String *restrict other);


/// \brief Remove a range of characters from the string.
/// \param this The string from which to remove
/// \param index The number of characters to remove
/// \param count The number of characters to remove
void string_remove(String *restrict this, u32 index, u32 count);


void string_remove_char(String *restrict this, char ch);


void string_remove_chars(String *restrict this, const char *restrict chars);


void string_remove_substr(String *restrict this, const char *restrict substr);


void string_remove_substrs(String *restrict this, const char **restrict substrs);


void string_replace_char(String *restrict this, char ch, char value) {
    str_replace_char(this->str, ch, value);
}


void string_replace_chars(String *restrict this, const char *restrict chars, char value) {
    str_replace_chars(this->str, chars, value);
}


void string_replace_chars_list(String *restrict this, const char *restrict chars, const char *restrict values) {
    str_replace_chars_list(this->str, chars, values);
}


result_t string_slice(const String *restrict this, String *restrict other, u32 start, u32 end);


result_t string_fill(String *this, char ch, u32 index, u32 size);


/// \brief Reverse the characters in the string.
/// \param this the string to process
inline void string_reverse(String *this) {
    for (u32 i = 0; i < this->size / 2; i++) {
        char_swap(&this->str[i], &this->str[this->size - i]);
    }
}


/// \brief Convert the all alphabet characters in the string to uppercase.
/// \param this The string to process
inline void string_to_upper(String *this) {
    str_to_upper(this->str);
}


/// \brief Convert the all alphabet characters in the string to uppercase.
/// \param this The string to process
/// \param max The maximum number of characters to process
inline void string_to_upper_max(String *this, u32 max) {
    for (u32 i = 0; i < u32_min(this->size, max); i++) {
        if (char_is_lower(this->str[i])) {
            this->str[i] -= 'a' - 'A';
        }
    }
}


/// \brief Convert the all alphabet characters in the string to lowercase.
/// \param this the string to process
inline void string_to_lower(String *this) {
    str_to_lower(this->str);
}


/// \brief Convert the all alphabet characters in the string to lowercase.
/// \param this the string to process
/// \param max the maximum number of characters to process
inline void string_to_lower_max(String *this, u32 max) {
    for (u32 i = 0; i < u32_min(this->size, max); i++) {
        if (char_is_upper(this->str[i])) {
            this->str[i] += 'a' - 'A';
        }
    }
}


inline bool string_contains_char(const String *this, char ch) {
    return str_contains_char(this->str, ch);
}


inline result_t string_find_char(const String *restrict this, u32 *restrict index, char ch) {
    return str_find_char(this->str, index, ch);
}


inline result_t string_find_char_max(const String *restrict this, u32 *restrict index, char ch, u32 max) {
    return str_find_char_max(this->str, index, ch, max);
}


inline result_t string_find_last_char(const String *restrict this, u32 *restrict index, char ch) {
    for (u32 i = this->size; i-- > 0;) {
        if (this->str[i] == ch) {
            *index = i;
            return RESULT_SUCCESS;
        }
    }

    return RESULT_FAILURE;
}


inline result_t string_find_last_char_max(const String *restrict this, u32 *restrict index, char ch, u32 max) {
    for (u32 i = this->size; i-- > 0;) {
        if (this->str[i] == ch) {
            *index = i;
            return RESULT_SUCCESS;
        }
    }

    return RESULT_FAILURE;
}


inline result_t string_find_str(const String *restrict this, u32 *restrict index, const char *restrict substr) {
    return str_find_str(this->str, index, substr);
}


inline result_t string_find_str_max(const String *restrict this, u32 *restrict index, const char *restrict substr, u32 max) {
    return str_find_str_max(this->str, index, substr, max);
}


inline result_t string_find_string(const String *restrict this, u32 *restrict index, const String *restrict substring) {
    return str_find_str(this->str, index, substring->str);
}


inline result_t string_find_string_max(const String *restrict this, u32 *restrict index, const String *restrict substring, u32 max) {
    return str_find_str_max(this->str, index, substring->str, max);
}


inline result_t string_substring(const String *restrict this, String *restrict copy, u32 max);


/// \brief Compare two strings.
/// \param this The first string
/// \param other The second string
/// \return 0 if 'this' == 'other'
///         posative if 'this' >  'other'
///         negative if 'this' <  'other'
inline i32 string_compare(const String *restrict this, const String *restrict other) {
    return str_compare(this->str, other->str);
}


inline i32 string_compare_max(const String *this, const String *other, u32 max) {
    return str_compare_max(this->str, other->str, max);
}


inline bool string_is_equ(const String *this, const String *other) {
    return str_is_equ(this->str, other->str);
}


inline bool string_is_neq(const String *this, const String *other) {
    return str_is_neq(this->str, other->str);
}


inline bool string_is_les(const String *this, const String *other) {
    return str_is_les(this->str, other->str);
}


inline bool string_is_leq(const String *this, const String *other) {
    return str_is_leq(this->str, other->str);
}


inline bool string_is_gtr(const String *this, const String *other) {
    return str_is_gtr(this->str, other->str);
}


inline bool string_is_geq(const String *this, const String *other) {
    return str_is_geq(this->str, other->str);
}


inline bool string_is_equ_max(const String *this, const String *other, u32 max) {
    return str_is_equ_max(this->str, other->str, max);
}


inline bool string_is_neq_max(const String *this, const String *other, u32 max) {
    return str_is_neq_max(this->str, other->str, max);
}


inline bool string_is_les_max(const String *this, const String *other, u32 max) {
    return str_is_les_max(this->str, other->str, max);
}


inline bool string_is_leq_max(const String *this, const String *other, u32 max) {
    return str_is_leq_max(this->str, other->str, max);
}


inline bool string_is_gtr_max(const String *this, const String *other, u32 max) {
    return str_is_gtr_max(this->str, other->str, max);
}


inline bool string_is_geq_max(const String *this, const String *other, u32 max) {
    return str_is_geq_max(this->str, other->str, max);
}


inline u32 string_hash(const String *this) {
    return str_hash(this->str);
}


inline u32 string_hash_max(const String *this, u32 max) {
    return str_hash_max(this->str, max);
}



















///
/// Parseable
///


///
inline result_t string_vparse(const String *restrict this, const char *restrict format, va_list *restrict args) {
    return parseable_vparse(this->str, format, args);
}


///
inline result_t string_parse(const String *restrict this, const char *restrict format, ...) {
    va_list args;
    va_start(args, format);
    result_t res = string_vparse(this, format, &args);
    va_end(args);
    return res;
}


///
/// Printable
///


extern PrintableVTable string_printable_vtable; // 


inline void printable_from_string(Printable *printable, String *string) {
    printable->derived = string;
    printable->vtable = &string_printable_vtable;
}


///
inline result_t string_vprint(String *restrict this, const char *restrict format, va_list *args) {
    Printable printable;
    printable_init(&printable, this, &string_printable_vtable);
    return printable_vprint(&printable, format, args);
}


///
inline result_t string_print(String *restrict this, const char *restrict format, ...) {
    va_list args;
    va_start(args, format);
    result_t res = string_vprint(this, format, args);
    va_end(args);
    return res;
}


#endif
