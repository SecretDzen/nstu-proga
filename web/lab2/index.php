<?php

require_once(__DIR__ . '/../utils/connection.php');
$db = connect();

session_start();

$books = pg_query(
  $db, 'SELECT teachers.id,
    position.name as position,
    degree.name as degree,
    courses.name as courses,
    teachers.surname as teacher,
    teachers.room_number
    from labs.teachers as teachers
    inner join labs.position on position.id = teachers.position
    inner join labs.degree on degree.id = teachers.degree
    inner join labs.courses on courses.id = teachers.courses 
    where ' . (isset($_GET['position']) ? "lower(position.name) like lower('%" . pg_escape_string($_GET['position']) . "%')" : "1=1")
);

if (isset($_POST["log_out"])) {
  session_destroy();
  header("location:index.php");
}

$authenticated = !empty($_SESSION['auth']);
$authenticated = $authenticated && $_SESSION['auth'] == true;

if (isset($_POST["log_out"])) {
  session_destroy();
  header("location:index.php");
}

?>

<html>
<style>
  * {
    padding: 0;
    margin: 0;
    box-sizing: border-box;
    font-size: 16px;
    font-weight: 500;
  }

  .body {
    margin: 0 auto;
    max-width: 1024px;
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

  .status {
    display: flex;
    gap: 4px;
    align-items: center;
    padding: 4px 0;
  }

  button {
    outline: none;
    background: none;
    border: none;
    border-bottom: 1px solid blue;
    cursor: pointer;
    color: blue;
  }
</style>

<head>
  <title>Web - lab2</title>
</head>


<body>
  <header class="header">
      <h1 class="h1">Лабораторная работа №2</h1>
  </header>
  <main class="body">
    <div>
      <div class="status">
        <span>
	  <?= isset($_SESSION['login']) ? 'Вы вошли как: ' . $_SESSION['login'] . '. Будьте как дома ' : 'Вы не вошли в систему! Будьте гостем ' ?>
          или
	</span>
      <?php
      if ($authenticated) {
        echo '<form method="post" action="index.php"><p><button type="submit" name="log_out">выйдите из системы</button></p></form>';
      } else {
	echo '<form method="get" action="auth.php"><p><button type="submit">войдите в систему</button></p></form>';
      }
      ?>
      </div>

      <h2>Поиск по должности: </h2>
      <form action="index.php" method="get">
        <div>
          <input name="position" id="position" placeholder="Введите должность" />
          <button type="submit">Поиск</button>
        </div>
      </form>
      <br>
      <?php
      if ($authenticated && $_SESSION['group'] > 1) {
        echo '<a href="insert.php">Добавить запись</a>';
      }
      ?>
      <table>
        <tr>
          <th>ID</th>
          <th>Должность</th>
          <th>Учёная степень</th>
          <th>Курс</th>
          <th>Фамилия</th>
          <th>Аудитория</th>
          <?php
          if ($authenticated && $_SESSION['group'] >= 1) {
            echo "<th></th>";
          }
          if ($authenticated && $_SESSION['group'] >= 2) {
            echo "<th></th>";
          }
          ?>
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
          if ($authenticated && $_SESSION['group'] >= 1) {
            echo "\t<td><a href=\"update.php?id=" . $line["id"] . "\">Обновить</a></td>";
            if ($authenticated && $_SESSION['group'] >= 2) {
              echo "\t<td><a href=\"delete.php?id=" . $line["id"] . "\">Удалить</a></td>";
            }
          }
        }
        ?>
        </tr>
      </table>
    </div>
  </main>
</body>

</html>
