#pragma once

#include <QDialog>
#include "ui_EditCircleDialog.h"
#include "LCircle.h"

class EditCircleDialog : public QDialog
{
	Q_OBJECT

public:
	EditCircleDialog(QWidget *parent = Q_NULLPTR);
	~EditCircleDialog();

	void setCircle(LCircle<double>* circle);

public slots:
	void accept() override;

private:
	void fillFields();

	Ui::EditCircleDialog ui;

	LCircle<double>* m_circle;
};
