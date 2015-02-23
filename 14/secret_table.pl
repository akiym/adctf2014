#!/usr/bin/env perl
use Mojolicious::Lite;
use DBI;

my $dbh = DBI->connect(
    'dbi:SQLite:dbname=./secret_table.db', '', '',
    +{
        RaiseError     => 1,
        sqlite_unicode => 1,
    }
);
app->helper(dbh => sub { $dbh });

get '/' => sub {
    my $self = shift;
    my $ip = $self->tx->remote_address;
    my $agent = $self->req->headers->user_agent;
    $self->dbh->do(
        "INSERT INTO access_log (accessed_at, ip, agent) VALUES (DATETIME('NOW'), '$ip', '$agent')"
    );
    return $self->render('index');
};

app->start;
__DATA__

@@ index.html.ep
<!DOCTYPE html>
<html>
  <head>
    <title>secret table</title>
  </head>
  <style>
body, input {
  color: #333;
  background: #fff;
  font-family: monospace;
  font-size: 150%;
}
  </style>
  <body>
    <div class="container">
        <p>we recorded your IP and user agent.</p>
    </div>
  </body>
</html>
