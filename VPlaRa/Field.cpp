#include "Field.h"

//-------------------------------------------------------------------------------------------------
Field::Field(stringw name) {
	this->name = name;
}

//-------------------------------------------------------------------------------------------------
void Field::init() {
	tNode = sceneManager->addAnimatedMeshSceneNode(sceneManager->getMesh(stringw(L"Assets/levels/") + name + L"/" + name + L".3ds"), 0, CID_T);
	tNode->setScale(vector3df(100, 100, 100));
	tNode->setMaterialFlag(EMF_LIGHTING, false);
	ITriangleSelector *sele = sceneManager->createTriangleSelector(tNode);
	tNode->setTriangleSelector(sele);
	sele->drop();

	IAnimatedMesh *mesh = sceneManager->addHillPlaneMesh("myHill", dimension2d<f32>(20, 20), dimension2d<u32>(200, 200), 0, 0, dimension2d<f32>(0, 0), dimension2d<f32>(10, 10));
	oceanNode = sceneManager->addWaterSurfaceSceneNode(mesh->getMesh(0), 10, 500);
	oceanNode->setScale(vector3df(50, 1, 50));
	oceanNode->setMaterialFlag(EMF_LIGHTING, false);
	oceanNode->setMaterialTexture(0, videoDriver->getTexture(L"Assets/levels/ocean.png"));

	skyNode = sceneManager->addSkyDomeSceneNode(videoDriver->getTexture(L"Assets/levels/sky.png"));

	pointerNode = sceneManager->addAnimatedMeshSceneNode(sceneManager->getMesh("Assets/objects/pointer.3ds"));
	pointerNode->setScale(vector3df(20, 20, 20));
	pointerNode->setMaterialFlag(EMF_LIGHTING, false);

	cameraNode = sceneManager->addCameraSceneNode();
	cameraNode->setFarValue(1000000);

	setPos();

	scm = sceneManager->getSceneCollisionManager();

	then = timer->getTime();
}

//-------------------------------------------------------------------------------------------------
void Field::drop() {
	sceneManager->clear();
	GUIEnvironment->clear();

	delete this;
}

//-------------------------------------------------------------------------------------------------
void Field::update() {
	u32 now = timer->getTime();
	frameDeltaTime = (f32)(now - then) / 1000.0f;
	then = now;

	{
		if (key[KEY_KEY_W]) {
			vector3df after(pointer);
			after.Z -= (POINTERSPEED + wheel * 50) * frameDeltaTime;
			after.rotateXZBy(angle + 180, pointer);
			pointer = after;
			setPos();
		}

		if (key[KEY_KEY_S]) {
			vector3df after(pointer);
			after.Z += (POINTERSPEED + wheel * 50) * frameDeltaTime;
			after.rotateXZBy(angle + 180, pointer);
			pointer = after;
			setPos();
		}

		if (key[KEY_KEY_A]) {
			vector3df after(pointer);
			after.X += (POINTERSPEED + wheel * 50) * frameDeltaTime;
			after.rotateXZBy(angle + 180, pointer);
			pointer = after;
			setPos();
		}

		if (key[KEY_KEY_D]) {
			vector3df after(pointer);
			after.X -= (POINTERSPEED + wheel * 50) * frameDeltaTime;
			after.rotateXZBy(angle + 180, pointer);
			pointer = after;
			setPos();
		}

		if (key[KEY_LSHIFT]) {
			pointer.Y -= (POINTERSPEED + wheel * 50) * frameDeltaTime;
			if (pointer.Y < 0) {
				pointer.Y = 0;
			}
			setPos();
		}

		if (key[KEY_SPACE]) {
			pointer.Y += (POINTERSPEED + wheel * 50) * frameDeltaTime;
			if (pointer.Y > 10000) {
				pointer.Y = 10000;
			}
			setPos();
		}

		rotate += 100 * frameDeltaTime;
		pointerNode->setRotation(vector3df(0, rotate, 0));
	}

	line3df ray(pointer.X, pointer.Y - 20, pointer.Z, pointer.X, pointer.Y + 1000, pointer.Z);
	vector3df hitPoint;
	triangle3df hitTriangle;

	do {
		ISceneNode *hitNode = scm->getSceneNodeAndCollisionPointFromRay(ray, hitPoint, hitTriangle);
		if (!hitNode) {
			break;
		}
		else if (hitNode->getID() == CID_T) {
			pointer.Y++;
			ray.start.Y++;
			ray.end.Y++;
			setPos();
		}
	} while (true);
}

//-------------------------------------------------------------------------------------------------
void Field::draw() {
	sceneManager->drawAll();
	GUIEnvironment->drawAll();
}

//-------------------------------------------------------------------------------------------------
void Field::gui(SEvent::SGUIEvent event) {

}

//-------------------------------------------------------------------------------------------------
void Field::joystick(SEvent::SJoystickEvent event) {

}

//-------------------------------------------------------------------------------------------------
void Field::keyPressed(EKEY_CODE code, bool control, bool shift) {
	key[code] = true;
}

//-------------------------------------------------------------------------------------------------
void Field::keyReleased(EKEY_CODE code, bool control, bool shift) {
	key[code] = false;

	switch (code) {
	case KEY_KEY_Q :
		angle -= 45;
		setPos();
		break;
	case KEY_KEY_E :
		angle += 45;
		setPos();
		break;
	case KEY_KEY_H :
		pointer = vector3df();
		setPos();
		break;
	case KEY_ESCAPE :
		break;
	}
}

//-------------------------------------------------------------------------------------------------
void Field::log(SEvent::SLogEvent event) {

}

//-------------------------------------------------------------------------------------------------
void Field::mousePressed(s32 x, s32 y, EKEY_CODE code, bool control, bool shift) {

}

//-------------------------------------------------------------------------------------------------
void Field::mouseReleased(s32 x, s32 y, EKEY_CODE code, bool control, bool shift) {

}

//-------------------------------------------------------------------------------------------------
void Field::mouseDoubleClicked(s32 x, s32 y, EKEY_CODE code, bool control, bool shift) {

}

//-------------------------------------------------------------------------------------------------
void Field::mouseTripleClicked(s32 x, s32 y, EKEY_CODE code, bool control, bool shift) {

}

//-------------------------------------------------------------------------------------------------
void Field::mouseMoved(s32 x, s32 y) {

}

//-------------------------------------------------------------------------------------------------
void Field::mouseDraged(s32 width, s32 height, EKEY_CODE code, bool control, bool shift) {

}

//-------------------------------------------------------------------------------------------------
void Field::mouseWheel(f32 value) {
	wheel -= value * 4;
	if (wheel < 0) {
		wheel = 0;
	}
	else if (wheel > 32) {
		wheel = 32;
	}
	setPos();
}

//-------------------------------------------------------------------------------------------------
void Field::user(SEvent::SUserEvent event) {

}

void Field::setPos() {
	pointerNode->setPosition(pointer);
	vector3df camera(pointer);
	camera.Y += 20 + wheel * 10;
	camera.Z -= 40 + wheel * 10;
	camera.rotateXZBy(angle, pointer);
	cameraNode->setPosition(camera);
	cameraNode->setTarget(pointer);
}