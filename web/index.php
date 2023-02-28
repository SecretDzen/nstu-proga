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

  .main__div {
    background-image: url("./bg.jpg");
  }

  .main {
    background-color: rgba(255, 255, 255, 0.8);
    height: 100vh;
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

  .block__cookies {
    display: flex;
    flex-direction: column;
    gap: 4px;
    padding: 4px;
  }

  .form {
    padding: 2px;
    display: flex;
    flex-direction: column;
    gap: 4px;
  }

  .form__flags {
    display: flex;
    gap: 4px;
    align-items: center;
  }

  .form__flags__div {
    display: flex;
    flex-direction: column;
    align-items: center;
    gap: 2px;
  }
</style>

<head>
  <title>Web - lab1</title>
</head>

<body>
  <header class="header">
    <h1 class="h1">Лабораторная работа №1</h1>
  </header>

  <div class="main__div">
    <main class="main">
      <h2 class="h2">MySQL. Проектирование и реализация базы данных.</h2>
      <section class="block__download">
        <img src="hacker.png" class="img" alt="hacker" />
        <a href="/web/dump.sql" target="_blank">Открыть дамп базы данных</a>
      </section>

      <h2 class="h2">PHP. Работа с файлами теневых посылок (cookies) и текстовыми файлами.</h2>

      <section class="block__cookies">
        <?php
        $flags = "отсутствует";

        function flagsName($name)
        {
          if ($name == "text") {
            return "Текст";
          } else if ($name == "graphics") {
            return "Графика";
          } else if ($name == "styles") {
            return "Стили";
          }

          return "отсутствует";
        }

        if ($_SERVER['REQUEST_METHOD'] == 'POST') {
          setcookie("visit", date('m/d/y h:m'), time() + 365 * 24 * 60 * 60);

          if (isset($_POST["flags"])) {
            setcookie("flags", json_encode($_POST["flags"]), time() + 365 * 24 * 60 * 60);
          } else {
            setcookie("flags", json_encode([""]), time() + 365 * 24 * 60 * 60);
          }

          header("location:index.php");
        }

        if (isset($_COOKIE["visit"]) && isset($_COOKIE["flags"])) {
          $text = json_decode($_COOKIE["flags"]);
          $flags = "";

          for ($i = 0; $i < count($text); $i++) {
            $flags = $flags . "---" . flagsName($text[$i]);
          }

          echo "<p>Время последнего визита: " . $_COOKIE["visit"] . "</p>";
        }

        echo "<h3>Приветствуем, юзер!</h3>";
        echo "<p>Ваш выбор: " . $flags . "</p>";
        ?>
        <FORM class="form" method="post" action="index.php">
          <div class="form__flags">
            <p>Набор флажков:</p>
            <div class="form__flags__div">
              <P><INPUT TYPE="checkbox" id="text" VALUE="text" NAME="flags[]"></P>
              <label for="text">Текст</label>
            </div>
            <div class="form__flags__div">
              <P><INPUT TYPE="checkbox" id="graphics" VALUE="graphics" NAME="flags[]"></P>
              <label for="graphics">Граф. данные</label>
            </div>
            <div class="form__flags__div">
              <P><INPUT TYPE="checkbox" id="styles" VALUE="styles" NAME="flags[]"></P>
              <label for="styles">Стили оформления</label>
            </div>
          </div>

          <div>
            <INPUT TYPE="SUBMIT" VALUE="Отправить!">
            <INPUT TYPE="RESET" VALUE="Очистить">
          </div>
        </FORM>
      </section>
    </main>
  </div>
</body>

</html>