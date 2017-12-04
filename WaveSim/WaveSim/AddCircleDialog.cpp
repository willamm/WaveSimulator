#include "AddCircleDialog.h"

/**
*	Constructor for Add Cicle Dialog box.
*	
*	@param parent The parent QWidget
*/
AddCircleDialog::AddCircleDialog(QWidget* parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	connect(ui.pusButtonAdd, &QPushButton::pressed, this, &AddCircleDialog::apply);
	connect(ui.pushButtonCancel, &QPushButton::pressed, this, &QDialog::hide);
}

/**
*	Emits a signal containing the parameters of the desired circle.
*/
void AddCircleDialog::sendCircle()
{
	int x = ui.lineEditX->text().toInt();
	int y = ui.lineEditY->text().toInt();
	int r = ui.lineEditR->text().toInt();
	int vel = ui.lineEditVel->text().toInt();

	emit CircleSpecifiedSignal(x, y, r, vel * 0.01);
}

/**
*	Clears all the input fields in this dialog box.
*/
void AddCircleDialog::clearFields()
{
	ui.lineEditX->setText("");
	ui.lineEditY->setText("");
	ui.lineEditR->setText("");
	ui.lineEditVel->setText("");
}

/**
*	A Qt Slot.
*
*	When Okay is clicked by the user this slot gets triggered. This function
*	will specify a circle, clear the input fields and hide the dialog box.
*/
void AddCircleDialog::apply()
{
	sendCircle();
	clearFields();
	hide();
}
