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

#include <TestHarness.h>

#include "Context/ErrorHandling.h"

#include "Codec/CodecTestFixture.h"
#include "Context/TestSupport/ContextHolder.h"
#include "Context/TestSupport/DecodeBufferHolder.h"

#include "Codec/Type/Type.h"

#include "Codec/Type/TypePrint.h"

#ifdef putc
#undef putc
#endif

#define check_output(e) CHECK_EQUAL((e), (const char *) output);

SUITE(TypePrint)
{
    class TypePrintTestFixture;
    static TypePrintTestFixture *active_test;
    static int printc(int c);

    class TypePrintTestFixture :
            public virtual TestSupport::ContextHolder,
            public virtual TestSupport::DecodeBufferHolder
    {

    public:
        TypePrintTestFixture() : type(0), count(0)
        {
            active_test = this;
            amqp_context_define_putc_function(context, printc);
        }
        ~TypePrintTestFixture() 
        {
            amqp_deallocate(context, &context->memory.amqp_type_t_pool, type);
        }
        int putc(int c)
        {
            if (count < sizeof(output))
            {
                output[count++] = c;
                output[count] = '\0';
            }
            return c;
        }
        void print_type()
        {
            amqp_type_print(context, type);
        }
    
        void print_type_formatted()
        {
            amqp_type_print_formatted(context, type);
        }

    public:
        amqp_type_t *type;

        char output[1024];
        size_t count;
    };

    static int printc(int c)
    {
        return active_test->putc(c);
    }

    TEST_FIXTURE(TypePrintTestFixture, utf8_string)
    {
        load_decode_buffer(test_data::utf8_string);
        type = amqp_decode(context, decode_buffer);

        ASSERT_VALID(type);
        print_type();
        check_output("\"utf8 string\"");
    }

    TEST_FIXTURE(TypePrintTestFixture, utf8_string_formatted)
    {
        load_decode_buffer(test_data::utf8_string);
        type = amqp_decode(context, decode_buffer);

        ASSERT_VALID(type);
        print_type_formatted();
        check_output("string-str8-utf8: \"utf8 string\";\n");
    }

    TEST_FIXTURE(TypePrintTestFixture, ubyte)
    {
        load_decode_buffer(test_data::neg_ubyte_1);
        type = amqp_decode(context, decode_buffer);

        ASSERT_VALID(type);
        print_type();
        check_output("(ubyte) 195");
    }

    TEST_FIXTURE(TypePrintTestFixture, byte)
    {
        load_decode_buffer(test_data::byte_1);
        type = amqp_decode(context, decode_buffer);

        ASSERT_VALID(type);
        print_type();
        check_output("(byte) -2");
    }

    TEST_FIXTURE(TypePrintTestFixture, ushort)
    {
        load_decode_buffer(test_data::ushort_2);
        type = amqp_decode(context, decode_buffer);

        ASSERT_VALID(type);
        print_type();
        check_output("(ushort) 65534");
    }

    TEST_FIXTURE(TypePrintTestFixture, short)
    {
        load_decode_buffer(test_data::short_2);
        type = amqp_decode(context, decode_buffer);

        ASSERT_VALID(type);
        print_type();
        check_output("(short) -2");
    }

    TEST_FIXTURE(TypePrintTestFixture, Float)
    {
        load_decode_buffer(test_data::float_4);
        type = amqp_decode(context, decode_buffer);

        ASSERT_VALID(type);
        print_type();
        check_output("(float) 123.455994");
    }

    TEST_FIXTURE(TypePrintTestFixture, Double)
    {
        load_decode_buffer(test_data::double_8);
        type = amqp_decode(context, decode_buffer);

        ASSERT_VALID(type);
        print_type();
        check_output("(double) 123.456000");
    }

    TEST_FIXTURE(TypePrintTestFixture, Symbol)
    {
        load_decode_buffer(test_data::foo_bar_symbol_32);
        type = amqp_decode(context, decode_buffer);

        ASSERT_VALID(type);
        print_type();
        check_output("\'FooBar\'");
    }

    TEST_FIXTURE(TypePrintTestFixture, PrintInvalidSymbol)
    {
        load_decode_buffer(test_data::bad_symbol);
        type = amqp_decode_supress_messages(context, decode_buffer);

        ASSERT_INVALID(type);
        print_type();
        check_output("invalid: 42 e1 72");
    }

    TEST_FIXTURE(TypePrintTestFixture, PrintInvalidSymbolFormatted)
    {
        load_decode_buffer(test_data::bad_symbol);
        type = amqp_decode_supress_messages(context, decode_buffer);

        ASSERT_INVALID(type);
        print_type_formatted();
        check_output("symbol-sym8: invalid: 42 e1 72;\n");
    }

    TEST_FIXTURE(TypePrintTestFixture, PrintUdid)
    {
        load_decode_buffer(test_data::uuid_16);
        type = amqp_decode(context, decode_buffer);

        ASSERT_VALID(type);
        print_type();
        check_output("f81d4fae-7dec-11d0-a765-00a0c91e6bf6");
    }

    TEST_FIXTURE(TypePrintTestFixture, PrintChar)
    {
        load_decode_buffer(test_data::utf32_char);
        type = amqp_decode(context, decode_buffer);

        ASSERT_VALID(type);

        // TODO - print wchar_t characters
    }

    TEST_FIXTURE(TypePrintTestFixture, SmallArray)
    {
        load_decode_buffer(test_data::array_shorts);
        type = amqp_decode(context, decode_buffer);

        ASSERT_VALID(type);
        ASSERT_VALID(type->value.array.elements[0]);

        CHECK_EQUAL(0x61, type->value.array.elements[0]->constructor.format_code);
        print_type();
        check_output("[(short) 10, 11, 11, 13, 14]");
    }

    TEST_FIXTURE(TypePrintTestFixture, List)
    {
        load_decode_buffer(test_data::list);
        type = amqp_decode(context, decode_buffer);

        ASSERT_VALID(type);
        CHECK_LIST(type);

        print_type();
        check_output("{\n    \'Foo\',\n    (double) 123.456000,\n    \"Hello\",\n    (short) 10,\n    [(short) 10, 11],\n    [(short) 12]\n}\n");
    }

    TEST_FIXTURE(TypePrintTestFixture, empty_list)
    {
        load_decode_buffer(test_data::empty_list_8);
        type = amqp_decode(context, decode_buffer);

        ASSERT_VALID(type);
        CHECK_LIST(type);

        print_type();
        check_output("{\n}\n");
    }

    TEST_FIXTURE(TypePrintTestFixture, empty_list_0)
    {
        load_decode_buffer(test_data::empty_list_0);
        type = amqp_decode(context, decode_buffer);

        ASSERT_VALID(type);
        CHECK_LIST(type);

        print_type();
        check_output("{\n}\n");
    }

    TEST_FIXTURE(TypePrintTestFixture, Map)
    {
        load_decode_buffer(test_data::map);
        type = amqp_decode(context, decode_buffer);

        ASSERT_VALID(type);
        CHECK_MAP(type);

        print_type();
        check_output("{\n    \"list:\"->{\n\t(long) 1,\n\t\"two\",\n\t(double) 3.141593,\n\tnull,\n\tfalse\n    },\n    null->true,\n    \"pi\"->(double) 3.141593,\n    \"two\"->(long) 2,\n    \"129\"->(long) 129\n}\n");
    }

    TEST_FIXTURE(TypePrintTestFixture, TimeStamp)
    {
        load_decode_buffer(test_data::timestamp_8);
        type = amqp_decode(context, decode_buffer);

        ASSERT_VALID(type);
        print_type();

        check_output("2010-12-06T17:00:00.000Z");
    }

    TEST_FIXTURE(TypePrintTestFixture, TimeStamp2)
    {
        load_decode_buffer(test_data::timestamp_before_epoc_8);
        type = amqp_decode(context, decode_buffer);

        ASSERT_VALID(type);
        print_type();

        check_output("1910-12-06T17:00:00.000Z");
    }

    TEST_FIXTURE(TypePrintTestFixture, BooleanTrue)
    {
        load_decode_buffer(test_data::true_0);
        type = amqp_decode(context, decode_buffer);

        ASSERT_VALID(type);

        print_type();
        check_output("true");
    }

    TEST_FIXTURE(TypePrintTestFixture, BooleanFalse)
    {
        load_decode_buffer(test_data::false_0);
        type = amqp_decode(context, decode_buffer);

        ASSERT_VALID(type);

        print_type();
        check_output("false");
    }

    TEST_FIXTURE(TypePrintTestFixture, BooleanOneByteEncodingTrueValue)
    {
        load_decode_buffer(test_data::true_1);
        type = amqp_decode(context, decode_buffer);

        ASSERT_VALID(type);

        print_type();
        check_output("true");
    }

    TEST_FIXTURE(TypePrintTestFixture, BooleanOneByteEncodingFalseValue)
    {
        load_decode_buffer(test_data::false_1);
        type = amqp_decode(context, decode_buffer);

        ASSERT_VALID(type);

        print_type();
        check_output("false");
    }
}
