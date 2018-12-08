//------------------------------------------------------------------------------
// Copyright (c) 2018 Darby Johnston
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions, and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions, and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
// * Neither the names of the copyright holders nor the names of any
//   contributors may be used to endorse or promote products derived from this
//   software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//------------------------------------------------------------------------------

#include <djvAV/OpenGLShader.h>

#include <djvAV/Color.h>
#include <djvAV/OpenGL.h>
#include <djvAV/Shader.h>

#include <djvCore/String.h>

using namespace djv::Core;

namespace djv
{
    namespace AV
    {
        namespace OpenGL
        {
            void Shader::_init(const std::shared_ptr<AV::Shader> & shader)
            {
                _shader = shader;

                auto glFuncs = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>();
                _vertex = glFuncs->glCreateShader(GL_VERTEX_SHADER);
                if (!_vertex)
                {
                    throw std::runtime_error("Cannot create vertex shader");
                }
                const char* src = _shader->getVertexSource().c_str();
                glFuncs->glShaderSource(_vertex, 1, &src, NULL);
                glFuncs->glCompileShader(_vertex);
                int success = 0;
                char infoLog[String::cStringLength];
                glFuncs->glGetShaderiv(_vertex, GL_COMPILE_STATUS, &success);
                if (!success)
                {
                    glFuncs->glGetShaderInfoLog(_vertex, String::cStringLength, NULL, infoLog);
                    std::stringstream s;
                    s << "Cannot compile vertex shader: " << _shader->getVertexName() << ": " << infoLog;
                    throw std::runtime_error(s.str());
                }

                _fragment = glFuncs->glCreateShader(GL_FRAGMENT_SHADER);
                if (!_fragment)
                {
                    throw std::runtime_error("Cannot create fragment shader");
                }
                src = _shader->getFragmentSource().c_str();
                glFuncs->glShaderSource(_fragment, 1, &src, NULL);
                glFuncs->glCompileShader(_fragment);
                glFuncs->glGetShaderiv(_fragment, GL_COMPILE_STATUS, &success);
                if (!success)
                {
                    glFuncs->glGetShaderInfoLog(_fragment, String::cStringLength, NULL, infoLog);
                    std::stringstream s;
                    s << "Cannot compile framgent shader: " << _shader->getFragmentName() << ": " << infoLog;
                    throw std::runtime_error(s.str());
                }

                _program = glFuncs->glCreateProgram();
                glFuncs->glAttachShader(_program, _vertex);
                glFuncs->glAttachShader(_program, _fragment);
                glFuncs->glLinkProgram(_program);
                glFuncs->glGetProgramiv(_program, GL_LINK_STATUS, &success);
                if (!success)
                {
                    glFuncs->glGetProgramInfoLog(_program, String::cStringLength, NULL, infoLog);
                    std::stringstream s;
                    s << "Cannot link program: " << _shader->getVertexName() << ": " << infoLog;
                    throw std::invalid_argument(s.str());
                }
            }

            Shader::Shader()
            {}

            Shader::~Shader()
            {
                auto glFuncs = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>();
                if (_program)
                {
                    glFuncs->glDeleteProgram(_program);
                    _program = 0;
                }
                if (_vertex)
                {
                    glFuncs->glDeleteShader(_vertex);
                    _vertex = 0;
                }
                if (_fragment)
                {
                    glFuncs->glDeleteShader(_fragment);
                    _fragment = 0;
                }
            }

            std::shared_ptr<Shader> Shader::create(const std::shared_ptr<AV::Shader> & shader)
            {
                auto out = std::shared_ptr<Shader>(new Shader);
                out->_init(shader);
                return out;
            }

            void Shader::setUniform(const std::string& name, int value)
            {
                auto glFuncs = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>();
                const GLint loc = glFuncs->glGetUniformLocation(_program, name.c_str());
                glFuncs->glUniform1iv(loc, 1, &value);
            }

            void Shader::setUniform(const std::string& name, float value)
            {
                auto glFuncs = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>();
                const GLint loc = glFuncs->glGetUniformLocation(_program, name.c_str());
                glFuncs->glUniform1fv(loc, 1, &value);
            }

            void Shader::setUniform(const std::string& name, const glm::vec2& value)
            {
                auto glFuncs = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>();
                const GLint loc = glFuncs->glGetUniformLocation(_program, name.c_str());
                glFuncs->glUniform2fv(loc, 1, &value[0]);
            }

            void Shader::setUniform(const std::string& name, const glm::vec3& value)
            {
                auto glFuncs = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>();
                const GLint loc = glFuncs->glGetUniformLocation(_program, name.c_str());
                glFuncs->glUniform3fv(loc, 1, &value[0]);
            }

            void Shader::setUniform(const std::string& name, const glm::vec4& value)
            {
                auto glFuncs = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>();
                const GLint loc = glFuncs->glGetUniformLocation(_program, name.c_str());
                glFuncs->glUniform4fv(loc, 1, &value[0]);
            }

            void Shader::setUniform(const std::string& name, const glm::mat3x3& value)
            {
                auto glFuncs = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>();
                const GLint loc = glFuncs->glGetUniformLocation(_program, name.c_str());
                glFuncs->glUniformMatrix3fv(loc, 1, GL_FALSE, &value[0][0]);
            }

            void Shader::setUniform(const std::string& name, const glm::mat4x4& value)
            {
                auto glFuncs = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>();
                const GLint loc = glFuncs->glGetUniformLocation(_program, name.c_str());
                glFuncs->glUniformMatrix4fv(loc, 1, GL_FALSE, &value[0][0]);
            }

            void Shader::setUniform(const std::string& name, const Color & value)
            {
                auto glFuncs = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>();
                const GLint loc = glFuncs->glGetUniformLocation(_program, name.c_str());
                auto color = value.convert(Pixel::Type::RGBA_F32);
                glFuncs->glUniform4fv(loc, 1, reinterpret_cast<const GLfloat *>(color.getData()));
            }

            void Shader::bind()
            {
                auto glFuncs = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>();
                glFuncs->glUseProgram(_program);
            }

        } // namespace OpenGL
    } // namespace AV
} // namespace djv