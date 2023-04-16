<html>
<style>
  * {
    padding: 0;
    margin: 0;
    box-sizing: content-box;
  }

  #app {
    display: flex;
    flex-direction: column;
    min-height: 100vh;
  }

  .header {
    padding: 4px;
    text-align: center;
    background-color: #333;
    color: #fff;
  }

  .main {
    padding: 8px 4px;
    background-color: #ccc;
    flex-grow: 1;
    display: flex;
    flex-direction: column;
    justify-content: space-evenly;
    align-items: center;
  }

  .link {
    font-size: 20px;
    padding: 8px 24px;
    border: 1px solid black;
    border-radius: 10px;
  }

  .footer {
    background-color: #333;
    color: #fff;
    padding: 8px 4px;
    text-align: center;
  }
</style>

<head>
  <title>Web labs</title>
</head>

<body>
  <div id="app">
    <header class="header">
      <h1>Список лабораторных</h1>
    </header>
    <main class="main">
      <a class="link" href="/web/lab1/">Лабораторная работа №1</a>
      <a class="link" href="/web/lab2/">Лабораторная работа №2</a>
      <a class="link" href="/web/lab3/">Лабораторная работа №3</a>
      <a class="link" href="/web/lab4/">Лабораторная работа №4</a>
    </main>
    <footer class="footer">
      <p>Лабораторные выполнил студент АВТ-019 - Попов П.С.</p>
      <p>Вариант №8</p>
    </footer>
  </div>

  <body>

</html>