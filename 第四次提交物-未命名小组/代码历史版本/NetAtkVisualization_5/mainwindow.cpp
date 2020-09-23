#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

#define windowsWidth 1100
#define windowsHeight 700

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    rate(1),
    cycle(100),
    validTime(300000),
    threshold(1000),
    reader(nullptr),
    start(false),
    textCount(0)
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
    rateLabel ->setGeometry(windowsWidth / 2 - 535, 50, 170, 30);
    rateLabel ->setFont(QFont("Timers", 15, QFont::Bold));
    rateLabel ->setAlignment(Qt::AlignCenter);
    rateLabel ->setText("倍速|实速");

    cycleLabel = new QLabel(this);
    cycleLabel ->setGeometry(windowsWidth / 2 - 360, 50, 170, 30);
    cycleLabel ->setFont(QFont("Timers", 15, QFont::Bold));
    cycleLabel ->setAlignment(Qt::AlignCenter);
    cycleLabel ->setText("刷新周期(ms)");

    validTimeLabel = new QLabel(this);
    validTimeLabel ->setGeometry(windowsWidth / 2 - 160, 50, 170, 30);
    validTimeLabel ->setFont(QFont("Timers", 15, QFont::Bold));
    validTimeLabel ->setAlignment(Qt::AlignCenter);
    validTimeLabel ->setText("显示范围(ms)");

    thresholdLabel = new QLabel(this);
    thresholdLabel ->setGeometry(windowsWidth / 2 + 40, 50, 170, 30);
    thresholdLabel ->setFont(QFont("Timers", 15, QFont::Bold));
    thresholdLabel ->setAlignment(Qt::AlignCenter);
    thresholdLabel ->setText("攻击检测阈值");

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

    userRateEdit = new QLineEdit(this);
    userRateEdit ->setGeometry(windowsWidth / 2 - 500, 80, 50, 40);
    userRateEdit ->setFont(QFont("Timers", 15, QFont::Bold));
    userRateEdit ->setText(QString::number(1));

    currentRateEdit = new QLineEdit(this);
    currentRateEdit ->setGeometry(windowsWidth / 2 - 450, 80, 50, 40);
    currentRateEdit ->setFont(QFont("Timers", 15, QFont::Bold));
    currentRateEdit ->setText(QString::number(1));

    cycleEdit = new QLineEdit(this);
    cycleEdit ->setGeometry(windowsWidth / 2 - 350, 80, 150, 40);
    cycleEdit ->setFont(QFont("Timers", 15, QFont::Bold));
    cycleEdit ->setText(QString::number(100));

    validTimeEdit = new QLineEdit(this);
    validTimeEdit ->setGeometry(windowsWidth / 2 - 150, 80, 150, 40);
    validTimeEdit ->setFont(QFont("Timers", 15, QFont::Bold));
    validTimeEdit ->setText(QString::number(300000));

    thresholdEdit = new QLineEdit(this);
    thresholdEdit ->setGeometry(windowsWidth / 2 + 50, 80, 150, 40);
    thresholdEdit ->setFont(QFont("Timers", 15, QFont::Bold));
    thresholdEdit ->setText(QString::number(10000));

    filePathEdit = new QLineEdit(this);
    filePathEdit ->setGeometry(150, windowsHeight - 70, windowsWidth - 400, 40);
    filePathEdit ->setFont(QFont("Timers", 15, QFont::Bold));

    acceptButton = new QPushButton(this);
    acceptButton ->setGeometry(windowsWidth / 2 + 250, 80, 100, 40);
    acceptButton ->setFont(QFont("Timers", 15, QFont::Bold));
    acceptButton ->setText("应用");
    QObject::connect(acceptButton, SIGNAL(clicked()), this, SLOT(accept()));
    acceptButton ->setEnabled(false);

    resetButton = new QPushButton(this);
    resetButton ->setGeometry(windowsWidth / 2 + 400, 80, 100, 40);
    resetButton ->setFont(QFont("Timers", 15, QFont::Bold));
    resetButton ->setText("复原");
    QObject::connect(resetButton, SIGNAL(clicked()), this, SLOT(reset()));
    resetButton ->setEnabled(false);

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

void MainWindow::pause()
{
    start = false;
    start_pauseButton ->setIcon(QIcon(":/icon/start.png"));
    reader ->keepReading = false;
}

void MainWindow::accept()
{
    float tempRate = userRateEdit ->text().toFloat();
    int tempCycle = cycleEdit ->text().toInt();
    int tempValidTime = validTimeEdit ->text().toInt();
    int tempThreshold = thresholdEdit ->text().toInt();
    if(notIn(tempRate, 0.1f, 100.0f) || notIn(tempCycle, 50, 2000) || notIn(tempValidTime, 1000, 1200000) || notIn(tempThreshold, 100, 120000))
    {
        QMessageBox::warning(nullptr, "参数错误", "请检查参数是否合法(速率:0.1~100，刷新周期:50~2000，显示范围:1000~1200000，攻击检测阈值:100~120000)");
    }
    else
    {
        currentRateEdit ->setText(QString::number(tempRate));
        rate = tempRate;
        cycle = tempCycle;
        validTime = tempValidTime;
        threshold = tempThreshold;
        if(reader != nullptr)
        {
            reader ->userRate = rate;
            reader ->currentRate = rate;
            reader ->cycle = cycle;
            reader ->validTime = validTime;
            reader ->csvProcessor ->warningThreshold = threshold;
            reader ->start();
        }
    }
}

void MainWindow::reset()
{
    userRateEdit ->setText(QString::number(rate));
    currentRateEdit ->setText(QString::number(rate));
    cycleEdit ->setText(QString::number(cycle));
    validTimeEdit ->setText(QString::number(validTime));
    thresholdEdit ->setText(QString::number(threshold));
}

void MainWindow::openFile()
{
    if(start)
    {
        start_pause();
    }
    setTime(0);
    filePath = "I:/monday.csv";
    if(filePathEdit ->text().isEmpty() || filePath == filePathEdit ->text())
    {
//        filePath = QFileDialog::getOpenFileName(this, tr("选择文件"), "I:/", tr("csv files(*.csv);;pcap files(*.pcap*)"));
        if(filePath == filePathEdit ->text())
        {
            return;
        }
        filePathEdit ->setText(filePath);
    }
    else
    {
        filePath = filePathEdit ->text();
    }
    DataReader_csv* temp = new DataReader_csv(filePath);
    if(temp == nullptr || !temp ->checkLegality())
    {
        QMessageBox::warning(nullptr, "文件不合法", "请检查是否是合法的csv文件！");
        delete temp;
        temp = nullptr;
        return;
    }
    delete reader;
    reader = temp;
    connect(signalSenter, SIGNAL(readData(QString)), this, SLOT(getData(QString)));
    connect(signalSenter, SIGNAL(timeLapse(int)), this, SLOT(changeTime(int)));
    connect(signalSenter, SIGNAL(slowDown(float)), this, SLOT(changeRate(float)));
    connect(signalSenter, SIGNAL(underAttack(unsigned char*, bool, int)), this, SLOT(warning(unsigned char*, bool, int)));

    acceptButton ->setEnabled(true);
    resetButton ->setEnabled(true);
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
    /*
     * 通知前端清空所有点和线
    */

    reader ->setStartTime(slider ->value());
    reader ->start();
    connect(signalSenter, SIGNAL(timeLapse(int)), this, SLOT(changeTime(int)));
}

void MainWindow::getData(QString data)
{
    if(textCount > 1000)
    {
        dataEdit ->clear();
        textCount = 0;
    }
    dataEdit ->append(data);
    ++textCount;
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

void MainWindow::changeRate(float rate)
{
    currentRateEdit ->setText(QString::number(rate));
}

void MainWindow::warning(unsigned char *ip, bool isSender, int times)
{
    pause();
    QString tarIP = IP_to_QString(ip), type, sum = QString::number(times), state;
    if(isSender)
    {
        type = "发送";
    }
    else
    {
        type = "接收";
    }
    QMessageBox::warning(nullptr, "检测到可能的攻击", QString("IP为%1的设备因短时间内%2了%3条数据而可能正处于攻击/被攻击状态!")
                         .arg(tarIP).arg(type).arg(sum));
}
