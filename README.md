# testProject
Это задание нацелено на проектирование абстрактных систем, поэтому в остальном не
ограничивает Вас в выборе способов реализации, но постарайтесь обосновать, почему Вы
приняли то или иное решение.
Задание необходимо выполнить на языке С++ (не ниже C++11 стандарта). Оцениваемыми
параметрами являются быстродействие, безопасность, точность, элегантность решения, стиль и
т.д.
В качестве результата ожидаются файлы с исходным кодом и файл сборки
(Makefile/CMakeLists.txt). Также желательно указать название и версию использованного
компилятора.
Дополнительным преимуществом будет наличие юнит-тестов, проверяющих правильность
решения.
Задание.
Необходимо написать систему, состоящую из трёх сущностей:
1
Генератор: имеет два режима работы (G*):
a.
Должен выдавать новое число через случайный промежуток времени,
находящийся в заданном диапазоне R*.
b.
Должен читать ранее записанный файл (см. п.3), и выдавать числа из файла в
соответствии с указанными параметрами.
2
База данных: получает у генератора числа и складывает их в массив.
Как только массив достигает заданного размера М* или проходит заданное время T* весь
массив единым блоком добавляется в список блоков.
В списке базы единовременно хранится только N* новых блоков, старые блоки
записываются в файл на диске и удаляются из оперативной памяти.
Файл с данными должен также содержать записи, содержащие значения параметров, с
которыми данные были получены и отметки времени.
3
Модуль управления и отображения, обрабатывающий команды пользователя по
изменению параметров, отмеченных звёздочкой (*). Параметры могут быть изменены в
произвольный момент времени. Если генератор работает в режиме Б, то параметры R, M,
N, T не могут быть изменены.
Также модуль отображает последнее, выданное генератором число.
Все три сущности должны выполняться в различных потоках либо процессах.
Система не должна выделять новую память в ходе работы (нужна статическая реализация).
Система должна обрабатывать ошибки при помощи исключений.
