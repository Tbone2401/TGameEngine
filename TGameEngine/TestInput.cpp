#include "stdafx.h"
#include "TestInput.h"
#include "InputManager.h"


TestInput::TestInput()
{
}


TestInput::~TestInput()
{
}
//void TestInput::Testing()
//{
//	std::cout << "Testing function pointer calling" << std::endl;
//}
void TestInput::Initialise()
{
	SA::delegate<void()> delegateType;
	auto dInstance = decltype(delegateType)::create<TestInput, &TestInput::Testing>(this); //this is the function pointer we need here
	InputManager::getInstance().AddInput(dInstance, 'W');
	//InputManager::getInstance().AddInput();
}
void TestInput::Tick()
{

}
void TestInput::Destroy()
{

}
void TestInput::Testing()
{
	std::cout << "W is pressed" << std::endl;
}