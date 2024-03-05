Лабораторные работы по ООП.

Структура репозитория:
* `lab_1/` - лабораторная #1
* `lab_2/` - лабораторная #2
* `lab_3/` - лабораторная #3
* `lab_4/` - лабораторная #4
* `lab_5/` - лабораторная #5

Установка зависимостей:
* git clone https://github.com/google/fuzztest.git

Сборка:
```sh
export CXX=clang++
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DCODE_COVERAGE=ON
make -C build
```

Генерация покрытия (на примере цели five):
```sh
make -C build ccov-five
```
