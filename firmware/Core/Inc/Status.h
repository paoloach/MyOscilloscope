/*
 * Status.h
 *
 *  Created on: Jan 7, 2022
 *      Author: Paolo Achdjian
 */

#pragma once


enum class Status {
	Idle,
	ContinuosTriggerWaiting,
	Acquiring
};

extern Status status;

