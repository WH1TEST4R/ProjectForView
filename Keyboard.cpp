#include "Headers.h"


bool KeyboardEventHandler::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa) {
   if (ea.getEventType() == osgGA::GUIEventAdapter::KEYDOWN)
   {
      switch (ea.getKey())
      {
      case 'w':
      case 'W':
         moveRedCube(osg::Vec3(0.0f, 0.0f, 1.0f));
         break;
      case 's':
      case 'S':
         moveRedCube(osg::Vec3(0.0f, 0.0f, -1.0f));
         break;
      case 'a':
      case 'A':
         moveRedCube(osg::Vec3(-1.0f, 0.0f, 0.0f));
         break;
      case 'd':
      case 'D':
         moveRedCube(osg::Vec3(1.0f, 0.0f, 0.0f));
         break;
      case '1':
         addSmallCube();
         break;
      default:
         break;
      }
   }

   return false;
}

void KeyboardEventHandler::moveRedCube(const osg::Vec3& direction) {
   osg::Vec3 currentPosition = _redCubeTransform->getPosition();
   osg::Vec3 newPosition = currentPosition + (direction * CubeSpeed);

   if (isPositionValid(newPosition))
   {
      newPosition.y() = -(CubeSize * 0.5f + 0.01f); // Устанавливаем позицию над полом с учетом небольшого смещения
      _redCubeTransform->setPosition(newPosition);
      checkCollision();
   }
}

bool KeyboardEventHandler::isPositionValid(const osg::Vec3& position) {
   float halfFloorSize = FloorSize * 0.5f;
   float halfCubeSize = CubeSize * 0.5f;

   return (position.x() >= -halfFloorSize + halfCubeSize &&
      position.x() <= halfFloorSize - halfCubeSize &&
      position.z() >= -halfFloorSize + halfCubeSize &&
      position.z() <= halfFloorSize - halfCubeSize);
}

void KeyboardEventHandler::checkCollision() {
   osg::Vec3 redCubePosition = _redCubeTransform->getPosition();
   float redCubeSize = CubeSize * 0.5f;

   for (unsigned int i = 0; i < _blueCubesGroup->getNumChildren(); ++i)
   {
      osg::PositionAttitudeTransform* smallCubeTransform = dynamic_cast<osg::PositionAttitudeTransform*>(_blueCubesGroup->getChild(i));

      if (smallCubeTransform)
      {
         osg::Vec3 smallCubePosition = smallCubeTransform->getPosition();
         float smallCubeSize = SmallCubeSize * 0.5f;
         float distance = (redCubePosition - smallCubePosition).length();

         if (distance <= (redCubeSize + smallCubeSize))
         {
            // Удаление синего куба
            _blueCubesGroup->removeChild(i);
            break;
         }
      }
   }
}

void KeyboardEventHandler::addSmallCube() {
   osg::Node* smallCube = createSmallCube();
   osg::Vec3 position = osg::Vec3(
      (SmallCubeSize + rand() % 5) * (rand() % 2 == 0 ? -1.0f : 1.0f),
      -(SmallCubeSize * 0.5f),
      (SmallCubeSize + rand() % 5) * (rand() % 2 == 0 ? -1.0f : 1.0f)); // Изменение положения синего куба
   osg::PositionAttitudeTransform* smallCubeTransform = new osg::PositionAttitudeTransform;
   smallCubeTransform->setPosition(position);
   smallCubeTransform->addChild(smallCube);
   _blueCubesGroup->addChild(smallCubeTransform);
}