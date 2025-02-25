#pragma once
#include <SDL2/SDL.h>

#include <filesystem>

namespace blackboard::core::resources {

inline std::filesystem::path path()
{
    return std::filesystem::current_path();
}

}    // namespace blackboard::core::resources
