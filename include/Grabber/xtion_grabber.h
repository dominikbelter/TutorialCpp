/** @file xtion_grabber.h
 *
 * implementation - Xtion Grabber
 *
 */
#ifndef XTION_GRABBER_H
#define XTION_GRABBER_H

#include <stddef.h>
#include "grabber.h"
#include "../../3rdParty/tinyXML/tinyxml2.h"
#include <iostream>
#include <memory>

#define MAX_DEPTH 10000

enum DisplayModes
{
    DISPLAY_MODE_OVERLAY,
    DISPLAY_MODE_DEPTH,
    DISPLAY_MODE_IMAGE
};

namespace tutorial {
    /// create a single grabber (Xtion)
    Grabber* createGrabberXtion(void);
    Grabber* createGrabberXtion(std::string configFile);
};

using namespace tutorial;

class XtionGrabber : public Grabber {

public:

    /// Pointer
    typedef std::unique_ptr<XtionGrabber> Ptr;

    /// Construction
    XtionGrabber(void);

    /// Construction
    XtionGrabber(std::string configFilename) : Grabber("Xtion Grabber", TYPE_PRIMESENSE){
        tinyxml2::XMLDocument config;
        std::string filename = "../../resources/" + configFilename;
        config.LoadFile(filename.c_str());
        if (config.ErrorID())
            std::cout << "unable to load Kinect config file.\n";
        tinyxml2::XMLElement * posXML = config.FirstChildElement( "pose" );
        double query[4];
        posXML->QueryDoubleAttribute("qw", &query[0]); posXML->QueryDoubleAttribute("qx", &query[1]); posXML->QueryDoubleAttribute("qy", &query[2]); posXML->QueryDoubleAttribute("qz", &query[3]);
        double queryPos[4];
        posXML->QueryDoubleAttribute("x", &queryPos[0]); posXML->QueryDoubleAttribute("y", &queryPos[1]); posXML->QueryDoubleAttribute("z", &queryPos[2]);
        pose = Quaternion (query[0], query[1], query[2], query[3])*Vec3(queryPos[0], queryPos[1], queryPos[2]);
    }

    /// Name of the grabber
    virtual const std::string& getName() const;

    /// Returns current point cloud
    virtual const PointCloud& getCloud(void) const;

    /// Returns the current 2D image
    virtual const SensorFrame& getSensorFrame(void) const;

    /// Grab image and/or point cloud
    virtual void grab();

protected:


private:


};


#endif // XTION_GRABBER_H
