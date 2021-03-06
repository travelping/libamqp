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

#include <assert.h>
#include <string.h>

#include "AmqpTypes/AmqpTypesInternal.h"
#include "Codec/Type/TypeExtension.h"
#include "AmqpTypes/AmqpVariableInternal.h"

#include "AmqpTypes/AmqpString.h"

#include "debug_helper.h"


void amqp_string_initialize_as_null(amqp_context_t *context, amqp_string_t *string)
{
    string->leader.fn_table = 0;
    amqp_variable_initialize_as_null(&string->v);
}

static void create_dtor(amqp_context_t *context, amqp_amqp_type_t *type)
{
    amqp_string_t *string = (amqp_string_t *) type;
    if (string->v.data)
    {
        AMQP_FREE(context, string->v.data);
    }

    AMQP_FREE(context, string);
}
static void initialize_dtor(amqp_context_t *context, amqp_amqp_type_t *type)
{
    amqp_string_t *string = (amqp_string_t *) type;
    if (string->v.data)
    {
        AMQP_FREE(context, string->v.data);
    }
}

void amqp_string_initialize_from_type(amqp_context_t *context, amqp_string_t *string, amqp_type_t *type)
{
    static amqp_fn_table_t table = {
        .dtor = initialize_dtor
    };
    string->leader.fn_table = &table;

    assert(amqp_type_is_string(type));
    amqp_variable_initialize_from_type(&string->v, type);
}

void amqp_string_initialize(amqp_context_t *context, amqp_string_t *string, const char *data, size_t size)
{
    static amqp_fn_table_t table = {
        .dtor = initialize_dtor
    };
    string->leader.fn_table = &table;

    amqp_variable_initialize(&string->v, (uint8_t *) amqp_duplicate(context, data, size), size);
}

amqp_string_t *amqp_string_create_from_type(amqp_context_t *context, amqp_type_t *type)
{
    static amqp_fn_table_t table = {
        .dtor = create_dtor
    };
    amqp_string_t *result = AMQP_MALLOC(context, amqp_string_t);
    assert(amqp_type_is_string(type));

    result->leader.fn_table = &table;
    amqp_variable_initialize_from_type(&result->v, type);
    return result;
}

static
amqp_string_t *string_create(amqp_context_t *context, const uint8_t *data, size_t size)
{
    static amqp_fn_table_t table = {
        .dtor = create_dtor
    };

    amqp_string_t *result = AMQP_MALLOC(context, amqp_string_t);
    result->leader.fn_table = &table;
    amqp_variable_initialize(&result->v, data, size);
    return result;
}

amqp_string_t *amqp_string_create(amqp_context_t *context, const char *data, size_t size)
{
    return string_create(context, (uint8_t *) amqp_duplicate(context, data, size), size);
}

amqp_string_t *amqp_string_clone(amqp_context_t *context, amqp_string_t *source_string)
{
    return string_create(context, amqp_variable_clone_data(context, &source_string->v), source_string->v.size);
}

int amqp_string_to_bytes(amqp_string_t *string, uint8_t *buffer, size_t buffer_size)
{
    return amqp_variable_to_bytes(&string->v, buffer, buffer_size);
}

int amqp_string_compare(amqp_string_t *lhs, amqp_string_t *rhs)
{
    return amqp_variable_compare(&lhs->v, &rhs->v);
}

int amqp_string_compare_with_cstr(amqp_string_t *lhs, const char *rhs)
{
    return amqp_variable_compare_with_cstr(&lhs->v, rhs);
}

int amqp_string_compare_with_bytes(amqp_string_t *lhs, const uint8_t *rhs, size_t size)
{
    return amqp_variable_compare_with_bytes(&lhs->v, rhs, size);
}

uint32_t amqp_string_hash(amqp_string_t *string)
{
    return amqp_variable_hash(&string->v);
}

const char *amqp_string_to_cstr(amqp_context_t *context, amqp_string_t *string)
{
    // TODO - not a utf8 conversion
    return !amqp_string_is_null(string) ? (char *) amqp_variable_clone_data(context, &string->v) : 0;
}

int amqp_string_print(amqp_context_t *context, amqp_string_t *string)
{
    const char *c_str = amqp_string_to_cstr(context, string);
    int n_chars = strlen(c_str);
    int i;
    for (i = 0; i < n_chars; i++)
    {
        amqp_context_putc(context, c_str[i]);
    }
    amqp_free(context, c_str);
    return i;
}
