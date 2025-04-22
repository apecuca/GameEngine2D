#include "Component.hpp"

Component::Component(GameObject& parent) : Entity(),
	gameObject{ parent },
	enabled{ true }
{
	//
}

//
// Generic component
// for testing :)
//

GenericComponent::GenericComponent(GameObject& parent) :
	Component(parent)
{
	// Constructor example
}

void GenericComponent::Update()
{
	// Custom behaviour example
}