#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glx.h>
#include <MultiCloud/point_visualizer.hpp>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <iostream>

Visualizer::Visualizer(const std::string& window_name_) : 
  display(nullptr), window(0),
  gl_context(nullptr), stopped(false) {
    this->window_name = window_name_;
    this->InitWindow(window_name_);
}

Visualizer::~Visualizer() {
  if(gl_context) {
    glXMakeCurrent(this->display, None, nullptr);
    glXDestroyContext(this->display, this->gl_context);
  }
  if(this->window)
    XDestroyWindow(this->display, this->window);
  if(this->display)
    XCloseDisplay(this->display);
}

void Visualizer::InitWindow(const std::string& window_name) {
  this->display = XOpenDisplay(nullptr);

  if(!this->display) {
    std::cerr << "Failed to open X Display" << std::endl;
    exit(EXIT_FAILURE);
  }

  int screen = DefaultScreen(this->display);
  int visual_attr[] = {
    GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None
  };

  XVisualInfo* visual = glXChooseVisual(this->display, screen, visual_attr);
  if(!visual) {
    std::cerr << "Failed to choose a visual" << std::endl;
    exit(EXIT_FAILURE);
  }

  Colormap colormap = XCreateColormap(this->display, RootWindow(this->display, visual->screen), visual->visual, AllocNone);
  
  XSetWindowAttributes win_attr = {};
  win_attr.colormap = colormap;
  win_attr.event_mask = ExposureMask | KeyPressMask | StructureNotifyMask;

  window = XCreateWindow(this->display, RootWindow(this->display, visual->screen), 0, 0, this->window_width,
      this->window_height, 0, visual->depth, InputOutput, visual->visual, CWColormap, &win_attr);

  XMapWindow(this->display, this->window);
  XStoreName(this->display, this->window, window_name.c_str());

  this->gl_context = glXCreateContext(this->display, visual, nullptr, GL_TRUE);
  if(!this->gl_context) {
    std::cerr << "Failed to create GL Context." << std::endl;
    exit(EXIT_FAILURE);
  }

  glXMakeCurrent(this->display, this->window, this->gl_context);
  glEnable(GL_DEPTH_TEST);

  XFree(visual);
}

void Visualizer::HandleResize(const uint16_t height, const uint16_t width) {
  this->window_height = height;
  this->window_width = width;

  glViewport(0, 0, this->window_height, this->window_height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // Setup perspective proj
  float aspect = static_cast<float>(this->window_width) / static_cast<float>(this->window_height);
  gluPerspective(45.0f, aspect, .1f, 100.0f);

  glMatrixMode(GL_MODELVIEW);
}

void Visualizer::Spin(const uint16_t freq) {
  const std::chrono::milliseconds frame_time(1000/freq);

  while(!this->IsStopped()) {
    XEvent event;
    while(XPending(this->display)) {
      XNextEvent(this->display, &event);
      if(event.type == KeyPress) {
        stopped = true;
      } else if (event.type == ConfigureNotify) { // Handle Window Resize
        XConfigureEvent xce = event.xconfigure;
        if(xce.width != this->window_width || xce.height != this->window_height) {
          HandleResize(xce.width, xce.height);
        }
      }
    }
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(.0f, .0f, 5.0f,   // Camera Position
              .0f, .0f, .0f,    // Look at
              .0f, 1.0f, .0f);  // Up vector
    glBegin(GL_QUADS);

    // Front face (red)
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(-1.0, 1.0, 1.0);

    glEnd();

    glXSwapBuffers(this->display, this->window);
    std::this_thread::sleep_for(frame_time);
  }
}

bool Visualizer::IsStopped() {
  return stopped;
}
