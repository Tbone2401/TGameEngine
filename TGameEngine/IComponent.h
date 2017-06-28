#pragma once
class IComponent
{
public:
	virtual ~IComponent();

	virtual void Initialise() = 0;
	virtual void Tick() = 0;
	virtual void Destroy() = 0;
};

