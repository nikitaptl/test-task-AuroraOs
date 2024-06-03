<h1 align = 'center'>SharingFramework</h1>
<h2 align = 'center'>Задание выполнил Потылицин Никита</h2>
<h3 align = 'center'>Краткое описание идеи</h3>

Фреймворк работает следующим образом
- В коде приложения создаётся объект SharingFramework, наследник QDBusAbstractAdaptor. Этот объект отвечает за всё взаимодействие приложения с операционной системой и удалённый запуск программы.
- Разработчику или пользователю доступны методы для регистрации, добавления, удаления и просмотра поддерживаемых форматов файлов.
- Форматы сохраняются перманентно в специальном конфигурационном файле formats.conf
- Также предоставляются методы для создания файла .service, который необходимо переместить в /usr/share/dbus-1/services/ для удалённого запуска приложения.
- После этого приложение становится зарегистрированной D-Bus службой, которую можно запускать удалённо, передавать файлы, смотреть поддерживаемые форматы и выполнять все ранее перечисленные операции.

Таким образом, **любое** приложение, использовавшее фреймворк в своём коде, может зарегистрировать себя в реестре D-Bus служб, после чего можно будет запускать его удалённо в любом другом приложении и передавать в него файлы для обработки. Именно так я и реализовал механизм **sharing**, на основе этого можно создать приложение, которое будет просматривать зарегистрированные службы и поддерживаемые ими форматы, чтобы находить, какое именно приложение может работать с типом файла. Подробности и демонстрация работы далее

<h3 align = 'center'>Описание функционала фреймворка</h3>

#### 1. Создание объекта SharingFramework:

- Подключите "SharingFramework.h" и создайте объект SharingFramework в main.cpp.
- В конструктор передайте название службы, путь к службе и путь к исполняемому файлу (обычно argv[0])
```C++
SharingFramework framework(&parent, "handler.Text", "/handler/Text", argv[0]);
```
- Это создаст службу с указанными параметрами и интерфейсом "dbus.application". Методы этого объекта, обозначенные как public slots, доступны как разработчику в коде приложения, так и из консоли
```C++
public slots:
    QString registerFormats(QStringList formatList);
    QString addFormat(QString format);
    QString deleteFormat(QString format);
    QStringList GetSupportedFileTypes();
    QString createServiceFile();
    QString createServiceFile(QStringList args);
    QString openFile(QString path);
    void stop();
```

#### 2. Использование методов и регистрация поддерживаемых форматов

- Методы можно вызывать с помощью dbus-send. Например, чтобы узнать поддерживаемые типы файлов:
```
dbus-send --session --print-reply --dest=handler.Text /handler/Text dbus.application.GetSupportedFileTypes
```
```Console
OUTPUT
method return time=1717433061.335865 sender=:1.1 -> destination=:1.0 serial=4 reply_serial=2
   array [
      string ".xml"
      string ".csv"
      string ".json"
      string ".txt"
   ]
```
- Или добавить новый формат:
```
dbus-send --session --print-reply --dest=handler.Text /handler/Text dbus.application.addFormat string:".rtf"
```
```Console
OUTPUT
method return time=1717433260.909643 sender=:1.1 -> destination=:1.4 serial=5 reply_serial=2
string "The new format has been successfully added"
```
- Вся информация о форматах сохраняется в файле "formats.conf" в той же директории, что и исполняемый файл.

#### 3. Регистрация приложения в реестре служб

- Необходимо вызвать функцию createServiceFile, передав имя службы и путь к исполняемому файлу.
```
dbus-send --session --print-reply --dest=handler.Text /handler/Text dbus.application.createServiceFile array:string:"handler.Text","/home/nikita_ptl/AuroraOs/TextHandler"
```
- Это создаст .service файл, который нужно самостоятельно переместить в /usr/share/dbus-1/services/. После этого приложение будет зарегистрировано и готово к удалённому запуску и передаче файлов.
```.service
[D-BUS Service]
Name=handler.Text
Exec=/home/nikita_ptl/AuroraOs/TextHandler
```
#### 4. Обработка сообщений и ошибок:
- Все действия пользователя и разработчика, а также команды, отправленные через консоль, сопровождаются выводом сообщений, ошибок и подсказок для корректного ввода.
- Кроме того, вызываются соответствующие сигналы (signals), что позволяет разработчику подключить их к своим слотам (slots) и обрабатывать по своему усмотрению.
```C++
signals:
    void formatsChanged(QStringList formatList);
    void newFile(QString path);
```
Таким образом, использование фреймворка позволяет приложению зарегистрировать себя в реестре D-Bus служб и поддерживать удалённый запуск, передачу файлов и другие операции, предоставляя гибкие возможности для взаимодействия с системой.
