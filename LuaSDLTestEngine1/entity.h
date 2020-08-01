#ifndef ENTITY_H
#define ENTITY_H

#include "globals.h"
#include "component.h"

class KEntity
{
public:

	KEntity(int id);

	KComponent* getComponent(unsigned int id);
	void addComponent(KComponent* component);
	void addComponent(std::vector<KComponent*> components, unsigned int id);
	bool hasComponent(unsigned int id);

	unsigned int getID();
private:
	std::vector<KComponent*> mComponents;
	unsigned int mID;
};

#endif
