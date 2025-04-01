#include "event_manager.h"
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

static Event* head = NULL;

void EVENT_MANAGER_Init(void) {
   head = NULL;
}


bool EVENT_MANAGER_RegisterEvent(Event* event, OnEventHandler onEvent, void* context) {
	Event* temp = head;
	if(NULL==event) return false;
	if(NULL == onEvent) return false;
	
	if(head == NULL){
	    head = event;
	    event->isScheduled = false;
	    event->scheduledTime = 0;
	    event->onEvent = onEvent;
	    event->context = context;
        event->next=NULL;
        return true;
	}
	else
	{
	while(1){
	        if(temp == event) return false;
	        if(temp->next==NULL){
	        temp->next=event;
	        event->isScheduled = false;
	        event->scheduledTime = 0;
	        event->onEvent = onEvent;
	        event->context = context;
            event->next=NULL;
            return true;
	        }
	        else temp = temp->next;
	    }
	}
    return false;
}



void EVENT_MANAGER_UnregisterEvent(Event* event) {
    Event* temp1 = head;
    if(head == NULL) return;
    if(event == head){
        head=event->next;
        return;
	    }
    
    while(temp1->next!=event){
	        if(temp1->next==event){
	            temp1->next==event->next;
	            return;
	        }
	        else temp1 = temp1->next;
	    }
}


bool EVENT_MANAGER_ScheduleEvent(Event* event, uint64_t time) {
    Event* temp = head;
    while(1){
	   if(temp==event){
	        event->isScheduled = true;
	        event->scheduledTime = time;
	        return true;
	   }
	   else temp = temp->next;
    }
	return false;
}


void EVENT_MANAGER_Proc(uint64_t currentTime) {
    Event* temp = head;
    while(temp!=NULL){
        if(temp->next!=NULL){
    	    if(temp->isScheduled){
    	        if(temp->scheduledTime == currentTime){
    	            temp->isScheduled = false;
    	            temp->onEvent(temp, temp->scheduledTime, temp->context);
    	        }
    	    }
    	    temp=temp->next;
        }
        else break;
    }
}

