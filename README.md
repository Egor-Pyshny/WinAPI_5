# ЛАБА 5
Изучение создание и использование потоков и механизмов синхронизации
Разработать очередь заданий в к-ой несколько потоков могут вставлять эл-ты атомарно
Разработать обработчик этой очереди, к-ый извлекает из нее задания и раздаёт заданному кол-ву потоков
Разработать программу к-ая использует очередь заданий и обработчик очереди для сортировки строк в тхт файле: входной поток читает файл в память, нарезает его на части и создаёт несколько заданий на сортировку по числу сортирующих потоков, входной поток помещает их в очередь заданий
Сортирующие потоки извлекают задание, сортируют свои части файла, отдают результаты выходному потоку. Выход ждёт все сортирующие части и мержит их методом сортирующего слияния.
