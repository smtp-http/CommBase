set(EV_EXAMPLE_CLI_SRCS
		ev_example_client.c)
set(EV_EXAMPLE_SVR_SRCS
		ev_example_server.c)
set(EV_CONNECTION_TEST_SRCS
		conn_test.cpp)
#ADD_EXECUTABLE(ev_example_client ${EV_EXAMPLE_CLI_SRCS})
#ADD_EXECUTABLE(ev_example_server ${EV_EXAMPLE_SVR_SRCS})
ADD_EXECUTABLE(connection_test ${EV_CONNECTION_TEST_SRCS})

#MESSAGE(STATUS "========== test src:" ${EV_EXAMPLE_SVR_SRCS}${EV_EXAMPLE_CLI_SRCS})
#TARGET_LINK_LIBRARIES(ev_example_client event event_openssl event_pthreads)
#TARGET_LINK_LIBRARIES(ev_example_server event event_openssl event_pthreads)
TARGET_LINK_LIBRARIES(connection_test ucom pthread event)