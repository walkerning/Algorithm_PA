#include <sstream>
#include <fstream>

#include <QIntValidator>
#include <QFileDialog>
#include <QString>
#include <QWidget>

#include "ui_gamegui.h"
#include "boardgui.h"


#define DEFAULT_COORINATE_LIMIT 100
#define DEFAULT_DECIMAL_LIMIT 5
#define MAX_RANDOM_GEN_NUM 10000

class GameGui: public QWidget {
  Q_OBJECT

public:
  GameGui();
  const double kCOORDINATE_LIMIT;
  const double kDECIMAL_LIMIT;

public slots:
  void Clear();
  void CalClosestPair();
  void NewPoint(int);
  void SavePoints();
  void LoadPoints();
  void GenRandomPoints();
  void LocateClosestPair();

private:
  Ui::GameGui ui;
  BoardGui* boardGui;
  ClosestPairSolver* solver_;
  int last_index1_;
  int last_index2_;
  double last_mindist_;
};
