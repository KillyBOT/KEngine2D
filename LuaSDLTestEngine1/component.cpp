#include "component.h"

KComponent::KComponent(unsigned int id) {
	mID = id;
}

unsigned int KComponent::getID() { return mID; }