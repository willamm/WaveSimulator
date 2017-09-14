#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_WaveSim.h"

class WaveSim : public QMainWindow
{
	Q_OBJECT

public:
	WaveSim(QWidget *parent = Q_NULLPTR);

private:
	Ui::WaveSimClass ui;
};
