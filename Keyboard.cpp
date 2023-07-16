#include "Headers.h"

//Метод handle()
//При нажатии клавиш WASD двигает красный куб в соотв направлении
//При нажатии 1 - создает один синий куб в случайной точке поля

bool KeyboardEventHandler::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa) {
   if (ea.getEventType() == osgGA::GUIEventAdapter::KEYDOWN)
   {
      switch (ea.getKey())
      {
      case 'w':
      case 'ц':
         moveRedCube(osg::Vec3(0.0f, 0.0f, 1.0f));
         break;
      case 's':
      case 'ы':
         moveRedCube(osg::Vec3(0.0f, 0.0f, -1.0f));
         break;
      case 'a':
      case 'ф':
         moveRedCube(osg::Vec3(-1.0f, 0.0f, 0.0f));
         break;
      case 'd':
      case 'в':
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

//Метод moveRedCube()
//Передвигает красный куб по полю
//Получает текущее положение красного куба, затем высчитывает новое
//Новое - к текущей позиции прибавить вектор*скорость движения красного куба
//Если новая позиция валидна - устанавливаем куб на нее
//130 строка для того, чтобы куб всегда был "на поле"
//Проверяем столкновения с синим кубом

void KeyboardEventHandler::moveRedCube(const osg::Vec3& direction) {
   osg::Vec3 currentPosition = _redCubeTransform->getPosition();
   osg::Vec3 newPosition = currentPosition + (direction * CubeSpeed);

   if (isPositionValid(newPosition))
   {
      newPosition.y() = -(CubeSize * 0.5f + 0.01f);
      _redCubeTransform->setPosition(newPosition);
      checkCollision();
   }
}

//Метод isPositionValid()
//Проверяет валидность позиции красого куба
//Если ни одна из координат не вышла за пределы половины поля
//Позиция валидна
//В другом случае - красный куб не будет двигаться в направлении колизии

bool KeyboardEventHandler::isPositionValid(const osg::Vec3& position) {
   float halfFloorSize = FloorSize * 0.5f;
   float halfCubeSize = CubeSize * 0.5f;

   return (position.x() >= -halfFloorSize + halfCubeSize &&
      position.x() <= halfFloorSize - halfCubeSize &&
      position.z() >= -halfFloorSize + halfCubeSize &&
      position.z() <= halfFloorSize - halfCubeSize);
}

//Метод checkCollision()
//сначала узнает позицию красного куба
//Далее задает расстояние, равное половине красного куба 
//Далее в цикле проходится по всем синим кубам (все они находятся в _blueCubesGroup)
//Получает дочерний объект из группы _blueCubesGroup i-ый и приводит его к типу PAT
//Если smallCubeTransform не nullptr, то проверяем расстояние от каждого куба до нашего куба
//Если оно меньше, чем минимально разрешенная дистанция
//Синий куб удаляется
//Иначе все хорошо

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
            _blueCubesGroup->removeChild(smallCubeTransform);
            break;
         }
      }
   }
}

//addSmallCube() создает синий куб
//затем помещает в сгенерированные координаты в пределах поля
//Далее добавляет его в дочерний узел 
//Затем добавляет его в группу синих кубов

void KeyboardEventHandler::addSmallCube() {
   osg::Node* smallCube = createSmallCube();
   osg::Vec3 position = osg::Vec3(
      (SmallCubeSize + rand() % (int)(FloorSize/2)) * (rand() % 2 == 0 ? -1.0f : 1.0f),
      -(SmallCubeSize * 0.5f),
      (SmallCubeSize + rand() % (int)(FloorSize / 2)) * (rand() % 2 == 0 ? -1.0f : 1.0f));
   osg::PositionAttitudeTransform* smallCubeTransform = new osg::PositionAttitudeTransform;
   smallCubeTransform->setPosition(position);
   smallCubeTransform->addChild(smallCube);
   _blueCubesGroup->addChild(smallCubeTransform);
}
