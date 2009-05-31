#ifndef COMPONENTINFO_H
#define COMPONENTINFO_H

#include <stdexcept>

class ComponentInfo {

protected:

	int id;

	float weight;

public:
	ComponentInfo(const float weight);

	//virtual ~ComponentInfo();

	const int getId() const;

	const float getWeight() const;

};

#endif /* COMPONENTINFO_H */
