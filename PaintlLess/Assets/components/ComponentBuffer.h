#include "../ecs/Component.h"
#include <vector>

class ComponentBuffer : public Component
{
public:
	ComponentBuffer(){}
	virtual ~ComponentBuffer();
	virtual void update() override;
	virtual void render() override;
	void addComponent(Component* component);
private:
	std::vector<Component*> components;
};