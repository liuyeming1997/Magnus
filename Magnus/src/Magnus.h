#pragma once

//For use by Magnus application
#include "Magnus/Application.h"
#include "Magnus/Log.h"
#include "Magnus/ImGui/ImGuiLayer.h"
#include "Magnus/Input.h"
#include "Magnus/KeyCode.h"
#include "Magnus/MouseButtonCode.h"
//-----Entry Point------------------
#include "Magnus/EntryPoint.h"
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
#include "Magnus/Core.h"