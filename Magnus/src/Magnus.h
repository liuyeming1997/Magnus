#pragma once

//For use by Magnus application
#include "Magnus/Core/Application.h"
#include "Magnus/Core/Log.h"
#include "Magnus/ImGui/ImGuiLayer.h"
#include "Magnus/Core/Input.h"
#include "Magnus/Core/KeyCode.h"
#include "Magnus/Core/MouseButtonCode.h"
//-----Entry Point------------------
#include "Magnus/Core/EntryPoint.h"
//----------------------------------

//---------Render-------------------
#include "Magnus/Render/CameraControl.h"
#include "Magnus/Render/RenderCommand.h"
#include "Magnus/Render/Render.h"
#include "Magnus/Render/Texture.h"
#include "Platform/OpenGL/OpenGlShader.h"
#include "Platform/OpenGL/OpenGLTexture.h"

//---------Core?--------------------
#include "Magnus/Core/Timestep.h"
#include "Magnus/Core/Core.h"