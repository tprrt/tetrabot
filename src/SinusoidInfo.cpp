#include "SinusoidInfo.h"

SinusoidInfo::SinusoidInfo(const float period, const float scale, const float phase) {

	if(period < 0) {
		throw std::invalid_argument("Sinusoid period something less 0");
	}
	this->period = period;
	this->scale = scale;
	this->phase = phase;

}

float SinusoidInfo::getPeriod() const {
	return this->period;
}

float SinusoidInfo::getScale() const {
	return this->scale;
}

float SinusoidInfo::getPhase() const {
	return this->phase;
}

