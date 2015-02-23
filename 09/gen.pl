use 5.016;
use warnings;
use Imager;
use Imager::QRCode;

# ADCTF_re4d1n9_Qrc0de_15_FuN

sub gen_random_flag {
    my @prefix_chars = ('A'..'Z');
    my $prefix_len = scalar @prefix_chars;
    my $flag;
  RETRY:
    $flag = '';
    for (1..2) {
        $flag .= $prefix_chars[int rand $prefix_len];
    }
    if ($flag eq 'AD') {
        goto RETRY;
    }
    $flag .= 'CTF_';
    my @chars = ('0'..'9', 'A'..'Z', 'a'..'z');
    my $len = scalar @chars;
    for (1..21) {
        if (int rand 10 == 0) {
            $flag .= '_';
        } else {
            $flag .= $chars[int rand $len];
        }
    }
    return $flag;
}

sub gen_qrcode {
    my $data = shift;
    my $qrcode = Imager::QRCode->new(
        size    => 3,
        margin  => 0,
        version => 3,
        level   => 'M',
    );
    return $qrcode->plot($data);
}

my $SIZE = 87;
my $WIDTH = 100;
my $HEIGHT = 100;

my $img = Imager->new(
    xsize => $SIZE * $WIDTH,
    ysize => $SIZE * $HEIGHT,
) or die Imager->errstr;

my $i = 0;
for my $y (0..$HEIGHT-1) {
for my $x (0..$WIDTH-1) {
    my $qr;
    if ($i == 7852) {
        $qr = gen_qrcode('ADCTF_re4d1n9_Qrc0de_15_FuN');
    } else {
        $qr = gen_qrcode(gen_random_flag());
    }
    $img->paste(
        left => $SIZE * $x,
        top  => $SIZE * $y,
        img  => $qr,
    );
    $i++;
}
}

$img->write(file => 'qrgarden.png');
