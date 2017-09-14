#include <QApplication>
#include <QObject>
#include <QPushButton>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QWidget window;
	QPushButton *button;

	window.setFixedSize(1280, 720);

	button = new QPushButton("Hello World", &window);
	button->setGeometry(10, 10, 500, 300);
	button->setToolTip("This is a tooltip");

	QObject::connect(button, SIGNAL(clicked()), QApplication::instance(), SLOT(quit()));

	window.show();
	return app.exec();
}
