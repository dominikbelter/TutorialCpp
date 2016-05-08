/** @file QVisualizer.h
 *
 * implementation - QGLVisualizer
 *
 */

#ifndef QVISUALIZER_H_INCLUDED
#define QVISUALIZER_H_INCLUDED

#include "../Defs/defs.h"
#include "../include/Utilities/observer.h"
#include "../3rdParty/tinyXML/tinyxml2.h"
#include <QGLViewer/qglviewer.h>
#include <iostream>

/// Map implementation
class QGLVisualizer: public QGLViewer, public Observer{
public:
    /// Pointer
    typedef std::unique_ptr<QGLVisualizer> Ptr;

    class Config{
      public:
        Config() {
        }
        Config(std::string configFilename){
            tinyxml2::XMLDocument config;
            std::string filename = "../../resources/" + configFilename;
            config.LoadFile(filename.c_str());
            if (config.ErrorID())
                std::cout << "unable to load Visualizer config file.\n";
            tinyxml2::XMLElement * model = config.FirstChildElement( "VisualizerConfig" );
            double rgba[4]={0,0,0,0};
            model->FirstChildElement( "background" )->QueryDoubleAttribute("red", &rgba[0]);
            model->FirstChildElement( "background" )->QueryDoubleAttribute("green", &rgba[1]);
            model->FirstChildElement( "background" )->QueryDoubleAttribute("blue", &rgba[2]);
            model->FirstChildElement( "background" )->QueryDoubleAttribute("alpha", &rgba[3]);
            backgroundColor.setRedF(rgba[0]); backgroundColor.setGreenF(rgba[1]);
            backgroundColor.setBlueF(rgba[2]); backgroundColor.setAlphaF(rgba[3]);
        }
        public:
        /// Background color
        QColor backgroundColor;
    };

    /// Construction
    QGLVisualizer(void);

    /// Construction
    QGLVisualizer(std::string configFile);

    /// Construction
    QGLVisualizer(Config _config);

    /// Destruction
    ~QGLVisualizer(void);

    /// Observer update
    void update(const tutorial::Mat34& newPose);

private:
    Config config;

    tutorial::Mat34 teapotPose;

    /// draw objects
    void draw();

    /// draw objects
    void animate();

    /// initialize visualizer
    void init();

    /// generate help string
    std::string help() const;
};

#endif // QVISUALIZER_H_INCLUDED
