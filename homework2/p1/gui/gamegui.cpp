#include "gamegui.h"

GameGui::GameGui(): kCOORDINATE_LIMIT(DEFAULT_COORINATE_LIMIT),
                    kDECIMAL_LIMIT(DEFAULT_DECIMAL_LIMIT),
                    last_index1_(-1), last_index2_(-1), last_mindist_(-1) {
  ui.setupUi(this);
  // Setup the solver
  solver_ = new ClosestPairSolver();

  // Setup the graphic view
  boardGui = new BoardGui(kCOORDINATE_LIMIT, this);
  ui.graphicViewLayout->addWidget(boardGui);

  // Set validator for `randomNumEdit`
  ui.randomNumEdit->setValidator(new QIntValidator(0, MAX_RANDOM_GEN_NUM, this));

  // Connect singal and slots
  connect(boardGui, SIGNAL(newPoint(int)), this, SLOT(NewPoint(int)));
  connect(ui.calBtn, SIGNAL(clicked()), this, SLOT(CalClosestPair()));
  connect(ui.locateBtn, SIGNAL(clicked()), this, SLOT(LocateClosestPair()));
  connect(ui.saveBtn, SIGNAL(clicked()), this, SLOT(SavePoints()));
  connect(ui.loadBtn, SIGNAL(clicked()), this, SLOT(LoadPoints()));
  connect(ui.clearBtn, SIGNAL(clicked()), this, SLOT(Clear()));
  connect(ui.randomGenBtn, SIGNAL(clicked()), this, SLOT(GenRandomPoints()));
}

void GameGui::Clear() {
  boardGui->Clear();
  ui.totalNumLabel->setText(QString::number(0));
  last_index1_ = -1;
  last_index2_ = -1;
  last_mindist_ = -1;
  ui.p1Label->clear();
  ui.p2Label->clear();
  ui.minDistLabel->clear();
}

void GameGui::CalClosestPair() {
  solver_->SetPoints(boardGui->points());
  // FIXME: calculation should be done in background thread
  solver_->FindClosestPair(&last_index1_, &last_index2_, &last_mindist_);
  // Draw line between the closest pair of points
  boardGui->NewClosestPair(last_index1_, last_index2_);
  std::ostringstream os1, os2;
  os1 << "(" << boardGui->points().at(last_index1_) << ")";
  ui.p1Label->setText(QString::fromStdString(os1.str()));
  os2 << "(" << boardGui->points().at(last_index2_) << ")";
  ui.p2Label->setText(QString::fromStdString(os2.str()));
  ui.minDistLabel->setText(QString::number(last_mindist_));
}

void GameGui::NewPoint(int new_num_point) {
  ui.totalNumLabel->setText(QString::number(new_num_point));
}

void GameGui::SavePoints() {
  QString fileName = QFileDialog::getSaveFileName(this,
                                                  tr("Save points"), "./points.bin", tr("(*.bin)"));
  if (!fileName.isEmpty()) {
    std::ofstream ofs(fileName.toStdString());
    WriteFile(ofs, boardGui->points());
  }
}

void GameGui::LoadPoints() {
  QString fileName = QFileDialog::getOpenFileName(this,
                                                  tr("Load points"), ".", tr("(*.bin)"));
  if (!fileName.isEmpty()) {
    std::ifstream ifs(fileName.toStdString());
    std::vector<Point> vec;
    ReadFile(ifs, vec);
    boardGui->AddPoints(vec);
  }
}

void GameGui::GenRandomPoints() {
  QString str = ui.randomNumEdit->text();
  if (!str.isEmpty()) {
    std::vector<Point> vec;
    for (int i = 0; i < str.toInt(); i++) {
      double new_x = (double)rand() / RAND_MAX;
      new_x = (-kCOORDINATE_LIMIT) + new_x * (2*kCOORDINATE_LIMIT);
      double new_y = (double)rand() / RAND_MAX;
      new_y = (-kCOORDINATE_LIMIT) + new_y * (2*kCOORDINATE_LIMIT);
      vec.push_back(Point(new_x, new_y));
    }
    boardGui->AddPoints(vec);
  }
}

void GameGui::LocateClosestPair() {
  if (last_index1_ != -1 && last_index2_ != -1) {
    boardGui->FocusPair(boardGui->points().at(last_index1_),
                        boardGui->points().at(last_index2_));
  }
}
