#ifndef CLFVRWINDOW_H
#define CLFVRWINDOW_H

#include <QMainWindow>

namespace Ui {
class clFVRWindow;
}

class clFVRWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit clFVRWindow(QWidget *parent = 0);
    ~clFVRWindow();

private:
    Ui::clFVRWindow *ui;
};

#endif // CLFVRWINDOW_H
