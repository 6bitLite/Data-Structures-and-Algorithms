#include "mainwindow.h"
#include "queue.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QDialog>
#include <QTextEdit>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    currentOrderNumber(1) // Initialize order number to 1
{
    // Set the main window title
    setWindowTitle("Food Ordering App");

    // Apply styles to the application
    setStyleSheet(R"(
        QMainWindow {
            background-color: #f9f9f9;
        }
        QComboBox, QSpinBox, QLineEdit {
            background-color: #ffffff;
            border: 1px solid #cccccc;
            border-radius: 5px;
            padding: 5px;
        }
        QPushButton {
            background-color: #0078d7;
            color: white;
            border: none;
            border-radius: 5px;
            padding: 8px;
            font-size: 14px;
        }
        QPushButton:hover {
            background-color: #005a9e;
        }
        QLabel {
            font-size: 14px;
            font-weight: bold;
            color: #333333;
        }
        QListWidget {
            border: 1px solid #cccccc;
            border-radius: 5px;
            background-color: #ffffff;
        }
    )");

    // Create and populate food menu combo box
    foodMenuComboBox = new QComboBox(this);
    foodMenuComboBox->addItems({
        "Pizza", "Burger", "Pasta", "Salad",
        "Soup", "Spaghetti", "Chicken", "Coke",
        "Pepsi", "Nuggets"
    });

    // Create quantity spin box
    quantitySpinBox = new QSpinBox(this);
    quantitySpinBox->setRange(1, 100); // Allow selecting between 1 and 100 items
    quantitySpinBox->setValue(1);      // Default quantity is 1

    // Create buttons
    pushButton = new QPushButton("Push Order", this);
    queueButton = new QPushButton("Queue Order", this);
    popButton = new QPushButton("Pop Food Item", this);
    serveOrderButton = new QPushButton("Serve Order", this); // Serve button
    cancelOrderButton = new QPushButton("Cancel Order", this); // Cancel button
    viewHistoryButton = new QPushButton("View History", this); // View history button

    // Create list widgets and label
    orderListWidget = new QListWidget(this);
    waitingListWidget = new QListWidget(this);
    statusLabel = new QLabel("Waiting for orders...", this);

    // Set up button layout
    buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(pushButton);
    buttonLayout->addWidget(queueButton);
    buttonLayout->addWidget(popButton);
    buttonLayout->addWidget(serveOrderButton);
    buttonLayout->addWidget(cancelOrderButton);
    buttonLayout->addWidget(viewHistoryButton);

    // Set up main layout
    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(foodMenuComboBox);
    mainLayout->addWidget(new QLabel("Quantity:"));
    mainLayout->addWidget(quantitySpinBox);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(statusLabel);
    mainLayout->addWidget(new QLabel("Customer's Order:"));
    mainLayout->addWidget(orderListWidget);
    mainLayout->addWidget(new QLabel("Waiting Orders:"));
    mainLayout->addWidget(waitingListWidget);

    // Set central widget
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    // Connect signals to slots
    connect(pushButton, &QPushButton::clicked, this, &MainWindow::onPushButtonClicked);
    connect(queueButton, &QPushButton::clicked, this, &MainWindow::onQueueButtonClicked);
    connect(popButton, &QPushButton::clicked, this, &MainWindow::onPopButtonClicked);
    connect(serveOrderButton, &QPushButton::clicked, this, &MainWindow::onServeOrderClicked);
    connect(cancelOrderButton, &QPushButton::clicked, this, &MainWindow::onCancelOrderClicked);
    connect(viewHistoryButton, &QPushButton::clicked, this, &MainWindow::onViewHistoryButtonClicked);
}

MainWindow::~MainWindow() {}

void MainWindow::onPushButtonClicked()
{
    QString selectedFood = foodMenuComboBox->currentText();
    int quantity = quantitySpinBox->value();

    QList<QListWidgetItem*> existingItems = orderListWidget->findItems(selectedFood, Qt::MatchExactly);
    if (existingItems.isEmpty()) {
        orderListWidget->addItem(QString("%1 x %2").arg(selectedFood).arg(quantity));
    } else {
        QListWidgetItem *item = existingItems.first();
        QStringList parts = item->text().split(" x ");
        int currentQuantity = parts[1].toInt();
        int newQuantity = currentQuantity + quantity;
        item->setText(QString("%1 x %2").arg(selectedFood).arg(newQuantity));
    }

    statusLabel->setText(QString("%1 added to the order (%2 items)").arg(selectedFood).arg(quantity));
}

void MainWindow::onQueueButtonClicked()
{
    if (orderListWidget->count() == 0) {
        QMessageBox::warning(this, "Empty Order", "No items in the order to queue.");
        return;
    }

    QStringList orderItems;
    for (int i = 0; i < orderListWidget->count(); ++i) {
        orderItems.append(orderListWidget->item(i)->text());
    }

    QString currentOrder = QString("Order %1: %2 (Waiting)").arg(currentOrderNumber).arg(orderItems.join(", "));
    queue.enqueue(currentOrder);
    waitingListWidget->addItem(currentOrder);
    statusLabel->setText("Order queued successfully.");

    orderListWidget->clear();
    currentOrderNumber++;
}

void MainWindow::onPopButtonClicked()
{
    if (orderListWidget->count() > 0) {
        delete orderListWidget->takeItem(orderListWidget->count() - 1);
        statusLabel->setText("Removed the last item from the order.");
    } else {
        QMessageBox::warning(this, "No Items", "No items to remove from the order.");
    }
}

void MainWindow::onServeOrderClicked()
{
    if (waitingListWidget->count() == 0) {
        QMessageBox::information(this, "No Orders", "There are no orders to serve.");
        return;
    }

    QListWidgetItem *item = waitingListWidget->item(0);
    QString updatedText = item->text().replace("(Waiting)", "(Served)");
    item->setText(updatedText);

    queue.dequeue();
    statusLabel->setText("The first order has been served.");
}

void MainWindow::onCancelOrderClicked()
{
    if (waitingListWidget->count() == 0) {
        QMessageBox::information(this, "No Orders", "There are no orders to cancel.");
        return;
    }

    QListWidgetItem *item = waitingListWidget->item(0);
    QString updatedText = item->text().replace("(Waiting)", "(Canceled)");
    item->setText(updatedText);

    queue.dequeue();
    statusLabel->setText("The first order has been canceled.");
}

void MainWindow::onViewHistoryButtonClicked()
{
    if (waitingListWidget->count() == 0) {
        QMessageBox::information(this, "Order History", "No orders have been served or canceled yet.");
        return;
    }

    QDialog historyDialog(this);
    historyDialog.setWindowTitle("Order History");
    historyDialog.resize(400, 300);

    QVBoxLayout layout(&historyDialog);

    QTextEdit *historyDisplay = new QTextEdit(&historyDialog);
    historyDisplay->setReadOnly(true);

    QStringList historyList;
    for (int i = 0; i < waitingListWidget->count(); ++i) {
        historyList.append(waitingListWidget->item(i)->text());
    }

    historyDisplay->setText(historyList.join("\n"));
    layout.addWidget(historyDisplay);

    historyDialog.setLayout(&layout);
    historyDialog.exec();
}
