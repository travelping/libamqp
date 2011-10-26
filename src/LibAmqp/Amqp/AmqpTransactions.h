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
#ifndef LIBAMQP_AMQP_AMQP_TRANSACTIONS_H
#define LIBAMQP_AMQP_AMQP_TRANSACTIONS_H
#ifdef __cplusplus
extern "C" {
#endif

#include "AmqpTypes/AmqpTypes.h"
    
typedef struct amqp_txn_coordinator_t amqp_txn_coordinator_t;
typedef struct amqp_txn_declare_t amqp_txn_declare_t;
typedef struct amqp_txn_discharge_t amqp_txn_discharge_t;
typedef struct amqp_txn_declared_t amqp_txn_declared_t;
typedef struct amqp_txn_transactional_state_t amqp_txn_transactional_state_t;

struct amqp_txn_coordinator_t {
    // 1 fields
    amqp_multiple_symbol_t capabilities; 
};

struct amqp_txn_declare_t {
    // 1 fields
    amqp_wildcard_t global_id; 
};

struct amqp_txn_discharge_t {
    // 2 fields
    amqp_wildcard_t txn_id; /* mandatory; */
    int fail; 
};

struct amqp_txn_declared_t {
    // 1 fields
    amqp_wildcard_t txn_id; /* mandatory; */
};

struct amqp_txn_transactional_state_t {
    // 2 fields
    amqp_wildcard_t txn_id; /* mandatory; */
    amqp_wildcard_t outcome; 
};
#ifdef __cplusplus
}
#endif
#endif