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
    background-color: rgba(255, 255, 255, 0.9);
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
    font-size: 24px;
    padding: 4px;

    display: flex;
    flex-direction: column;
    align-items: center;
    gap: 4px;
  }

  .block__cookies {
    padding: 8px;

    display: flex;
    flex-direction: column;
    gap: 4px;
  }

  .block__text {
    padding: 8px;

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

  .journal {
    display: grid;
    grid-template-columns: 1fr 1fr 1fr;
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
      <h3 class="h2">Кукисы</h3>

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

        if ($_SERVER['REQUEST_METHOD'] == 'POST' && $_POST["comment"] == "" && count($_POST["styles"]) == 0) {
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
            $flags = $flags . flagsName($text[$i]);
            if ($i != count($text) - 1) {
              $flags = $flags . "---";
            }
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
      <section>
        <h3 class="h2">Текстовые файлы</h3>

        <FORM class="form" method="post" action="index.php">
          <div class="form__flags">
            <p>Оформления текста:</p>
            <div class="form__flags__div">
              <P><INPUT TYPE="checkbox" id="cat" VALUE="cat" NAME="styles[]"></P>
              <label for="cat">Котиками</label>
            </div>
            <div class="form__flags__div">
              <P><INPUT TYPE="checkbox" id="dogs" VALUE="dog" NAME="styles[]"></P>
              <label for="dog">Собачками</label>
            </div>
            <div class="form__flags__div">
              <P><INPUT TYPE="checkbox" id="turtle" VALUE="turtle" NAME="styles[]"></P>
              <label for="turtle">Черепахами</label>
            </div>
          </div>

          <div>
            <p>Ваш комментарий: </p>
            <P><TEXTAREA rows="4" cols="50" TYPE="text" NAME="comment"></TEXTAREA></P>
          </div>

          <div>
            <INPUT TYPE="SUBMIT" VALUE="Отправить!">
            <INPUT TYPE="RESET" VALUE="Очистить">
          </div>
        </FORM>
      </section>
      <section>
        <?php
        $styles = "";
        $comment = "---";

        function stylesName($name)
        {
          if ($name == "cat") {
            return "Кошки";
          } else if ($name == "dog") {
            return "Собаки";
          } else if ($name == "turtle") {
            return "Черепахи";
          }

          return "---";
        }

        if ($_SERVER['REQUEST_METHOD'] == 'POST' && count($_POST["flags"]) == 0) {
          if (isset($_POST["styles"])) {
            for ($i = 0; $i < count($_POST["styles"]); $i++) {
              $styles = $styles . stylesName($_POST["styles"][$i]);
              if ($i != count($_POST["styles"]) - 1) {
                $styles = $styles . " | ";
              }
            }
          } else {
            $styles = "---";
          }

          if (isset($_POST["comment"]) && $_POST["comment"] != "") {
            $comment = $_POST["comment"];
          }

          $fp = @fopen(__DIR__ . "/logs.txt", "a");
          if (!$fp) {
            echo "<p>Ошибка доступа к журналу</p>";
            echo "Путь - " . __DIR__ . "/logs.txt";
          } else {
            $str = "<p>" . date('d/m/y h:m') . "</p>" . "<p>" . $styles . "</p>" . "<p>" . $comment . "</p>";
            fwrite($fp, $str);
          }

          header("location:index.php");
        }

        if (!file_exists(__DIR__ . "/logs.txt")) {
          echo "<p>Ошибка доступа к журналу</p>";
        } else {
          echo '<h3 class="h2">Журнал</h3>';
          echo '<div class="journal"><p>Дата</p><p>Стили</p><p>Комментарий</p>';

          $file = fopen(__DIR__ . '/logs.txt', 'r');
          while (!feof($file)) {
            $text = fgets($file);
            echo $text;
          }

          fclose($file);
        }
        ?>
      </section>
    </main>
  </div>
</body>

</html>