#pragma once

#include <QDialog>
#include "ui_EditRectDialog.h"
#include "LRect.h"

class EditRectDialog : public QDialog
{
	Q_OBJECT

public:
	EditRectDialog(QWidget *parent = Q_NULLPTR);
	~EditRectDialog();

	void setRect(LRect<double>* rect);

public slots:
	void accept() override;

private:
	void fillFields();

	Ui::EditRectDialog ui;

	LRect<double>* m_rect;
};
