<html>
<style>
  * {
    padding: 0;
    margin: 0;
    box-sizing: border-box;
    font-size: 16px;
    font-weight: 500;
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

  .a {
    border: 1px black solid;
    border-radius: 50px;
  }

  .h2 {
    font-size: 28px;
    text-align: center;
  }

  .img {
    border-radius: 9999px;
    width: 150px;
  }

  .block__download {
    display: flex;
    flex-direction: column;
    align-items: center;
    gap: 4px;
    padding: 4px;
    font-size: 24px;
  }
</style>

<head>
  <title>Web - lab1</title>
</head>

<body>
  <header class="header">
    <h1 class="h1">Лабораторная работа №1</h1>
  </header>

  <main>
    <h2 class="h2">MySQL. Проектирование и реализация базы данных.</h2>
    <section class="block__download">
      <img src="hacker.png" class="img" alt="hacker" />
      <a href="/web/dump.sql" target="_blank">Открыть дамп базы данных</a>
    </section>

    <h2 class="h2">PHP. Работа с файлами теневых посылок (cookies) и текстовыми файлами.</h2>

    <section>
      <?php
      $surname = "преподаватель";
      $course = "не выбран";

      if ($_SERVER['REQUEST_METHOD'] == 'POST') {
        if (isset($_POST["surname"]) && isset($_POST["course"])) {
          $surname = $_POST["surname"];
          $course = $_POST["course"];

          setcookie("visit", date('d.M.y'), time() + 365 * 24 * 60 * 60);
          setcookie("surname", $_POST["surname"], time() + 365 * 24 * 60 * 60);
          setcookie("course", $_POST["course"], time() + 365 * 24 * 60 * 60);
          header("location:index.php");
        } else {
          echo "<p>Все поля обязательны к заполнению :)</p>";
        }
      }


      if (
        isset($_COOKIE["visit"]) && isset($_COOKIE["surname"])
        && isset($_COOKIE["course"])
      ) {
        $surname = $_COOKIE["surname"];
        $course = $_COOKIE["course"];
        echo "<p>Время последнего визита: " . $_COOKIE["visit"] . "</p>";
      }

      echo "<h3>Приветствуем, " . $surname . "!</h3>";
      echo "<p>Ваш курс: " . $course . ". </p>";

      ?>
      <FORM method="post" action="index.php">
        <p>Введите вашу фамилию:</p>
        <P><INPUT TYPE="TEXT" NAME="surname" PLACEHOLDER="Фамилия"></P>
        <p>Ваш курс:</p>
        <div>
          <INPUT TYPE="radio" id="web" VALUE="web" NAME="course" PLACEHOLDER="Фамилия"></P>
          <label for="web">Веб</label>
        </div>
        <div>
          <INPUT TYPE="radio" id="csa" VALUE="csa" NAME="course" PLACEHOLDER="Фамилия">
          <label for="csa">Клиент-Сервер</label>
        </div>
        <div>
          <INPUT TYPE="radio" id="economy" VALUE="economy" NAME="course">
          <label for="economy">Экономика</label>
        </div>
        <div>
          <INPUT TYPE="radio" id="compilers" VALUE="compilers" NAME="course">
          <label for="compilers">Компиляторы</label>
        </div>
        <div>
          <INPUT TYPE="radio" id="ls" VALUE="ls" NAME="course">
          <label for="ls">БЖД</label>
        </div>

        <P><INPUT TYPE="SUBMIT" VALUE="Отправить!"></P>
        <P><INPUT TYPE="RESET" VALUE="Очистить"></P>
      </FORM>
    </section>
  </main>
</body>

</html>