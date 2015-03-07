#ifndef WEBBROWSER_H
#define WEBBROWSER_H

#include <QGridLayout>
#include <QWebView>
#include <QLineEdit>
#include <QToolButton>
#include <QWidget>
#include <QSettings>
#include <QDialog>
#include <QListWidget>

class WebBrowser : public QWidget
{
    Q_OBJECT
public:
    explicit WebBrowser(QWidget *parent = 0);

private:
    QWebView *web_;
    QLineEdit *address_;
    QToolButton *refresh_;
    QToolButton *back_;
    QToolButton *forward_;
    QToolButton *home_;
    QToolButton *homeplus_;
    QToolButton *fav_;
    QToolButton *history_;
    QToolButton *plus_;
    QToolButton *minus_;
    QGridLayout *layout_;
    QString homepage_;
    QSettings settings_;
    QDialog *dialogHistory_;
    QListWidget *historyList_;
    QHBoxLayout *layoutHistory_;

private:
    void setupConnections();
signals:

public slots:
    void onLoad();
    void onHome();
    void onSetHome();
    void onUrlChange(QUrl url);
    void onFavourite();
    void onHistory();
    void onPlus();
    void onMinus();

    void onLoadFinished(bool ok);
};

#endif // WEBBROWSER_H
