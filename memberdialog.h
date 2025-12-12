#ifndef MEMBERDIALOG_H
#define MEMBERDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QDateEdit>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include "member.h"

class MemberDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MemberDialog(QWidget *parent = nullptr);
    MemberDialog(const Member& member, QWidget *parent = nullptr);
    
    Member getMember() const;
    bool isEditMode() const { return editMode; }

private slots:
    void onOkClicked();
    void onCancelClicked();

private:
    void setupUI();
    void loadMemberData(const Member& member);
    
    bool editMode;
    QLineEdit *idEdit;
    QLineEdit *nameEdit;
    QLineEdit *phoneEdit;
    QComboBox *genderCombo;
    QDateEdit *joinDateEdit;
    QDoubleSpinBox *balanceSpin;
    QComboBox *statusCombo;
    QTextEdit *noteEdit;
    
    QPushButton *okButton;
    QPushButton *cancelButton;
};

#endif // MEMBERDIALOG_H





