#include "window.h"

#include <SDL2/SDL.h>

namespace blackboard::core {

class WindowImpl {
    friend class Window;

    WindowImpl(std::string title, uint16_t width, uint16_t height, bool fullscreen) {
        auto flag = fullscreen 
                ?  (SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_BORDERLESS) 
                : SDL_WINDOW_SHOWN;
        flag |= SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI;
        auto sdlwindow = SDL_CreateWindow(
                title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                width, height, flag);
        //    SDL_SetWindowBordered(window.window, SDL_FALSE);

        window = sdlwindow;
        windowHandle = SDL_GetWindowID(sdlwindow);
    }
    ~WindowImpl() {
        SDL_DestroyWindow(window);
    }

    std::pair<uint16_t, uint16_t> get_size_in_pixels() const
    {
        int w{0u}, h{0u};
        SDL_GL_GetDrawableSize(window, &w, &h);
        return {w, h};
    }

    std::pair<uint16_t, uint16_t> get_position() const
    {
        int x{0u}, y{0u};
        SDL_GetWindowPosition(window, &x, &y);
        return {x, y};
    }

    void* get_native_handle() const {
        return (void*)(intptr_t)windowHandle;
    }

    void* get_native_window() const {
        return (void*)window;
    }


private:
    SDL_Window *window{nullptr};
    Uint32 windowHandle{ 0 };
};



void Window::init_platform_window()
{
    destroy_platform_window();
    impl = new WindowImpl(title, width, height, fullscreen);
}

void Window::destroy_platform_window() {
    if (impl) delete impl;
}

std::pair<uint16_t, uint16_t> Window::get_size_in_pixels() const
{
    if (impl) return impl->get_size_in_pixels();
    return {0u, 0u};
}

std::pair<uint16_t, uint16_t> Window::get_position() const
{
    if (impl) return impl->get_position();
    return {0u, 0u};
}

void* Window::get_native_handle() const {
    if (impl) return impl->get_native_handle();
    return NULL;
}

void* Window::get_native_window() const {
    if (impl) return impl->get_native_window();
    return NULL;
}

}    // namespace blackboard::core
