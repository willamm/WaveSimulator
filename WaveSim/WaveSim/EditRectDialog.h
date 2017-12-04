#pragma once

#include <QDialog>

#include "ui_EditRectDialog.h"
#include "LRect.h"

class EditRectDialog : public QDialog
{
	Q_OBJECT

public:
	EditRectDialog(QWidget *parent = Q_NULLPTR);
	~EditRectDialog() = default;

	void setRect(LRect<double>* rect);

private:
	void fillFields();

	Ui::EditRectDialog ui;

	LRect<double>* mRect;	/*! The LRect that is being edited. */

signals:
	void RectEdited(LRect<double>* rect, const int x, const int y, const int w, const int h, const int vel);

public slots:
	void accept() override;

};
