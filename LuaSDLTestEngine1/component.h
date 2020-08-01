#ifndef COMPONENT_H
#define COMPONENT_H

class KComponent
{
public:
	KComponent(unsigned int id);
	virtual ~KComponent() {};

	unsigned int getID();
private:
	unsigned int mID;
};

#endif
