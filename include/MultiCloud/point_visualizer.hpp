#pragma once

#include <X11/Xlib.h>
#include <GL/glx.h>
#include <GL/glext.h>

typedef GLXContext (*glXCreateContextAttribsARBProc)
  (Display*, GLXFBConfig, GLXContext, Bool, const int*);

const char *vert_shader_src = "#version 330 core\n"
    "in vec3 aPos;\n"
  	"uniform vec3 u1;\n"
    "uniform vec3 u2;\n"
    "uniform vec3 u3;\n"
    "uniform float scaling;\n"
    "uniform vec3 lookAt;\n"
    "void main()\n"
    "{\n"
    "	gl_Position = vec4((u1.x*(aPos.x-lookAt.x)+u1.y*(aPos.y-lookAt.y)+u1.z*(aPos.z-lookAt.z))*scaling,(u2.x*(aPos.x-lookAt.x)+u2.y*(aPos.y-lookAt.y)+u2.z*(aPos.z-lookAt.z))*scaling,0,1.0);\n"
    "}\0";

const char *fragment_shader_src = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);\n"
    "}\0";

/* class PointVisualizer : Public */
