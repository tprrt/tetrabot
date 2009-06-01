#include "RobotInfo.h"

RobotInfo::RobotInfo() {

}

void RobotInfo::addSignal(const SignalInfo signal) {
	this->signal = signal;
}

const SignalInfo RobotInfo::getSignal() const {
	return this->signal;
}

void RobotInfo::addLink(const LinkInfo link) {
	this->architecture.insert(link);
}

const std::set<LinkInfo> RobotInfo::getArchitecture() const {
	return this->architecture;
}

