#include "boardgui.h"

BoardGui::BoardGui(double coordinate_limit, QWidget *parent) :
  QGraphicsView(parent),
  coordinate_limit_(coordinate_limit),
  mindist_line_(NULL)
{
  setScene(new QGraphicsScene(this));
  setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
  // QGraphicView.setSceneRect 设置scroll bar scroll时(非zoom)能够看到的scene大小
  setSceneRect(-coordinate_limit*10, -coordinate_limit*10, coordinate_limit*20, coordinate_limit * 20);
  setMouseTracking(true);

  // Draw the x, y axis
  QPen pen(Qt::black);
  pen.setWidth(pen.width() * 8);
  x_axis_ = scene()->addLine(-coordinate_limit*10, 0, coordinate_limit*10, 0, pen);
  y_axis_ = scene()->addLine(0, -coordinate_limit*10, 0, coordinate_limit*10, pen);
}

void BoardGui::mousePressEvent(QMouseEvent * e)
{
  QPointF pt = mapToScene(e->pos());
  Point new_point(pt.x()/10.0, pt.y()/10.0);
  _AddPoint(new_point);
  emit newPoint(points_.size());
}

void BoardGui::NewClosestPair(int index1, int index2) {
  if (mindist_line_ != NULL) {
    scene()->removeItem(mindist_line_);
  }
  Point p1 = points_.at(index1);
  Point p2 = points_.at(index2);
  QPen pen(Qt::red);
  mindist_line_ = scene()->addLine(p1.x*10, p1.y*10, p2.x*10, p2.y*10, pen);
}

void BoardGui::Clear() {
  mindist_line_ = NULL;
  points_.clear();
  scene()->clear();
  // Draw the x, y axis
  QPen pen(Qt::black);
  pen.setWidth(pen.width() * 8);
  x_axis_ = scene()->addLine(-coordinate_limit_*10, 0, coordinate_limit_*10, 0, pen);
  y_axis_ = scene()->addLine(0, -coordinate_limit_*10, 0, coordinate_limit_*10, pen);
  viewport()->update();
}

void BoardGui::_AddPoint(Point p) {
  scene()->addEllipse(p.x * 10 - BoardGui::kPOINT_DRAW_RADIUS,
                      p.y * 10 - BoardGui::kPOINT_DRAW_RADIUS,
                      BoardGui::kPOINT_DRAW_RADIUS * 2.0,
                      BoardGui::kPOINT_DRAW_RADIUS * 2.0,
                      QPen(), QBrush(Qt::blue, Qt::SolidPattern));
  points_.push_back(p);
}

void BoardGui::AddPoints(const std::vector<Point>& vec) {
  for (std::vector<Point>::const_iterator it = vec.begin();
       it != vec.end(); it++) {
    _AddPoint(*it);
  }
  emit newPoint(points_.size());
}

void BoardGui::wheelEvent(QWheelEvent* e) {
  double zoomFactor = 1.25;

  QPointF oldPos = mapToScene(e->pos());

  // Zoom in or out
  if (e->delta() < 0) {
    zoomFactor = 1 / zoomFactor;
  }
  scale(zoomFactor, zoomFactor);
  // Get the new position
  QPointF newPos = mapToScene(e->pos());
  // Move scene to old position
  QPointF delta = newPos - oldPos;
  // FIXME: not work well
  translate(delta.x(), delta.y());
}

void BoardGui::FocusPair(Point p1, Point p2) {
  double half_rect_size;
  double x_dist = fabs(p1.x - p2.x) * 10;
  double y_dist = fabs(p1.y - p2.y) * 10;
  half_rect_size = x_dist > y_dist? x_dist: y_dist;//矩形边长取两倍长边的长度
  QPointF center = (QPointF(p1.x, p1.y) + QPointF(p2.x, p2.y)) * 5; // center取中心
  // 用于填满view里的矩形QRect
  QRectF exactRect(center.x() - half_rect_size, center.y() - half_rect_size,
                   2 * half_rect_size,
                   2 * half_rect_size);
  QMatrix mtx;
  // scale matrix把scene里的rect_size*2画到width()和height(). view的width和height本身就是正方形。所以不会畸形
  mtx.scale(width()/half_rect_size/2, height()/half_rect_size/2);
  // scene坐标到view坐标转换矩阵
  setMatrix(mtx);
  //setSceneRect(exactRect); // 可以没有, 没有就仍然可以scroll到整个空间. 感觉没有更科学
  // 设置center
  centerOn(exactRect.center());
}
