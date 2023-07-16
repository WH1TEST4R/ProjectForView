#include "Headers.h"

//Метод createCube
//Отвечает за создание красного куба на сцене
//За размер куба отвечает CubeSize

osg::Node* createCube()
{
   osg::ref_ptr<osg::Box> cubeBox = new osg::Box(osg::Vec3(0.0f, 0.0f, 0.0f), CubeSize, CubeSize, CubeSize);
   osg::ref_ptr<osg::ShapeDrawable> cubeShapeDrawable = new osg::ShapeDrawable(cubeBox);
   cubeShapeDrawable->setColor(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));
   osg::ref_ptr<osg::Geode> cubeGeode = new osg::Geode;
   cubeGeode->addDrawable(cubeShapeDrawable);

   return cubeGeode.release();
}

//Метод createSmallCube
//Отвечает за создание синих кубов на сцене
//За размер кубов отвечат SmallCubeSize

osg::Geode* createSmallCube()
{
   osg::ref_ptr<osg::Box> smallCubeBox = new osg::Box(osg::Vec3(0.0f, 0.0f, 0.0f), SmallCubeSize, SmallCubeSize, SmallCubeSize);
   osg::ref_ptr<osg::ShapeDrawable> smallCubeShapeDrawable = new osg::ShapeDrawable(smallCubeBox);
   smallCubeShapeDrawable->setColor(osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f));
   osg::ref_ptr<osg::Geode> smallCubeGeode = new osg::Geode;
   smallCubeGeode->addDrawable(smallCubeShapeDrawable);

   return smallCubeGeode.release();
}
