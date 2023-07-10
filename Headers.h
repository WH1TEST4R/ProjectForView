#include <Windows.h>
#include <osgViewer/Viewer>
#include <osg/ShapeDrawable>
#include <osg/Geode>
#include <osg/PositionAttitudeTransform>
#include <osg/ClearNode>
#include <osgGA/TrackballManipulator>
#include <osgGA/KeySwitchMatrixManipulator>
#include <iostream>
#include <osgGA/GUIEventAdapter>
#include <osgText/Text>
#include "Constants.h"

osg::Node* createCube(const osg::Vec4& color, float size);
osg::Node* createSmallCube();

class KeyboardEventHandler : public osgGA::GUIEventHandler
{
public:
   KeyboardEventHandler(osg::PositionAttitudeTransform* redCubeTransform, osg::Group* blueCubesGroup)
      : _redCubeTransform(redCubeTransform), _blueCubesGroup(blueCubesGroup) {}

   bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

private:
   osg::ref_ptr<osg::PositionAttitudeTransform> _redCubeTransform;
   osg::ref_ptr<osg::Group> _blueCubesGroup;

   void moveRedCube(const osg::Vec3& direction);
   bool isPositionValid(const osg::Vec3& position);
   void checkCollision();
   void addSmallCube();
};


#pragma once
