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

#include <TestHarness.h>

#include "Transport/Connection/IO/ConnectionSocketTestFixture.h"
#include "Context/TestSupport/BufferHolder.h"

#include "debug_helper.h"

SUITE(ConnectionRead)
{
    class ConnectionReadFixture :
            public SuiteConnectionSocket::ConnectionSocketTestFixture,
            public virtual TestSupport::BufferHolder
    {
    public:
        ConnectionReadFixture();
        ~ConnectionReadFixture();

        static void read_callback(amqp_connection_t *connection, amqp_buffer_t *buffer, int amount);
        static void write_callback(amqp_connection_t *connection);
    public:
        static bool reading;
    };

    ConnectionReadFixture::ConnectionReadFixture()
    {
        connect_to("localhost", TestParameters::port);
        CHECK_EQUAL("connecting", connection->state.socket.name);
        loop_while_socket_state_is("connecting");
        amqp_connection_writer_initialize(connection);
        connection->state.writer.enable(connection);

        reading = true;
    }

    ConnectionReadFixture::~ConnectionReadFixture()
    {
        connection->state.writer.stop(connection, write_callback);
    }

    bool ConnectionReadFixture::reading;


    void ConnectionReadFixture::read_callback(amqp_connection_t *connection, amqp_buffer_t *buffer, int amount)
    {
        reading = false;
    }

    void ConnectionReadFixture::write_callback(amqp_connection_t *connection)
    {
    }

    TEST_FIXTURE(ConnectionReadFixture, verify_fixture_clean_resources)
    {
    }

    TEST_FIXTURE(ConnectionReadFixture, stop_without_read)
    {
        amqp_connection_reader_initialize(connection);
        CHECK_EQUAL("initialized", connection->state.reader.name);
        connection->state.reader.enable(connection);
        CHECK_EQUAL("enabled", connection->state.reader.name);

        connection->state.reader.stop(connection);
        CHECK_EQUAL("stopped", connection->state.reader.name);
    }

    TEST_FIXTURE(ConnectionReadFixture, stop_without_prior_enable)
    {
        amqp_connection_reader_initialize(connection);
        CHECK_EQUAL("initialized", connection->state.reader.name);

        connection->state.reader.stop(connection);
        CHECK_EQUAL("stopped", connection->state.reader.name);

        connection->state.reader.stop(connection);
        CHECK_EQUAL("stopped", connection->state.reader.name);
    }

    TEST_FIXTURE(ConnectionReadFixture, reader_states)
    {
        amqp_connection_reader_initialize(connection);
        CHECK_EQUAL("initialized", connection->state.reader.name);
        connection->state.reader.enable(connection);
        CHECK_EQUAL("enabled", connection->state.reader.name);

        amqp_buffer_t *write_buffer = amqp_allocate_buffer(context);

        write_size(write_buffer, 1);
        amqp_buffer_putc(write_buffer, 'X');
        amqp_connection_write_buffer(connection, write_buffer);
        connection->state.reader.commence_read(connection, read_buffer, 5, read_callback);

        CHECK_EQUAL("reading", connection->state.reader.name);
//        while (run_loop_with_timeout() && amqp_connection_reader_is_state(connection, "reading"));
        while (run_loop_with_timeout() && reading);

        CHECK_EQUAL("enabled", connection->state.writer.name);
        CHECK_EQUAL("enabled", connection->state.reader.name);

        CHECK_EQUAL(1U, amqp_buffer_read_size_field(read_buffer, 4));
        CHECK_EQUAL('X', amqp_buffer_getc(read_buffer));

        connection->state.reader.stop(connection);
        CHECK_EQUAL("stopped", connection->state.reader.name);
    }

    TEST_FIXTURE(ConnectionReadFixture, read_small_message)
    {
        amqp_connection_reader_initialize(connection);
        connection->state.reader.enable(connection);
        CHECK_EQUAL("enabled", connection->state.reader.name);

        amqp_buffer_t *write_buffer = amqp_allocate_buffer(context);
        const char *hello_world = "Hello World";
        write_size(write_buffer, strlen(hello_world));
        amqp_buffer_puts(write_buffer, (const unsigned char *) hello_world, strlen(hello_world));

        amqp_connection_write_buffer(connection, write_buffer);
        connection->state.reader.commence_read(connection, read_buffer, strlen(hello_world) + 4, read_callback);

//        while (run_loop_with_timeout() && amqp_connection_reader_is_state(connection, "reading"));
        while (run_loop_with_timeout() && reading);

        uint32_t size = amqp_buffer_read_size_field(read_buffer, 4);
        CHECK_EQUAL(size, strlen(hello_world));

        char buffer[32];
        size_t i;
        for (i = 0; i < size; i++)
        {
            buffer[i] = amqp_buffer_getc(read_buffer);
        }
        buffer[i] = '\0';
        CHECK_EQUAL(hello_world, buffer);

        connection->state.reader.stop(connection);
        CHECK_EQUAL("stopped", connection->state.reader.name);
    }

    TEST_FIXTURE(ConnectionReadFixture, read_huge_message)
    {
        amqp_connection_reader_initialize(connection);
        connection->state.reader.enable(connection);
        CHECK_EQUAL("enabled", connection->state.reader.name);

        const size_t size = 32 * 1024 - 4;
        amqp_buffer_t *write_buffer = amqp_allocate_buffer(context);
        amqp_buffer_grow(context, write_buffer, size + 4);
        write_size(write_buffer, size);
        for (size_t i = 0; i < size; i++)
        {
            amqp_unchecked_putc(write_buffer, 19 + i % 67);
        }

        amqp_connection_write_buffer(connection, write_buffer);

        amqp_buffer_grow(context, read_buffer, size + 4);
        connection->state.reader.commence_read(connection, read_buffer, size + 4, read_callback);

        while (run_loop_with_timeout() && reading);
        CHECK_EQUAL("enabled", connection->state.reader.name);

        CHECK_EQUAL(size, amqp_buffer_read_size_field(read_buffer, 4));

        for (size_t i = 0; i < size; i++)
        {
            int c = amqp_buffer_getc(read_buffer);
            int expect = 19 + i % 67;
	    if (expect != c)
	    {	
		CHECK_EQUAL(expect, c);
		SOUTV(i);
		SOUTV(expect);
		SOUTV(c);
		break;
	    }
        }

        connection->state.reader.stop(connection);
        CHECK_EQUAL("stopped", connection->state.reader.name);
    }

}
