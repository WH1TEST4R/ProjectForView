#include <Windows.h>
#include <osgViewer/Viewer>
#include <osg/ShapeDrawable>
#include <osg/Geode>
#include <osg/PositionAttitudeTransform>
#include <osg/ClearNode>
#include <osgGA/TrackballManipulator>
#include <osgGA/KeySwitchMatrixManipulator>
#include <osgUtil/LineSegmentIntersector>
#include <iostream>
#include <osgGA/GUIEventAdapter>
#include <osg/Material>
#include "Constants.h"

osg::Node* createCube(const osg::Vec4& color, float size);
osg::Geode* createSmallCube();

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

//class MouseEventHandler : public osgGA::GUIEventHandler
//{
//public:
//   MouseEventHandler(osg::PositionAttitudeTransform* redCubeTransform, osg::Group* blueCubesGroup)
//      : _redCubeTransform(redCubeTransform), _blueCubesGroup(blueCubesGroup) {}
//   virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);
//private:
//   void pickObjectUnderMouse(float x, float y);
//   void changeCubeColor(osg::PositionAttitudeTransform* cubeTransform, const osg::Vec4& color);
//   osg::ref_ptr<osgGA::GUIEventAdapter> _eventProxy;
//   osg::Camera* _camera;
//   osg::PositionAttitudeTransform* _redCubeTransform;
//   osg::Group* _blueCubesGroup;
//  };

#pragma once
