#include "StartMenu.h"

int main() {
	IrrGameHost host;
	host.fullscreen = false;
	host.start((IrrGameBase *)new StartMenu());

	return 0;
}