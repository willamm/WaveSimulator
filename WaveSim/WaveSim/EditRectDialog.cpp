#include "EditRectDialog.h"

EditRectDialog::EditRectDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	connect(ui.buttonBox, &QDialogButtonBox::accepted, this, &EditRectDialog::accept);
	connect(ui.buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

void EditRectDialog::setRect(LRect<double>* rect)
{
	mRect = rect;
	fillFields();
}

void EditRectDialog::fillFields()
{
	ui.xLineEdit->setText(QString::number(mRect->GetX() + 1));
	ui.yLineEdit->setText(QString::number(mRect->GetY() + 1));
	ui.velocityLineEdit->setText(QString::number(mRect->GetVel()));
	ui.widthLineEdit->setText(QString::number(mRect->GetWidth()));
	ui.heightLineEdit->setText(QString::number(mRect->GetHeight()));
}

void EditRectDialog::accept()
{
	const int x = ui.xLineEdit->text().toInt();
	const int y = ui.yLineEdit->text().toInt();
	const int w = ui.widthLineEdit->text().toInt();
	const int h = ui.heightLineEdit->text().toInt();
	const int vel = ui.velocityLineEdit->text().toDouble();

	emit RectEdited(mRect, x, y, w, h, vel);

	QDialog::accept();
}