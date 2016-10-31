#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logclient.h"
#include <QCloseEvent>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->fileNameKey->setText(QString("testLog"));
    ui->textLogData->setPlainText("0:this is a test data!12345678");

    ui->logLevelComboBox->addItem(QString("ALL_LOG_LEVEL"));
    ui->logLevelComboBox->addItem(QString("DEBUG_LOG_LEVEL"));
    ui->logLevelComboBox->addItem(QString("INFO_LOG_LEVEL"));
    ui->logLevelComboBox->addItem(QString("WARN_LOG_LEVEL"));
    ui->logLevelComboBox->addItem(QString("ERROR_LOG_LEVEL"));
    ui->logLevelComboBox->addItem(QString("FATAL_LOG_LEVEL"));
    ui->logLevelComboBox->addItem(QString("OFF_LOG_LEVEL"));

    m_pTableModel = new QStandardItemModel();
    m_pTableModel->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("FileName")));
    m_pTableModel->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("LogLvel")));
    m_pTableModel->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("Reserve")));
    //利用setModel()方法将数据模型与QTableView绑定
    ui->logTableView->setModel(m_pTableModel);

    ui->logTableView->setColumnWidth(0,200);
    ui->logTableView->setColumnWidth(1,200);
    ui->logTableView->setColumnWidth(2,100);

    //默认显示行头，如果你觉得不美观的话，我们可以将隐藏
//    ui->logTableView->verticalHeader()->hide();

    //设置选中时为整行选中
    ui->logTableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    //设置表格的单元为只读属性，即不能编辑
    ui->logTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //如果你用在QTableView中使用右键菜单，需启用该属性
    ui->logTableView->setContextMenuPolicy(Qt::CustomContextMenu);


    //设置单元格文本居中，张三的数据设置为居中显示
   /* m_pTableModel->item(0, 0)->setTextAlignment(Qt::AlignCenter);
    m_pTableModel->item(0, 1)->setTextAlignment(Qt::AlignCenter);
    m_pTableModel->item(0, 2)->setTextAlignment(Qt::AlignCenter);

    //设置单元格文本颜色，张三的数据设置为红色
    m_pTableModel->item(0, 0)->setForeground(QBrush(QColor(255, 0, 0)));
    m_pTableModel->item(0, 1)->setForeground(QBrush(QColor(255, 0, 0)));
    m_pTableModel->item(0, 2)->setForeground(QBrush(QColor(255, 0, 0)));

    //将字体加粗
    m_pTableModel->item(0, 0)->setFont( QFont( "Times", 10, QFont::Black ) );
    m_pTableModel->item(0, 1)->setFont( QFont( "Times", 10, QFont::Black ) );
    m_pTableModel->item(0, 2)->setFont( QFont( "Times", 10, QFont::Black ) );

    //设置排序方式，按年龄降序显示
    m_pTableModel->sort(3, Qt::DescendingOrder);*/

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString strFileName = ui->fileNameKey->text();
    QString strLogLevel = ui->logLevelComboBox->currentText();
    QString strLogData =ui->textLogData->toPlainText();

    int iCount = m_pTableModel->rowCount();
    m_pTableModel->setItem(iCount, 0, new QStandardItem(strFileName));
    m_pTableModel->setItem(iCount, 1, new QStandardItem(strLogLevel));

    CLogClient* pLogClient = new CLogClient(this);
    pLogClient->Start(strFileName.toStdString().c_str(),ui->logLevelComboBox->currentIndex(),strLogData);
}

void MainWindow::closeEvent(QCloseEvent * event)
{
    event->accept();

    emit closeLog();
}
