#include "entity.h"

using namespace std;

KEntity::KEntity(int id) {
	mID = id;
}

//Just crappy linear searches
//I don't think any objects will have more than 20 components, so this shouldn't be an issue
//TODO (maybe): If this gets too slow, replace it with an std::map or something

KComponent* KEntity::getComponent(unsigned int id) {
	for (vector<KComponent*>::iterator it = mComponents.begin(); it != mComponents.end(); ++it) {
		if ((*it)->getID() == id) return (*it);
	}

	return NULL;
}
void KEntity::addComponent(KComponent* component) {
	mComponents.push_back(component);
}
void KEntity::addComponent(std::vector<KComponent*> components, unsigned int id) {
	for (vector<KComponent*>::iterator it = components.begin(); it != components.end(); ++it) {
		if ((*it)->getID() == id) {
			addComponent(*it);
			return;
		}
	}
}
bool KEntity::hasComponent(unsigned int id) {
	for (vector<KComponent*>::iterator it = mComponents.begin(); it != mComponents.end(); ++it) {
		if ((*it)->getID() == id) return true;
	}

	return false;
}

unsigned int KEntity::getID() {
	return mID;
}