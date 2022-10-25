#ifndef RUBIUM_H
#define RUBIUM_H

#include <QMainWindow>
#include <QMouseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class Rubium; }
QT_END_NAMESPACE

class Rubium : public QMainWindow
{
    Q_OBJECT

public:
    Rubium(QWidget *parent = nullptr);
    ~Rubium();
    void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void loadfile();
    void savefile(QString fdir);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_fontComboBox_currentFontChanged(const QFont &f);

    void on_pushButton_3_clicked();

    void on_checkBox_4_stateChanged(int arg1);

    void on_checkBox_5_stateChanged(int arg1);

    void on_pushButton_4_clicked();

    void on_spinBox_valueChanged(int arg1);

    void on_checkBox_6_stateChanged(int arg1);

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_textBrowser_textChanged();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();
    void exitapp();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_checkBox_7_stateChanged(int arg1);

    void on_pushButton_15_clicked();

    void on_pushButton_16_clicked();

private:
    Ui::Rubium *ui;
};
#endif // RUBIUM_H
