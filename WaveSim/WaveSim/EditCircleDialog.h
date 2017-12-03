#pragma once

#include <QDialog>

#include "ui_EditCircleDialog.h"
#include "LCircle.h"

class EditCircleDialog : public QDialog
{
	Q_OBJECT

public:
	EditCircleDialog(QWidget *parent = Q_NULLPTR);
	~EditCircleDialog() = default;

	void setCircle(LCircle<double>* circle);

private:
	void fillFields();

	Ui::EditCircleDialog ui;

	LCircle<double>* mCircle;

signals:
	void CircleEdited(LCircle<double>* circle, const int x, const int y, const int r, const int vel);

public slots:
	void accept() override;

};

