#include "AddCircleDialog.h"

AddCircleDialog::AddCircleDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	connect(ui.pusButtonAdd, &QPushButton::pressed, this, &AddCircleDialog::apply);
	connect(ui.pushButtonCancel, &QPushButton::pressed, this, &QDialog::hide);
}

void AddCircleDialog::sendCircle()
{
	int x = ui.lineEditX->text().toInt();
	int y = ui.lineEditY->text().toInt();
	int r = ui.lineEditR->text().toInt();
	int vel = ui.lineEditVel->text().toInt();

	emit CircleSpecifiedSignal(x, y, r, vel * 0.01);
}

void AddCircleDialog::clearFields()
{
	ui.lineEditX->setText("");
	ui.lineEditY->setText("");
	ui.lineEditR->setText("");
	ui.lineEditVel->setText("");
}

void AddCircleDialog::apply()
{
	sendCircle();
	clearFields();
	hide();
}
