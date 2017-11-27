#include "EditCircleDialog.h"

EditCircleDialog::EditCircleDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	connect(ui.buttonBox, &QDialogButtonBox::accepted, this, &EditCircleDialog::accept);
	connect(ui.buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

EditCircleDialog::~EditCircleDialog()
{
}

void EditCircleDialog::setCircle(LCircle<double>* circle)
{
	m_circle = circle;
	fillFields();
}

void EditCircleDialog::fillFields()
{
	ui.xLineEdit->setText(QString::number(m_circle->GetX() + 1));
	ui.yLineEdit->setText(QString::number(m_circle->GetY() + 1));
	ui.velocityLineEdit->setText(QString::number(m_circle->GetVel()));
	ui.radiusLineEdit->setText(QString::number(m_circle->GetRadius()));
}
void EditCircleDialog::accept()
{
	m_circle->SetX(ui.xLineEdit->text().toInt());
	m_circle->SetY(ui.yLineEdit->text().toInt());
	m_circle->SetVel(ui.velocityLineEdit->text().toDouble());
	m_circle->SetRadius(ui.radiusLineEdit->text().toInt());
	emit circleEdited();
	QDialog::accept();
}
