<h1 align = 'center'>SharingFramework</h1>
<h1 align = 'center'>ИЗМЕНЕНО</h1>

### 1. Вынесение фреймворка в динамическую библиотеку

Фреймворк вынесен в динамическую библиотеку `libSharingFramework.so`. Добавлен пример простейшего обработчика, который принимает на вход текстовый файл и выводит его содержимое на экран. Демонстрация: 

https://github.com/nikitaptl/test-task-AuroraOs/assets/145208333/2c6a1083-1529-408a-900f-0be62d20f6c4

### 2. Поправки в `CMakeLists.txt`

В `CMakeLists.txt` добавлена следующая конфигурация:
```cmake
find_package(Qt5 REQUIRED COMPONENTS Core DBus)
target_link_libraries(test-task-AuroraOs Qt5::Core Qt5::DBus)
```
### 3. Явное задание пути к конфигурационному файлу
Путь к конфигурационному файлу теперь задаётся явно последним параметром в конструкторе:

```cpp
SharingFramework sharingFramework(&w, "txt.Handler", "/txt/Handler", "/home/nikita_ptl/Qt/test-task-AuroraOs/application");
```
### 4. Обработка случая, когда служба уже запущена
При попытке повторного запуска службы теперь выбрасывается исключение:
```cpp
if(dbusConnection.interface()->isServiceRegistered(nameService)) {
    writeMessage("The service has already been launched");
    throw ServiceException("The service has already been launched");
}
```
### 5. Завершение работы программы с использованием сигнала stopRequested
Для завершения работы программы теперь используется сигнал stopRequested. Разработчик подключает свой метод к сигналу и определяет, какие действия должны быть выполнены перед завершением работы программы.
```cpp
connect(&sharingFramework, &SharingFramework::stopRequested, this, &YourClass::yourMethod);
```

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

<h3 align='center'>Демонстрация работы и тестирования</h3>
Фреймворк был протестирован на приложениях, расположенных в папке demo_applications. Эти приложения не имеют собственного функционала и только подключают фреймворк, так как предназначены исключительно для демонстрации. Каждое из них представляет собой "Обработчик какого-то типа файлов".

Сначала мы протестируем фреймворк на TextHandler, а затем покажем, как выглядят в системе три зарегистрированных приложения — обработчики видео, текста и документов.

#### 1. Регистрация поддерживаемых форматов

https://github.com/nikitaptl/test-task-AuroraOs/assets/145208333/fc7e3d31-957c-43b7-a4fd-9e200aff1b12

#### 2. Регистрация в реестре служб D-Bus и удалённый запуск

https://github.com/nikitaptl/test-task-AuroraOs/assets/145208333/aa3e93ad-93ea-4b0d-b13c-52b3f4078856

#### 3. Просмотр поддерживаемых форматов файлов у приложений через консоль

https://github.com/nikitaptl/test-task-AuroraOs/assets/145208333/f4854186-70d5-4431-abb5-82eb6473af33

Здесь видно, как служба регистрируется в системе и как, благодаря фреймворку, можно узнавать поддерживаемые форматы файлов для любых приложений.

<h3 align = 'center'>Краткое описание классов</h3>

- Работа с проверкой корректности пользовательского ввода полностью делегирована классу InputValidator
- Работа с конфигурационным файлом "formats.conf" также делегирована классу ConfManager
- Классы и методы сообщают друг другу о результате операций с помощью специального класса Response
