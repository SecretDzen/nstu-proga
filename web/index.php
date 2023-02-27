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
            <a href="/web/dump.sql" target="_blank">Скачать дамп базы данных</a>
        </section>
    </main>
</body>

</html>
