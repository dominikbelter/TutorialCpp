// Undeprecate CRT functions
#ifndef _CRT_SECURE_NO_DEPRECATE
    #define _CRT_SECURE_NO_DEPRECATE 1
#endif

#include "../include/Visualizer/visualizerGL.h"
#include <memory>
#include <stdexcept>
#include <chrono>
#include <thread>

using namespace tutorial;

/// A single instance of OpenGL visualizer
VisualizerGL::Ptr visuGL;

VisualizerGL::VisualizerGL(void) : Visualizer("OpenGL visualizer", TYPE_OPENGL) {

}

const std::string& VisualizerGL::getName() const {
    return name;
}

void VisualizerGL::draw(const PointCloud& cloud) const {
    std::cout << "Draw cloud\n";
}

tutorial::Visualizer* tutorial::createVisualizerGL(void) {
    visuGL.reset(new VisualizerGL());
    return visuGL.get();
}


