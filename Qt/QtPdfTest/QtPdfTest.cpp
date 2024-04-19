
#include <QPdfDocument>
#include <QLabel>
#include <QApplication>
#include <QDebug>

int main(int argc, char**argv)
{
    QApplication app(argc, argv);

    QPdfDocument doc;
    doc.load("gdpr.pdf");

    qDebug() << doc.status() << doc.pageCount();

    auto image = doc.render(10, QSize {210 * 3, 270 * 3});
    QLabel label;
    label.setPixmap(QPixmap::fromImage(image));
    label.show();

    return app.exec();
}