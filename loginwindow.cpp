#include "loginwindow.h"
#include <QApplication>

LoginWindow::LoginWindow(QWidget *parent)
    : QWidget(parent), mainWindow(nullptr)
{
    setupUI();
    setupConnections();
    
    // 设置窗口属性
    setWindowTitle("健身房管理系统 - 登录");
    setFixedSize(400, 250);
    
    // 加载数据
    DataManager::getInstance().loadAllData();
}

LoginWindow::~LoginWindow()
{
}

void LoginWindow::setupUI()
{
    titleLabel = new QLabel("健身房管理系统", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(18);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    
    usernameLabel = new QLabel("用户名:", this);
    usernameEdit = new QLineEdit(this);
    usernameEdit->setPlaceholderText("请输入用户名");
    
    passwordLabel = new QLabel("密码:", this);
    passwordEdit = new QLineEdit(this);
    passwordEdit->setPlaceholderText("请输入密码");
    passwordEdit->setEchoMode(QLineEdit::Password);
    
    loginButton = new QPushButton("登录", this);
    loginButton->setFixedHeight(35);
    exitButton = new QPushButton("退出", this);
    exitButton->setFixedHeight(35);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(titleLabel);
    mainLayout->addSpacing(20);
    mainLayout->addWidget(usernameLabel);
    mainLayout->addWidget(usernameEdit);
    mainLayout->addWidget(passwordLabel);
    mainLayout->addWidget(passwordEdit);
    mainLayout->addSpacing(10);
    
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(loginButton);
    buttonLayout->addWidget(exitButton);
    
    mainLayout->addLayout(buttonLayout);
    mainLayout->addStretch();
    
    setLayout(mainLayout);
}

void LoginWindow::setupConnections()
{
    connect(loginButton, &QPushButton::clicked, this, &LoginWindow::onLoginClicked);
    connect(exitButton, &QPushButton::clicked, this, &LoginWindow::onExitClicked);
    connect(passwordEdit, &QLineEdit::returnPressed, this, &LoginWindow::onLoginClicked);
}

void LoginWindow::onLoginClicked()
{
    QString username = usernameEdit->text().trimmed();
    QString password = passwordEdit->text();
    
    if (username.isEmpty()) {
        QMessageBox::warning(this, "警告", "请输入用户名！");
        usernameEdit->setFocus();
        return;
    }
    
    if (password.isEmpty()) {
        QMessageBox::warning(this, "警告", "请输入密码！");
        passwordEdit->setFocus();
        return;
    }
    
    DataManager& dm = DataManager::getInstance();
    if (dm.authenticate(username, password)) {
        User* user = dm.findUser(username);
        if (user) {
            if (mainWindow) {
                delete mainWindow;
            }
            mainWindow = new MainWindow(user->getRole(), this);
            mainWindow->show();
            this->hide();
            usernameEdit->clear();
            passwordEdit->clear();
        }
    } else {
        QMessageBox::critical(this, "错误", "用户名或密码错误！");
        passwordEdit->clear();
        passwordEdit->setFocus();
    }
}

void LoginWindow::onExitClicked()
{
    QApplication::quit();
}





