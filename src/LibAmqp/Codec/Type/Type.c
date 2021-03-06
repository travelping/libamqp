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
#include <string.h>

#include "Context/ErrorHandling.h"
#include "Codec/Type/Type.h"
#include "Context/Context.h"
#include "Memory/Pool.h"

#include "debug_helper.h"

void amqp_mark_type_invalid(amqp_type_t *type, int cause)
{
    assert(type != 0);
    amqp_typedef_flags_set(type, amqp_is_invalid);
    type->invalid_cause = cause;
}

static
void amqp_initialize_amqp_type_t(amqp_context_t *c, amqp_memory_pool_t *pool, amqp_type_t *type)
{
    assert(pool != 0);
    assert(type != 0);

    type->constructor.extension_type_code = -1;
}

static
void amqp_cleanup_amqp_type_t(amqp_context_t *c, amqp_memory_pool_t *pool, amqp_type_t *type)
{
    assert(pool != 0);
    assert(type != 0);

    if (amqp_type_is_container(type))
    {
        amqp_deallocate_amqp_type_t_array(c, pool, type->value.compound.elements, type->value.compound.count);
    }
    if (amqp_type_is_array(type) && (!amqp_type_is_encoded(type) || (amqp_type_is_encoded(type) && type->value.array.count == 0)))
    {
        amqp_deallocate_type(c, type->value.array.constructor);
    }
}

void amqp_type_initialize_pool(amqp_memory_pool_t *pool)
{
    amqp_initialize_pool_suggesting_block_size(pool, sizeof(amqp_type_t), 2048, "type");
    amqp_pool_specify_initialization_callbacks(pool, (amqp_pool_callback_t) amqp_initialize_amqp_type_t, (amqp_pool_callback_t) amqp_cleanup_amqp_type_t);
}

amqp_type_t ** amqp_allocate_amqp_type_t_array(amqp_context_t *c, size_t count)
{
    size_t n = (count / 16 + 1) * 16;
    return (amqp_type_t **) amqp_malloc(c, n * sizeof(amqp_type_t *));
}

amqp_type_t ** amqp_realloc_amqp_type_t_array(amqp_context_t *c, amqp_type_t **elements, size_t count)
{
    size_t old_n = ((count - 1) / 16 + 1) * 16;
    size_t new_n = (count / 16 + 1) * 16;

    if (new_n > old_n)
    {
        elements = amqp_realloc(c, elements, new_n * sizeof(amqp_type_t *));
    }
    return elements;
}

void amqp_deallocate_amqp_type_t_array(amqp_context_t *context, amqp_memory_pool_t *pool, amqp_type_t **array, size_t count)
{
    size_t i;

    if (array)
    {
        for (i = 0; i < count; i++)
        {
            amqp_deallocate(context, pool, array[i]);
        }
        AMQP_FREE(context, array);
    }
}

int amqp_type_match(amqp_type_t *lhs, amqp_type_t *rhs)
{
    if (lhs->constructor.format_code != rhs->constructor.format_code)
    {
        return false;
    }
    return true;
}

void amqp_describe_type(char *buffer, size_t size, amqp_type_t *type)
{
    amqp_encoding_meta_data_t *meta_data = type->constructor.meta_data;
    if (meta_data)
    {
        snprintf(buffer, size, "name=\"%s\", encoding=\"%s\", category=\"%s\"", meta_data->name, meta_data->encoding_name, amqp_category_names[meta_data->category_name_index]);
    }
    else
    {
        snprintf(buffer, size, "name=\"unknown\"");
    }
}