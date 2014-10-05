/** @file visualizerGL.h
 *
 * implementation - OpenGL visualizer
 *
 */

#ifndef VISUALIZERGL_H_INCLUDED
#define VISUALIZERGL_H_INCLUDED

#include "visualizer.h"
#include "../../3rdParty/tinyXML/tinyxml2.h"
#include <iostream>
#include <memory>

namespace tutorial {
    /// create a OpenGL visualizer
    Visualizer* createVisualizerGL(void);
};

using namespace tutorial;

/// Visualizer implementation
class VisualizerGL : public Visualizer {
    public:

        /// Pointer
        typedef std::unique_ptr<VisualizerGL> Ptr;

        /// Construction
        VisualizerGL(void);

        /// Name of the grabber
        const std::string& getName() const;

        /// Draw
        void draw(const PointCloud& cloud) const;

    private:
};

#endif // KINECT_GRABBER_H_INCLUDED
