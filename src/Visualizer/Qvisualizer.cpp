#include "../include/Visualizer/Qvisualizer.h"
#include <memory>
#include <cmath>
#include <stdexcept>
#include <chrono>
#include <GL/glut.h>

using namespace tutorial;

/// A single instance of Visualizer
QGLVisualizer::Ptr visualizer;

QGLVisualizer::QGLVisualizer(void) : teapotPose(Mat34::Identity()){
}

/// Construction
QGLVisualizer::QGLVisualizer(Config _config): config(_config), teapotPose(Mat34::Identity()){

}

/// Construction
QGLVisualizer::QGLVisualizer(std::string configFile) :
        config(configFile), teapotPose(Mat34::Identity()) {
    tinyxml2::XMLDocument configXML;
    std::string filename = "../../resources/" + configFile;
    configXML.LoadFile(filename.c_str());
    if (configXML.ErrorID())
        std::cout << "unable to load visualizer config file.\n";
}

/// Destruction
QGLVisualizer::~QGLVisualizer(void) {
}

/// Observer update
void QGLVisualizer::update(const Mat34& newPose) {
    teapotPose = newPose;
}


/// draw objects
void QGLVisualizer::draw(){
    // Here we are in the world coordinate system. Draw unit size axis.
    drawAxis();
    float_type GLmat[16]={teapotPose(0,0), teapotPose(1,0), teapotPose(2,0), teapotPose(3,0), teapotPose(0,1), teapotPose(1,1), teapotPose(2,1), teapotPose(3,1), teapotPose(0,2), teapotPose(1,2), teapotPose(2,2), teapotPose(3,2), teapotPose(0,3), teapotPose(1,3), teapotPose(2,3), teapotPose(3,3)};
    glPushMatrix();
        glMultMatrixd(GLmat);
        glutSolidTeapot(1.0);
    glPopMatrix();
}

/// draw objects
void QGLVisualizer::animate(){
}

/// initialize visualizer
void QGLVisualizer::init(){
    // Light setup
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 50.0);
    GLfloat specular_color[4] = { 0.8f, 0.8f, 0.8f, 1.0 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  specular_color);

    GLfloat ambientLight0[] = {0.2f, 0.2f, 0.2f, 0.0f};
    GLfloat diffuseLight0[] = {0.6f, 0.6f, 0.6f, 0.0f};
    GLfloat specularLight0[] = {1.0f, 1.0f, 1.0f, 1.0f};

    GLfloat positionLight0[] = {0,0,0, 1.0f};
    GLfloat directionLight0[] = {0,0,1};

    GLfloat lm_ambient[] = {(float)0.3, (float)0.3, (float)0.3, (float)1.0};

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lm_ambient);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight0);

    glLightfv(GL_LIGHT0, GL_POSITION, positionLight0);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, directionLight0);

    glEnable (GL_LIGHTING);
    glEnable (GL_LIGHT0);
//    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);
    // Restore previous viewer state.
    restoreStateFromFile();

    camera()->setZNearCoefficient((float)0.00001);
    camera()->setZClippingCoefficient(100.0);

    setBackgroundColor(config.backgroundColor);

    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Opens help window
    help();

    startAnimation();
}

/// generate help string
std::string QGLVisualizer::help() const{
    std::string text("S i m p l e V i e w e r");
    text += "Use the mouse to move the camera around the object. ";
    text += "You can respectively revolve around, zoom and translate with the three mouse buttons. ";
    text += "Left and middle buttons pressed together rotate around the camera view direction axis<br><br>";
    text += "Pressing <b>Alt</b> and one of the function keys (<b>F1</b>..<b>F12</b>) defines a camera keyFrame. ";
    text += "Simply press the function key again to restore it. Several keyFrames define a ";
    text += "camera path. Paths are saved when you quit the application and restored at next start.<br><br>";
    text += "Press <b>F</b> to display the frame rate, <b>A</b> for the world axis, ";
    text += "<b>Alt+Return</b> for full screen mode and <b>Control+S</b> to save a snapshot. ";
    text += "See the <b>Keyboard</b> tab in this window for a complete shortcut list.<br><br>";
    text += "Double clicks automates single click actions: A left button double click aligns the closer axis with the camera (if close enough). ";
    text += "A middle button double click fits the zoom of the camera and the right button re-centers the scene.<br><br>";
    text += "A left button double click while holding right button pressed defines the camera <i>Revolve Around Point</i>. ";
    text += "See the <b>Mouse</b> tab and the documentation web pages for details.<br><br>";
    text += "Press <b>Escape</b> to exit the viewer.";
    return text;
}

