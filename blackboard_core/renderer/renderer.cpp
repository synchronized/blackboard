#include "renderer.h"

#include "platform/imgui_impl_sdl_bgfx.h"
#include "platform/window.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <imgui_impl_sdl2.h>
#include <spdlog/spdlog.h>

#include <iostream>

namespace blackboard::core {
namespace renderer {

bool init(Window &window, const Api renderer_api, const uint16_t width, const uint16_t height)
{
    //    SDL_SysWMinfo wmi;
    //    SDL_VERSION(&wmi.version);
    //    if (!SDL_GetWindowWMInfo(window.window, &wmi))
    //    {
    //        std::cout << "SDL_SysWMinfo could not be retrieved. SDL_Error: " << SDL_GetError() << std::endl;
    //        return false;
    //    }

    bgfx::PlatformData pd{};
    bgfx::Init bgfx_init;
    bgfx::renderFrame();    // single threaded mode
    switch (renderer_api)
    {
        case Api::metal:
            bgfx_init.type = bgfx::RendererType::Metal;    // auto choose renderer
            break;
        case Api::d3d11:
            bgfx_init.type = bgfx::RendererType::Direct3D11;    // auto choose renderer
            break;
        //case Api::webgpu:
        //    bgfx_init.type = bgfx::RendererType::WebGPU;    // auto choose renderer
        //    break;
        default:
            bgfx_init.type = bgfx::RendererType::Count;    // auto choose renderer
            break;
    }
    const auto [drawable_width, drawable_height] = window.get_size_in_pixels();
    bgfx_init.resolution.width = drawable_width;
    bgfx_init.resolution.height = drawable_height;
    pd.nwh = renderer::native_window_handle(window.get_native_handle());
    bgfx_init.resolution.numBackBuffers = 1;

    bgfx_init.resolution.reset = BGFX_RESET_VSYNC | BGFX_RESET_HIDPI | BGFX_RESET_MSAA_X4;
    bgfx_init.platformData = pd;
    if (!bgfx::init(bgfx_init)) {
        spdlog::error("bgfx::init failed");
        return false; // 初始化失败
    }

    bgfx::setDebug(BGFX_DEBUG_TEXT);
    bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x000000FF, 1.0f, 0);
    bgfx::setViewRect(0, 0, 0, drawable_width, drawable_height);

    return true;
}
}    // namespace renderer
}    // namespace blackboard::core
