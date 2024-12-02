#include "Queue.h"

Queue::Queue() {}

void Queue::enqueue(const QString &order)
{
    orders.append(order);
}

QString Queue::dequeue()
{
    if (isEmpty())
        return QString();
    return orders.takeFirst();
}

bool Queue::isEmpty() const
{
    return orders.isEmpty();
}

int Queue::size() const
{
    return orders.size();
}

QString Queue::peekOrder(int index) const
{
    if (index >= 0 && index < orders.size())
        return orders.at(index);
    return QString();
}
