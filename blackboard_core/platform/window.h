#pragma once

#include <string>

namespace blackboard::core {

class WindowImpl;

struct Window
{

    void init_platform_window();
    void destroy_platform_window();

    std::pair<uint16_t, uint16_t> get_size_in_pixels() const;

    // get position
    std::pair<uint16_t, uint16_t> get_position() const;

    void* get_native_handle() const;
    void* get_native_window() const;

    std::string title{"title"};
    uint16_t width{1280u};
    uint16_t height{720u};
    uint16_t imgui_view_id{255};    // might be possible to remove this id
    bool fullscreen{false};
    bool is_dragging{false};
    WindowImpl* impl{nullptr};
};

}    // namespace blackboard::core
