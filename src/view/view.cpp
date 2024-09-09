#include "view.h"
#include <QMessageBox>
#include "ui_view.h"

s21::View::View(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::View)
{
    ui->setupUi(this);
    ui->label->setText("0");
    connect(ui->pushButton_00, SIGNAL(clicked()), this, SLOT(add_numbers()));
    connect(ui->pushButton_01, SIGNAL(clicked()), this, SLOT(add_numbers()));
    connect(ui->pushButton_02, SIGNAL(clicked()), this, SLOT(add_numbers()));
    connect(ui->pushButton_03, SIGNAL(clicked()), this, SLOT(add_numbers()));
    connect(ui->pushButton_04, SIGNAL(clicked()), this, SLOT(add_numbers()));
    connect(ui->pushButton_05, SIGNAL(clicked()), this, SLOT(add_numbers()));
    connect(ui->pushButton_06, SIGNAL(clicked()), this, SLOT(add_numbers()));
    connect(ui->pushButton_07, SIGNAL(clicked()), this, SLOT(add_numbers()));
    connect(ui->pushButton_08, SIGNAL(clicked()), this, SLOT(add_numbers()));
    connect(ui->pushButton_09, SIGNAL(clicked()), this, SLOT(add_numbers()));
    connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(add_numbers()));


    connect(ui->bdiv, SIGNAL(clicked()), this, SLOT(add_operators()));
    connect(ui->bplus, SIGNAL(clicked()), this, SLOT(add_operators()));
    connect(ui->bminus, SIGNAL(clicked()), this, SLOT(add_operators()));
    connect(ui->bmult, SIGNAL(clicked()), this, SLOT(add_operators()));
    connect(ui->bmod, SIGNAL(clicked()), this, SLOT(add_operators()));
    connect(ui->bdegree, SIGNAL(clicked()), this, SLOT(add_operators()));

    connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(add_functions()));
    connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(add_functions()));
    connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(add_functions()));
    connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(add_functions()));
    connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(add_functions()));
    connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(add_functions()));
    connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(add_functions()));
    connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(add_functions()));
    connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(add_functions()));

    connect(ui->pushButton_op_br, SIGNAL(clicked()), this, SLOT(add_brackets()));
    connect(ui->pushButton_cl_br, SIGNAL(clicked()), this, SLOT(add_brackets()));

    ui->widget->xAxis->setRange(-10, 10);
    ui->widget->yAxis->setRange(-10, 10);

}

void s21::View::add_numbers() {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (button) {
        QString buttonText = button->text();
        QString currentText = ui->label->text();
        if (currentText == "0") {
            ui->label->setText(buttonText);
        } else {
            ui->label->setText(currentText + buttonText);
        }
    }
}

void s21::View::add_operators() {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (button) {
        QString buttonText = button->text();
        QString currentText = ui->label->text();
        if (currentText == "0") {
            ui->label->setText(buttonText);
        } else {
            ui->label->setText(currentText + " " + buttonText + " ");
        }
    }
}

void s21::View::add_functions() {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (button) {
        QString buttonText = button->text();
        QString currentText = ui->label->text();
        if (currentText == "0") {
            ui->label->setText(buttonText);
        } else {
            ui->label->setText(currentText + buttonText);
        }
    }
}

void s21::View::add_brackets() {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (button) {
        QString buttonText = button->text();
        QString currentText = ui->label->text();
        if (currentText == "0") {
            ui->label->setText(buttonText);
        } else {
            ui->label->setText(currentText + buttonText);
        }
    }
}

void s21::View::on_pushButton_AC_clicked()
{
    ui->label->clear();
    ui->label->setText("0");
}


void s21::View::on_pushButton_point_clicked()
{
    QString currentText = ui->label->text();
        if (currentText == "0") {
            ui->label->setText("0.");
        } else {
            ui->label->setText(currentText + ".");
        }
    }


s21::View::~View()
{
    delete ui;
}

void s21::View::on_pushButton_E_clicked()
{
    ui->label->setText(QString::number(M_E, 'f', 7));
}

void s21::View::on_pushButton_pi_clicked()
{
    ui->label->setText(QString::number(M_PI, 'f', 7));
}


void s21::View::on_pushButton_C_clicked()
{
    QString currentText = ui->label->text();
    if (!currentText.isEmpty()) {
        currentText.chop(1);
        if (currentText.isEmpty()) {
            ui->label->setText("0");
    } else {
        ui->label->setText(currentText);
        }
    }
}

double s21::View::SmartCalc(QString const currentText, double x_value) {
    std::string expression = currentText.toStdString();
    expression.append(" ");
    s21::ExampleController calc_controller;
    char *str = (char *)expression.c_str();
    double res = calc_controller.calculate(str, x_value);
    return res;
}

void s21::View::on_beq_clicked()
{
    QString currentText = ui->label->text();
    double x_value = ui->doubleSpinBox->value();
    try {
    double res = SmartCalc(currentText, x_value);
    QString result = QString::number(res, 'f', 7);
    ui->label->setText(result);
    } catch (const std::invalid_argument& e) {
        QMessageBox::warning(this, "Error", e.what());
        ui->label->setText("Error");
    }
}


void s21::View::on_pushButton_graph_clicked()
{
    QString currentText = ui->label->text();

    Xmin = ui->doubleSpinBox_Xmin->value();
    Xmax = ui->doubleSpinBox_Xmax->value();
    Ymax = ui->doubleSpinBox_Ymax->value();
    Ymin = ui->doubleSpinBox_Ymin->value();
    double N = 300;
    double h = (Xmax - Xmin)/(N -2);

    if (Xmin == 0 && Xmax == 0) {
        QMessageBox::warning(this, "Error:", "Values Xmin and Xmax can not be zero");
        return;
    }
    if (Ymin == 0 && Ymax == 0) {
        QMessageBox::warning(this, "Error:", "Values Ymin and Ymax can not be zero");
        return;
    }

    for (double X = Xmin; X <= Xmax; X += h) {
        x.push_back(X);
        double res = SmartCalc(currentText, X);
        if (res > Ymax || res < Ymin || isnan(res) || isinf(res)) {
            y.push_back(qQNaN());
        } else {
            y.push_back(res);
        }
    }

    ui->widget->clearGraphs();
    ui->widget->addGraph();
    for (int i = 0; i < x.size(); i++) {
        ui->widget->graph(0)->addData(x[i], y[i]);
    }
    ui->widget->replot();
    x.clear();
    y.clear();

    ui->widget->yAxis->setLabel("y(x) = " + currentText);
    ui->widget->xAxis->setRange(Xmin, Xmax);
    ui->widget->yAxis->setRange(Ymin, Ymax);
}


void s21::View::on_pushButton_graph_clear_clicked()
{
    ui->widget->clearGraphs();
    ui->widget->replot();
}

