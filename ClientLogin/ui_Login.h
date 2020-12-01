/********************************************************************************
** Form generated from reading UI file ''
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QPushButton *connectButton;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *inputName;
    QLineEdit *inputHost;
    QLineEdit *inputPort;
    QLabel *label_4;
    QLabel *label_5;

    void setupUi(QWidget *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName(QStringLiteral("Login"));
        Login->resize(640, 480);
        connectButton = new QPushButton(Login);
        connectButton->setObjectName(QStringLiteral("connectButton"));
        connectButton->setGeometry(QRect(400, 250, 89, 25));
        formLayoutWidget = new QWidget(Login);
        formLayoutWidget->setObjectName(QStringLiteral("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(120, 150, 281, 91));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(formLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        label_2 = new QLabel(formLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        label_3 = new QLabel(formLayoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        inputName = new QLineEdit(formLayoutWidget);
        inputName->setObjectName(QStringLiteral("inputName"));

        formLayout->setWidget(0, QFormLayout::FieldRole, inputName);

        inputHost = new QLineEdit(formLayoutWidget);
        inputHost->setObjectName(QStringLiteral("inputHost"));

        formLayout->setWidget(1, QFormLayout::FieldRole, inputHost);

        inputPort = new QLineEdit(formLayoutWidget);
        inputPort->setObjectName(QStringLiteral("inputPort"));

        formLayout->setWidget(2, QFormLayout::FieldRole, inputPort);

        label_4 = new QLabel(Login);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(20, 50, 291, 61));
        label_5 = new QLabel(Login);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(170, 60, 81, 51));

        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QWidget *Login)
    {
        Login->setWindowTitle(QApplication::translate("Login", "Form", Q_NULLPTR));
        connectButton->setText(QApplication::translate("Login", "Connect", Q_NULLPTR));
        label->setText(QApplication::translate("Login", "<html><head/><body><p><span style=\" color:#cc0000;\">Name</span></p></body></html>", Q_NULLPTR));
        label_2->setText(QApplication::translate("Login", "<html><head/><body><p><span style=\" color:#cc0000;\">Host</span></p></body></html>", Q_NULLPTR));
        label_3->setText(QApplication::translate("Login", "<html><head/><body><p><span style=\" color:#cc0000;\">Port</span></p></body></html>", Q_NULLPTR));
        label_4->setText(QApplication::translate("Login", "<html><head/><body><p><span style=\" font-family:'-apple-system,BlinkMacSystemFont,Segoe UI,Helvetica,Arial,sans-serif,Apple Color Emoji,Segoe UI Emoji'; font-size:xx-large; font-weight:600; color:#cc0000; background-color:#ffffff;\">Wolfenstein</span><span style=\" font-family:'-apple-system,BlinkMacSystemFont,Segoe UI,Helvetica,Arial,sans-serif,Apple Color Emoji,Segoe UI Emoji'; font-size:xx-large; font-weight:600; color:#24292e; background-color:#ffffff;\"/></p><p><br/></p></body></html>", Q_NULLPTR));
        label_5->setText(QApplication::translate("Login", "<html><head/><body><p><span style=\" font-size:36pt; color:#4e9a06;\">3D</span></p></body></html>", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

