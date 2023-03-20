<?php
ini_set('display_errors', '1');
ini_set('display_startup_errors', '1');
error_reporting(E_ALL);

require_once(__DIR__ . '/../utils/connection.php');
$db = connect();

$query = 'SELECT distinct position.id, position.name from labs.position inner join labs.teachers
as teacher on teacher.position = position.id
where (select count(*) from labs.teachers where position = id) > 0 order by id;';

$result = pg_query($db, $query);

$teachers = array();

while ($line = pg_fetch_array($result, null, PGSQL_ASSOC)) {
    array_push($teachers, $line);
}
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
    <title>Web - lab4</title>
    <script src="https://cdn.tailwindcss.com"></script>
</head>

<body>
    <header class="header">
        <h1 class="h1">Лабораторная работа №4</h1>
    </header>
    <div class="flex flex-col justify-center items-center">

        <div class="flex flex-col space-y-6 justify-center items-center">
            <h3 class="text-xl">Выберите должность</h3>
            <form class="form flex flex-col space-y-6 justify-center items-center">
                <select class="position" name="position">
                    <?php
                    foreach ($teachers as $value) {
                        echo "<option value=\"" . $value['id'] . "\">" . $value['name'] . "</option>";
                    }
                    ?>
                </select>
            </form>
        </div>

        <br>

        <div class="flex flex-col space-y-6 justify-center items-center">
            <h3 class="text-xl">Сотрудники выбранной должности</h3>
            <table class="list" border="1">
                <tr>
                    <th>ID</th>
                    <th>Должность</th>
                    <th>Учёная степень</th>
                    <th>Курс</th>
                    <th>Фамилия</th>
                    <th>Аудитория</th>
                </tr>
            </table>
        </div>

        <script>
            const getTeachersByPosition = async (position) => {
                const response = await fetch(`http://poddon.ex4to.ru/web/lab4/teachers_by_position.php?position=` + position);
                const json = await response.json();
                console.log(json);
                return json;
            };

            const renderList = ({ teachers }) => {
                const list = document.querySelector('.list');

                [...list.children].forEach((child, idx) => idx > 0 && child.remove());

                teachers
                    .map((teacher) => {
                        const row = document.createElement('tr');
                        row.innerHTML = `<td>${teacher.id}</td> 
                    <td>${teacher.position}</td> 
                    <td>${teacher.degree}</td> 
                    <td>${teacher.courses}</td> 
                    <td>${teacher.teacher}</td> 
                    <td>${teacher.room_number}</td`;
                        return row;
                    })
                    .forEach((row) => list.appendChild(row));
            };

            const select = document.querySelector('.position');

            const app = async () => {
                const position = select.value;
                const teachers = await getTeachersByPosition(position);
                renderList({ teachers });
            };

            app();

            select.addEventListener('input', app);
        </script>
    </div>
</body>

</html>