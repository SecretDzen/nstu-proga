<?php
ini_set('display_errors', '1');
ini_set('display_startup_errors', '1');
error_reporting(E_ALL);
require_once(__DIR__ . '/../utils/connection.php');
$db = connect();
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

  .body {
    padding: 4px 0;
    max-width: 1024px;
    margin: 0 auto;
  }

  .form {
    display: flex;
    align-items: center;
    flex-direction: column;
    gap: 4px;
  }
</style>


<head>
    <title>Authentication</title>
</head>


<body>
  <header class="header">
    <h1 class="h1">Вход</h1>
  </header>
    <?php
    session_start();

    if (!empty($_POST['password']) and !empty($_POST['login'])) {
        $login = $_POST['login'];
        $password = $_POST['password'];

        $query = "SELECT * FROM users WHERE login=$1 AND password=$2";
        $result = pg_query_params($db, $query, array($login, $password));
        $user = pg_fetch_assoc($result);

        if (!empty($user)) {
            $_SESSION['auth'] = true;
            $_SESSION['group'] = $user['access_level'];
            $_SESSION['login'] = $user['login'];
            header("location:index.php");
        } else {
            echo 'Логин или пароль неверные <br><br>';
        }
    }

?>
  <main class="body">
    <form class="form" method="post" action="auth.php">
      <div>
        <input name="login" id="login" placeholder="Введите логин" />
      </div>
      <div>
        <input name="password" id="password" placeholder="Введите пароль" />
      </div>
      <button type=" submit">Войти</button>
    </form>
  </main>
</body>
