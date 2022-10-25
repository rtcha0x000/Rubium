#include "rubium.h"
#include "ui_rubium.h"
#include <QToolButton>
#include <QPixmap>
#include <QStyle>
#include <QFileDialog>
#include <QColorDialog>
#include <QFile>
#include <QIODevice>
#include <QClipboard>
#include <QMessageBox>
#include <QtTextToSpeech>
bool m_bPressed=false,exs=false,isc=false,xoc=false;
QPoint m_point;
QString curfile;
QColor curcolor;
QToolButton *minButton;
QToolButton *closeButton;
QTextToSpeech *s;

void Rubium::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        m_bPressed = true;
        m_point = event->pos();
    }
}

void Rubium::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    m_bPressed = false;
}

void Rubium::mouseMoveEvent(QMouseEvent *event)
{
    if (m_bPressed)
    move(event->pos()-m_point+pos());
}

void Rubium::loadfile(){
    ui->textBrowser->clear();
    QFile file(curfile);
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream in(&file);
    ui->textBrowser->append(in.readAll());
    file.close();
    ui->textBrowser->moveCursor(QTextCursor::Start);
    QFileInfo fi=QFileInfo(file);
    ui->label->setText(fi.fileName()+"-Rubium");
    isc=false;
}

void Rubium::savefile(QString fdir){
    QFile file(fdir);
    file.open(QIODevice::WriteOnly|QIODevice::Truncate);
    QTextStream out(&file);
    out<<ui->textBrowser->toPlainText();
    file.close();
}

void Rubium::exitapp(){
    if(!isc){
        QApplication::exit();
        return;
    }
    QMessageBox msgBox;
    msgBox.setText("The document has been modified.");
    msgBox.setInformativeText("Do you want to save your changes?");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    int ret = msgBox.exec();
    switch (ret) {
        case QMessageBox::Save:
            if(curfile=="")
                curfile=QFileDialog::getSaveFileName(this,"Save File","","*.rng");
            savefile(curfile);
            QApplication::exit();
            break;
        case QMessageBox::Discard:
            QApplication::exit();
            break;
        case QMessageBox::Cancel:
            break;
        default:
            break;
}
}

Rubium::Rubium(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Rubium)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);
    setFixedSize(this->width(), this->height());
    setWindowOpacity(0.9);
    setWindowFlags(Qt::FramelessWindowHint);
    int wide = width();
    minButton = new QToolButton(this);
    closeButton = new QToolButton(this);
    QPixmap minPix  = style()->standardPixmap(QStyle::SP_TitleBarMinButton);
    QPixmap closePix = style()->standardPixmap(QStyle::SP_TitleBarCloseButton);
    minButton->setIcon(minPix);
    closeButton->setIcon(closePix);
    minButton->setGeometry(wide-45,5,20,20);
    closeButton->setGeometry(wide-25,5,20,20);
    minButton->setStyleSheet("background-color:transparent;");
    closeButton->setStyleSheet("background-color:transparent;");
    connect(closeButton, SIGNAL(clicked()), this, SLOT(exitapp()));
    connect(minButton, SIGNAL(clicked()), this, SLOT(showMinimized()));
    ui->label->setAlignment(Qt::AlignCenter);
    ui->label_6->setAlignment(Qt::AlignCenter);
    char *username=getenv("USERNAME");
    ui->lineEdit->setPlaceholderText(" Text To Find");
    ui->lineEdit_2->setPlaceholderText(" Replace Text With");
    ui->frame_2->setVisible(0);
}

Rubium::~Rubium()
{
    delete ui;
}


void Rubium::on_pushButton_clicked()
{
    curfile=QFileDialog::getOpenFileName(this,"Open File","","Text File(*.txt)");
    loadfile();
}


void Rubium::on_pushButton_2_clicked()
{
    curfile="";
    ui->textBrowser->clear();
    ui->label->setText("Untitled-Rubium");
}


void Rubium::on_fontComboBox_currentFontChanged(const QFont &f)
{
    ui->textBrowser->setFont(f);
    ui->spinBox->setValue(ui->textBrowser->font().pointSize());
}


void Rubium::on_pushButton_3_clicked()
{
    bool tmp=isc;
    curcolor=QColorDialog::getColor(curcolor,this,"Choose Color");
    ui->pushButton_3->setStyleSheet("border-radius:0px;background-color:rgb("
                                    +QString::number(curcolor.red())
                                    +","+QString::number(curcolor.green())
                                    +","+QString::number(curcolor.blue())+");");
    ui->textBrowser->moveCursor(QTextCursor::Start);
    ui->textBrowser->setTextColor(curcolor);
    QString txt=ui->textBrowser->toPlainText();
    ui->textBrowser->clear();
    ui->textBrowser->append(txt);
    ui->textBrowser->moveCursor(QTextCursor::Start);
    isc=tmp;
    if(!isc){
        QFileInfo fi=QFileInfo(curfile);
        ui->label->setText(fi.fileName()+"-Rubium");
    }
}

void Rubium::on_checkBox_4_stateChanged(int arg1)
{
    bool tmp=isc;
    ui->textBrowser->setFontUnderline(ui->checkBox_4->isChecked());
    if(ui->radioButton->isChecked()){
        QString txt=ui->textBrowser->toPlainText();
        ui->textBrowser->clear();
        ui->textBrowser->append(txt);
        ui->textBrowser->moveCursor(QTextCursor::Start);
    }
    isc=tmp;
    if(!isc){
        QFileInfo fi=QFileInfo(curfile);
        ui->label->setText(fi.fileName()+"-Rubium");
    }
}


void Rubium::on_checkBox_5_stateChanged(int arg1)
{
    bool tmp=isc;
    ui->textBrowser->setFontItalic(ui->checkBox_5->isChecked());
    if(ui->radioButton->isChecked()){
        QString txt=ui->textBrowser->toPlainText();
        ui->textBrowser->clear();
        ui->textBrowser->append(txt);
        ui->textBrowser->moveCursor(QTextCursor::Start);
    }
    isc=tmp;
    if(!isc){
        QFileInfo fi=QFileInfo(curfile);
        ui->label->setText(fi.fileName()+"-Rubium");
    }
}


void Rubium::on_pushButton_4_clicked()
{
    if(ui->comboBox->currentText()=="Top")ui->textBrowser->moveCursor(QTextCursor::Start);
    else ui->textBrowser->moveCursor(QTextCursor::End);
}


void Rubium::on_spinBox_valueChanged(int arg1)
{
    bool tmp=isc;
    QFont f=ui->textBrowser->font();
    f.setPointSize(arg1);
    ui->textBrowser->setFont(f);
    if(ui->radioButton->isChecked()){
        QString txt=ui->textBrowser->toPlainText();
        ui->textBrowser->clear();
        ui->textBrowser->append(txt);
        ui->textBrowser->moveCursor(QTextCursor::Start);
    }
    isc=tmp;
    if(!isc){
        QFileInfo fi=QFileInfo(curfile);
        ui->label->setText(fi.fileName()+"-Rubium");
    }
}


void Rubium::on_checkBox_6_stateChanged(int arg1)
{
    bool tmp=isc;
    ui->textBrowser->setFontWeight(ui->checkBox_6->isChecked()?700:400);
    if(ui->radioButton->isChecked()){
        QString txt=ui->textBrowser->toPlainText();
        ui->textBrowser->clear();
        ui->textBrowser->append(txt);
        ui->textBrowser->moveCursor(QTextCursor::Start);
    }
    isc=tmp;
    if(!isc){
        QFileInfo fi=QFileInfo(curfile);
        ui->label->setText(fi.fileName()+"-Rubium");
    }
}


void Rubium::on_pushButton_5_clicked()
{
    Rubium::loadfile();
}


void Rubium::on_pushButton_6_clicked()
{
    QClipboard *b=QApplication::clipboard();
    b->setText(ui->textBrowser->toPlainText());
}


void Rubium::on_pushButton_7_clicked()
{
    bool tmp=isc;
    QString txt=ui->textBrowser->toPlainText();
    if(!txt.contains(ui->lineEdit->text(), Qt::CaseSensitive))
        QMessageBox::warning(this,"Not Found","The phrase is not found in the text.");
    else{
        ui->textBrowser->clear();
        int param=0,last=0;
        if(!txt.indexOf(ui->lineEdit->text())){
            ui->textBrowser->setTextBackgroundColor(QColor(0,255,255));
            ui->textBrowser->insertPlainText(ui->lineEdit->text());
            ui->textBrowser->setTextBackgroundColor(QColor(170, 255, 127));
            last=param+ui->lineEdit->text().size();
            param=ui->lineEdit->text().size();
        }
        while(1){
            param=txt.indexOf(ui->lineEdit->text(),param+ui->lineEdit->text().size());
            if(param<0){
                QString str="";
                for(int i=last;i<txt.size();i++)
                    str+=txt[i];
                ui->textBrowser->insertPlainText(str);
                break;
            }
            QString str="";
            for(int i=last;i<param;i++)
                str+=txt[i];
            ui->textBrowser->insertPlainText(str);
            ui->textBrowser->setTextBackgroundColor(QColor(0,255,255));
            ui->textBrowser->insertPlainText(ui->lineEdit->text());
            ui->textBrowser->setTextBackgroundColor(QColor(170, 255, 127));
            last=param+ui->lineEdit->text().size();
        }
    }
    isc=tmp;
    if(!isc){
        QFileInfo fi=QFileInfo(curfile);
        ui->label->setText(fi.fileName()+"-Rubium");
    }
}


void Rubium::on_pushButton_8_clicked()
{
    if(exs){
        setFixedSize(QSize(1020, 741));
        ui->pushButton_8->setText("More Functions(&X)");
        minButton->setGeometry(width()-45,5,20,20);
        closeButton->setGeometry(width()-25,5,20,20);
        exs=false;
    }
    else{
        setFixedSize(QSize(1277, 741));
        ui->pushButton_8->setText("Less Functions(&L)");
        minButton->setGeometry(width()-45,5,20,20);
        closeButton->setGeometry(width()-25,5,20,20);
        exs=true;
    }
}


void Rubium::on_pushButton_9_clicked()
{
    s=new QTextToSpeech;
    if(ui->comboBox_2->currentText()=="English")s->setLocale(QLocale::English);
    else if(ui->comboBox_2->currentText()=="Español")s->setLocale(QLocale::Spanish);
    else s->setLocale(QLocale::Chinese);
    s->say(ui->textBrowser->toPlainText());
}


void Rubium::on_pushButton_10_clicked()
{
    showFullScreen();
    minButton->setGeometry(width()-45,5,20,20);
    closeButton->setGeometry(width()-25,5,20,20);
    ui->textBrowser->setGeometry(QRect(0,0,width(),height()));
    ui->label_3->setVisible(0);
    ui->label_5->setVisible(0);
    ui->label_6->setVisible(0);
    ui->label_8->setVisible(0);
    ui->pushButton_14->setVisible(0);
    ui->pushButton_8->setVisible(0);
    ui->frame->setVisible(0);
}


void Rubium::on_textBrowser_textChanged()
{
    if(!isc){
        ui->label->setText("*"+ui->label->text());
        isc=true;
    }
}


void Rubium::on_pushButton_11_clicked()
{
    savefile(curfile);
    QFileInfo fi=QFileInfo(curfile);
    ui->label->setText(fi.fileName()+"-Rubium");
}


void Rubium::on_pushButton_12_clicked()
{
    curfile=QFileDialog::getSaveFileName(this,"Save File","","Text File(*.txt)");
    savefile(curfile);
    QFileInfo fi=QFileInfo(curfile);
    ui->label->setText(fi.fileName()+"-Rubium");
}


void Rubium::on_pushButton_13_clicked()
{
    QString txt=ui->textBrowser->toPlainText();
    if(!txt.contains(ui->lineEdit->text(), Qt::CaseSensitive))
        QMessageBox::warning(this,"Not Found","The phrase is not found in the text.");
    else{
        ui->textBrowser->clear();
        int param=0,last=0;
        if(!txt.indexOf(ui->lineEdit->text())){
            ui->textBrowser->setTextBackgroundColor(QColor(0,255,255));
            ui->textBrowser->insertPlainText(ui->lineEdit_2->text());
            ui->textBrowser->setTextBackgroundColor(QColor(170, 255, 127));
            last=param+ui->lineEdit->text().size();
            param=ui->lineEdit->text().size();
        }
        while(1){
            param=txt.indexOf(ui->lineEdit->text(),param+ui->lineEdit->text().size());
            if(param<0){
                QString str="";
                for(int i=last;i<txt.size();i++)
                    str+=txt[i];
                ui->textBrowser->insertPlainText(str);
                break;
            }
            QString str="";
            for(int i=last;i<param;i++)
                str+=txt[i];
            ui->textBrowser->insertPlainText(str);
            ui->textBrowser->setTextBackgroundColor(QColor(0,255,255));
            ui->textBrowser->insertPlainText(ui->lineEdit_2->text());
            ui->textBrowser->setTextBackgroundColor(QColor(170, 255, 127));
            last=param+ui->lineEdit->text().size();
        }
    }
}


void Rubium::on_pushButton_14_clicked()
{
    if(xoc){
        ui->frame_2->setVisible(0);
        ui->textBrowser->setGeometry(QRect(10, 130, 1001, 601));
        ui->pushButton_14->setText("Extra Options(&O)");
        xoc=false;
    }
    else{
        ui->frame_2->setVisible(1);
        ui->textBrowser->setGeometry(QRect(10, 130, 811, 601));
        ui->pushButton_14->setText("No Extra Options(&N)");
        xoc=true;
    }
}


void Rubium::on_checkBox_7_stateChanged(int arg1)
{
    ui->textBrowser->setReadOnly(ui->checkBox_7->isChecked());
}


void Rubium::on_pushButton_15_clicked()
{
    s->stop();
}


void Rubium::on_pushButton_16_clicked()
{
    curfile=QFileDialog::getSaveFileName(this,"Save File","","Rich Text File(*.rtf)");
    QFile file(curfile);
    file.open(QIODevice::WriteOnly|QIODevice::Truncate);
    QTextStream out(&file);
    out<<ui->textBrowser->toHtml();
    file.close();
    QFileInfo fi=QFileInfo(curfile);
    ui->label->setText(fi.fileName()+"-Rubium");
}

