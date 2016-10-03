#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QMouseEvent>
#include <QWheelEvent>
#include "algo/algo.h"

class BoardGui: public QGraphicsView {
  Q_OBJECT

public:
  double kPOINT_DRAW_RADIUS = 1;
  explicit BoardGui(double corrdinate_limit, QWidget *parent = NULL);
  const std::vector<Point>& points() { return points_; }
  void Clear();
  void NewClosestPair(int index1, int index2);
  void AddPoints(const std::vector<Point>& vec);
  void FocusPair(Point p1, Point p2);

signals:
  void newPoint(int num_point);

public slots:
  void mousePressEvent(QMouseEvent* e);

protected:
  virtual void wheelEvent(QWheelEvent* e);

private:
  // FIXME: qt的风格太不一样了...有点控制不住style跑偏
  void _AddPoint(Point p);
  double coordinate_limit_;
  // Member attributes
  std::vector<Point> points_;
  QGraphicsLineItem* mindist_line_;
  QGraphicsLineItem* x_axis_;
  QGraphicsLineItem* y_axis_;
};
