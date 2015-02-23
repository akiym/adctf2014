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
        <p>stage2: capture!</p>
        <ul>
            <li>Capture stage3 URL in this source.</li>
            <li>You may not use the following characters: <code>/[stage0-9]/</code></li>
            <li>You can capture only once.</li>
            <li>Max length: 15</li>
        </ul>
        <pre>if (!preg_match("/[stage0-9]/", $pattern)) {
    $src = file_get_contents("stage2_30c401d6f53803c3e3dfe2beaf94c620.php");
    if (preg_match("/$pattern/", $src, $matches) &amp;&amp; count($matches) == 2) {</pre>
        <form class="console" method="post" action="stage2_30c401d6f53803c3e3dfe2beaf94c620.php">
            /<input type="text" class="ptn" name="pattern" maxlength="15" />/
            <button type="submit" class="btn">check</button>
        </form>
<?php

if (isset($_POST["pattern"])) {
    $pattern = $_POST["pattern"];
    if (strlen($pattern) <= 15 && !preg_match("/[stage0-9]/", $pattern)) {
        $src = file_get_contents("stage2_30c401d6f53803c3e3dfe2beaf94c620.php");
        if (preg_match("/$pattern/", $src, $matches) && count($matches) == 2) {
            if ($matches[1] === "stage3_9eaeec9bd606f259e92546a7fff593d6.php") {
                echo '<p>Correct! Go <a href="stage3_9eaeec9bd606f259e92546a7fff593d6.php">next stage</a>.</p>';
            } else {
                echo "<p>Wrong: <code>/" . htmlspecialchars($pattern) . "/ => " . htmlspecialchars($matches[1]) . "</code></p>";
            }
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
