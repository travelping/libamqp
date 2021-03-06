/*
   Copyright 2011-2012 StormMQ Limited

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
 */

#include <stdio.h>

#include "Codec/Type/EncodingMetaData.h"
#include "Codec/Type/TypeMethods.h"
#include "Codec/Decode/Decode.h"
#include "Codec/Type/Type.h"

const char *amqp_category_names[] = {
    "fixed",
    "variable",
    "compound",
    "array"
};



amqp_encoding_meta_data_t amqp_type_meta_data_described = {
    0x00,
    0,
    amqp_decode_described_type,
    &amqp_methods_described,
    "described",
    "",
    amqp_is_composite, AMQP_TYPE_CATEGORY_COMPOUND,
};
amqp_encoding_meta_data_t amqp_type_meta_data_null = {
    0x40,
    0,
    amqp_decode_null,
    &amqp_methods_null,
    "null",
    "",
    amqp_is_null, AMQP_TYPE_CATEGORY_FIXED,
};
amqp_encoding_meta_data_t amqp_type_meta_data_boolean_true = {
    0x41,
    0,
    amqp_decode_boolean_true,
    &amqp_methods_boolean_true,
    "boolean",
    "true",
    amqp_is_boolean, AMQP_TYPE_CATEGORY_FIXED,
};
amqp_encoding_meta_data_t amqp_type_meta_data_boolean_false = {
    0x42,
    0,
    amqp_decode_boolean_false,
    &amqp_methods_boolean_false,
    "boolean",
    "false",
    amqp_is_boolean, AMQP_TYPE_CATEGORY_FIXED,
};
// <encoding name="uint0" code="0x43" category="fixed" width="0"/>
amqp_encoding_meta_data_t amqp_type_meta_data_uint_uint0 = {
    0x43,
    0,
    amqp_decode_uint0,
    &amqp_methods_uint,
    "uint",
    "uint0",
    amqp_is_int | amqp_is_unsigned, AMQP_TYPE_CATEGORY_FIXED,
};
// <encoding name="ulong0" code="0x44" category="fixed" width="0"/>
amqp_encoding_meta_data_t amqp_type_meta_data_ulong_ulong0 = {
    0x44,
    0,
    amqp_decode_ulong0,
    &amqp_methods_ulong,
    "ulong",
    "ulong0",
    amqp_is_long | amqp_is_unsigned, AMQP_TYPE_CATEGORY_FIXED,
};
amqp_encoding_meta_data_t amqp_type_meta_data_list_0 = {
    0x45,
    0,
    amqp_decode_list_0,
    &amqp_methods_list_0,
    "list",
    "list0",
    amqp_is_list, AMQP_TYPE_CATEGORY_FIXED,
};
amqp_encoding_meta_data_t amqp_type_meta_data_extension_fixed_0 = {
    0x4F,
    0,
    amqp_decode_extension_type,
    &amqp_methods_extension_type,
    "extension",
    "fixed-0",
    amqp_is_extension, AMQP_TYPE_CATEGORY_FIXED,
};
amqp_encoding_meta_data_t amqp_type_meta_data_ubyte = {
    0x50,
    1,
    amqp_decode_ubyte,
    &amqp_methods_ubyte,
    "ubyte",
    "",
    amqp_is_byte | amqp_is_unsigned, AMQP_TYPE_CATEGORY_FIXED,
};
amqp_encoding_meta_data_t amqp_type_meta_data_byte = {
    0x51,
    1,
    amqp_decode_byte,
    &amqp_methods_byte,
    "byte",
    "",
    amqp_is_byte, AMQP_TYPE_CATEGORY_FIXED,
};
amqp_encoding_meta_data_t amqp_type_meta_data_uint_small_uint = {
    0x52,
    1,
    amqp_decode_small_uint,
    &amqp_methods_uint,
    "uint",
    "smalluint",
    amqp_is_int | amqp_is_unsigned, AMQP_TYPE_CATEGORY_FIXED,
};
amqp_encoding_meta_data_t amqp_type_meta_data_ulong_small_ulong = {
    0x53,
    1,
    amqp_decode_small_ulong,
    &amqp_methods_ulong,
    "ulong",
    "smallulong",
    amqp_is_long | amqp_is_unsigned, AMQP_TYPE_CATEGORY_FIXED,
};
amqp_encoding_meta_data_t amqp_type_meta_data_int_small_int = {
    0x54,
    1,
    amqp_decode_small_int,
    &amqp_methods_int,
    "int",
    "smallint",
    amqp_is_int, AMQP_TYPE_CATEGORY_FIXED,
};
amqp_encoding_meta_data_t amqp_type_meta_data_long_small_long = {
    0x55,
    1,
    amqp_decode_small_long,
    &amqp_methods_long,
    "long",
    "smalllong",
    amqp_is_long, AMQP_TYPE_CATEGORY_FIXED,
};
amqp_encoding_meta_data_t amqp_type_meta_data_boolean = {
    0x56,
    1,
    amqp_decode_boolean,
    &amqp_methods_boolean,
    "boolean",
    "",
    amqp_is_boolean, AMQP_TYPE_CATEGORY_FIXED,
};
amqp_encoding_meta_data_t amqp_type_meta_data_extension_fixed_1 = {
    0x5F,
    1,
    amqp_decode_extension_type,
    &amqp_methods_extension_type,
    "extension",
    "fixed-1",
    amqp_is_extension, AMQP_TYPE_CATEGORY_FIXED,
};
amqp_encoding_meta_data_t amqp_type_meta_data_ushort = {
    0x60,
    2,
    amqp_decode_ushort,
    &amqp_methods_ushort,
    "ushort",
    "",
    amqp_is_short | amqp_is_unsigned, AMQP_TYPE_CATEGORY_FIXED,
};
amqp_encoding_meta_data_t amqp_type_meta_data_short = {
    0x61,
    2,
    amqp_decode_short,
    &amqp_methods_short,
    "short",
    "",
    amqp_is_short, AMQP_TYPE_CATEGORY_FIXED,
};
amqp_encoding_meta_data_t amqp_type_meta_data_extension_fixed_2 = {
    0x6F,
    2,
    amqp_decode_extension_type,
    &amqp_methods_extension_type,
    "extension",
    "fixed-2",
    amqp_is_extension, AMQP_TYPE_CATEGORY_FIXED,
};
amqp_encoding_meta_data_t amqp_type_meta_data_uint = {
    0x70,
    4,
    amqp_decode_uint,
    &amqp_methods_uint,
    "uint",
    "",
    amqp_is_int | amqp_is_unsigned, AMQP_TYPE_CATEGORY_FIXED,
};
amqp_encoding_meta_data_t amqp_type_meta_data_int = {
    0x71,
    4,
    amqp_decode_int,
    &amqp_methods_int,
    "int",
    "",
    amqp_is_int, AMQP_TYPE_CATEGORY_FIXED,
};
amqp_encoding_meta_data_t amqp_type_meta_data_float_ieee_754 = {
    0x72,
    4,
    amqp_decode_float,
    &amqp_methods_float,
    "float",
    "ieee-754",
    amqp_is_float, AMQP_TYPE_CATEGORY_FIXED,
};
amqp_encoding_meta_data_t amqp_type_meta_data_char_utf32 = {
    0x73,
    4,
    amqp_decode_char,
    &amqp_methods_char,
    "char",
    "utf32",
    amqp_is_char, AMQP_TYPE_CATEGORY_FIXED,
};
amqp_encoding_meta_data_t amqp_type_meta_data_decimal32_ieee_754 = {
    0x74,
    4,
    amqp_decode_decimal32,
    &amqp_methods_decimal32,
    "decimal32",
    "ieee-754",
    amqp_is_decimal32, AMQP_TYPE_CATEGORY_FIXED,
};
amqp_encoding_meta_data_t amqp_type_meta_data_extension_fixed_4 = {
    0x7F,
    4,
    amqp_decode_extension_type,
    &amqp_methods_extension_type,
    "extension",
    "fixed-4",
    amqp_is_extension, AMQP_TYPE_CATEGORY_FIXED,
};
amqp_encoding_meta_data_t amqp_type_meta_data_ulong = {
    0x80,
    8,
    amqp_decode_ulong,
    &amqp_methods_ulong,
    "ulong",
    "",
    amqp_is_long | amqp_is_unsigned, AMQP_TYPE_CATEGORY_FIXED,
};
amqp_encoding_meta_data_t amqp_type_meta_data_long = {
    0x81,
    8,
    amqp_decode_long,
    &amqp_methods_long,
    "long",
    "",
    amqp_is_long, AMQP_TYPE_CATEGORY_FIXED,
};
amqp_encoding_meta_data_t amqp_type_meta_data_double_ieee_754 = {
    0x82,
    8,
    amqp_decode_double,
    &amqp_methods_double,
    "double",
    "ieee-754",
    amqp_is_double, AMQP_TYPE_CATEGORY_FIXED,
};
amqp_encoding_meta_data_t amqp_type_meta_data_timestamp_ms64 = {
    0x83,
    8,
    amqp_decode_timestamp,
    &amqp_methods_timestamp,
    "timestamp",
    "ms64",
    amqp_is_timestamp, AMQP_TYPE_CATEGORY_FIXED,
};
amqp_encoding_meta_data_t amqp_type_meta_data_decimal64_ieee_754 = {
    0x84,
    8,
    amqp_decode_decimal64,
    &amqp_methods_decimal64,
    "decimal64",
    "ieee-754",
    amqp_is_decimal64, AMQP_TYPE_CATEGORY_FIXED,
};
amqp_encoding_meta_data_t amqp_type_meta_data_extension_fixed_8 = {
    0x8F,
    8,
    amqp_decode_extension_type,
    &amqp_methods_extension_type,
    "extension",
    "fixed-8",
    amqp_is_extension, AMQP_TYPE_CATEGORY_FIXED,
};
amqp_encoding_meta_data_t amqp_type_meta_data_decimal128_ieee_754 = {
    0x94,
    16,
    amqp_decode_decimal128,
    &amqp_methods_decimal128,
    "decimal128",
    "ieee-754",
    amqp_is_decimal128, AMQP_TYPE_CATEGORY_FIXED,
};
amqp_encoding_meta_data_t amqp_type_meta_data_uuid = {
    0x98,
    16,
    amqp_decode_uuid,
    &amqp_methods_uuid,
    "uuid",
    "",
    amqp_is_uuid, AMQP_TYPE_CATEGORY_FIXED,
};
amqp_encoding_meta_data_t amqp_type_meta_data_extension_fixed_16 = {
    0x9F,
    16,
    amqp_decode_extension_type,
    &amqp_methods_extension_type,
    "extension",
    "fixed-16",
    amqp_is_extension, AMQP_TYPE_CATEGORY_FIXED,
};
amqp_encoding_meta_data_t amqp_type_meta_data_binary_vbin8 = {
    0xA0,
    1,
    amqp_decode_binary_vbin8,
    &amqp_methods_binary_vbin8,
    "binary",
    "vbin8",
    amqp_is_binary, AMQP_TYPE_CATEGORY_VARIABLE,
};
amqp_encoding_meta_data_t amqp_type_meta_data_string_str8_utf8 = {
    0xA1,
    1,
    amqp_decode_string_str8_utf8,
    &amqp_methods_string_str8_utf8,
    "string",
    "str8-utf8",
    amqp_is_string, AMQP_TYPE_CATEGORY_VARIABLE,
};
amqp_encoding_meta_data_t amqp_type_meta_data_symbol_sym8 = {
    0xA3,
    1,
    amqp_decode_symbol_sym8,
    &amqp_methods_symbol_sym8,
    "symbol",
    "sym8",
    amqp_is_symbol, AMQP_TYPE_CATEGORY_VARIABLE,
};
amqp_encoding_meta_data_t amqp_type_meta_data_extension_variable_1 = {
    0xAF,
    1,
    amqp_decode_extension_type,
    &amqp_methods_extension_type,
    "extension",
    "variable-1",
    amqp_is_extension, AMQP_TYPE_CATEGORY_VARIABLE,
};
amqp_encoding_meta_data_t amqp_type_meta_data_binary_vbin32 = {
    0xB0,
    4,
    amqp_decode_binary_vbin32,
    &amqp_methods_binary_vbin32,
    "binary",
    "vbin32",
    amqp_is_binary, AMQP_TYPE_CATEGORY_VARIABLE,
};
amqp_encoding_meta_data_t amqp_type_meta_data_string_str32_utf8 = {
    0xB1,
    4,
    amqp_decode_string_str32_utf8,
    &amqp_methods_string_str32_utf8,
    "string",
    "str32-utf8",
    amqp_is_string, AMQP_TYPE_CATEGORY_VARIABLE,
};
amqp_encoding_meta_data_t amqp_type_meta_data_symbol_sym32 = {
    0xB3,
    4,
    amqp_decode_symbol_sym32,
    &amqp_methods_symbol_sym32,
    "symbol",
    "sym32",
    amqp_is_symbol, AMQP_TYPE_CATEGORY_VARIABLE,
};
amqp_encoding_meta_data_t amqp_type_meta_data_extension_variable_4 = {
    0xBF,
    4,
    amqp_decode_extension_type,
    &amqp_methods_extension_type,
    "extension",
    "variable-4",
    amqp_is_extension, AMQP_TYPE_CATEGORY_VARIABLE,
};
amqp_encoding_meta_data_t amqp_type_meta_data_list_8 = {
    0xC0,
    1,
    amqp_decode_list_8,
    &amqp_methods_list_8,
    "list",
    "list8",
    amqp_is_list, AMQP_TYPE_CATEGORY_COMPOUND,
};
amqp_encoding_meta_data_t amqp_type_meta_data_map_8 = {
    0xC1,
    1,
    amqp_decode_map_8,
    &amqp_methods_map_8,
    "map",
    "map8",
    amqp_is_map, AMQP_TYPE_CATEGORY_COMPOUND,
};
amqp_encoding_meta_data_t amqp_type_meta_data_extension_compound_1 = {
    0xCF,
    1,
    amqp_decode_extension_type,
    &amqp_methods_extension_type,
    "extension",
    "compound-1",
    amqp_is_extension, AMQP_TYPE_CATEGORY_COMPOUND,
};
amqp_encoding_meta_data_t amqp_type_meta_data_list_32 = {
    0xD0,
    4,
    amqp_decode_list_32,
    &amqp_methods_list_32,
    "list",
    "list32",
    amqp_is_list, AMQP_TYPE_CATEGORY_COMPOUND,
};
amqp_encoding_meta_data_t amqp_type_meta_data_map_32 = {
    0xD1,
    4,
    amqp_decode_map_32,
    &amqp_methods_map_32,
    "map",
    "map32",
    amqp_is_map, AMQP_TYPE_CATEGORY_COMPOUND,
};
amqp_encoding_meta_data_t amqp_type_meta_data_extension_compound_4 = {
    0xDF,
    4,
    amqp_decode_extension_type,
    &amqp_methods_extension_type,
    "extension",
    "compound-4",
    amqp_is_extension, AMQP_TYPE_CATEGORY_COMPOUND,
};
amqp_encoding_meta_data_t amqp_type_meta_data_array_8 = {
    0xE0,
    1,
    amqp_decode_array_8,
    &amqp_methods_array_8,
    "array",
    "array8",
    amqp_is_array, AMQP_TYPE_CATEGORY_ARRAY,
};
amqp_encoding_meta_data_t amqp_type_meta_data_extension_array_1 = {
    0xEF,
    1,
    amqp_decode_extension_type,
    &amqp_methods_extension_type,
    "extension",
    "array-1",
    amqp_is_extension, AMQP_TYPE_CATEGORY_ARRAY,
};
amqp_encoding_meta_data_t amqp_type_meta_data_array_32 = {
    0xF0,
    4,
    amqp_decode_array_32,
    &amqp_methods_array_32,
    "array",
    "array32",
    amqp_is_array, AMQP_TYPE_CATEGORY_ARRAY,
};
amqp_encoding_meta_data_t amqp_type_meta_data_extension_array_4 = {
    0xFF,
    4,
    amqp_decode_extension_type,
    &amqp_methods_extension_type,
    "extension",
    "array-4",
    amqp_is_extension, AMQP_TYPE_CATEGORY_ARRAY,
};

amqp_encoding_meta_data_t *amqp__type_lookup_table[] = {
    &amqp_type_meta_data_described,
    &amqp_type_meta_data_null,
    &amqp_type_meta_data_boolean_true,
    &amqp_type_meta_data_boolean_false,
    &amqp_type_meta_data_uint_uint0,
    &amqp_type_meta_data_ulong_ulong0,
    &amqp_type_meta_data_list_0,
    &amqp_type_meta_data_extension_fixed_0,
    &amqp_type_meta_data_ubyte,
    &amqp_type_meta_data_byte,
    &amqp_type_meta_data_uint_small_uint,
    &amqp_type_meta_data_ulong_small_ulong,
    &amqp_type_meta_data_int_small_int,
    &amqp_type_meta_data_long_small_long,
    &amqp_type_meta_data_boolean,
    &amqp_type_meta_data_extension_fixed_1,
    &amqp_type_meta_data_ushort,
    &amqp_type_meta_data_short,
    &amqp_type_meta_data_extension_fixed_2,
    &amqp_type_meta_data_uint,
    &amqp_type_meta_data_int,
    &amqp_type_meta_data_float_ieee_754,
    &amqp_type_meta_data_char_utf32,
    &amqp_type_meta_data_decimal32_ieee_754,
    &amqp_type_meta_data_extension_fixed_4,
    &amqp_type_meta_data_ulong,
    &amqp_type_meta_data_long,
    &amqp_type_meta_data_double_ieee_754,
    &amqp_type_meta_data_timestamp_ms64,
    &amqp_type_meta_data_decimal64_ieee_754,
    &amqp_type_meta_data_extension_fixed_8,
    &amqp_type_meta_data_decimal128_ieee_754,
    &amqp_type_meta_data_uuid,
    &amqp_type_meta_data_extension_fixed_16,
    &amqp_type_meta_data_binary_vbin8,
    &amqp_type_meta_data_string_str8_utf8,
    &amqp_type_meta_data_symbol_sym8,
    &amqp_type_meta_data_extension_variable_1,
    &amqp_type_meta_data_binary_vbin32,
    &amqp_type_meta_data_string_str32_utf8,
    &amqp_type_meta_data_symbol_sym32,
    &amqp_type_meta_data_extension_variable_4,
    &amqp_type_meta_data_list_8,
    &amqp_type_meta_data_map_8,
    &amqp_type_meta_data_extension_compound_1,
    &amqp_type_meta_data_list_32,
    &amqp_type_meta_data_map_32,
    &amqp_type_meta_data_extension_compound_4,
    &amqp_type_meta_data_array_8,
    &amqp_type_meta_data_extension_array_1,
    &amqp_type_meta_data_array_32,
    &amqp_type_meta_data_extension_array_4
};


int amqp__type_lookup_table_ntypes = sizeof(amqp__type_lookup_table) / sizeof(amqp_encoding_meta_data_t *);


// TODO - this binary search can take 5 compares to find a value, do lookup table for fast version
amqp_encoding_meta_data_t *
amqp_type_meta_data_lookup(amqp_context_t *context, int format_code)
{
    int s = 0;
    int e = amqp__type_lookup_table_ntypes;
    int m;
    amqp_encoding_meta_data_t *candidate;

    while (s < e)
    {
        m = s + (e - s) / 2;

        candidate = amqp__type_lookup_table[m];

        if (candidate->format_code == format_code)
        {
            return candidate;
        }
        else if (format_code < candidate->format_code)
        {
            e = m;
        }
        else
        {
            s = m + 1;
        }
    }

    return 0;
}
