#include <QApplication>
#include "gamegui.h"

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);
  GameGui* gui = new GameGui();
  gui->show();
  return app.exec();
}
