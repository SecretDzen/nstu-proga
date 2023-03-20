<!DOCTYPE html>
<html>

<head>
    <title>Журнал</title>
    <meta charset='utf-8'>
</head>

<body>
    <?php
    session_start();

    if ($_SERVER['REQUEST_METHOD'] == 'POST' && isset($_POST["code"]) && isset($_SESSION['captcha_keystring'])) {
        if ($_SESSION['captcha_keystring'] != $_POST["code"]) {
            header('location:part2.php');
            exit;
        }
        unset($_SESSION['captcha_keystring']);

        $styles = "";
        $comment = "";
        $username = "";


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

        if ($_SERVER['REQUEST_METHOD'] == 'POST' && ($_POST["comment"] != "" || $_POST["styles"] != [])) {
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
            if (isset($_POST["username"]) && $_POST["username"] != "") {
                $username = $_POST["username"];
            }

            $fp = @fopen(__DIR__ . "/logs.txt", "a");
            if (!$fp) {
                echo "<p>Ошибка доступа к журналу</p>";
                echo "Путь - " . __DIR__ . "/logs.txt";
            } else {
                $str = "Дата: " . date('d/m/y h:m') . "<br>Стили оформления: " . htmlspecialchars($styles) . "<br>Комментарий: " . $comment . "<br>Пользователь: " . htmlspecialchars($username) . "<br>========================<br><br>";
                fwrite($fp, $str);
            }

        }

        if (!file_exists(__DIR__ . "/logs.txt")) {
            echo "<p>Ошибка доступа к журналу</p>";
        } else {
            echo '<h3 class="h2">Журнал</h3>';

            $file = fopen(__DIR__ . '/logs.txt', 'r');
            while (!feof($file)) {
                $text = fgets($file);
                echo $text;
            }

            fclose($file);
        }
    } else {
        session_abort();
        header('location:part2.php');
    }
    ?>

</body>

</html>