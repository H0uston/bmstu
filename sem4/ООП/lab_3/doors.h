#ifndef DOORS_H
#define DOORS_H

#include <QObject>
#include <QTextEdit>
#include <QTimer>
#include "config.h"

class Doors : public QObject
{
    Q_OBJECT
    enum doors_state
    {
        OPENED,
        OPENNING,
        CLOSING,
        CLOSED
    };

public:
    explicit Doors(QObject *parent = nullptr);
    void set_consol(QTextEdit *text);

signals:
    void closeddoors();
    void openeddoors();

public slots:
    void start_openning();
    void start_closing();
    void open();
    void close();

private:
    doors_state current_state;

    QTextEdit *consol;

    QTimer doors_open_timer;
    QTimer doors_close_timer;
    QTimer doors_stay_open_timer;
};

#endif // DOORS_H
