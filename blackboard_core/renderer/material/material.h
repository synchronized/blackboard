#pragma once

#include "renderer/program.h"

#include <bgfx/bgfx.h>

#include <entt/core/type_info.hpp>

#include <array>
#include <filesystem>
#include <variant>
#include <unordered_map>
#include <mutex>

namespace blackboard::core::renderer {
namespace material {

struct Uniform
{
    std::array<float, 3> u_camera_position{0.0f, 0.0f, 0.0f};
    float u_time{0.0f};
    std::array<float, 4> u_color{1.0f, 0.0f, 0.0f, 1.0f};
    std::array<float, 4> u_edge_color{0.0f, 1.0f, 0.0f, 1.0f};
    float u_edge_thickness{1.0f};
    std::array<float, 3> padding{0.0f, 0.0f, 0.0f};
};

class Material
{
public:
    struct Material_concept
    {
        virtual ~Material_concept() = default;
        virtual std::unique_ptr<Material_concept> clone() const = 0;
    };

    template<typename T>
    struct Material_model : public Material_concept
    {
        virtual std::unique_ptr<Material_concept> clone() const override
        {
            return std::make_unique<Material_concept>(*this);
        }
    };

public:
    virtual void init() = 0;

    virtual std::vector<std::filesystem::path> paths() const = 0;

    virtual const bgfx::ProgramHandle program_handle() const = 0;

    virtual const bool isValid() const = 0;

private:
    //std::mutex mutex;

private:
    //std::unique_ptr<Material_concept> p_impl;
};


class MaterialShaderSource : public Material {
public:
    MaterialShaderSource(const std::filesystem::path &vert_shader, const std::filesystem::path &frag_shader)
        : m_vert_path(vert_shader), m_frag_path(frag_shader)
    {
        init();
    }

    virtual void init() override
    {
        shader_prog.init(m_vert_path, m_frag_path);
    }

    virtual std::vector<std::filesystem::path> paths() const override
    {
        return {m_vert_path, m_frag_path};
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
    std::filesystem::path m_vert_path;
    std::filesystem::path m_frag_path;
};

}    // namespace material

}    // namespace blackboard::core::renderer