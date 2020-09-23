#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

#define windowsWidth 1200
#define windowsHeight 900

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    rate(1),
    cycle(100),
    validTime(300000),
    reader(nullptr),
    start(false)
{
    ui->setupUi(this);

    initializeUI();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initializeUI()
{
    setFixedSize(windowsWidth, windowsHeight);
    setWindowTitle("网络被攻击过程图形化");

    rateLabel = new QLabel(this);
    rateLabel ->setGeometry(windowsWidth / 2 - 400, 50, 100, 30);
    rateLabel ->setFont(QFont("Timers", 15, QFont::Bold));
    rateLabel ->setAlignment(Qt::AlignCenter);
    rateLabel ->setText("倍速");

    cycleLabel = new QLabel(this);
    cycleLabel ->setGeometry(windowsWidth / 2 - 260, 50, 170, 30);
    cycleLabel ->setFont(QFont("Timers", 15, QFont::Bold));
    cycleLabel ->setAlignment(Qt::AlignCenter);
    cycleLabel ->setText("刷新周期(ms)");

    validTimeLabel = new QLabel(this);
    validTimeLabel ->setGeometry(windowsWidth / 2 - 60, 50, 170, 30);
    validTimeLabel ->setFont(QFont("Timers", 15, QFont::Bold));
    validTimeLabel ->setAlignment(Qt::AlignCenter);
    validTimeLabel ->setText("显示范围(ms)");

    filePathLabel = new QLabel(this);
    filePathLabel ->setGeometry(50, windowsHeight - 65, 100, 30);
    filePathLabel ->setFont(QFont("Timers", 15, QFont::Bold));
    filePathLabel ->setAlignment(Qt::AlignRight);
    filePathLabel ->setText("目标文件");

    time_h_now = new QLabel(this);
    time_h_now ->setGeometry(windowsWidth - 345, windowsHeight - 120, 35, 20);
    time_h_now ->setFont(QFont("Timers", 12, QFont::Bold));
    time_h_now ->setAlignment(Qt::AlignRight);
    time_h_now ->setText("00:");

    time_m_now = new QLabel(this);
    time_m_now ->setGeometry(windowsWidth - 310, windowsHeight - 120, 35, 20);
    time_m_now ->setFont(QFont("Timers", 12, QFont::Bold));
    time_m_now ->setAlignment(Qt::AlignRight);
    time_m_now ->setText("00:");

    time_s_now = new QLabel(this);
    time_s_now ->setGeometry(windowsWidth - 275, windowsHeight - 120, 35, 20);
    time_s_now ->setFont(QFont("Timers", 12, QFont::Bold));
    time_s_now ->setAlignment(Qt::AlignRight);
    time_s_now ->setText("00:");

    time_ms_now = new QLabel(this);
    time_ms_now ->setGeometry(windowsWidth - 240, windowsHeight - 120, 45, 20);
    time_ms_now ->setFont(QFont("Timers", 12, QFont::Bold));
    time_ms_now ->setAlignment(Qt::AlignRight);
    time_ms_now ->setText("000/");

    time_h_sum = new QLabel(this);
    time_h_sum ->setGeometry(windowsWidth - 195, windowsHeight - 120, 35, 20);
    time_h_sum ->setFont(QFont("Timers", 12, QFont::Bold));
    time_h_sum ->setAlignment(Qt::AlignRight);
    time_h_sum ->setText("00:");

    time_m_sum = new QLabel(this);
    time_m_sum ->setGeometry(windowsWidth - 160, windowsHeight - 120, 35, 20);
    time_m_sum ->setFont(QFont("Timers", 12, QFont::Bold));
    time_m_sum ->setAlignment(Qt::AlignRight);
    time_m_sum ->setText("00:");

    time_s_sum = new QLabel(this);
    time_s_sum ->setGeometry(windowsWidth - 125, windowsHeight - 120, 35, 20);
    time_s_sum ->setFont(QFont("Timers", 12, QFont::Bold));
    time_s_sum ->setAlignment(Qt::AlignRight);
    time_s_sum ->setText("00:");

    time_ms_sum = new QLabel(this);
    time_ms_sum ->setGeometry(windowsWidth - 90, windowsHeight - 120, 35, 20);
    time_ms_sum ->setFont(QFont("Timers", 12, QFont::Bold));
    time_ms_sum ->setAlignment(Qt::AlignRight);
    time_ms_sum ->setText("000");

    rateEdit = new QLineEdit(this);
    rateEdit ->setGeometry(windowsWidth / 2 - 400, 80, 100, 40);
    rateEdit ->setFont(QFont("Timers", 15, QFont::Bold));
    rateEdit ->setText(QString::number(1));

    cycleEdit = new QLineEdit(this);
    cycleEdit ->setGeometry(windowsWidth / 2 - 250, 80, 150, 40);
    cycleEdit ->setFont(QFont("Timers", 15, QFont::Bold));
    cycleEdit ->setText(QString::number(100));

    validTimeEdit = new QLineEdit(this);
    validTimeEdit ->setGeometry(windowsWidth / 2 - 50, 80, 150, 40);
    validTimeEdit ->setFont(QFont("Timers", 15, QFont::Bold));
    validTimeEdit ->setText(QString::number(300000));

    filePathEdit = new QLineEdit(this);
    filePathEdit ->setGeometry(150, windowsHeight - 70, windowsWidth - 400, 40);
    filePathEdit ->setFont(QFont("Timers", 15, QFont::Bold));

    acceptButton = new QPushButton(this);
    acceptButton ->setGeometry(windowsWidth / 2 + 150, 80, 100, 40);
    acceptButton ->setFont(QFont("Timers", 15, QFont::Bold));
    acceptButton ->setText("应用");
    QObject::connect(acceptButton, SIGNAL(clicked()), this, SLOT(accept()));

    resetButton = new QPushButton(this);
    resetButton ->setGeometry(windowsWidth / 2 + 300, 80, 100, 40);
    resetButton ->setFont(QFont("Timers", 15, QFont::Bold));
    resetButton ->setText("重置");
    QObject::connect(resetButton, SIGNAL(clicked()), this, SLOT(reset()));

    openFileButton = new QPushButton(this);
    openFileButton ->setGeometry(windowsWidth - 200, windowsHeight - 70, 150, 40);
    openFileButton ->setFont(QFont("Timers", 15, QFont::Bold));
    openFileButton ->setText("打开文件");
    QObject::connect(openFileButton, SIGNAL(clicked()), this, SLOT(openFile()));

    start_pauseButton = new QPushButton(this);
    start_pauseButton ->setGeometry(50, windowsHeight - 130, 40, 40);
    start_pauseButton ->setFont(QFont("Timers", 15, QFont::Bold));
    start_pauseButton ->setIcon(QIcon(":/icon/start.png"));
    QObject::connect(start_pauseButton, SIGNAL(clicked()), this, SLOT(start_pause()));
    start_pauseButton ->setEnabled(false);

    slider = new QSlider(this);
    slider ->setOrientation(Qt::Horizontal);
    slider ->setGeometry(100, windowsHeight - 130, windowsWidth - 450, 40);
    slider ->setMinimum(0);
    slider ->setSingleStep(5000);
    slider ->setPageStep(5000);
    slider ->setStyleSheet
            (
                "QSlider::groove:horizontal {\
                border: 1px solid #4A708B;\
                background: #C0C0C0;\
                height: 30px;\
                border-radius: 1px;\
                padding-left:-1px;\
                padding-right:-1px;\
                }\
                \
                QSlider::sub-page:horizontal {\
                background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\
                    stop:0 #B1B1B1, stop:1 #c4c4c4);\
                background: qlineargradient(x1: 0, y1: 0.2, x2: 1, y2: 1,\
                    stop: 0 #5DCCFF, stop: 1 #1874CD);\
                border: 1px solid #4A708B;\
                height: 10px;\
                border-radius: 2px;\
                }\
                \
                QSlider::add-page:horizontal {\
                background: #575757;\
                border: 0px solid #777;\
                height: 10px;\
                border-radius: 2px;\
                }\
                \
                QSlider::handle:horizontal\
                {\
                    background: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5,\
                    stop:0.6 #45ADED, stop:0.778409 rgba(255, 255, 255, 255));\
                \
                    width: 11px;\
                    margin-top: -3px;\
                    margin-bottom: -3px;\
                    border-radius: 5px;\
                }\
                \
                QSlider::handle:horizontal:hover {\
                    background: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0.6 #2A8BDA,\
                    stop:0.778409 rgba(255, 255, 255, 255));\
                \
                    width: 11px;\
                    margin-top: -3px;\
                    margin-bottom: -3px;\
                    border-radius: 5px;\
                }\
                \
                QSlider::sub-page:horizontal:disabled {\
                background: #00009C;\
                border-color: #999;\
                }\
                \
                QSlider::add-page:horizontal:disabled {\
                background: #eee;\
                border-color: #999;\
                }\
                \
                QSlider::handle:horizontal:disabled {\
                background: #eee;\
                border: 1px solid #aaa;\
                border-radius: 4px;\
                }"
            );
    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(changeTime(int)));
    connect(slider, SIGNAL(sliderReleased()), this, SLOT(setTime()));
    connect(slider, SIGNAL(sliderPressed()), this, SLOT(pauseChangeTime()));
    slider ->setEnabled(false);

    dataEdit = new QTextEdit(this);
    dataEdit ->setGeometry(50, 150, windowsWidth - 100, windowsHeight - 300);
}

void MainWindow::setCurrentTime(Time time)
{
    QString h_s;
    QTextStream h_ts(&h_s);
    h_ts.setFieldWidth(3);
    h_ts.setPadChar('0');
    h_ts << QString::number(time.h) + ":";
    time_h_now ->setText(h_s);
    QString m_s;
    QTextStream m_ts(&m_s);
    m_ts.setFieldWidth(3);
    m_ts.setPadChar('0');
    m_ts << QString::number(time.m) + ":";
    time_m_now ->setText(m_s);
    QString s_s;
    QTextStream s_ts(&s_s);
    s_ts.setFieldWidth(3);
    s_ts.setPadChar('0');
    s_ts << QString::number(time.s) + ":";
    time_s_now ->setText(s_s);
    QString ms_s;
    QTextStream ms_ts(&ms_s);
    ms_ts.setFieldWidth(4);
    ms_ts.setPadChar('0');
    ms_ts << QString::number(time.ms) + "/";
    time_ms_now ->setText(ms_s);
}

void MainWindow::setMaxTime(Time time)
{
    QString h_s;
    QTextStream h_ts(&h_s);
    h_ts.setFieldWidth(3);
    h_ts.setPadChar('0');
    h_ts << QString::number(time.h) + ":";
    time_h_sum ->setText(h_s);
    QString m_s;
    QTextStream m_ts(&m_s);
    m_ts.setFieldWidth(3);
    m_ts.setPadChar('0');
    m_ts << QString::number(time.m) + ":";
    time_m_sum ->setText(m_s);
    QString s_s;
    QTextStream s_ts(&s_s);
    s_ts.setFieldWidth(3);
    s_ts.setPadChar('0');
    s_ts << QString::number(time.s) + ":";
    time_s_sum ->setText(s_s);
    QString ms_s;
    QTextStream ms_ts(&ms_s);
    ms_ts.setFieldWidth(3);
    ms_ts.setPadChar('0');
    ms_ts << QString::number(time.ms);
    time_ms_sum ->setText(ms_s);
}

void MainWindow::accept()
{
    float tempRate = rateEdit ->text().toFloat();
    int tempCycle = cycleEdit ->text().toInt();
    int tempValidTime = validTimeEdit ->text().toInt();
    if(notIn(tempRate, 0.1f, 20.0f) || notIn(tempCycle, 50, 2000) || notIn(tempValidTime, 1000, 1200000))
    {
        QMessageBox::warning(nullptr, "参数错误", "请检查参数是否合法(速率:0.1~20，刷新周期:50~2000，显示范围:1000~1200000)");
    }
    else
    {
        rate = tempRate;
        cycle = tempCycle;
        validTime = tempValidTime;
        if(reader != nullptr)
        {
            reader ->rate = rate;
            reader ->cycle = cycle;
            reader ->validTime = validTime;
            reader ->start();
        }
    }
}

void MainWindow::reset()
{
    rateEdit ->setText(QString::number(rate));
    cycleEdit ->setText(QString::number(cycle));
    validTimeEdit ->setText(QString::number(validTime));
}

void MainWindow::openFile()
{
//    if(start)
//    {
//        start_pause();
//    }
//    setTime(0);
//    if(filePathEdit ->text().isEmpty() || filePath == filePathEdit ->text())
//    {
        filePath = QFileDialog::getOpenFileName(this, tr("选择文件"), "I:/", tr("csv files(*.csv);;pcap files(*.pcap*)"));
//        if(filePath == filePathEdit ->text())
//        {
//            return;
//        }
        filePathEdit ->setText(filePath);
//    }
//    else
//    {
//        filePath = filePathEdit ->text();
//    }
//    filePath = "I:/monday.csv";
    DataReader_csv* temp = new DataReader_csv(filePath);
//    if(temp == nullptr || !temp ->checkLegality())
//    {
//        QMessageBox::warning(nullptr, "文件不合法", "请检查是否是合法的csv文件！");
//        delete temp;
//        temp = nullptr;
//        return;
//    }
    delete reader;
    reader = temp;
    connect(signalSenter, SIGNAL(readData(QString)), this, SLOT(getData(QString)));
    connect(signalSenter, SIGNAL(timeLapse(int)), this, SLOT(changeTime(int)));

    start_pauseButton ->setEnabled(true);
    slider ->setEnabled(true);
    slider ->setMaximum(reader ->maxTimeStamp);

    setMaxTime(reader ->maxTimeStamp);
}

void MainWindow::start_pause()
{
    switch(start)
    {
    case true:
    {
        start = false;
        start_pauseButton ->setIcon(QIcon(":/icon/start.png"));
        reader ->keepReading = false;
        break;
    }
    case false:
    {
        start = true;
        start_pauseButton ->setIcon(QIcon(":/icon/pause.png"));
        reader ->keepReading = true;
        reader ->start();
    }
    }
}

void MainWindow::changeTime(int time)
{
    setCurrentTime(time);
}

void MainWindow::setTime()
{
    reader ->setStartTime(slider ->value());
    reader ->start();
    connect(signalSenter, SIGNAL(timeLapse(int)), this, SLOT(changeTime(int)));
}

void MainWindow::getData(QString data)
{
    dataEdit ->append(data);
}

void MainWindow::setTime(int time)
{
    setCurrentTime(time);
    slider ->setValue(time);
}

void MainWindow::pauseChangeTime()
{
    disconnect(signalSenter, SIGNAL(timeLapse(int)), this, SLOT(changeTime(int)));
}
