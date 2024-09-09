#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include <QVector>
#include <QtMath>
#include "../controller/exampleController.h"

QT_BEGIN_NAMESPACE
namespace Ui { class View; }
QT_END_NAMESPACE

namespace s21 {
class View : public QMainWindow
{
    Q_OBJECT

public:
    View(QWidget *parent = nullptr);
    ~View();

private:
    Ui::View *ui;
    ExampleController calc_controller;
    double Xmin, Xmax, Ymin, Ymax;
    QVector<double> x, y;

private slots:
    void add_numbers();
    void add_operators();
    void add_functions();
    void add_brackets();
    void on_pushButton_AC_clicked();
    void on_pushButton_point_clicked();
    void on_pushButton_E_clicked();
    void on_pushButton_pi_clicked();
    void on_pushButton_C_clicked();
    void on_beq_clicked();
    double SmartCalc(QString const currentText, double x_value);
    void on_pushButton_graph_clicked();
    void on_pushButton_graph_clear_clicked();
};
} // namespace 21
#endif // VIEW_H
