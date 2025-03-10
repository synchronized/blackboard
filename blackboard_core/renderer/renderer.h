#pragma once
#include "renderer/material/manager.h"

#include <string>

struct SDL_Window;

namespace blackboard::core {

struct Window;

namespace renderer {

enum class Api : uint8_t
{
    none = 0,
    metal,
    d3d11,
    webgpu,
    count
};

bool init(Window &window, const Api, const uint16_t width, const uint16_t height);

inline renderer::material::Manager &material_manager()
{
    static renderer::material::Manager mm;
    return mm;
}
}    // namespace renderer
}    // namespace blackboard::core
