#ifndef SINUSOIDINFO_H
#define SINUSOIDINFO_H

#include <stdexcept>

#include "SignalInfo.h"

class SinusoidInfo : public SignalInfo {

protected:
	float period;

	float scale;

	float phase;

public:
	SinusoidInfo(const float period, const float scale, const float phase);

	//virtual ~SinusoidInfo();

	float getPeriod() const;

	float getScale() const;

	float getPhase() const;

};

#endif /* SINUSOIDINFO_H */
