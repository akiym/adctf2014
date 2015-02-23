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
        <p>stage3: replace!</p>
        <ul>
            <li>Write a regexp replace to the specified strings.</li>
            <li>You may not use the following characters: <code>/[ \.0-9]/</code></li>
            <li>Max length: 15</li>
        </ul>
        <pre>&lt;p&gt;The requested URL &lt;code&gt;/404&lt;/code&gt; was not found on this server.  &lt;ins&gt;That's all we know.&lt;/ins&gt;</pre>
        ↓
        <pre>The requested URL /404 was not found on this server.</pre>
        <form class="console" method="post" action="stage3_9eaeec9bd606f259e92546a7fff593d6.php">
            s/<input type="text" class="ptn" name="pattern" maxlength="15" />/<input type="text" class="ptn" name="replacement" maxlength="15" />/
            <button type="submit" class="btn">check</button>
        </form>
<?php

if (isset($_POST["pattern"], $_POST["replacement"])) {
    $pattern = $_POST["pattern"];
    $replacement = $_POST["replacement"];
    if (strlen($pattern) <= 15 && strlen($replacement) <= 15
        && !preg_match("/[ \.0-9]/", $pattern) && !preg_match("/[ \.0-9]/", $replacement)
        && preg_replace("/$pattern/", $replacement, "<p>The requested URL <code>/404</code> was not found on this server.  <ins>That's all we know.</ins>") === "The requested URL /404 was not found on this server.") {
            echo "<p>Congrats! But there is no flag here, hehe. Find a vulnerability and pwn me on your second try :P</p>";
    } else {
        echo "<p>Wrong: <code>s/" . htmlspecialchars($pattern) . "/" . htmlspecialchars($replacement) . "/</code></p>";
    }
}

?>

    </div>
</body>
</html>
