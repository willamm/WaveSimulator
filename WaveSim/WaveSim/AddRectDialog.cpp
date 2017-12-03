#include "AddRectDialog.h"

AddRectDialog::AddRectDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	connect(ui.pushButtonAdd, &QPushButton::pressed, this, &AddRectDialog::apply);
	connect(ui.pushButtonCancel, &QPushButton::pressed, this, &QDialog::hide);
}

void AddRectDialog::sendRectangle()
{
	int x = ui.lineEditX->text().toInt();
	int y = ui.lineEditY->text().toInt();
	int w = ui.lineEditW->text().toInt();
	int h = ui.lineEditH->text().toInt();
	int vel = ui.lineEditVel->text().toDouble();

	emit RectSpecifiedSignal(x, y, w, h, vel * 0.01);
}

void AddRectDialog::clearFields()
{
	ui.lineEditX->setText("");
	ui.lineEditY->setText("");
	ui.lineEditW->setText("");
	ui.lineEditH->setText("");
	ui.lineEditVel->setText("");
}

void AddRectDialog::apply()
{
	sendRectangle();
	clearFields();
	hide();
}
