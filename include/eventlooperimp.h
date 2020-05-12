#ifndef __CDYEVENTLOOPERIMP_H__
#define __CDYEVENTLOOPERIMP_H__

//#include <event.h>
#include <event2/event.h>
#include "eventlooper.h"

namespace ucom{

class EventLooperImp : public EventLooper
{
	struct event_base *m_evBase;
public:
	EventLooperImp();
	~EventLooperImp();
public:
	event_base* CurrentEvBase() const;
	
	virtual void RunEventLoop();

	virtual void StopEventLoop(long timeAfter);
	
	virtual TimerID ScheduleTimer(struct timeval *tv, TimerFlag flag, ITimerUserSink *sink);
	
	virtual void CancelTimer(TimerID tid);
};

};
#endif //__CDYEVENTLOOPERIMP_H__