<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8" />
    <title>Regexp Quiz</title>
    <link rel="stylesheet" type="text/css" href="static/style.css" />
</head>
<body>
    <div class="header">
        <h1>Regexp Quiz</h1>
    </div>
    <div class="container">
        <p>stage1: match!</p>
        <ul>
            <li>Write a regexp match the specified strings.</li>
            <li>You may not use the following characters: <code>[\\\.]</code></li>
            <li>Max length: 15</li>
        </ul>
        <pre>Tue, 29 Feb 2000 12:34:56 GMT</pre>
        <form class="console" method="post" action="stage1.php">
            /<input type="text" class="ptn" name="pattern" maxlength="15" />/
            <button type="submit" class="btn">check</button>
        </form>
<?php

if (isset($_POST["pattern"])) {
    $pattern = $_POST["pattern"];
    if (strlen($pattern) <= 15 && !preg_match("/[\\\.]/", $pattern)
        && preg_match("/($pattern)/", "Tue, 29 Feb 2000 12:34:56 GMT", $matches)) {
        if (isset($matches[1]) && $matches[1] === "Tue, 29 Feb 2000 12:34:56 GMT") {
            echo '<p>Correct! Go <a href="stage2_30c401d6f53803c3e3dfe2beaf94c620.php">next stage</a>.</p>';
        } else {
            echo "<p>Wrong: <code>/" . htmlspecialchars($pattern) . "/</code></p>";
        }
    } else {
        echo "<p>Wrong: <code>/" . htmlspecialchars($pattern) . "/</code></p>";
    }
}

?>

    </div>
</body>
</html>
