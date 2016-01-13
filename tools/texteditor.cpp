#include <QtWidgets>

#include "editor.h"
#include "texteditor.h"
#include "ui_texteditor.h"

TextEditor::TextEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TextEditor)
{
    ui->setupUi(this);

    setCentralWidget(ui->mdiArea);
    connect(ui->mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)),
            this, SLOT(updateActions()));
    windowActionGroup = new QActionGroup(this);
    readyLabel = new QLabel(tr(" Ready"));
    statusBar()->addWidget(readyLabel, 1);

    connect(ui->action_New, SIGNAL(triggered()), this, SLOT(newFile()));
    connect(ui->action_Open, SIGNAL(triggered()), this, SLOT(open()));
    connect(ui->action_Save, SIGNAL(triggered()), this, SLOT(save()));
    connect(ui->action_Save_As, SIGNAL(triggered()), this, SLOT(saveAs()));
    connect(ui->action_Exit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->action_Cut, SIGNAL(triggered()), this, SLOT(cut()));
    connect(ui->action_Copy, SIGNAL(triggered()), this, SLOT(copy()));
    connect(ui->action_Paste, SIGNAL(triggered()), this, SLOT(paste()));
    connect(ui->action_Close, SIGNAL(triggered()),
            ui->mdiArea, SLOT(closeActiveSubWindow()));
    connect(ui->action_Close_All, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->action_Tile, SIGNAL(triggered()),
            ui->mdiArea, SLOT(tileSubWindows()));
    connect(ui->action_Cascade, SIGNAL(triggered()),
            ui->mdiArea, SLOT(cascadeSubWindows()));
    connect(ui->action_Next, SIGNAL(triggered()),
            ui->mdiArea, SLOT(activateNextSubWindow()));
    connect(ui->action_Previous, SIGNAL(triggered()),
            ui->mdiArea, SLOT(activatePreviousSubWindow()));
    connect(ui->action_About, SIGNAL(triggered()), this, SLOT(about()));

    QTimer::singleShot(0, this, SLOT(loadFiles()));
}

TextEditor::~TextEditor()
{
    delete ui;
}

void TextEditor::loadFiles()
{
    QStringList args = QApplication::arguments();
    args.removeFirst();
    if (!args.isEmpty())
    {
        foreach (QString arg, args)
            openFile(arg);
        ui->mdiArea->cascadeSubWindows();
    }
    else
    {
        newFile();
    }
    ui->mdiArea->activateNextSubWindow();
}

void TextEditor::newFile()
{
    Editor *editor = new Editor;
    editor->newFile();
    addEditor(editor);
}

void TextEditor::openFile(const QString &fileName)
{
    Editor *editor = Editor::openFile(fileName, this);
    if (editor)
        addEditor(editor);
}

void TextEditor::closeEvent(QCloseEvent *event)
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

void TextEditor::open()
{
    Editor *editor = Editor::open(this);
    if (editor)
        addEditor(editor);
}

void TextEditor::save()
{
    if (activeEditor())
        activeEditor()->save();
}

void TextEditor::saveAs()
{
    if (activeEditor())
        activeEditor()->saveAs();
}

void TextEditor::cut()
{
    if (activeEditor())
        activeEditor()->cut();
}

void TextEditor::copy()
{
    if (activeEditor())
        activeEditor()->copy();
}

void TextEditor::paste()
{
    if (activeEditor())
        activeEditor()->paste();
}

void TextEditor::about()
{
    QMessageBox::about(this, tr("About Text Editor"),
            tr("<h2>Text Editor</h2>"
               "<p>Copyright &copy; 2016 Software Inc."
               "<p>Text Editor is a small application that for text "
               "Editing."));
}

void TextEditor::updateActions()
{
    bool hasEditor = (activeEditor() != 0);
    bool hasSelection = activeEditor()
                        && activeEditor()->textCursor().hasSelection();

    ui->action_Save->setEnabled(hasEditor);
    ui->action_Save_As->setEnabled(hasEditor);
    ui->action_Cut->setEnabled(hasSelection);
    ui->action_Copy->setEnabled(hasSelection);
    ui->action_Paste->setEnabled(hasEditor);
    ui->action_Close->setEnabled(hasEditor);
    ui->action_Close_All->setEnabled(hasEditor);
    ui->action_Tile->setEnabled(hasEditor);
    ui->action_Cascade->setEnabled(hasEditor);
    ui->action_Next->setEnabled(hasEditor);
    ui->action_Previous->setEnabled(hasEditor);

    if (activeEditor())
        activeEditor()->windowMenuAction()->setChecked(true);
}


void TextEditor::addEditor(Editor *editor)
{
    connect(editor, SIGNAL(copyAvailable(bool)),
            ui->action_Cut, SLOT(setEnabled(bool)));
    connect(editor, SIGNAL(copyAvailable(bool)),
            ui->action_Copy, SLOT(setEnabled(bool)));

    QMdiSubWindow *subWindow = ui->mdiArea->addSubWindow(editor);
    ui->menu_Window->addAction(editor->windowMenuAction());
    windowActionGroup->addAction(editor->windowMenuAction());
    subWindow->show();
}

Editor *TextEditor::activeEditor()
{
    QMdiSubWindow *subWindow = ui->mdiArea->activeSubWindow();
    if (subWindow)
        return qobject_cast<Editor *>(subWindow->widget());
    return 0;
}
