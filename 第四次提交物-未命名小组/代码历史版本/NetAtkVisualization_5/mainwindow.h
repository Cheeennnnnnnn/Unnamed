#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QFileDialog>
#include <QSlider>
#include <QIcon>
#include <QTextStream>
#include <QTextEdit>

#include "prolib.h"
#include "dataReader.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void initializeUI();
    void setCurrentTime(Time time);
    void setMaxTime(Time time);
    void pause();

private:
    Ui::MainWindow *ui;

    QLabel* rateLabel;
    QLabel* cycleLabel;
    QLabel* validTimeLabel;
    QLabel* thresholdLabel;
    QLabel* filePathLabel;
    QLabel* time_h_now;
    QLabel* time_m_now;
    QLabel* time_s_now;
    QLabel* time_ms_now;
    QLabel* time_h_sum;
    QLabel* time_m_sum;
    QLabel* time_s_sum;
    QLabel* time_ms_sum;
    QLineEdit* userRateEdit;
    QLineEdit* currentRateEdit;
    QLineEdit* cycleEdit;
    QLineEdit* validTimeEdit;
    QLineEdit* thresholdEdit;
    QLineEdit* filePathEdit;
    QPushButton* acceptButton;
    QPushButton* resetButton;
    QPushButton* openFileButton;
    QPushButton* start_pauseButton;
    QSlider* slider;
    QTextEdit* dataEdit;

    QString filePath;
    float rate;
    int cycle;
    int validTime;
    int threshold;
    DataReader_csv* reader;
    bool start;
    int textCount;

private slots:
    void accept();
    void reset();
    void openFile();
    void start_pause();
    void changeTime(int time);
    void setTime();
    void getData(QString data);
    void setTime(int time);
    void pauseChangeTime();
    void changeRate(float rate);
    void warning(unsigned char* ip, bool isSender, int times);
};

#endif // MAINWINDOW_H
