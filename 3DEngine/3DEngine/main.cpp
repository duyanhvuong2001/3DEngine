#include "AppWindow.h"

int main() {
	AppWindow app;
	if (app.Init()) {
		while (app.isRunning()) {
			
			app.Broadcast();
		}
	}


	return 0;
}