#include "Headers.h"

//Метод handle
//Проверяет, произошло ли нажатие ЛКМ
//Через указатели получаем доступ к камере и вьюпорту
//Далее создаем объект для хранения пересечений лучей сцены и объектами
//P.S как я понял, этот объект и след. метод необходим для корректного подсчета координат клика
//Далее по всем таким пересечениям получаем мировые координаты пересечения
//В цикле по всем синим кубам проверяем пересечение с каждым
//Пересечение произошло, если расстояние между двумя точками в пространстве
//(клик мыши и центр куба) меньше чем размер синего куба
//Если пересекли - красим в зеленый и останавливаем цикл

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

//Метод createCow 
//Создает корову в месте клика, если клик был не на синем кубе
//Проверяем, что клик был в поле
//Задаем размер корове и ее позицию по клику
//Подгружаем файл и задаем матрицу трансформации 
//Добавляем в корень сцены

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

//Функции для передачи копии основного корня сцены
//Чтобы можно было добавлять коров 
void MouseEventHandler::initRoot(osg::Group* root) {
   _root = root;
}
