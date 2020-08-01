#ifndef SYSTEM_H
#define SYSTEM_H

#include "globals.h"
#include "entity.h"

class KSystem
{
public:

	KSystem(unsigned int id);

	virtual void load() = 0;
	virtual void update(Uint32 dt, std::vector<KEntity*> entities) = 0;

	//virtual void sendEvent();

	virtual ~KSystem() {}

	unsigned int getID();
private:
	unsigned int mID;
};

#endif
