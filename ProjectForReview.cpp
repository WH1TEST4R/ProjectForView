#include "Headers.h"
   
int main()
{
   // Создание визуализатора для отображения сцены
   osgViewer::Viewer viewer;
   // Создание фона
   viewer.getCamera()->setClearColor(osg::Vec4(0.0f, 0.5f, 1.0f, 1.0f)); // Голубой цвет

   // Создание корневого узла, который содержит все объекты сцены
   osg::ref_ptr<osg::Group> root = new osg::Group;

   // Создание геометрии пола
   osg::ref_ptr<osg::Box> floorBox = new osg::Box(osg::Vec3(0.0f, -0.01f, 0.0f), FloorSize, 0.02f, FloorSize);

   // Создание отображения геометрии пола
   osg::ref_ptr<osg::ShapeDrawable> floorShapeDrawable = new osg::ShapeDrawable(floorBox);

   floorShapeDrawable->setColor(osg::Vec4(0.545f, 0.271f, 0.075f, 1.0f)); // Коричневый цвет
   osg::ref_ptr<osg::Geode> floorGeode = new osg::Geode;
   floorGeode->addDrawable(floorShapeDrawable);

   // Добавление пола в корневой узел
   root->addChild(floorGeode);

   // Создание группы для синих кубов
   osg::ref_ptr<osg::Group> blueCubesGroup = new osg::Group;
   root->addChild(blueCubesGroup);

   // Создание основного куба
   osg::ref_ptr<osg::Node> redCube = createCube(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f), CubeSize); // Красный цвет
   osg::ref_ptr<osg::PositionAttitudeTransform> redCubeTransform = new osg::PositionAttitudeTransform;
   redCubeTransform->setPosition(osg::Vec3(0.0f, -0.3f, 0.0f));
   redCubeTransform->addChild(redCube);
   root->addChild(redCubeTransform);

   // Добавление обработчика клавиатуры
   osg::ref_ptr<KeyboardEventHandler> keyboardEventHandler = new KeyboardEventHandler(redCubeTransform, blueCubesGroup);
   viewer.addEventHandler(keyboardEventHandler);


   // Установка корневого узла в визуализатор
   viewer.setSceneData(root);

   osgGA::TrackballManipulator* manipulator = new osgGA::TrackballManipulator;
   viewer.setCameraManipulator(manipulator);

   // Установка начальной позиции камеры
   manipulator->setHomePosition(osg::Vec3d(0.0, -5.0, -11.0), osg::Vec3d(), osg::Vec3d(0.0, 0.0, 0.0));




   viewer.run();

   return 0;
}