#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void closeLog();

private slots:
    void on_pushButton_clicked();

protected:
    void closeEvent(QCloseEvent * event);

private:
    Ui::MainWindow *ui;
    QStandardItemModel *m_pTableModel;
};

#endif // MAINWINDOW_H
