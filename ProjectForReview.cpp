#include "Headers.h"
   
int main()
{
   // Создание визуализатора для отображения сцены
   osgViewer::Viewer viewer;

   // Создание фона
   viewer.getCamera()->setClearColor(osg::Vec4(0.0f, 0.5f, 1.0f, 1.0f));

   // Создание корневого узла, который содержит все объекты сцены
   osg::Group* root = new osg::Group;

   // Создание геометрии пола
   osg::ref_ptr<osg::Box> floorBox = new osg::Box(osg::Vec3(0.0f, -0.01f, 0.0f), FloorSize, 0.02f, FloorSize);

   // Создание отображения геометрии пола
   osg::ref_ptr<osg::ShapeDrawable> floorShapeDrawable = new osg::ShapeDrawable(floorBox);

   floorShapeDrawable->setColor(osg::Vec4(0.545f, 0.271f, 0.075f, 1.0f));
   osg::ref_ptr<osg::Geode> floorGeode = new osg::Geode;
   floorGeode->addDrawable(floorShapeDrawable);

   // Добавление пола в корневой узел
   root->addChild(floorGeode);

   // Создание группы для синих кубов
   osg::ref_ptr<osg::Group> blueCubesGroup = new osg::Group;
   root->addChild(blueCubesGroup);

   // Создание основного куба красного цвета
   osg::ref_ptr<osg::Node> redCube = createCube();
   osg::ref_ptr<osg::PositionAttitudeTransform> redCubeTransform = new osg::PositionAttitudeTransform;
   redCubeTransform->setPosition(osg::Vec3(0.0f, -0.3f, 0.0f));
   redCubeTransform->addChild(redCube);
   root->addChild(redCubeTransform);

   // Добавление обработчика клавиатуры
   osg::ref_ptr<KeyboardEventHandler> keyboardEventHandler = new KeyboardEventHandler(redCubeTransform, blueCubesGroup);
   viewer.addEventHandler(keyboardEventHandler);

   osg::ref_ptr<osg::Group> _root = new osg::Group;
   root->addChild(_root);

   // Добавление обработчика мыши
   osg::ref_ptr<MouseEventHandler> mouseEventHandler = new MouseEventHandler(_root, blueCubesGroup);
   viewer.addEventHandler(mouseEventHandler);

   // Установка корневого узла в визуализатор
   viewer.setSceneData(root);

   // Добавление манипулятора камеры, который устанавливаем для визуализатора
   osgGA::TrackballManipulator* manipulator = new osgGA::TrackballManipulator;
   viewer.setCameraManipulator(manipulator);

   // Установка начальной позиции камеры (от 3-го лица над красным кубом)
   manipulator->setHomePosition(osg::Vec3d(0.0, -13.0, -17.0), osg::Vec3d(), osg::Vec3d(0.0, 0.0, 0.0));

   // Создание эффекта тумана
   osg::ref_ptr<osg::Fog> fog = new osg::Fog;
   fog->setColor(osg::Vec4(0.0f, 0.5f, 1.0f, 1.0f));
   fog->setDensity(0.0030f); 

   // Создание атрибута состояния для тумана
   osg::ref_ptr<osg::StateSet> stateSet = root->getOrCreateStateSet();
   stateSet->setAttributeAndModes(fog.get(), osg::StateAttribute::ON);

   viewer.run();

   return 0;
}
