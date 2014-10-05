/** @file visualizer.h
 *
 * Visualizer interface
 *
 */

#ifndef _VISUALIZER_H_
#define _VISUALIZER_H_

#include "../Defs/defs.h"
#include <iostream>
#include <string>
#include <vector>
#include <mutex>

namespace tutorial {
    /// Visualizer interface
    class Visualizer {
        public:

            /// Visualizer type
            enum Type {
                    /// openGL
                    TYPE_OPENGL,
            };

            /// overloaded constructor
            Visualizer(const std::string _name, Type _type) : name(_name), type(_type) {};

            /// Name of the visualizer
            virtual const std::string& getName() const = 0;

            /// Draw point cloud
            virtual void draw(const PointCloud& cloud) const = 0;

            /// Virtual desctrutor
            virtual ~Visualizer() {}

        protected:
            /// Grabber type
            Type type;

            /// Grabber name
            const std::string name;
    };
};

#endif // _VISUALIZER_H_
