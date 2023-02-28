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

  .main {
    background-image: url("./bg.jpg");
    background-color: rgba(0, 0, 0, 0.5);
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
</style>

<head>
  <title>Web - lab1</title>
</head>

<body>
  <header class="header">
    <h1 class="h1">Лабораторная работа №1</h1>
  </header>

  <main class="main">
    <h2 class="h2">MySQL. Проектирование и реализация базы данных.</h2>
    <section class="block__download">
      <img src="hacker.png" class="img" alt="hacker" />
      <a href="/web/dump.sql" target="_blank">Открыть дамп базы данных</a>
    </section>

    <h2 class="h2">PHP. Работа с файлами теневых посылок (cookies) и текстовыми файлами.</h2>

    <section class="block_cookies">
      <?php
      $text = "не выбран";
      $graphics = "не выбраны";
      $styles = "не выбраны";

      function textName($name)
      {
        if ($name == "standard") {
          return "Стандарт";
        } else if ($name == "bold") {
          return "Строгий";
        } else if ($name == "italic") {
          return "Мягкий";
        }

        return "не выбран";
      }

      function graphicsName($name)
      {
        if ($name == "minimal") {
          return "Минимально";
        } else if ($name == "normal") {
          return "Нормально";
        }

        return "не выбраны";
      }

      function stylesName($name)
      {
        if ($name == "noir") {
          return "Нуар";
        } else if ($name == "future") {
          return "Футуризм";
        }

        return "не выбраны";
      }

      if ($_SERVER['REQUEST_METHOD'] == 'POST') {
        if (isset($_POST["text"]) && isset($_POST["graphics"]) && isset($_POST["styles"])) {
          setcookie("visit", date('m/d/y h:m'), time() + 365 * 24 * 60 * 60);
          setcookie("text", $_POST["text"], time() + 365 * 24 * 60 * 60);
          setcookie("graphics", $_POST["graphics"], time() + 365 * 24 * 60 * 60);
          setcookie("styles", $_POST["styles"], time() + 365 * 24 * 60 * 60);

          header("location:index.php");
        }
      }

      if (
        isset($_COOKIE["visit"]) && isset($_COOKIE["text"])
        && isset($_POST["graphics"]) && isset($_POST["styles"])
      ) {
        $text = textName($_COOKIE["text"]);
        $graphics = graphicsName($_COOKIE["graphics"]);
        $styles = stylesName($_COOKIE["styles"]);

        echo "<p>Время последнего визита: " . $_COOKIE["visit"] . "</p>";
      }

      echo "<h3>Приветствуем, юзер!</h3>";
      echo "<p>Текст: " . $text . ". </p>";
      echo "<p>Граф. данные: " . $graphics . ". </p>";
      echo "<p>Стили офорлмения: " . $styles . ". </p>";

      ?>
      <FORM class="form" method="post" action="index.php">
        <div class="form__flags">
          <p>Текст:</p>
          <div>
            <P><INPUT TYPE="radio" id="standard" VALUE="standard" NAME="text"></P>
            <label for="standard">Стандарт</label>
          </div>
          <div>
            <P><INPUT TYPE="radio" id="bold" VALUE="bold" NAME="text"></P>
            <label for="bold">Строгий</label>
          </div>
          <div>
            <P><INPUT TYPE="radio" id="italic" VALUE="italic" NAME="text"></P>
            <label for="italic">Мягкий</label>
          </div>
        </div>

        <div class="form__flags">
          <p>Граф. данные:</p>
          <div>
            <P><INPUT TYPE="radio" id="minimal" VALUE="minimal" NAME="graphics"></P>
            <label for="minimal">Минимально</label>
          </div>
          <div>
            <P><INPUT TYPE="radio" id="normal" VALUE="normal" NAME="graphics"></P>
            <label for="normal">Нормально</label>
          </div>
        </div>

        <div class="form__flags">
          <p>Стили оформления:</p>
          <div>
            <P><INPUT TYPE="radio" id="noir" VALUE="noir" NAME="styles"></P>
            <label for="noir">Нуар</label>
          </div>
          <div>
            <P><INPUT TYPE="radio" id="future" VALUE="future" NAME="styles"></P>
            <label for="future">Футуризм</label>
          </div>
        </div>

        <div>
          <INPUT TYPE="SUBMIT" VALUE="Отправить!">
          <INPUT TYPE="RESET" VALUE="Очистить">
        </div>
      </FORM>
    </section>
  </main>
</body>

</html>