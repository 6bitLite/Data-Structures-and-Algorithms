#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QComboBox>
#include <QSpinBox>
#include <QListWidget>
#include <QLabel>
#include <QStringList>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "queue.h" // Custom Queue class for managing orders

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onPushButtonClicked();        // Add selected food items to the order
    void onQueueButtonClicked();       // Add the current order to the queue
    void onPopButtonClicked();         // Remove the last item from the current order
    void onServeOrderClicked();        // Mark the first order in the queue as served
    void onCancelOrderClicked();       // Cancel the first order in the queue
    void onViewHistoryButtonClicked(); // View the status of all orders (waiting, served, or canceled)

private:
    // Queue for managing orders
    Queue queue;

    // Widgets for the UI
    QComboBox *foodMenuComboBox;       // Drop-down menu for selecting food items
    QSpinBox *quantitySpinBox;         // Spin box for selecting item quantity
    QPushButton *pushButton;           // Button to add food items
    QPushButton *queueButton;          // Button to queue the current order
    QPushButton *popButton;            // Button to remove the last food item
    QPushButton *serveOrderButton;     // Button to serve an order
    QPushButton *cancelOrderButton;    // Button to cancel an order
    QPushButton *viewHistoryButton;    // Button to view the order history
    QListWidget *orderListWidget;      // List to display the current order
    QListWidget *waitingListWidget;    // List to display waiting orders
    QLabel *statusLabel;               // Label to display the current status

    // Layouts for organizing the UI
    QVBoxLayout *mainLayout;           // Main vertical layout
    QHBoxLayout *buttonLayout;         // Horizontal layout for buttons

    // Internal state
    int currentOrderNumber;            // Counter for assigning order numbers
};

#endif // MAINWINDOW_H
