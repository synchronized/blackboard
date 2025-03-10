#pragma once
#include <bgfx/bgfx.h>
#include <imgui.h>

#include <filesystem>
#include <string>

namespace blackboard {
namespace core {
struct State;
}
namespace editor {

void init();

void dockspace();

void entities_window(core::State &state);

}    // namespace editor
}    // namespace blackboard
