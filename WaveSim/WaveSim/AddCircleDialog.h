#pragma once

#include <QDialog>
#include "ui_AddCircleDialog.h"

class AddCircleDialog : public QDialog
{
	Q_OBJECT

public:
	AddCircleDialog(QWidget *parent = Q_NULLPTR);
	~AddCircleDialog() = default;

private:
	Ui::AddCircleDialog ui;

	void sendCircle();
	void clearFields();

signals:
	void CircleSpecifiedSignal(const int x, const int y, const int r, const double vel);

private slots:
	void apply();
};
