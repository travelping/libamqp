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

#ifndef LIBAMQP_AMQP_TYPES_DECODE_AMQP_DEFINITIONS_DECODE_H
#define LIBAMQP_AMQP_TYPES_DECODE_AMQP_DEFINITIONS_DECODE_H

// TODO - optimize includes
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include "AmqpTypes/AmqpTypes.h"
#include "AmqpTypes/Decode/AmqpTypesDecode.h"
#include "AmqpTypes/Decode/AmqpDecodeInternal.h"
#include "AmqpTypes/Decode/AmqpDefinitionsDecode.h"

#include "debug_helper.h"

extern int amqp_decode_multiple_type_symbol(amqp_context_t *context, amqp_type_t *field, int field_number, int total_fields, amqp_multiple_symbol_t *multiple);
extern int amqp_decode_mandatory_multiple_type_symbol(amqp_context_t *context, amqp_type_t *field, int field_number, int total_fields, amqp_multiple_symbol_t *multiple);
extern int amqp_decode_mandatory_primitive_sasl_code(amqp_context_t *context, amqp_type_t *field, int field_number, int total_fields, uint8_t *result);
extern int amqp_decode_primitive_sender_settle_mode(amqp_context_t *context, amqp_type_t *field, int field_number, int total_fields, int *null_flag, amqp_sender_settle_mode_t *result, amqp_sender_settle_mode_t default_value);
extern int amqp_decode_primitive_receiver_settle_mode(amqp_context_t *context, amqp_type_t *field, int field_number, int total_fields, int *null_flag, amqp_receiver_settle_mode_t *result, amqp_receiver_settle_mode_t default_value);

extern void amqp_amqp_error_cleanup(amqp_context_t *context, amqp_error_t *error);
extern int amqp_decode_type_amqp_error(amqp_context_t *context, amqp_type_t *field_type, int field_number, int total_fields, amqp_error_t *result);

extern void amqp_wildcard_cleanup(amqp_context_t *context, amqp_wildcard_t *wildcard);

extern int amqp_decode_type_wildcard_expecting_source(amqp_context_t *context, amqp_type_t *field, int field_number, int total_fields, amqp_wildcard_t *wildcard);
extern int amqp_decode_type_wildcard_expecting_target(amqp_context_t *context, amqp_type_t *field, int field_number, int total_fields, amqp_wildcard_t *wildcard);
extern int amqp_decode_type_wildcard_expecting_delivery_state(amqp_context_t *context, amqp_type_t *field, int field_number, int total_fields, amqp_wildcard_t *wildcard);

extern int amqp_decode_primitive_handle(amqp_context_t *context, amqp_type_t *field, int field_number, int total_fields, int *null_flag, amqp_handle_t *result, uint32_t default_value);
extern int amqp_decode_mandatory_primitive_handle(amqp_context_t *context, amqp_type_t *field, int field_number, int total_fields, amqp_handle_t *result);
extern int amqp_decode_primitive_sequence_no(amqp_context_t *context, amqp_type_t *field, int field_number, int total_fields, int *null_flag, amqp_sequence_no_t *result, uint32_t default_value);
extern int amqp_decode_mandatory_primitive_sequence_no(amqp_context_t *context, amqp_type_t *field, int field_number, int total_fields, amqp_sequence_no_t *result);
extern int amqp_decode_primitive_message_format(amqp_context_t *context, amqp_type_t *field, int field_number, int total_fields, int *null_flag, amqp_message_format_t *result, uint32_t default_value);


#endif
