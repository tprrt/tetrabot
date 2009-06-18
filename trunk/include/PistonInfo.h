#ifndef PISTONINFO_H
#define PISTONINFO_H

#include "EdgeInfo.h"

class PistonInfo : public EdgeInfo {

protected:
	float velocity;

	float strength;

public:
	PistonInfo(const float weight, const float minSize, const float maxSize, const float velocity, const float strength);

	//virtual ~PistonInfo();

	const float getVelocity() const;

	const float getStrenght() const;
};

#endif /* PISTON_H */
