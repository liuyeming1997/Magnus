#include <Magnus.h>
class Sandbox : public Magnus::Application
{
public:
	Sandbox() {

	}
	~Sandbox() {

	}

private: 

};
Magnus::Application* Magnus::CreateApplication() {
	return new Sandbox();
}

