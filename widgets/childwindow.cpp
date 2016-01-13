#include "childwindow.h"
#include "ui_childwindow.h"

ChildWindow::ChildWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChildWindow)
{
    ui->setupUi(this);
}

ChildWindow::~ChildWindow()
{
    delete ui;
}
