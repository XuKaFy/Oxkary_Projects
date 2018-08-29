#ifndef SETTING_H
#define SETTING_H


#include <QString>
#include <QSettings>
#include <QFile>

class Settings : public QSettings {
public:
    explicit Settings(const QString &file)
        : QSettings(file, QSettings::IniFormat) { }

private:
    QString path;
};


#endif // SETTING_H
