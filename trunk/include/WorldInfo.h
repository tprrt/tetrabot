#ifndef WORLDINFO_H
#define WORLDINFO_H

#include "Vector3Gen.h"

class WorldInfo {

protected:
	Vector3Gen *min;
	Vector3Gen *max;
	Vector3Gen *gravity;

public:
	WorldInfo(Vector3Gen *min, Vector3Gen *max, Vector3Gen *gravity);

	//virtual ~WorldInfo();

	const Vector3Gen *getMin() const;

	const Vector3Gen *getMax() const;

	const Vector3Gen *getGravity() const;
};

#endif /* WORLDINFO_H */
