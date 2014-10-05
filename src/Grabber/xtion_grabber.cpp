// Undeprecate CRT functions
#ifndef _CRT_SECURE_NO_DEPRECATE
    #define _CRT_SECURE_NO_DEPRECATE 1
#endif

#include "../include/Grabber/xtion_grabber.h"
#include <memory>
#include <stdexcept>
#include <chrono>
#include <thread>

using namespace tutorial;

/// A single instance of Kinect grabber
XtionGrabber::Ptr grabberX;

XtionGrabber::XtionGrabber(void) : Grabber("Xtion Grabber", TYPE_PRIMESENSE) {

}


const std::string& XtionGrabber::getName() const {
    return name;
}

const PointCloud& XtionGrabber::getCloud(void) const {
    return cloud;
}

const SensorFrame& XtionGrabber::getSensorFrame(void) const {
    return sensor_frame;
}

void XtionGrabber::grab(void) {

}

tutorial::Grabber* tutorial::createGrabberXtion(void) {
    grabberX.reset(new XtionGrabber());
    return grabberX.get();
}

tutorial::Grabber* tutorial::createGrabberXtion(std::string configFile) {
    grabberX.reset(new XtionGrabber(configFile));
    return grabberX.get();
}

