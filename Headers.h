#include <Windows.h>
#include <iostream>
#include <osg/Fog>
#include <osg/Geode>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osg/ShapeDrawable>
#include <osg/MatrixTransform>
#include <osgGA/GUIEventAdapter>
#include <osgGA/TrackballManipulator>
#include <osg/PositionAttitudeTransform>
#include <osgUtil/LineSegmentIntersector>
#include <osgGA/KeySwitchMatrixManipulator>
#include "Constants.h"


osg::Node* createCube();
osg::Geode* createSmallCube();

class KeyboardEventHandler : public osgGA::GUIEventHandler
{

public:
   KeyboardEventHandler(osg::PositionAttitudeTransform* redCubeTransform, osg::Group* blueCubesGroup)
      : _redCubeTransform(redCubeTransform), _blueCubesGroup(blueCubesGroup) {}
   bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

private:
   void moveRedCube(const osg::Vec3& direction);
   bool isPositionValid(const osg::Vec3& position);
   void checkCollision();
   void addSmallCube();

   osg::ref_ptr<osg::PositionAttitudeTransform> _redCubeTransform;
   osg::ref_ptr<osg::Group> _blueCubesGroup;
};

class MouseEventHandler : public osgGA::GUIEventHandler
{

public: 
   MouseEventHandler(osg::Group* root, osg::Group* blueCubesGroup)
      : _root(root),_blueCubesGroup(blueCubesGroup) {}
   bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);
   bool createCow(float x, float z);

private:
   void initRoot(osg::Group* root);
   osg::Group* _root;
   osg::Group* _blueCubesGroup;
};

#pragma once
