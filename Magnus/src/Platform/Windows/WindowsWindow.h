#pragma once
#include "Magnus/Core/Core.h"
#include "Magnus/Core/Window.h"
#include "Magnus/Render/GraphicContext.h"
#include <GLFW/glfw3.h>

namespace Magnus {
	class MAGNUS_API WindowsWindow : public WindowBasic
	{
	public:
		WindowsWindow(const WindowAttribute& att);
		virtual ~WindowsWindow();

		//override
		void OnUpdate() override;
		inline unsigned int GetWidth() const override { return m_Data.m_Width; }
		inline unsigned int GetHeight() const override { return m_Data.m_Height; }
		// Window attributes
		inline void SetEventCallBack(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;
		virtual void* GetNativeWindow() const override {
			return (void*)m_Window; 
		};
		


		void Init(const WindowAttribute& att);
		void ShutDown();
		
	private:
		GraphicContext* m_Context;
		GLFWwindow* m_Window;
		//需要发送给glfw的数据
		struct WindowData
		{
			std::string m_Title;
			unsigned int m_Width, m_Height;
			bool m_VSync;

			EventCallbackFn EventCallback;
		};
		WindowData m_Data;
	};

}

