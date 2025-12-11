#ifndef EQUIPDIALOG_H
#define EQUIPDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QDateEdit>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include "equipment.h"

class EquipDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EquipDialog(QWidget *parent = nullptr);
    EquipDialog(const Equipment& equipment, QWidget *parent = nullptr);
    
    Equipment getEquipment() const;
    bool isEditMode() const { return editMode; }

private slots:
    void onOkClicked();
    void onCancelClicked();

private:
    void setupUI();
    void loadEquipmentData(const Equipment& equipment);
    
    bool editMode;
    QLineEdit *idEdit;
    QLineEdit *nameEdit;
    QLineEdit *typeEdit;
    QDateEdit *purchaseDateEdit;
    QDoubleSpinBox *priceSpin;
    QComboBox *statusCombo;
    QLineEdit *locationEdit;
    QSpinBox *maintenanceCountSpin;
    
    QPushButton *okButton;
    QPushButton *cancelButton;
};

#endif // EQUIPDIALOG_H




