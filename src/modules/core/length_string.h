#pragma once

#include "karma.h"

constexpr u32 HIGH_SURROGATE_CODEPOINT_FIRST = 0xD800;
constexpr u32 HIGH_SURROGATE_CODEPOINT_LAST  = 0xDBFF;
constexpr u32 LOW_SURROGATE_CODEPOINT_FIRST  = 0xDC00;
constexpr u32 LOW_SURROGATE_CODEPOINT_LAST   = 0xDFFF;

#define string_cstr(string) ((char *)((string).data))

struct Utf32_Codepoint {
	utf32 code;
	u8    size_in_bytes;
};

struct String_Iter {
	Utf32_Codepoint codepoint = {};
	s64             index     = 0;
};

struct String_Search_Result {
	bool found;
	s64  start_index;
};

s64             string_utf8_length(const String str);
Utf32_Codepoint utf8_to_utf32(const utf8 *character);
u8              utf32_to_utf8(utf32 codepoint, utf8 buffer[4]);
bool            codepoint_is_surrogate(utf32 codepoint);
bool            string_iter_continue(const String string, String_Iter *iter);
bool            string_iter_next(const String string, String_Iter *iter);

// TODO: Implement these with Unicode String Normalization!
bool                 string_match(const String a, const String b);
int                  string_compare(const String a, const String b);
bool                 string_starts_with(const String a, const String b);
bool                 string_ends_with(const String a, const String b);
String               string_substring(const String string, s64 index, s64 count);
String_Search_Result string_isearch(const String string, const String item, s64 index = 0);
String_Search_Result string_isearch_reverse(const String string, const String item);

String      sprintf(String string, ANALYSE_PRINTF_FORMAT_STRING(const char *fmt), ...) ANALYSE_PRINTF_FORMAT(2, 3);
String      mprintf(ANALYSE_PRINTF_FORMAT_STRING(const char *fmt), ...) ANALYSE_PRINTF_FORMAT(1, 2);
String      tprintf(ANALYSE_PRINTF_FORMAT_STRING(const char *fmt), ...) ANALYSE_PRINTF_FORMAT(1, 2);
const char *null_tprintf(ANALYSE_PRINTF_FORMAT_STRING(const char *fmt), ...) ANALYSE_PRINTF_FORMAT(1, 2);
String      vsprintf(String string, ANALYSE_PRINTF_FORMAT_STRING(char const *fmt), va_list va);
String      vmprintf(ANALYSE_PRINTF_FORMAT_STRING(char const *fmt), va_list va);
String      vtprintf(ANALYSE_PRINTF_FORMAT_STRING(char const *fmt), va_list va);
char *      tto_cstring(String string);
char *      to_cstring(String string);
String      string_copy(String string);
String      string_tcopy(String string);
String      string_concat(String a, String b);
String      string_concat(Array_View<String> strings);
String      string_tconcat(String a, String b);
String      string_tconcat(Array_View<String> strings);
