#include "EditCircleDialog.h"

/**
*	Constructor for the edit circle dialog box.
*
*	@param parent The parent QWidget.
*/
EditCircleDialog::EditCircleDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	connect(ui.buttonBox, &QDialogButtonBox::accepted, this, &EditCircleDialog::accept);
	connect(ui.buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

/**
*	Assigns the circle the user wants to edit to this dialog.
*
*	@param circle A raw pointer to the circle to edit.
*/
void EditCircleDialog::setCircle(LCircle<double>* circle)
{
	mCircle = circle;
	fillFields();
}

/**
*	Populates the fields with the values from the current shape.
*/
void EditCircleDialog::fillFields()
{
	ui.xLineEdit->setText(QString::number(mCircle->GetX() + 1));
	ui.yLineEdit->setText(QString::number(mCircle->GetY() + 1));
	ui.velocityLineEdit->setText(QString::number(mCircle->GetVel()));
	ui.radiusLineEdit->setText(QString::number(mCircle->GetRadius()));
}

/**
*	Emits a signal containing the circle that the user wants to change
*	and the desired values.
*/
void EditCircleDialog::accept()
{
	const int x = ui.xLineEdit->text().toInt();
	const int y = ui.yLineEdit->text().toInt();
	const int r = ui.radiusLineEdit->text().toInt();
	const int vel = ui.velocityLineEdit->text().toDouble();

	emit CircleEdited(mCircle, x, y, r, vel);

	QDialog::accept();
}
