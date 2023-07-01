#pragma once

#include <../external/glm/glm/mat4x4.hpp>
#include <string>

namespace RenderEngine {

    class ShaderProgram
    {
    public:
        ShaderProgram(const std::string& vertex_shader_src, const std::string& fragment_shader_src);
        ShaderProgram(ShaderProgram&&);
        ShaderProgram& operator=(ShaderProgram&&);
        ~ShaderProgram();

        ShaderProgram() = delete;
        ShaderProgram(const ShaderProgram&) = delete;
        ShaderProgram& operator=(const ShaderProgram&) = delete;

        void bind() const;
        static void unbind();
        bool isCompiled() const { return m_isCompiled; }
        void set_matrix4(const std::string& name, const glm::mat4& matrix) const;
        void set_matrix3(const std::string& name, const glm::mat3& matrix) const;
        void set_vec3(const std::string& name, const glm::vec3& value) const;
        void set_float(const std::string& name, const float value) const;
        void set_int(const std::string& name, const int integ) const;

    private:
        bool m_isCompiled = false;
        unsigned int m_id = 0;
    };

}