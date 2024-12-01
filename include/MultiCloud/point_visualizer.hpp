#ifndef MULTICLOUD_VISUALIZER_HPP_
#define MULTICLOUD_VISUALIZER_HPP_

#pragma once
#include <cstdint>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/Xrandr.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glx.h>
#include <GL/glext.h>
#include <MultiCloud/point_visualizer.hpp>
#include "MultiCloud/types.hpp"
#include <chrono>
#include <thread>
#include <string>
#include <cstdlib>
#include <iostream>

typedef GLXContext (*glXCreateContextAttribsARBProc)
  (Display*, GLXFBConfig, GLXContext, Bool, const int*);

/* static const char *vert_shader_src = "#version 330 core\n" */
/*     "in vec3 aPos;\n" */
/*   	"uniform vec3 u1;\n" */
/*     "uniform vec3 u2;\n" */
/*     "uniform vec3 u3;\n" */
/*     "uniform float scaling;\n" */
/*     "uniform vec3 lookAt;\n" */
/*     "void main()\n" */
/*     "{\n" */
/*     "	gl_Position = vec4((u1.x*(aPos.x-lookAt.x)+u1.y*(aPos.y-lookAt.y)+u1.z*(aPos.z-lookAt.z))*scaling,(u2.x*(aPos.x-lookAt.x)+u2.y*(aPos.y-lookAt.y)+u2.z*(aPos.z-lookAt.z))*scaling,0,1.0);\n" */
/*     "}\0"; */

/* static const char *fragment_shader_src = "#version 330 core\n" */
/*     "out vec4 FragColor;\n" */
/*     "void main()\n" */
/*     "{\n" */
/*     "   FragColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);\n" */
/*     "}\0"; */
 
class Visualizer {
  public:
    Visualizer(const std::string& window_name_ = "Multi Cloud Visualizer");
    ~Visualizer();

    void Spin(const uint16_t freq);
    bool IsStopped();
    /**
     * @brief size in meter scale
     */
    void CreateCoordSystem(const uint16_t size);
    
    /**
     * @brief size_x in meter scale
     * @brief size_y in meter scale
     * @brief size_z in meter scale
     */
    void CreateCoordSystem(const uint16_t size_x, const uint16_t size_y, const uint16_t size_z);
  protected:
    void InitWindow(const std::string& window_name_ = "Multi Cloud Visualizer");
    void HandleResize(const uint16_t height, const uint16_t width);
  private:
    Display* display;
    Window window;
    GLXContext gl_context;

    bool stopped;
    std::string window_name;
    uint16_t window_height;
    uint16_t window_width;
};

template<typename CloudType>
class MultiCloudVisualizer: public CloudSet<CloudType>, Visualizer {
  public:
    MultiCloudVisualizer();
    ~MultiCloudVisualizer();
  protected:
  private:
};

template<typename MeshType>
class MultiMeshVisualizer : public MultiMesh<MeshType>, Visualizer {
  public:
    MultiMeshVisualizer();
    ~MultiMeshVisualizer();
  protected:
  private:
};

#endif
