#include <dust/string.h>
#include <dust/str.h>
#include <dust/memory.h>
#include <dust/common.h>


PrintableVTable string_printable_vtable = {
    .write_char = string_append_char,
    .write_str = string_append_str,
    .write_str_max = string_append_str_max,
};


result_t string_init(String *string, u32 capacity) {
    BUBBLE(memory_allocate(&string->str, capacity + 1));
    string->capacity = capacity;
    string->size = 0;
    string->str[0] = '\0';
    return RESULT_SUCCESS;
}


result_t string_from_str(String *restrict string, const char *restrict str) {
    string->capacity = str_size(str);
    BUBBLE(memory_allocate(&string->str, string->capacity + 1));
    string->size = string->capacity;
    memory_copy(string->str, str, string->size + 1);
    return RESULT_SUCCESS;
}


result_t string_from_str_max(String *restrict string, const char *restrict str, u32 max) {
    string->capacity = u32_min(max, str_size(str));
    BUBBLE(memory_allocate(&string->str, string->capacity + 1));
    string->size = string->capacity;
    memory_copy(string->str, str, string->size);
    string->str[string->size] = '\0';
    return RESULT_SUCCESS;
}


result_t string_copy(String *restrict string, const String *restrict other) {
    string->capacity = other->capacity;
    string->size = other->size;
    BUBBLE(memory_allocate(&string->str, string->capacity + 1));
    memory_copy(string->str, other->str, string->size + 1);
    return RESULT_SUCCESS;
}


extern inline void string_to_upper(String *string);
extern inline void string_to_upper_max(String *string, u32 max);
extern inline void string_to_lower(String *string);
extern inline void string_to_lower_max(String *string, u32 max);


result_t string_fill(String *string, char ch, u32 index, u32 size) {
    size = u32_min(string->size, index + size);
    BUBBLE(string_resize(string, size));
    string->size = size;

    for (u32 i = index; i < size; i++) {
        string->str[i] = ch;
    }

    string->str[size] = '\0';
    return RESULT_SUCCESS;
}


result_t string_append_char(String *string, char ch) {
    BUBBLE(string_resize(string, string->size + 1));
    string->str[string->size] = ch;
    string->size += 1;
    string->str[string->size] = '\0';
    return RESULT_SUCCESS;
}


result_t string_append_str(String *restrict string, const char *restrict str) {
    u32 size = str_copy_max(&string->str[string->size], str, string->capacity - string->size);
    string->size += size;

    if (str[size] != '\0') {
        str = &str[size];
        size = str_size(str);
        BUBBLE(string_resize(string, string->size + size));
        memory_copy(&string->str[string->size], str, size);
        string->size += size;
        string->str[string->size] = '\0';
    }

    return RESULT_SUCCESS;
}


result_t string_append_str_max(String *restrict string, const char *restrict str, u32 max) {
    u32 size = str_copy_max(&string->str[string->size], str, string->capacity - string->size);
    string->size += size;

    if (str[size] != '\0') {
        str = &str[size];
        size = str_size_max(str, max - size);
        BUBBLE(string_resize(string, string->size + str_size(str)));
        memory_copy(&string->str[string->size], str, size);
        string->size += size;
    }

    string->str[string->size] = '\0';
    return RESULT_SUCCESS;
}


result_t string_append_string(String *restrict string, const String *restrict other) {
    BUBBLE(string_resize(string, string->size + other->size));
    memory_copy(&string->str[string->size], other->str, other->size);
    string->size += other->size;
    string->str[string->size] = '\0';
    return RESULT_SUCCESS;
}


result_t string_insert_char(String *string, u32 index, char ch) {
    BUBBLE(string_resize(string, string->size + 1));
    memory_move(&string->str[index], &string->str[index + 1], string->size - index);
    string->size += 1;
    return RESULT_SUCCESS;
}


result_t string_insert_str(String *restrict string, u32 index, const char *restrict str) {
    u32 size = str_size(str);
    BUBBLE(string_resize(string, string->size + size));
    memory_move(&string->str[index], &string->str[index + size], string->size - index);
    string->size += size;
    return RESULT_SUCCESS;
}


result_t string_insert_string(String *restrict string, u32 index, const String *restrict other) {
    BUBBLE(string_resize(string, string->size + other->size));
    memory_move(&string->str[index], &string->str[index + other->size], string->size - index);
    string->size += other->size;
    return RESULT_SUCCESS;
}


void string_remove(String *restrict string, u32 index, u32 count) {
    memory_move(&string->str[index], &string->str[index + count], string->size - index - count);
}




void string_remove(String *restrict string, u32 index, u32 count) {
    memory_move(&string->str[index], &string->str[index + count], string->size - index);
}


void string_remove_char(String *restrict string, char ch) {
    u32 j = 0;

    for (u32 i = 0; i < string->size; i++) {
        if (string->str[i] != ch) {
            string->str[j] = string->str[i];
            j += 1;
        }
    }

    string->size = j;
    string->str[j] = '\0';
}


void string_remove_chars(String *restrict string, const char *restrict chars) {
    u32 j = 0;

    for (u32 i = 0; i < string->size; i++, j++) {
        string->str[j] = string->str[i];

        for (const char *ch = chars; *ch; ch++) {
            if (string->str[i] == *ch) {
                j -= 1;
                break;
            }
        }
    }

    string->size = j;
    string->str[j] = '\0';
}


void string_remove_substr(String *restrict string, const char *restrict substr) {
    u32 j = 0;

    for (u32 i = 0; i < string->size; i++, j++) {
        string->str[j] = string->str[i];

        for (const char *ch = substr; *ch; ch++) {
            if (string->str[i] == *ch) {
                j -= 1;
                break;
            }
        }
    }

    string->size = j;
    string->str[j] = '\0';
}


void string_remove_substrs(String *restrict string, const char **restrict substrs) {
    ;
}


void string_replace_char(String *restrict string, char ch, char value) {
    for (u32 i = 0; i < string->size; i++) {
        if (string->str[i] == ch) {
            string->str[i] = value;
        }
    }
}


void string_replace_chars(String *restrict string, const char *restrict chars, char value) {
    for (u32 i = 0; i < string->size; i++) {
        for (const char *ch = chars; *ch; ch++) {
            if (string->str[i] == *ch) {
                string->str[i] = value;
                break;
            }
        }
    }
}


void string_replace_chars_list(String *restrict string, const char *restrict chars, const char *restrict values) {
    for (u32 i = 0; i < string->size; i++) {
        for (u32 j = 0; chars[j]; j++) {
            if (string->str[i] == chars[j]) {
                string->str[i] = values[j];
                break;
            }
        }
    }
}


result_t string_slice(const String *restrict string, String *restrict other, u32 start, u32 end) {
    other->capacity = start - end;
    other->size = other->capacity;
    BUBBLE(memory_allocate(&other->str, other->capacity + 1));
    memory_copy(string->str, other->str, other->size + 1);
    other->str[other->size] = '\0';
    return RESULT_SUCCESS;
}


extern inline i32 string_compare(const String *restrict string, const String *restrict other);
extern inline bool string_equ(const String *restrict string, const String *restrict other);
extern inline bool string_neq(const String *restrict string, const String *restrict other);
extern inline bool string_les(const String *restrict string, const String *restrict other);
extern inline bool string_leq(const String *restrict string, const String *restrict other);
extern inline bool string_gtr(const String *restrict string, const String *restrict other);
extern inline bool string_geq(const String *restrict string, const String *restrict other);

extern inline i32 string_compare_max(const String *restrict string, const String *restrict other, u32 max);
extern inline bool string_equ_max(const String *restrict string, const String *restrict other, u32 max);
extern inline bool string_neq_max(const String *restrict string, const String *restrict other, u32 max);
extern inline bool string_les_max(const String *restrict string, const String *restrict other, u32 max);
extern inline bool string_leq_max(const String *restrict string, const String *restrict other, u32 max);
extern inline bool string_gtr_max(const String *restrict string, const String *restrict other, u32 max);
extern inline bool string_geq_max(const String *restrict string, const String *restrict other, u32 max);

extern inline u32 string_hash(const String *string);
extern inline u32 string_hash_max(const String *string, u32 max);
