#include <QCoreApplication>
#include <QTextStream>
#include <QStringList>
#include <QDebug>
#include <QDate>
#include <QFile>

class FuelPrice {
public:
    QString fuelType;
    QDate date;
    double price;

    FuelPrice(QString fuelType, QDate date, double price)
        : fuelType(fuelType), date(date), price(price) {}

    QString print() {
        qDebug() << "Fuel type - " << fuelType;
        qDebug() << "Date - " << date.toString("yyyy.MM.dd");
        qDebug() << "Price - " << price << "\n";
        return QString();
    }
};

int main() {

    QFile file("C:\\project\\Fuel.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return 1;
    }
    QTextStream in(&file);
    QList<FuelPrice> pricesList;
    while (!in.atEnd()) {
        QString line = in.readLine();
         QStringList fields = line.split('\"'); // предполагаем, что поля разделены запятыми
        QString fuelType = fields[1].trimmed();
        QDate date = QDate::fromString(fields[2].trimmed(), "yyyy.MM.dd");
        double price = fields[3].trimmed().toDouble();
        FuelPrice priceEntry(fuelType, date, price);
        pricesList.append(priceEntry);
        priceEntry.print();
    }

    file.close();

    return 0;
}

