#include "EditRectDialog.h"

EditRectDialog::EditRectDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	connect(ui.buttonBox, &QDialogButtonBox::accepted, this, &EditRectDialog::accept);
	connect(ui.buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

EditRectDialog::~EditRectDialog()
{
}

void EditRectDialog::setRect(LRect<double>* rect)
{
	m_rect = rect;
	fillFields();
}

void EditRectDialog::fillFields()
{
	ui.xLineEdit->setText(QString::number(m_rect->GetX() + 1));
	ui.yLineEdit->setText(QString::number(m_rect->GetY() + 1));
	ui.velocityLineEdit->setText(QString::number(m_rect->GetVel()));
	ui.widthLineEdit->setText(QString::number(m_rect->GetWidth()));
	ui.heightLineEdit->setText(QString::number(m_rect->GetHeight()));
}

void EditRectDialog::accept()
{
	m_rect->SetX(ui.xLineEdit->text().toInt());
	m_rect->SetY(ui.yLineEdit->text().toInt());
	m_rect->SetVel(ui.velocityLineEdit->text().toDouble());
	m_rect->SetWidth(ui.widthLineEdit->text().toInt());
	m_rect->SetHeight(ui.heightLineEdit->text().toInt());
	QDialog::accept();
}