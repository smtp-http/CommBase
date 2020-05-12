/*
 ============================================================================
 Name        : libevent_sample.c
 Author      : killerg
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include <netinet/tcp.h>

#include <event2/event.h>
#include <event2/listener.h>
#include <event2/util.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>


int main(void) {
	struct event_base* base = event_base_new();

	struct sockaddr saddr;
	int socklen = sizeof(saddr);
	
	struct bufferevent *conect_dev = bufferevent_socket_new(base,-1,BEV_OPT_DEFER_CALLBACKS | BEV_OPT_CLOSE_ON_FREE);
	if( !conect_dev){
		printf("bufferevent socket new error!\n ");
		return -1;
	}

	struct timeval tv = {15,0};
	bufferevent_set_timeouts(conect_dev,&tv,NULL);

	//bufferevent_setcb(conect_dev,

	event_base_dispatch(base);

	event_base_free(base);
}
