#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "System.h"
#include "RenderComponent.h"

#include <vector>

template<typename T>
class RenderSystem : public System
{
public:
	RenderSystem() {}
	~RenderSystem() {}

	void registerComp(Component* component)
	{
		T* tComp = dynamic_cast<T*>(component);
		if (tComp != nullptr)
			subscribers.push_back(tComp);
	}

	void removeComp(Component* component)
	{
		T* tComp = dynamic_cast<T*>(component);
		if (tComp != nullptr)
		{
			subscribers.erase(std::remove(subscribers.begin(), subscribers.end(), tComp));
		}
	}

private:
	std::vector<T*> subscribers;
};

#endif