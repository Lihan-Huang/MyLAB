#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QMainWindow>

class QAction;
class QActionGroup;
class QLabel;
class QMdiArea;
class QMenu;
class QToolBar;
class Editor;

namespace Ui {
class TextEditor;
}

class TextEditor : public QMainWindow
{
    Q_OBJECT

public:
    explicit TextEditor(QWidget *parent = 0);
    ~TextEditor();

public slots:
    void newFile();
    void openFile(const QString &fileName);

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void open();
    void save();
    void saveAs();
    void cut();
    void copy();
    void paste();
    void about();
    void updateActions();
    void loadFiles();

private:
    Ui::TextEditor *ui;
    QActionGroup *windowActionGroup;
    QLabel *readyLabel;

    void addEditor(Editor *editor);
    Editor *activeEditor();
};

#endif // TEXTEDITOR_H
