#include <glad.h>
#include <stdio.h>

#include "../util.h"
#include "../io/io.h"
#include "render_internal.h"

/**
 * Potentially Deprecated.
 * @deprecated
 */
u32 render_shader_create(const char* path_vert, const char* path_frag){
    int success;
    char log[512];

    //Vertex Shader
    File file_vertex = io_file_read(path_vert);
    if(!file_vertex.is_valid){
        ERROR_EXIT("Error reading shader: %s\n", path_vert);
    }

    u32 shader_vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shader_vertex, 1, (const char *const *)&file_vertex, NULL);
    glCompileShader(shader_vertex);
    glGetShaderiv(shader_vertex, GL_COMPILE_STATUS, &success);

    if(!success){
        glGetShaderInfoLog(shader_vertex, 512, NULL, log);
        ERROR_EXIT("Error compiling shader: %s\n", log);
    }

    //Fragment Shader
    File file_frag = io_file_read(path_frag);
    if(!file_vertex.is_valid){
        ERROR_EXIT("Error reading shader: %s\n", path_frag);
    }

    u32 shader_frag = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(shader_frag, 1, (const char *const *)&file_frag, NULL);
    glCompileShader(shader_frag);
    glGetShaderiv(shader_frag, GL_COMPILE_STATUS, &success);

    if(!success){
        glGetShaderInfoLog(shader_frag, 512, NULL, log);
        ERROR_EXIT("Error compiling shader: %s\n", log);
    }

    //Compile Shader and link it to program
    u32 shader = glCreateProgram();
    glAttachShader(shader, shader_vertex);
    glAttachShader(shader, shader_frag);
    glLinkProgram(shader);
    glGetProgramiv(shader, GL_LINK_STATUS, &success);

    if(!success){
        glGetProgramInfoLog(shader, 512, NULL, log);
        ERROR_EXIT("Error linking shader: %s\n", log);
    }

    free(file_vertex.data);
    free(file_frag.data);

    return shader;
}
