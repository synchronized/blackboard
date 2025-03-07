#pragma once
#include "program.h"

#include "app/resources.h"
#include "renderer/material/uniformcolor.h"

#include <utils/watchdog.h>

#include <bgfx/bgfx.h>
#include <entt/core/type_info.hpp>
#include <glm/ext.hpp>
#include <glm/glm.hpp>

#include <array>
#include <filesystem>
#include <unordered_map>
#include <variant>
#include <memory>

template<class... Ts>
struct overloaded : Ts...
{
    using Ts::operator()...;
};
template<class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

namespace blackboard::core::renderer {
namespace material {

using MaterialType = std::shared_ptr<Material>;
inline std::unordered_map<entt::id_type, MaterialType> materials;

struct Manager
{
    Manager()
    {
        m_wd = std::make_unique<utils::Watchdog>();
        m_wd->start();

        materials.emplace(entt::type_id<UniformColor>().hash(), std::make_shared<UniformColor>());

        for (auto &entry : materials)
        {
            for (auto shader_path : entry.second->paths()) {
                const auto callback_multi = [&entry](const std::vector<std::filesystem::path> &path) {
                    entry.second->init();
                };
                const auto callback = [&entry](const std::filesystem::path &path) { entry.second->init(); };
                m_wd->watch(shader_path, callback);
                m_wd->watchMany(shader_path, callback_multi);
            }
        }
    }

    ~Manager()
    {
        shutdown();
    }

    inline void shutdown()
    {

        if (bgfx::isValid(m_uniform_handle))
        {
            bgfx::destroy(m_uniform_handle);
            m_uniform_handle = BGFX_INVALID_HANDLE;
        }

        for (const auto &[name, material] : materials)
        {
            for (auto & shader_path : material->paths()) {
                m_wd->unwatch(shader_path);
            }
        }

        materials.clear();

        m_wd->close();
    }

    template<typename T>
    inline decltype(auto) material() const
    {
        assert(materials.contains(entt::type_id<T>().hash()));
        return materials.at(entt::type_id<T>().hash());
    }

    void set_uniform(bgfx::Encoder *encoder, Uniform *uniform)
    {
        if (encoder == NULL)
        {
            return;
        }

        encoder->setUniform(m_uniform_handle, uniform);
    }

    void set_uniform(Uniform *uniform)
    {
        static const uint16_t num{sizeof(Uniform) / sizeof(float[4])};
        if (!bgfx::isValid(m_uniform_handle))
        {
            m_uniform_handle = bgfx::createUniform("u_uniform", bgfx::UniformType::Vec4, num);
        }
        bgfx::setUniform(m_uniform_handle, uniform, num);
    }

private:
    bgfx::UniformHandle m_uniform_handle = BGFX_INVALID_HANDLE;

    std::unique_ptr<utils::WatchdogI> m_wd;
};
}    // namespace material

}    // namespace blackboard::core::renderer
