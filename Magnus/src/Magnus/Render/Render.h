#pragma once
namespace Magnus {
	enum RenderAPI
	{
		NONE = 0,
		OPENGL
	};
	class Render
	{
	public:
		static RenderAPI Get() { return s_RenderAPI; }

	private:
		static RenderAPI s_RenderAPI;

	};

}