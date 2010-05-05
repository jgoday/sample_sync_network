#include "mainwindow.h"

#include <QDebug>
#include <QEventLoop>
#include <QLineEdit>
#include <QPushButton>
#include <QProcess>
#include <QTextEdit>
#include <QThread>
#include <QVBoxLayout>

// Network stuff
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>


MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    m_textView = new QTextEdit(this);
    m_urlLine = new QLineEdit("http://localhost:5000/job/1213", this);
    QPushButton *button = new QPushButton("Do request", this);

    layout->addWidget(m_textView);
    layout->addWidget(m_urlLine);
    layout->addWidget(button);

    setLayout(layout);

    QObject::connect(button, SIGNAL(clicked()), SLOT(doRequest()));
}

void MainWindow::doRequest()
{
    m_textView->setText("DO REQUEST");

    QNetworkRequest request;

    QNetworkAccessManager *manager = new QNetworkAccessManager();

    request.setHeader(QNetworkRequest::ContentTypeHeader, "text/xml");
    request.setUrl(m_urlLine->text());

    QNetworkReply *reply = manager->get(request);

    QEventLoop *loop = new QEventLoop;

    QObject::connect(manager, SIGNAL(finished(QNetworkReply *)),
                     loop, SLOT(quit()));
    loop->exec();

    qDebug() << "Exit loop ";
    setLabelFromReply(reply);

    delete manager;
}

void MainWindow::requestFinished(QNetworkReply *reply)
{
    setLabelFromReply(reply);
}

void MainWindow::setLabelFromReply(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        m_textView->setText("DATA RECEIVED: " + QString(reply->readAll()));
    }
    else {
        m_textView->setText("ERROR: " + reply->errorString());
    }
}
