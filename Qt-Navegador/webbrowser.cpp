#include "webbrowser.h"
#include <QFile>
#include <QListWidget>
#include <QWebHistory>

WebBrowser::WebBrowser(QWidget *parent) :
    QWidget(parent)
{
    web_ = new QWebView(this);
    address_ = new QLineEdit(this);
    refresh_ = new QToolButton;
    back_ = new QToolButton;
    forward_ = new QToolButton;
    home_ = new QToolButton;
    homeplus_ = new QToolButton;
    fav_ = new QToolButton;
    history_ = new QToolButton;
    plus_ = new QToolButton;
    minus_ = new QToolButton;
    home_->setToolTip("Ir a la página principal");
    homeplus_->setToolTip("Establecer esta página como la página principal");
    layout_ = new QGridLayout;
    refresh_->setIcon(QIcon(QPixmap(":/icons/resources/refresh.png")));
    back_->setIcon(QIcon(QPixmap(":/icons/resources/go-previous.png")));
    forward_->setIcon(QIcon(QPixmap(":/icons/resources/go-next.png")));
    home_->setIcon(QIcon(QPixmap(":/icons/resources/go-home.png")));
    homeplus_->setIcon(QIcon(QPixmap(":/icons/resources/go-home.png")));
    fav_->setIcon(QIcon(QPixmap(":/icons/resources/favourite.png")));
    history_->setIcon(QIcon(QPixmap(":/icons/resources/history.gif")));
    plus_->setIcon(QIcon(QPixmap(":/icons/resources/plus.png")));
    minus_->setIcon(QIcon(QPixmap(":/icons/resources/minus.png")));
    layout_->addWidget(back_,0,0,1,1);
    layout_->addWidget(forward_,0,1,1,1);
    layout_->addWidget(home_,0,2,1,1);
    layout_->addWidget(homeplus_,0,3,1,1);
    layout_->addWidget(refresh_,0,4,1,1);
    layout_->addWidget(address_,0,5,1,1);
    layout_->addWidget(fav_,0,6,1,1);
    layout_->addWidget(history_,0,7,1,1);
    layout_->addWidget(plus_,0,8,1,1);
    layout_->addWidget(minus_,0,9,1,1);
    layout_->addWidget(web_,1,0,1,10);
    homepage_= "http://duckduckgo.com";
    if (settings_.value("homepage").toString() != "")
    {
        homepage_ = settings_.value("homepage").toString();
    }
    address_->setText(homepage_);
    web_->load(homepage_);
    setLayout(layout_);
    setupConnections();

    // Historial
    dialogHistory_ = new QDialog(this);
    historyList_ = new QListWidget(dialogHistory_);
    layoutHistory_ = new QHBoxLayout(dialogHistory_);
    layoutHistory_->addWidget(historyList_);
    dialogHistory_->setLayout(layoutHistory_);
}

void WebBrowser::setupConnections()
{
    connect(address_,SIGNAL(returnPressed()),this,SLOT(onLoad()));
    connect(refresh_,SIGNAL(pressed()),web_,SLOT(reload()));
    connect(forward_,SIGNAL(pressed()),web_,SLOT(forward()));
    connect(back_,SIGNAL(pressed()),web_,SLOT(back()));
    connect(home_,SIGNAL(pressed()),this,SLOT(onHome()));
    connect(homeplus_,SIGNAL(pressed()),this,SLOT(onSetHome()));
    connect(fav_,SIGNAL(pressed()),this,SLOT(onFavourite()));
    connect(history_,SIGNAL(pressed()),this,SLOT(onHistory()));
    connect(plus_,SIGNAL(pressed()),this,SLOT(onPlus()));
    connect(minus_,SIGNAL(pressed()),this,SLOT(onMinus()));
    connect(web_,SIGNAL(urlChanged(QUrl)),this,SLOT(onUrlChange(QUrl)));
    connect(web_,SIGNAL(loadFinished(bool)),this,SLOT(onLoadFinished(bool)));
}

void WebBrowser::onLoad()
{
    if (!address_->text().startsWith("http://") && !address_->text().startsWith("https://") && address_->text().length()!=0)
    {
        web_->load("http://"+address_->text());
    }
    else
    {
        web_->load(address_->text());
    }
}

void WebBrowser::onHome()
{
    web_->load(homepage_);
}

void WebBrowser::onUrlChange(QUrl url)
{
    address_->setText(url.toString());
}

void WebBrowser::onLoadFinished(bool ok)
{
    if(!ok)
    {
        web_->load("https://duckduckgo.com/?q="+address_->text());
    }
}

void WebBrowser::onFavourite()
{
    QString url = address_->text() + "\n";
    QFile archivo("favourites.txt");
    archivo.open(QIODevice::ReadWrite);
    bool found = false;
    while (!archivo.atEnd()) {
        QString urlFile = archivo.readLine();
        if (urlFile==url)
        {
            found = true;
            break;
        }
    }
    if (!found)
    {
        archivo.write(url.toStdString().c_str(), url.length());
    }
    archivo.close();
}

void WebBrowser::onSetHome()
{
    settings_.setValue("homepage", address_->text());
}

void WebBrowser::onHistory()
{
    historyList_->clear();

    QWebHistory * historial = web_->history();
    QString titulo;
    QString url;
    for (int i = 0; i < historial->items().length(); ++i) {
        titulo = historial->itemAt(i).title();
        url = historial->itemAt(i).url().toString();
        historyList_->addItem(titulo + " - " + url);
    }

    dialogHistory_->show();
}

void WebBrowser::onPlus()
{
    web_->setZoomFactor(web_->zoomFactor() + .05);
}

void WebBrowser::onMinus()
{
    web_->setZoomFactor(web_->zoomFactor() - .05);
}
