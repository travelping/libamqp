/*
   Copyright 2011 StormMQ Limited

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
 
/*
  WARNING: This file was generated by scripts/generate-amqp-types.rb. DO NOT HAND EDIT.
 */
#ifndef LIBAMQP_AMQP_AMQP_SECURITY_H
#define LIBAMQP_AMQP_AMQP_SECURITY_H
#ifdef __cplusplus
extern "C" {
#endif

#include "AmqpTypes/AmqpTypes.h"
    
typedef struct amqp_security_sasl_mechanisms_t amqp_security_sasl_mechanisms_t;
typedef struct amqp_security_sasl_init_t amqp_security_sasl_init_t;
typedef struct amqp_security_sasl_challenge_t amqp_security_sasl_challenge_t;
typedef struct amqp_security_sasl_response_t amqp_security_sasl_response_t;
typedef struct amqp_security_sasl_outcome_t amqp_security_sasl_outcome_t;

struct amqp_security_sasl_mechanisms_t {
    // 1 fields
    amqp_multiple_symbol_t sasl_server_mechanisms; /* mandatory; */
};

struct amqp_security_sasl_init_t {
    // 3 fields
    amqp_symbol_t mechanism; /* mandatory; */
    amqp_binary_t initial_response; 
    amqp_string_t hostname; 
};

struct amqp_security_sasl_challenge_t {
    // 1 fields
    amqp_binary_t challenge; /* mandatory; */
};

struct amqp_security_sasl_response_t {
    // 1 fields
    amqp_binary_t response; /* mandatory; */
};

struct amqp_security_sasl_outcome_t {
    // 2 fields
    amqp_sasl_code_t code; /* mandatory; */
    amqp_binary_t additional_data; 
};
#ifdef __cplusplus
}
#endif
#endif
