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
</style>

<head>
  <title>Web - lab2</title>
  <script src="https://cdn.tailwindcss.com"></script>
</head>

<body>
  <header class="header">
    <h1 class="p-4">Лабораторная работа №2</h1>
  </header>

  <?php
  require_once('../utils/connection.php');
  $db = connect();

  if (!$db) {
    echo "<p>Ошибка подключения</p>";
    exit;
  }

  echo "<p>Успешное подключение</p>";
  ?>
</body>

</html>