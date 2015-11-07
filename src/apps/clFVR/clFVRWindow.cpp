#include "clFVRWindow.h"
#include "ui_clFVRWindow.h"

clFVRWindow::clFVRWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::clFVRWindow)
{
    ui->setupUi(this);
}

clFVRWindow::~clFVRWindow()
{
    delete ui;
}
