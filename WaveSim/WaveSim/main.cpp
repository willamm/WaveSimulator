#include <QApplication>
#include <QProgressBar>
#include <QSlider>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	
	QWidget window;
	window.setFixedSize(800, 600);

	QProgressBar *progressBar = new QProgressBar(&window);
	progressBar->setRange(0, 100);
	progressBar->setValue(0);
	progressBar->setGeometry(10, 550, 780, 40);

	QSlider *slider = new QSlider(&window);
	slider->setOrientation(Qt::Horizontal);
	slider->setRange(0, 100);
	slider->setValue(0);
	slider->setGeometry(10, 500, 780, 40);

	QApplication::connect(slider, SIGNAL (valueChanged(int)), progressBar, SLOT (setValue(int)));

	window.show();
	return app.exec();
}
