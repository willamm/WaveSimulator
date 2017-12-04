#pragma once

#include <QDialog>

#include "ui_AddRectDialog.h"

class AddRectDialog : public QDialog
{
	Q_OBJECT

public:
	AddRectDialog(QWidget *parent = Q_NULLPTR);
	~AddRectDialog() = default;

private:
	Ui::AddRectDialog ui;

	void sendRectangle();
	void clearFields();

signals:
	void RectSpecifiedSignal(const int x, const int y, const int w, const int h, const double vel);

private slots:
	void apply();
};
