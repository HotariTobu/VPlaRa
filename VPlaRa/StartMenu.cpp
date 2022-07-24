#include "StartMenu.h"

//-------------------------------------------------------------------------------------------------
void StartMenu::init() {
	IGUISkin *skin = GUIEnvironment->getSkin();

	IGUIFont *font = CGUITTFont::create(GUIEnvironment, "C:/Windows/Fonts/YuGothM.ttc", 32);
	skin->setFont(font);
	font->drop();

	for (s32 i = 0; i < EGDC_COUNT; ++i) {
		SColor col = skin->getColor((EGUI_DEFAULT_COLOR)i);
		col.setAlpha(230);
		skin->setColor((EGUI_DEFAULT_COLOR)i, col);
	}

	drawResolution = videoDriver->getScreenSize();

	s32 x1 = (drawResolution.Width - 400) / 2;
	s32 x2 = x1 + 400;

	play = GUIEnvironment->addButton(recti(x1, 400, x2, 480), 0, GUI_ID_PLAY, L"遊ぶ");
	quit = GUIEnvironment->addButton(recti(x1, 500, x2, 580), 0, GUI_ID_QUIT, L"終了する");
}

//-------------------------------------------------------------------------------------------------
void StartMenu::drop() {
	sceneManager->clear();
	GUIEnvironment->clear();

	delete this;
}

//-------------------------------------------------------------------------------------------------
void StartMenu::update() {

}

//-------------------------------------------------------------------------------------------------
void StartMenu::draw() {
	sceneManager->drawAll();
	GUIEnvironment->drawAll();
}

//-------------------------------------------------------------------------------------------------
void StartMenu::gui(SEvent::SGUIEvent event) {
	switch (event.EventType) {
	case EGET_BUTTON_CLICKED :
		s32 x, y;

		s32 index;
		IWriteFile *writeFile;
		stringw name;
		stringc seed;

		switch (event.Caller->getID()) {
		case GUI_ID_PLAY :
			x = (drawResolution.Width - 1200) / 2;
			y = (drawResolution.Height - 600) / 2;

			window = GUIEnvironment->addWindow(recti(x, y, x + 1200, y + 600), true, L"セレクト");
			window->setDraggable(false);

			listBox = GUIEnvironment->addListBox(recti(50, 50, 1150, 400), window);
			GUIEnvironment->addButton(recti(420, 450, 780, 550), window, GUI_ID_LOAD, L"読み込み");

			listBox->addItem(L"01");
			break;
		case GUI_ID_QUIT :
			device->closeDevice();
			break;
		case GUI_ID_LOAD:
			index = listBox->getSelected();
			if (index != -1) {
				change((IrrGameBase *)new Field(listBox->getListItem(index)));
			}
			break;
		}
		break;
	}
}

//-------------------------------------------------------------------------------------------------
void StartMenu::joystick(SEvent::SJoystickEvent event) {

}

//-------------------------------------------------------------------------------------------------
void StartMenu::keyPressed(EKEY_CODE code, bool control, bool shift) {

}

//-------------------------------------------------------------------------------------------------
void StartMenu::keyReleased(EKEY_CODE code, bool control, bool shift) {

}

//-------------------------------------------------------------------------------------------------
void StartMenu::log(SEvent::SLogEvent event) {

}

//-------------------------------------------------------------------------------------------------
void StartMenu::mousePressed(s32 x, s32 y, EKEY_CODE code, bool control, bool shift) {

}

//-------------------------------------------------------------------------------------------------
void StartMenu::mouseReleased(s32 x, s32 y, EKEY_CODE code, bool control, bool shift) {

}

//-------------------------------------------------------------------------------------------------
void StartMenu::mouseDoubleClicked(s32 x, s32 y, EKEY_CODE code, bool control, bool shift) {

}

//-------------------------------------------------------------------------------------------------
void StartMenu::mouseTripleClicked(s32 x, s32 y, EKEY_CODE code, bool control, bool shift) {

}

//-------------------------------------------------------------------------------------------------
void StartMenu::mouseMoved(s32 x, s32 y) {

}

//-------------------------------------------------------------------------------------------------
void StartMenu::mouseDraged(s32 width, s32 height, EKEY_CODE code, bool control, bool shift) {

}

//-------------------------------------------------------------------------------------------------
void StartMenu::mouseWheel(f32 value) {

}

//-------------------------------------------------------------------------------------------------
void StartMenu::user(SEvent::SUserEvent event) {

}