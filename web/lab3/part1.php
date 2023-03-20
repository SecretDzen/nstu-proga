<?php

require_once(__DIR__ . '/../utils/connection.php');
$db = connect();

$books = pg_query(
    $db,
    'SELECT teachers.id,
    position.name as position,
    degree.name as degree,
    courses.name as courses,
    teachers.surname as teacher,
    teachers.room_number
    from labs.teachers as teachers
    inner join labs.position on position.id = teachers.position
    inner join labs.degree on degree.id = teachers.degree
    inner join labs.courses on courses.id = teachers.courses;'
);
?>

<html>
<style>
    * {
        padding: 0;
        margin: 0;
        box-sizing: border-box;
    }

    .header {
        background-color: #333;
        color: #fff;
        padding: 4px;
        text-align: center;
    }

    .h1 {
        font-size: 30px;
        padding: 4px;
    }


    :root {
        --main-color: #03c03c;
    }

    table {
        border-collapse: collapse;
        border-color: black;
    }

    table,
    th,
    td {
        border: 1px solid var(--main-color);
    }

    th,
    td {
        padding: 1rem;
    }

    th {
        background: var(--main-color);
        color: white;
    }

    td {
        color: #666;
    }
</style>

<head>
    <title>Web - lab3 - Part 1</title>
    <script src="https://cdn.tailwindcss.com"></script>
</head>


<body>
    <header class="header">
        <div class="flex flex-row justify-center w-full">
            <h1 class="p-4">Лабораторная работа №3</h1>

        </div>
    </header>
    <div class="flex flex-col h-full w-full justify-top items-center py-10 space-y-10 my-10">
        <div class="flex flex-col bg-white w-4/6 rounded-xl justify-center items-center space-y-4">

            <table>
                <tr>
                    <th>ID</th>
                    <th>Должность</th>
                    <th>Учёная степень</th>
                    <th>Курс</th>
                    <th>Фамилия</th>
                    <th>Аудитория</th>
                </tr>
                <?php
                while ($line = pg_fetch_array($books, null, PGSQL_ASSOC)) {
                    echo "\t<tr>\n";
                    foreach ($line as $col_value) {
                        ?>
                        <td>
                            <?= $col_value ?>
                        </td>
                        <?php
                    }
                }
                ?>
                </tr>
            </table>
        </div>
        <style>
            #v-legend {
                display: inline-block;
                transform: rotateZ(-90deg);
                position: absolute;
                top: 50%;
                left: -20%;
            }

            .graph {
                position: relative;
                max-width: fit-content;
            }
        </style>

        <div class="graph">
            <h3 class="text-xl" id="v-legend">Количество сотрудников</h3>
            <img id="image" src="chart.php" alt="">
        </div>

        <h3 class="text-xl">Должность</h3>
        <br>
        <br>
        <script>
            setInterval(() => {
                image.src = 'chart.php?' + new Date().getTime();
            }, 1000);
        </script>
    </div>
    </div>
</body>

</html>