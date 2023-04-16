<?php

require_once(__DIR__ . '/../utils/connection.php');
$db = connect();

$teachers = pg_query(
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

  #app {
    display: flex;
    flex-direction: column;
    min-height: 100vh;
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

  .main {
    padding: 8px 4px;
    background-color: #ccc;
    flex-grow: 1;
    display: flex;
    flex-direction: column;
    justify-content: space-evenly;
  }

  .table {
    padding: 8px;
    margin: auto;
    background-color: rgba(170, 170, 170, 0.9);
    border-radius: 8px;
    text-align: center;
  }

  td {
    padding: 0 4px;
  }

  .footer {
    background-color: #333;
    color: #fff;
    padding: 8px 4px;
    text-align: center;
  }

  #v-legend {
    display: inline-block;
    transform: rotateZ(-90deg);
    position: absolute;
    top: 50%;
    left: -20%;
  }

  .graph {
    display: flex;
    gap: 2px;
    align-items: center;
    justify-content: center;
  }

  .h3 {
    text-align: center;
  }

  .rotate {
    transform: rotateZ(90);
  }
</style>

<head>
  <title>Web - lab3 - Part 1</title>
</head>

<body>
  <div id="app">
    <header class="header">
      <h1 class="p-4">Лабораторная работа №3</h1>
    </header>

    <main class="main">
      <table class="table">
        <tr>
          <th>ID</th>
          <th>Должность</th>
          <th>Учёная степень</th>
          <th>Курс</th>
          <th>Фамилия</th>
          <th>Аудитория</th>
        </tr>
        <?php
        while ($line = pg_fetch_array($teachers, null, PGSQL_ASSOC)) {
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

      <div class="graph">
        <h3 class="rotate">Количество сотрудников</h3>
        <img id="image" src="chart.php" alt="Сотрудники">
      </div>

      <h3 class="h3">Должность</h3>
    </main>

    <footer class="footer">
      <p>Лабораторные выполнил студент АВТ-019 - Попов П.С.</p>
      <p>Вариант №8</p>
    </footer>
  </div>
</body>

<script>
  setInterval(() => {
    image.src = 'chart.php?' + new Date().getTime();
  }, 1000);
</script>

</html>