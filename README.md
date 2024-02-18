Лабораторные работы по ООП.

Структура репозитория:
* `lab_1/` - лабораторная #1
* `lab_2/` - лабораторная #2

Установка зависимостей:
* git clone https://github.com/google/googletest.git

Сборка:
```sh
export CXX=/usr/bin/clang++
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
make -C build
```
