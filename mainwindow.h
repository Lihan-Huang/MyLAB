#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QAction;
class QActionGroup;
class QLabel;
class QMdiArea;
class QMenu;
class QToolBar;
class ChildWindow;
class TextEditor;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_action_About_triggered();
    void on_action_New_triggered();

    void on_action_Text_Editor_triggered();

private:
    Ui::MainWindow *ui;

    void addChildWindow(ChildWindow *childwindow);
    ChildWindow *activeChildWindow();

    void addTextEditor(TextEditor *texteditor);
    TextEditor *activeTextEditor();
};

#endif // MAINWINDOW_H
