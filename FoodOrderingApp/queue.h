#ifndef QUEUE_H
#define QUEUE_H

#include <QString>
#include <QList>

class Queue
{
public:
    Queue();
    void enqueue(const QString &order);
    QString dequeue();
    bool isEmpty() const;
    int size() const;
    QString peekOrder(int index) const;  // Peek order based on index

private:
    QList<QString> orders;
};

#endif // QUEUE_H
