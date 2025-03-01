#include "Component.hpp"

int Component::nextCreationID = 0;

Component::Component(GameObject& parent) :
	gameObject{ parent },
	uniqueID{ nextCreationID },
	enabled{ true }
{
	// UniqueID handling
	nextCreationID++;
}

void Component::Update() {}

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