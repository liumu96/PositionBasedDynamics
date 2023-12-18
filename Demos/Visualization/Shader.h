#pragma once

#include <map>
#include <string>
#include <glad/gl.h>

namespace PBD
{
    class Shader
    {
    public:
        void compileShaderString(GLenum whichShader, const std::string &source);
        void compileShaderFile(GLenum whichShader, const std::string &filename);
        void createAndLinkProgram();
        void addUniform(const std::string &uniform);

        void begin();
        void end();

        // An indexer that returns the location of the attribute/uniform

        GLuint getUniform(const std::string &uniform);

    private:
        bool m_initialized;
        GLuint m_program;

        std::map<std::string, GLuint> m_uniforms;
        GLuint m_shaders[3];
    };
}