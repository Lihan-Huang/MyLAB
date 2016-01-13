#ifndef CHILDWINDOW_H
#define CHILDWINDOW_H

#include <QMainWindow>

namespace Ui {
class ChildWindow;
}

class ChildWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChildWindow(QWidget *parent = 0);
    ~ChildWindow();

private:
    Ui::ChildWindow *ui;
};

#endif // CHILDWINDOW_H


