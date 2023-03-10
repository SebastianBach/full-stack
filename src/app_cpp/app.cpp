#include <QApplication>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <text_conversion.h>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QWidget window;

    QString title{"Title Case App - "};
    title.append(text_conversion::version());
    title.append(" - ");
    title.append(text_conversion::date());

    window.setWindowTitle(title);

    auto* input  = new QLineEdit(&window);
    auto* result = new QLineEdit(&window);
    result->setReadOnly(true);

    auto* button = new QPushButton("Convert", &window);

    QObject::connect(button, &QPushButton::clicked,
                     [&]()
                     {
                         auto text = input->text().toStdString();
                         text_conversion::convert_to_title_case(text);
                         result->setText(QString(text.c_str()));
                     });

    auto* button_clear = new QPushButton("Clear", &window);

    QObject::connect(button_clear, &QPushButton::clicked,
                     [&]()
                     {
                         result->setText("");
                         input->setText("");
                     });

    auto* layout = new QVBoxLayout();
    auto* row1   = new QHBoxLayout();
    auto* row2   = new QHBoxLayout();
    auto* row3   = new QHBoxLayout();
    row1->addWidget(input);
    row1->addWidget(result);
    row2->addWidget(button);
    row3->addWidget(button_clear);
    layout->addLayout(row1);
    layout->addLayout(row2);
    layout->addLayout(row3);
    window.setLayout(layout);

    window.setMinimumWidth(500);

    window.show();
    return app.exec();
}
