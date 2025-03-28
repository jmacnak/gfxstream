/*
 * Copyright (C) 2021 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "Gles.h"

#include <iostream>
#include <vector>

namespace gfxstream {
namespace {

constexpr const char kGles2Lib[] = "libGLESv2.so";

static void GL_APIENTRY GlDebugCallback(GLenum, GLenum, GLuint, GLenum, GLsizei,
                                        const GLchar* message, const void*) {
  std::cout << "GlDebugCallback message: " << message << std::endl;
}

}  // namespace

/*static*/ gfxstream::expected<Gles, std::string> Gles::Load() {
    Gles gles;
    gles.lib_ = GFXSTREAM_EXPECT(Lib::Load(kGles2Lib));

    #define LOAD_GLES_FUNCTION_POINTER(return_type, function_name, signature, \
                                      args)                                   \
    gles.function_name = reinterpret_cast<return_type(*) signature>(          \
        gles.lib_.GetSymbol(#function_name));                                 \
    if (gles.function_name == nullptr) {                                      \
        gles.function_name = reinterpret_cast<return_type(*) signature>(      \
            gles.lib_.GetSymbol(#function_name));                             \
    }                                                                         \
    if (gles.function_name == nullptr) {                                      \
        gles.function_name = reinterpret_cast<return_type(*) signature>(      \
            gles.lib_.GetSymbol(#function_name "OES"));                       \
    }                                                                         \
    if (gles.function_name == nullptr) {                                      \
        gles.function_name = reinterpret_cast<return_type(*) signature>(      \
            gles.lib_.GetSymbol(#function_name "EXT"));                       \
    }                                                                         \
    if (gles.function_name == nullptr) {                                      \
        gles.function_name = reinterpret_cast<return_type(*) signature>(      \
            gles.lib_.GetSymbol(#function_name "ARB"));                       \
    }

    FOR_EACH_GLES_FUNCTION(LOAD_GLES_FUNCTION_POINTER);

    gles.Init();

    return std::move(gles);
}

/*static*/ gfxstream::expected<Gles, std::string> Gles::LoadFromEgl(Egl* egl) {
    Gles gles;

    #define LOAD_GLES_FUNCTION_POINTER_FROM_EGL(return_type, function_name, \
                                               signature, args)             \
    gles.function_name = reinterpret_cast<return_type(*) signature>(        \
        egl->eglGetProcAddress(#function_name));

    FOR_EACH_GLES_FUNCTION(LOAD_GLES_FUNCTION_POINTER_FROM_EGL);

    gles.Init();

    return std::move(gles);
}

void Gles::Init() {
    const GLubyte* glesVendor = glGetString(GL_VENDOR);
    if (glesVendor == nullptr) {
        return;
    }

    const std::string glesExtensionsStr = reinterpret_cast<const char*>(glGetString(GL_EXTENSIONS));
    if (glesExtensionsStr.empty()) {
        return;
    }

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_HIGH, 0,
                          nullptr, GL_TRUE);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_MEDIUM, 0,
                          nullptr, GL_TRUE);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_LOW, 0,
                          nullptr, GL_TRUE);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE,
                          GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE);
    glDebugMessageCallback(&GlDebugCallback, nullptr);
}

std::optional<GLuint> Gles::CreateShader(GLenum shader_type,
                                         const std::string& shader_source) {
    GLuint shader = glCreateShader(shader_type);

    const char* const shader_source_cstr = shader_source.c_str();
    glShaderSource(shader, 1, &shader_source_cstr, nullptr);
    glCompileShader(shader);

    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    if (status != GL_TRUE) {
        GLsizei log_length = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);

        std::vector<char> log(log_length + 1, 0);
        glGetShaderInfoLog(shader, log_length, nullptr, log.data());

        glDeleteShader(shader);
        return std::nullopt;
    }

    return shader;
}

std::optional<GLuint> Gles::CreateProgram(
        const std::string& vert_shader_source,
        const std::string& frag_shader_source) {
    auto vert_shader_opt = CreateShader(GL_VERTEX_SHADER, vert_shader_source);
    if (!vert_shader_opt) {
      return std::nullopt;
    }
    auto vert_shader = *vert_shader_opt;

    auto frag_shader_opt = CreateShader(GL_FRAGMENT_SHADER, frag_shader_source);
    if (!frag_shader_opt) {
      return std::nullopt;
    }
    auto frag_shader = *frag_shader_opt;

    GLuint program = glCreateProgram();
    glAttachShader(program, vert_shader);
    glAttachShader(program, frag_shader);
    glLinkProgram(program);

    GLint status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);

    if (status != GL_TRUE) {
      GLsizei log_length = 0;
      glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_length);

      std::vector<char> log(log_length + 1, 0);
      glGetProgramInfoLog(program, log_length, nullptr, log.data());

      glDeleteProgram(program);
      return std::nullopt;
    }

    glDeleteShader(vert_shader);
    glDeleteShader(frag_shader);

    return program;
}

}  // namespace gfxstream
