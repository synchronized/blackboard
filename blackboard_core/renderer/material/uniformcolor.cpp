#include "renderer/material/uniformcolor.h"

#include <spdlog/spdlog.h>

#include <glsl/uniform_color_fs.sc.bin.h>
#include <essl/uniform_color_fs.sc.bin.h>
#include <spirv/uniform_color_fs.sc.bin.h>
#include <glsl/uniform_color_vs.sc.bin.h>
#include <essl/uniform_color_vs.sc.bin.h>
#include <spirv/uniform_color_vs.sc.bin.h>
#if defined(_WIN32)
#include <dx11/uniform_color_fs.sc.bin.h>
#include <dx11/uniform_color_vs.sc.bin.h>
#endif //  defined(_WIN32)
#if __APPLE__
#include <mtl/uniform_color_fs.sc.bin.h>
#include <mtl/uniform_color_vs.sc.bin.h>
#endif // __APPLE__


namespace blackboard::core::renderer {
namespace material {

	static const bgfx::EmbeddedShader s_embeddedShaders[] =
	{
        BGFX_EMBEDDED_SHADER(uniform_color_vs),
        BGFX_EMBEDDED_SHADER(uniform_color_fs),

		BGFX_EMBEDDED_SHADER_END()
	};

UniformColor::UniformColor() {
    bgfx::ShaderHandle vsh = bgfx::createEmbeddedShader(s_embeddedShaders, bgfx::getRendererType(), "uniform_color_vs");
    bgfx::ShaderHandle fsh = bgfx::createEmbeddedShader(s_embeddedShaders, bgfx::getRendererType(), "uniform_color_fs");
    if (!bgfx::isValid(vsh) && !bgfx::isValid(fsh))
    {
        spdlog::error("createShader failed");
        return;
    }

    auto program = bgfx::createProgram(vsh, fsh, true);
    shader_prog.init(vsh, fsh, program);
}

}    // namespace material

}    // namespace blackboard::core::renderer
