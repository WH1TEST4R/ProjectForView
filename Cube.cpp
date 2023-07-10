#include "Headers.h"

osg::Node* createCube(const osg::Vec4& color, float size)
{
   osg::ref_ptr<osg::Box> cubeBox = new osg::Box(osg::Vec3(0.0f, 0.0f, 0.0f), size, size, size);
   osg::ref_ptr<osg::ShapeDrawable> cubeShapeDrawable = new osg::ShapeDrawable(cubeBox);
   cubeShapeDrawable->setColor(color);
   osg::ref_ptr<osg::Geode> cubeGeode = new osg::Geode;
   cubeGeode->addDrawable(cubeShapeDrawable);

   osg::ref_ptr<osg::PositionAttitudeTransform> cubeTransform = new osg::PositionAttitudeTransform;
   cubeTransform->addChild(cubeGeode);

   return cubeTransform.release();
}

osg::Node* createSmallCube()
{
   osg::ref_ptr<osg::Box> smallCubeBox = new osg::Box(osg::Vec3(0.0f, 0.0f, 0.0f), SmallCubeSize, SmallCubeSize, SmallCubeSize);
   osg::ref_ptr<osg::ShapeDrawable> smallCubeShapeDrawable = new osg::ShapeDrawable(smallCubeBox);
   smallCubeShapeDrawable->setColor(osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f));
   osg::ref_ptr<osg::Geode> smallCubeGeode = new osg::Geode;
   smallCubeGeode->addDrawable(smallCubeShapeDrawable);

   osg::ref_ptr<osg::PositionAttitudeTransform> smallCubeTransform = new osg::PositionAttitudeTransform;
   smallCubeTransform->addChild(smallCubeGeode);

   return smallCubeTransform.release();
}