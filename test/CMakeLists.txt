set(EV_EXAMPLE_SRCS
		ev_example.c)
ADD_EXECUTABLE(ev_example ${EV_EXAMPLE_SRCS})
MESSAGE(STATUS "========== test src:" ${EV_EXAMPLE_SRCS})
TARGET_LINK_LIBRARIES(ev_example event event_openssl event_pthreads)
