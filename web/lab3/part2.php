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


    :root {
        --main-color: #03c03c;
    }
</style>

<head>
    <title>Web - lab3 - Part 1</title>
    <script src="https://cdn.tailwindcss.com"></script>
</head>


<body>
    <header class="header">
        <div class="flex flex-row justify-center w-full">
            <h1 class="p-4">Лабораторная работа №3</h1>

        </div>
    </header>

    <?php
    include_once("fckeditor/fckeditor.php");
    session_start();
    ?>

    <form action="journal.php" method="post" target="_self">
        <div class="form__flags">
            <p>Оформления текста:</p>
            <div class="flex flex-row space-x-5">
                <div class="form__flags__div flex flex-col items-center">
                    <p><input type="checkbox" id="cat" value="cat" name="styles[]"></P>
                    <label for="cat">Котиками</label>
                </div>
                <div class="form__flags__div flex flex-col items-center">
                    <p><input type="checkbox" id="dogs" value="dog" name="styles[]"></p>
                    <label for="dog">Собачками</label>
                </div>
                <div class="form__flags__div flex flex-col items-center">
                    <p><input type="checkbox" id="turtle" value="turtle" name="styles[]"></p>
                    <label for="turtle">Черепахами</label>
                </div>
            </div>
        </div>
        <br>

        <h1>Комментарий: </h1>
        <div id="ckeditor">
            <?php
            $oFCKeditor = new FCKeditor('comment');
            $oFCKeditor->BasePath = 'fckeditor/';
            $oFCKeditor->Value = '';
            $oFCKeditor->Create();
            ?>
        </div>
        <br>
        <div class="w-72">
            <div class="relative h-10 w-full min-w-[200px]">
                <input name="username" required
                    class="peer h-full w-full rounded-[7px] border border-blue-gray-200 border-t-transparent bg-transparent px-3 py-2.5 font-sans text-sm font-normal text-blue-gray-700 outline outline-0 transition-all placeholder-shown:border placeholder-shown:border-blue-gray-200 placeholder-shown:border-t-blue-gray-200 focus:border-2 focus:border-pink-500 focus:border-t-transparent focus:outline-0 disabled:border-0 disabled:bg-blue-gray-50"
                    placeholder=" " />
                <label
                    class="before:content[' '] after:content[' '] pointer-events-none absolute left-0 -top-1.5 flex h-full w-full select-none text-[11px] font-normal leading-tight text-blue-gray-400 transition-all before:pointer-events-none before:mt-[6.5px] before:mr-1 before:box-border before:block before:h-1.5 before:w-2.5 before:rounded-tl-md before:border-t before:border-l before:border-blue-gray-200 before:transition-all after:pointer-events-none after:mt-[6.5px] after:ml-1 after:box-border after:block after:h-1.5 after:w-2.5 after:flex-grow after:rounded-tr-md after:border-t after:border-r after:border-blue-gray-200 after:transition-all peer-placeholder-shown:text-sm peer-placeholder-shown:leading-[3.75] peer-placeholder-shown:text-blue-gray-500 peer-placeholder-shown:before:border-transparent peer-placeholder-shown:after:border-transparent peer-focus:text-[11px] peer-focus:leading-tight peer-focus:text-pink-500 peer-focus:before:border-t-2 peer-focus:before:border-l-2 peer-focus:before:border-pink-500 peer-focus:after:border-t-2 peer-focus:after:border-r-2 peer-focus:after:border-pink-500 peer-disabled:text-transparent peer-disabled:before:border-transparent peer-disabled:after:border-transparent peer-disabled:peer-placeholder-shown:text-blue-gray-500">
                    Имя
                </label>
            </div>
        </div>
        <br>
        <img src="/web/lab3/kcaptcha/index.php?<?php echo session_name() ?>=<?php echo session_id() ?>"></p>
        <div class="w-72">
            <div class="relative h-10 my-10 w-full min-w-[200px]">
                <input name="code" required
                    class="peer h-full w-full rounded-[7px] border border-blue-gray-200 border-t-transparent bg-transparent px-3 py-2.5 font-sans text-sm font-normal text-blue-gray-700 outline outline-0 transition-all placeholder-shown:border placeholder-shown:border-blue-gray-200 placeholder-shown:border-t-blue-gray-200 focus:border-2 focus:border-pink-500 focus:border-t-transparent focus:outline-0 disabled:border-0 disabled:bg-blue-gray-50"
                    placeholder=" " />
                <label
                    class="before:content[' '] after:content[' '] pointer-events-none absolute left-0 -top-1.5 flex h-full w-full select-none text-[11px] font-normal leading-tight text-blue-gray-400 transition-all before:pointer-events-none before:mt-[6.5px] before:mr-1 before:box-border before:block before:h-1.5 before:w-2.5 before:rounded-tl-md before:border-t before:border-l before:border-blue-gray-200 before:transition-all after:pointer-events-none after:mt-[6.5px] after:ml-1 after:box-border after:block after:h-1.5 after:w-2.5 after:flex-grow after:rounded-tr-md after:border-t after:border-r after:border-blue-gray-200 after:transition-all peer-placeholder-shown:text-sm peer-placeholder-shown:leading-[3.75] peer-placeholder-shown:text-blue-gray-500 peer-placeholder-shown:before:border-transparent peer-placeholder-shown:after:border-transparent peer-focus:text-[11px] peer-focus:leading-tight peer-focus:text-pink-500 peer-focus:before:border-t-2 peer-focus:before:border-l-2 peer-focus:before:border-pink-500 peer-focus:after:border-t-2 peer-focus:after:border-r-2 peer-focus:after:border-pink-500 peer-disabled:text-transparent peer-disabled:before:border-transparent peer-disabled:after:border-transparent peer-disabled:peer-placeholder-shown:text-blue-gray-500">
                    Код подтверждения
                </label>
            </div>
        </div>
        <input type="submit" class="px-6 py-3 bg-blue-400 rounded-xl" value="Submit">
    </form>
</body>

</html>