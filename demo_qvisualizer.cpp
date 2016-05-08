#include "../include/Defs/defs.h"
#include "../3rdParty/tinyXML/tinyxml2.h"
#include "../include/Visualizer/Qvisualizer.h"
#include "Grabber/kinect_grabber.h"
#include "Grabber/xtion_grabber.h"
#include <GL/glut.h>
#include <qapplication.h>
#include <thread>
#include <iostream>

using namespace std;

tutorial::Grabber* grabber;

// run PUTSLAM
void runThread(){
    while (1){
        grabber->grab();
    }
}

int main(int argc, char** argv)
{
    try {
        tinyxml2::XMLDocument config;
        config.LoadFile("../../resources/configGlobal.xml");
        if (config.ErrorID())
            std::cout << "unable to load config file.\n";
        std::string grabberType(config.FirstChildElement( "Grabber" )->FirstChildElement( "name" )->GetText());
        std::string configFile(config.FirstChildElement( "Visualizer" )->FirstChildElement( "parametersFile" )->GetText());

        if (grabberType == "Kinect") {
            std::string configFile(config.FirstChildElement( "Grabber" )->FirstChildElement( "calibrationFile" )->GetText());
            grabber = createGrabberKinect(configFile);
        }
        if (grabberType == "Xtion") {
            std::string configFile(config.FirstChildElement( "Grabber" )->FirstChildElement( "calibrationFile" )->GetText());
            grabber = createGrabberXtion(configFile);
        }
        else // Default
            grabber = createGrabberKinect();

        QGLVisualizer::Config configVis(configFile);//something is wrong with QApplication when Qapplication
        //object is created. libTinyxml can read only ints from xml file

        QApplication application(argc,argv);

        glutInit(&argc, argv);

        QGLVisualizer visu(configVis);

        visu.setWindowTitle("Tutorial viewer");

        // Make the viewer window visible on screen.
        visu.show();
        grabber->attach(&visu);

        // run PUTSLAM
        std::thread thr(runThread);

        // Run main loop.
        application.exec();
        thr.join();

        return 1;
    }
    catch (const std::exception& ex) {
        std::cerr << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
