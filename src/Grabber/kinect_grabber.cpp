#include "../include/Grabber/kinect_grabber.h"
#include <memory>
#include <stdexcept>
#include <chrono>
#include <thread>

using namespace tutorial;

/// A single instance of Kinect grabber
KinectGrabber::Ptr grabberKinect;

KinectGrabber::KinectGrabber(void) : Grabber("Kinect Grabber", TYPE_PRIMESENSE) {

}

const std::string& KinectGrabber::getName() const {
	return name;
}

const PointCloud& KinectGrabber::getCloud(void) const {
    return cloud;
}

const SensorFrame& KinectGrabber::getSensorFrame(void) const {
    return sensor_frame;
}

void KinectGrabber::grab(void) {
    Point3D point;
    point.x() = 1.2; point.y() = 3.4; point.z() = 5.6;
	cloud.push_back(point);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

///
void KinectGrabber::calibrate(void) {

}

int KinectGrabber::grabberClose(){
    return 0;
}

tutorial::Grabber* tutorial::createGrabberKinect(void) {
    grabberKinect.reset(new KinectGrabber());
    return grabberKinect.get();
}

tutorial::Grabber* tutorial::createGrabberKinect(std::string configFile) {
    grabberKinect.reset(new KinectGrabber(configFile));
    return grabberKinect.get();
}

