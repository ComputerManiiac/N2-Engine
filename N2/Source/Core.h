#ifndef CORE_H
#define CORE_H

#include <GL\glew.h>
#include <GLFW\glfw3.h>


#include "OverloadNew.h"


#include "Loader.h"

#include "Entity.h"

#include "Component.h"
#include "TransformComponent.h"
#include "RenderComponent.h"

#include "System.h"
#include "RenderSystem.h"

#include "timer.h"


typedef RenderSystem<RenderComponent> RenderSys;

#endif