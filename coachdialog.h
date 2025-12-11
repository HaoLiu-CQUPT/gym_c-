#ifndef COACHDIALOG_H
#define COACHDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QDateEdit>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include "coach.h"

class CoachDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CoachDialog(QWidget *parent = nullptr);
    CoachDialog(const Coach& coach, QWidget *parent = nullptr);
    
    Coach getCoach() const;
    bool isEditMode() const { return editMode; }

private slots:
    void onOkClicked();
    void onCancelClicked();

private:
    void setupUI();
    void loadCoachData(const Coach& coach);
    
    bool editMode;
    QLineEdit *idEdit;
    QLineEdit *nameEdit;
    QLineEdit *phoneEdit;
    QComboBox *genderCombo;
    QDateEdit *hireDateEdit;
    QDoubleSpinBox *salarySpin;
    QLineEdit *specialtyEdit;
    QComboBox *statusCombo;
    
    QPushButton *okButton;
    QPushButton *cancelButton;
};

#endif // COACHDIALOG_H




