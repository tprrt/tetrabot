#ifndef ROBOTINFO_H
#define ROBOTINFO_H

#include <set>

#include "NodeInfo.h"
#include "EdgeInfo.h"
#include "LinkInfo.h"

#include "SignalInfo.h"

class RobotInfo {

protected:
	SignalInfo signal;

	std::set<LinkInfo> architecture;

public:
	RobotInfo();

	//virtual ~RobotInfo();

	void addSignal(const SignalInfo signal);

	const SignalInfo getSignal() const;

	void addLink(const LinkInfo link);

	const std::set<LinkInfo> getArchitecture() const;
};

#endif /* ROBOTINFO_H */
