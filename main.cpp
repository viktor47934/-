#include <QCoreApplication>
#include <QDebug>
#include <QStringList>
#include <QDate>
#include <QFile>
#include <QList>

class FuelPrice {
public:
    // Конструктор класса FuelPrice
    FuelPrice(QString fuel_type, QDate date, double price)
        : fuel_type_(fuel_type), date_(date), price_(price) {}

    // Метод, возвращающий строковое представление объекта
    QString toString() const {
        return QString("Fuel type - %1\nDate - %2\nPrice - %3\n")
            .arg(fuel_type_)
            .arg(date_.toString("yyyy.MM.dd"))
            .arg(price_);
    }

private:
    // Поля класса FuelPrice
    QString fuel_type_;
    QDate date_;
    double price_;
};

// Функция, читающая данные из файла и возвращающая список объектов FuelPrice
QList<FuelPrice> readData(const QString& file_path) {
    QFile file(file_path);
    QList<FuelPrice> prices_list;

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open the file:" << file_path;
        return prices_list;
    }

    while (!file.atEnd()) {
        QString line = file.readLine();
        QStringList fields = line.split('\"');  // предполагаем, что поля разделены запятыми
        if (fields.size() < 4) continue;  // простая проверка формата строки

        QString fuel_type = fields[1].trimmed();
        QDate date = QDate::fromString(fields[2].trimmed(), "yyyy.MM.dd");
        double price = fields[3].trimmed().toDouble();
        prices_list.append(FuelPrice(fuel_type, date, price));
    }

    file.close();
    return prices_list;
}

// Функция, выводящая данные на экран
void printData(const QList<FuelPrice>& prices_list) {
    for (const FuelPrice& price : prices_list) {
        qDebug() << price.toString();
    }
}

int main() {
    QString file_path = "C:\\project\\Fuel.txt";
    QList<FuelPrice> prices_list = readData(file_path);

    if (prices_list.isEmpty()) {
        qDebug() << "No prices to display.";
        return 1;
    }

    printData(prices_list);

    return 0;
}


