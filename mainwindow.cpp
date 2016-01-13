#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "widgets/childwindow.h"
#include "tools/texteditor.h"
#include <QtWidgets>

class QMessageBox;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setCentralWidget(ui->mdiArea);
    setWindowState(Qt::WindowMaximized);

    ui->statusBar->showMessage(tr("Ready"));
    connect(ui->action_About_Qt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_About_triggered()
{
    QMessageBox::about(this, tr("About MyLAB"),
            tr("<h2>MyLAB </h2>"
               "<p>Copyright &copy; 2016 Software Inc."
               "<p>MyLAB is an application that "
               "implements algorithms in Machine Learing, "
               "Optimization, Computer Vision and "
               "Computer Graphics."));
}


void MainWindow::on_action_New_triggered()
{
    ChildWindow *childwindow = new ChildWindow;
    addChildWindow(childwindow);
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    ui->mdiArea->closeAllSubWindows();
    if (!ui->mdiArea->subWindowList().isEmpty())
    {
        event->ignore();
    }
    else
    {
        event->accept();
    }
}

void MainWindow::addChildWindow(ChildWindow *childwindow)
{
    QMdiSubWindow *subWindow = ui->mdiArea->addSubWindow(childwindow);
    subWindow->show();
}

ChildWindow *MainWindow::activeChildWindow()
{
    QMdiSubWindow *subWindow = ui->mdiArea->activeSubWindow();
    if (subWindow)
        return qobject_cast<ChildWindow *>(subWindow->widget());
    return 0;
}

void MainWindow::on_action_Text_Editor_triggered()
{
    TextEditor *texteditor = new TextEditor;
    addTextEditor(texteditor);
}

void MainWindow::addTextEditor(TextEditor *texteditor)
{
    QMdiSubWindow *subWindow = ui->mdiArea->addSubWindow(texteditor);
    subWindow->show();
}

TextEditor *MainWindow::activeTextEditor()
{
    QMdiSubWindow *subWindow = ui->mdiArea->activeSubWindow();
    if (subWindow)
        return qobject_cast<TextEditor *>(subWindow->widget());
    return 0;
}
