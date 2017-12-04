#include "AddRectDialog.h"

/**
*	Constructor for the dialog box for adding rectangles.
*	
*	@param parent The parent QWidget.
*/
AddRectDialog::AddRectDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	connect(ui.pushButtonAdd, &QPushButton::pressed, this, &AddRectDialog::apply);
	connect(ui.pushButtonCancel, &QPushButton::pressed, this, &QDialog::hide);
}

/**
*	Emits a signal containg the parameters of the desired rectangle.
*/
void AddRectDialog::sendRectangle()
{
	int x = ui.lineEditX->text().toInt();
	int y = ui.lineEditY->text().toInt();
	int w = ui.lineEditW->text().toInt();
	int h = ui.lineEditH->text().toInt();
	int vel = ui.lineEditVel->text().toDouble();

	emit RectSpecifiedSignal(x, y, w, h, vel * 0.01);
}

/**
*	Clears all the input fields.
*/
void AddRectDialog::clearFields()
{
	ui.lineEditX->setText("");
	ui.lineEditY->setText("");
	ui.lineEditW->setText("");
	ui.lineEditH->setText("");
	ui.lineEditVel->setText("");
}

/**
*	This is a Qt slot.
*
*	When Okay is clicked by the user this slot is triggered. This function
*	will specify a rectangle, clear all fields and hide the dialog box.
*/
void AddRectDialog::apply()
{
	sendRectangle();
	clearFields();
	hide();
}
