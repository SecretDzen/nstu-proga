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
  <title>Web - lab2</title>
  <script src="https://cdn.tailwindcss.com"></script>
</head>


<body>
  <header class="header">
    <div class="flex flex-row justify-center w-full">
      <h1 class="p-4">Лабораторная работа №2</h1>

    </div>
  </header>
  <div class="flex flex-col h-full w-full justify-top items-center py-10 space-y-10 my-10">
    <div class="flex flex-col bg-white w-4/6 rounded-xl justify-center items-center space-y-4">
      <?php
      if ($authenticated) {
        echo '<form method="post" action="index.php"><p><button type="submit" class="px-6 py-3 rounded bg-blue-400" name="log_out">Выход</button></p></form>';
      } else {
        echo '<form method="get" action="auth.php"><p><button type="submit" class="px-6 py-3 rounded bg-blue-400">Вход</button></p></form>';
      }
      ?>

      <div class="flex flex-row w-1/2 h-full justify-center items-center">
        <span>
          <?= isset($_SESSION['login']) ? 'Вы вошли как: ' . $_SESSION['login'] : '' ?>
        </span>
      </div>



      <h1 class="text-l pt-10">Поиск по должности: </h1>
      <form action="index.php" method="get" class="flex flex-row w-full justify-center items-center space-x-4">
        <div class="w-72">
          <div class="relative h-10 w-full min-w-[200px]">
            <input name="position" id="position"
              class="peer h-full w-full rounded-[7px] border border-blue-gray-200 border-t-transparent bg-transparent px-3 py-2.5 font-sans text-sm font-normal text-blue-gray-700 outline outline-0 transition-all placeholder-shown:border placeholder-shown:border-blue-gray-200 placeholder-shown:border-t-blue-gray-200 focus:border-2 focus:border-pink-500 focus:border-t-transparent focus:outline-0 disabled:border-0 disabled:bg-blue-gray-50"
              placeholder=" " />
            <label
              class="before:content[' '] after:content[' '] pointer-events-none absolute left-0 -top-1.5 flex h-full w-full select-none text-[11px] font-normal leading-tight text-blue-gray-400 transition-all before:pointer-events-none before:mt-[6.5px] before:mr-1 before:box-border before:block before:h-1.5 before:w-2.5 before:rounded-tl-md before:border-t before:border-l before:border-blue-gray-200 before:transition-all after:pointer-events-none after:mt-[6.5px] after:ml-1 after:box-border after:block after:h-1.5 after:w-2.5 after:flex-grow after:rounded-tr-md after:border-t after:border-r after:border-blue-gray-200 after:transition-all peer-placeholder-shown:text-sm peer-placeholder-shown:leading-[3.75] peer-placeholder-shown:text-blue-gray-500 peer-placeholder-shown:before:border-transparent peer-placeholder-shown:after:border-transparent peer-focus:text-[11px] peer-focus:leading-tight peer-focus:text-pink-500 peer-focus:before:border-t-2 peer-focus:before:border-l-2 peer-focus:before:border-pink-500 peer-focus:after:border-t-2 peer-focus:after:border-r-2 peer-focus:after:border-pink-500 peer-disabled:text-transparent peer-disabled:before:border-transparent peer-disabled:after:border-transparent peer-disabled:peer-placeholder-shown:text-blue-gray-500">
              Должность
            </label>
          </div>
        </div>
        <button type="submit" class="px-4 py-2 bg-blue-400 rounded">Поиск</button>
      </form>
      <br>
      <?php
      if ($authenticated && $_SESSION['group'] > 1) {
        echo '<a href="insert.php" class="text-black px-6 py-3 bg-blue-400 rounded">Добавить запись</a>';
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
            echo "\t<td><a class=\"underline text-blue-500\" href=\"update.php?id=" . $line["id"] . "\">Update</a></td>";
            if ($authenticated && $_SESSION['group'] >= 2) {
              echo "\t<td><a class=\"underline text-blue-500\" href=\"delete.php?id=" . $line["id"] . "\">Delete</a></td>";
            }
          }
        }
        ?>
        </tr>
      </table>
    </div>
  </div>
</body>

</html>