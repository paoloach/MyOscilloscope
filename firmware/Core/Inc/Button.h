/*
 * Button.h
 *
 *  Created on: Jan 6, 2022
 *      Author: Paolo Achdjian
 */

#pragma once

#include <queue>
#include <map>
#include <functional>

enum class ButtonEvent {
	B1RISE,
	B1LOWER,
	B2RISE,
	B2LOWER,
	B3RISE,
	B4RISE,
	B5RISE,
	B6RISE
};

class Button {
public:
	void loop();
	void newIntEvent(ButtonEvent event){
		events.push(event);
	}
	void addCallback(ButtonEvent event, std::function< void (void)>  callback ){
		callbacks[event] = callback;
	}
private:
	std::queue<ButtonEvent> events;
	std::map<ButtonEvent, uint32_t> lastEventTime;
	std::map<ButtonEvent, std::function< void (void) > > callbacks;
};

