#pragma once

#define UUID_SYSTEM_GENERATOR
#include <stduuid/uuid.h>

#include <string>

namespace blackboard::core::components {

struct Uuid
{
    Uuid()
    {
        m_value = uuids::to_string(uuids::uuid_system_generator{}());
    }

    std::string get() const
    {
        return m_value;
    }

private:
    std::string m_value{};
};

}    // namespace blackboard::core::components
