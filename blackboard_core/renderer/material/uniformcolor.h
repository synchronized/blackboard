#pragma once
#include "app/resources.h"
#include "renderer/program.h"
#include "renderer/material/material.h"

#include <bgfx/bgfx.h>
#include <bgfx/embedded_shader.h>

#include <array>
#include <filesystem>
#include <unordered_map>
#include <variant>

namespace blackboard::core::renderer {
namespace material {

class UniformColorDynamic : public MaterialShaderSource
{
public:
    UniformColorDynamic()
        : MaterialShaderSource(
            blackboard::core::resources::path() / vert_path,
            blackboard::core::resources::path() / frag_path)
    {}

    ~UniformColorDynamic() = default;

private:
    inline static std::string vert_path{"assets/shaders/uniform_color/uniform_color.vert"};
    inline static std::string frag_path{"assets/shaders/uniform_color/uniform_color.frag"};
};


class UniformColor : public Material
{
public:
    UniformColor();

    ~UniformColor() = default;

    virtual void init() override
    { }

    virtual std::vector<std::filesystem::path> paths() const override
    {
        return {};
    }

    const bgfx::ProgramHandle program_handle() const override
    {
        return shader_prog.program();
    }

    virtual const bool isValid() const override
    {
        return bgfx::isValid(shader_prog.program());
    }

private:
    Program shader_prog;
};

}    // namespace material

}    // namespace blackboard::core::renderer
