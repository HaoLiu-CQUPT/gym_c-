#ifndef RESERVATIONDIALOG_H
#define RESERVATIONDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QDateEdit>
#include <QTimeEdit>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include "reservation.h"

class ReservationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReservationDialog(QWidget *parent = nullptr);
    ReservationDialog(const Reservation& reservation, QWidget *parent = nullptr);
    
    Reservation getReservation() const;
    bool isEditMode() const { return editMode; }

private slots:
    void onOkClicked();
    void onCancelClicked();
    void onTypeChanged(int index);

private:
    void setupUI();
    void loadReservationData(const Reservation& reservation);
    void updateResourceCombo();
    
    bool editMode;
    QLineEdit *idEdit;
    QComboBox *memberCombo;
    QComboBox *typeCombo;
    QComboBox *resourceCombo;
    QDateEdit *dateEdit;
    QTimeEdit *startTimeEdit;
    QTimeEdit *endTimeEdit;
    QComboBox *statusCombo;
    QDoubleSpinBox *feeSpin;
    
    QPushButton *okButton;
    QPushButton *cancelButton;
};

#endif // RESERVATIONDIALOG_H




