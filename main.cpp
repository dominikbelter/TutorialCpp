#include <iostream>
#include <thread>
#include "include/Defs/defs.h"
#include "Grabber/kinect_grabber.h"
#include "Grabber/xtion_grabber.h"
#include "Visualizer/visualizerGL.h"
#include "3rdParty/tinyXML/tinyxml2.h"
#include <cmath>
#include <ctime>
#include <ratio>
#include <chrono>

using namespace std;

int main()
{
    try {
        using namespace tutorial;

        tinyxml2::XMLDocument config;
        config.LoadFile("../../resources/configGlobal.xml");
        if (config.ErrorID())
            std::cout << "unable to load config file.\n";
        std::string grabberType(config.FirstChildElement( "Grabber" )->FirstChildElement( "name" )->GetText());

        Grabber* grabber;
        if (grabberType == "Kinect") {
            std::string configFile(config.FirstChildElement( "Grabber" )->FirstChildElement( "calibrationFile" )->GetText());
            grabber = createGrabberKinect(configFile);
        }
        else if (grabberType == "Xtion") {
            std::string configFile(config.FirstChildElement( "Grabber" )->FirstChildElement( "calibrationFile" )->GetText());
            grabber = createGrabberXtion(configFile);
        }
        else // Default
            grabber = createGrabberKinect();

        // create objects and print configuration
        cout << "Current grabber: " << grabber->getName() << std::endl;
        Visualizer * visu = createVisualizerGL();
        cout << "Current visualizer: " << visu->getName() << std::endl;

        while (1){ //tracking
            grabber->grab(); // grab frame
            visu->draw(grabber->getSensorFrame().cloud);
        }

    }
	catch (const std::exception& ex) {
		std::cerr << ex.what() << std::endl;
		return 1;
	}

	return 0;
}
