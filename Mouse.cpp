#include "Headers.h"

//����� handle
//���������, ��������� �� ������� ���
//����� ��������� �������� ������ � ������ � ��������
//����� ������� ������ ��� �������� ����������� ����� ����� � ���������
//P.S ��� � �����, ���� ������ � ����. ����� ��������� ��� ����������� �������� ��������� �����
//����� �� ���� ����� ������������ �������� ������� ���������� �����������
//� ����� �� ���� ����� ����� ��������� ����������� � ������
//����������� ���������, ���� ���������� ����� ����� ������� � ������������
//(���� ���� � ����� ����) ������ ��� ������ ������ ����
//���� ��������� - ������ � ������� � ������������� ����

bool MouseEventHandler::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{
   float testcoordX = 0;
   float testcoordY = -0.15f;
   float testcoordZ = 0;
   if (ea.getEventType() == osgGA::GUIEventAdapter::PUSH && ea.getButton() == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON)
   {
      osgViewer::View* view = dynamic_cast<osgViewer::View*>(&aa);
      osg::Camera* camera = view->getCamera();
      const osg::Viewport* viewport = camera->getViewport();

      osgUtil::LineSegmentIntersector::Intersections intersections;
      if (view->computeIntersections(ea.getX(), ea.getY(), intersections))
      {
         bool flag = true;
         for (const auto& intersection : intersections)
         {
            osg::Vec3d worldCoordinates = intersection.getWorldIntersectPoint();
            testcoordX = worldCoordinates.x();
            testcoordZ = worldCoordinates.z();
            for (unsigned int i = 0; i < _blueCubesGroup->getNumChildren(); ++i)
            {
               osg::PositionAttitudeTransform* smallCubeTransform = dynamic_cast<osg::PositionAttitudeTransform*>(_blueCubesGroup->getChild(i));
               osg::ShapeDrawable* smallCubeShapeDrawable = dynamic_cast<osg::ShapeDrawable*>(smallCubeTransform->getChild(0)->asGeode()->getDrawable(0));
               osg::Vec3 cubePosition = smallCubeTransform->getPosition();
               float f_numb = (cubePosition.x() - worldCoordinates.x()) * (cubePosition.x() - worldCoordinates.x());
               float s_numb = (cubePosition.z() - worldCoordinates.z()) * (cubePosition.z() - worldCoordinates.z());
               float distance = sqrt(f_numb + s_numb);

               if (distance <= SmallCubeSize)
               {
                  flag = false;
                  smallCubeShapeDrawable->setColor(osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f));
                  break;
               }
            }
         }
         if (flag) {
            createCow(testcoordX, testcoordZ);
         }
      }
   }

   return false;
}

//����� createCow 
//������� ������ � ����� �����, ���� ���� ��� �� �� ����� ����
//���������, ��� ���� ��� � ����
//������ ������ ������ � �� ������� �� �����
//���������� ���� � ������ ������� ������������� 
//��������� � ������ �����

bool MouseEventHandler::createCow(float x, float z) {
   float halfFloorSize = FloorSize * 0.5f;
   if (std::abs(x) <= halfFloorSize && std::abs(z) <= halfFloorSize)
   {
      osg::Vec3 initialScale(0.1f, 0.1f, 0.1f);
      osg::Vec3 initialPosition(x, -0.15f, z);

      osg::ref_ptr<osg::Node> glider = osgDB::readNodeFile("cow.osg");
      osg::ref_ptr<osg::MatrixTransform> transform = new osg::MatrixTransform;
      transform->setMatrix(osg::Matrix::translate(initialPosition * 10.0f) * osg::Matrix::scale(initialScale));
      transform->addChild(glider.get());
      _root->addChild(transform);

      return true;
   }

   return false;
}

//������� ��� �������� ����� ��������� ����� �����
//����� ����� ���� ��������� ����� 

void MouseEventHandler::initRoot(osg::Group* root) {
   _root = root;
}

//osg::Group* MouseEventHandler::getRoot() {
//
//   return _root;
//}