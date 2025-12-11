#ifndef COURSEDIALOG_H
#define COURSEDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QTimeEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include "course.h"

class CourseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CourseDialog(QWidget *parent = nullptr);
    CourseDialog(const Course& course, QWidget *parent = nullptr);
    
    Course getCourse() const;
    bool isEditMode() const { return editMode; }

private slots:
    void onOkClicked();
    void onCancelClicked();

private:
    void setupUI();
    void loadCourseData(const Course& course);
    void updateCoachCombo();
    
    bool editMode;
    QLineEdit *idEdit;
    QLineEdit *nameEdit;
    QComboBox *coachCombo;
    QTimeEdit *startTimeEdit;
    QTimeEdit *endTimeEdit;
    QSpinBox *durationSpin;
    QDoubleSpinBox *priceSpin;
    QSpinBox *maxStudentsSpin;
    QComboBox *dayOfWeekCombo;
    QComboBox *statusCombo;
    
    QPushButton *okButton;
    QPushButton *cancelButton;
};

#endif // COURSEDIALOG_H




