#include "eventlooperimp.h"

using namespace ucom;

EventLooper::EventLooper()
{
}

EventLooper& EventLooper::GetInstance()
{
	static EventLooperImp s_inst;
	return s_inst;
}
	
void EventLooper::RunEventLoop()
{
}

void EventLooper::StopEventLoop(long timeAfter)
{
}

TimerID EventLooper::ScheduleTimer(struct timeval *tv, TimerFlag flag, ITimerUserSink *sink)
{
	return (TimerID)0;
}

void EventLooper::CancelTimer(TimerID tid)
{
}
	
EventLooperImp::EventLooperImp()
{
	m_evBase = event_base_new();
}

EventLooperImp::~EventLooperImp()
{
	event_base_free(m_evBase);
	m_evBase = NULL;
}

event_base* EventLooperImp::CurrentEvBase() const
{
	return m_evBase;
}

void EventLooperImp::RunEventLoop()
{
	if (m_evBase){
		event_base_dispatch(m_evBase);
	}
}

void EventLooperImp::StopEventLoop(long timeAfter)
{
	if (m_evBase){
		struct timeval tv = {timeAfter/1000, (timeAfter%1000)*1000};
		event_base_loopexit(m_evBase, &tv);
	}
}

TimerID EventLooperImp::ScheduleTimer(struct timeval *tv, TimerFlag flag, ITimerUserSink *sink)
{
	return (TimerID)0;
}

void EventLooperImp::CancelTimer(TimerID tid)
{
}
