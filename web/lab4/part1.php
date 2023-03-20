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

    .footer {
        background-color: #333;
        color: #fff;
        padding: 8px 4px;
        text-align: center;
    }

    .error {
        color: red;
    }
</style>

<head>
    <title>Web - lab4</title>
    <script src="https://cdn.jsdelivr.net/npm/jquery@3.6.3/dist/jquery.min.js"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/jquery-validate/1.19.0/jquery.validate.min.js"></script>
</head>

<body>
    <header class="header">
        <h1 class="h1">Лабораторная работа №4</h1>
    </header>

    <div class="main__div">
        <main class="main">
            <section>
                <h2 class="h2">Валидация с помощью JS</h2>
                <FORM class="form" id="form1" method="post" action="part1.php">
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
                        <P><TEXTAREA rows="4" cols="50" TYPE="text" id="comment" NAME="comment"></TEXTAREA></P>
                    </div>

                    <div>
                        <INPUT TYPE="SUBMIT" VALUE="Отправить!">
                        <INPUT TYPE="RESET" VALUE="Очистить">
                    </div>
                </FORM>

                <script>
                    function validateForm(name) {
                        var radios = document.getElementsByName(name);
                        var formValid = false;

                        var i = 0;
                        while (!formValid && i < radios.length) {
                            if (radios[i].checked) formValid = true;
                            i++;
                        }
                        return formValid;
                    }

                    $("#form1").on("submit", (event) => {
                        const isCommentValid = $("#comment").val().length > 4
                        const isStylesValid = validateForm("styles[]")
                        if (!isCommentValid || !isStylesValid) {
                            event.preventDefault()
                            console.log("preventing default");
                            let res = ""
                            if (!isCommentValid) res += "Комментарий должен быть длиннее 4 символов. "
                            if (!isStylesValid) res += "Стиль оформления не выбран. "
                            alert(res)
                        }
                    })
                </script>

            </section>
            <section>
                <h2 class="h2">Валидация с помощью JQuery</h2>
                <FORM class="form" id="form2" method="post" action="part1.php">
                    <div class="form__flags">
                        <p>Оформления текста:</p>
                        <div class="form__flags__div">
                            <P><INPUT TYPE="checkbox" id="cat" class="styles" VALUE="cat" NAME="styles[]"></P>
                            <label for="cat">Котиками</label>
                        </div>
                        <div class="form__flags__div">
                            <P><INPUT TYPE="checkbox" id="dogs" VALUE="dog" class="styles" NAME="styles[]"></P>
                            <label for="dog">Собачками</label>
                        </div>
                        <div class="form__flags__div">
                            <P><INPUT TYPE="checkbox" id="turtle" VALUE="turtle" class="styles" NAME="styles[]"></P>
                            <label for="turtle">Черепахами</label>
                        </div>
                    </div>

                    <div>
                        <p>Ваш комментарий: </p>
                        <P><TEXTAREA rows="4" cols="50" TYPE="text" id="comment" NAME="comment"></TEXTAREA></P>
                    </div>

                    <div>
                        <INPUT TYPE="SUBMIT" VALUE="Отправить!">
                        <INPUT TYPE="RESET" VALUE="Очистить">
                    </div>
                </FORM>
                <script>
                    $(document).ready(function () {
                        $("#form2").validate({
                            rules: {
                                comment: {
                                    required: true,
                                    minlength: 4
                                },
                                'styles[]': {
                                    required: true,
                                    minlength: 1
                                },
                            },
                            messages: {
                                comment: {
                                    required: "Комментарий не может быть пустым. ",
                                    minlength: "Комментарий должен быть длиннее 4 символов. "
                                },
                                'styles[]': {
                                    required: "Стиль оформления не выбран. ",
                                    minlength: "Стиль оформления не выбран. "
                                },
                            },
                            errorElement: "div",
                            errorPlacement: function (error, element) {
                                if (element.is(":checkbox")) {
                                    error.appendTo(element.parents('.form__flags'));
                                }
                                else { // This is the default behavior 
                                    error.insertAfter(element);
                                }
                            },
                            // errorClass: ".error"
                        })
                    });
                </script>
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

                if ($_SERVER['REQUEST_METHOD'] == 'POST' && $_POST["flags"] == [] && ($_POST["comment"] != "" || $_POST["styles"] != []) || ($_POST["flags"] != [] && $_POST["comment"] != "" && $_POST["styles"] != [])) {
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

                    header("location:part1.php");
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
                    header("location:part1.php");
                }
                ?>
            </section>
        </main>
        <footer class="footer">
            <p>Лабораторные выполнил студент АВТ-019 - Попов П.С.</p>
            <p>Вариант №8</p>
        </footer>
    </div>
</body>

</html>