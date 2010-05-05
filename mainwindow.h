#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

class QLineEdit;
class QNetworkReply;
class QTextEdit;

class MainWindow : public QWidget
{
    Q_OBJECT
    public:
        MainWindow(QWidget *parent = 0);

    public slots:
        void doRequest();
        void requestFinished(QNetworkReply *);

    private:
        void setLabelFromReply(QNetworkReply *);

    private:
        QLineEdit *m_urlLine;
        QTextEdit *m_textView;
};
#endif
