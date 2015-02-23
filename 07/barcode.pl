use strict;
use warnings;

package BarcodeServer {
    use strict;
    use warnings;
    use parent qw/Net::Server::PreFork/;
    use Encode;
    use POSIX::AtFork;

    POSIX::AtFork->add_to_child(sub { srand });

    use constant CHUNKSIZE    => 64 * 1024;
    use constant READ_TIMEOUT => 3;

    our (@WORDS, $WORDS_NUM);

    sub process_request {
        my $self = shift;
        my $conn = $self->{server}->{client};

        my $peeraddr = $self->{server}->{peeraddr};
        my $peerport = $self->{server}->{peerport};

        warn "$peeraddr:$peerport connected\n";

        my $count = 0;
        while (1) {
            my $word = $WORDS[int rand $WORDS_NUM];
            #warn "$peeraddr:$peerport choose $word\n";
            syswrite $conn, $self->_gen_barcode($word) . "\n";

            last if !$conn->connected;
            last if !$self->_read;

            my $buf = delete $self->{client}->{inputbuf};
            chomp $buf;

            if ($buf eq $word) {
                $count++;
                #warn "$peeraddr:$peerport was correct $count times\n";
                if ($count == 10) {
                    warn "$peeraddr:$peerport got the flag\n";
                    syswrite $conn, "the flag is: ADCTF_4R3_y0U_B4rC0d3_R34D3r\n";
                    last;
                }
            } else {
                #warn "$peeraddr:$peerport choose $word -> $buf\n";
                last;
            }
        }

        warn "$peeraddr:$peerport closed\n";
    }

    sub _read {
        my $self = shift;

        eval {
            local $SIG{ALRM} = sub { die "Timed out\n"; };

            alarm(READ_TIMEOUT);

            while (1) {
                last if defined $self->{client}->{inputbuf};

                my $read = sysread $self->{server}->{client}, my $buf, CHUNKSIZE;

                if (!defined $read || $read == 0) {
                    die "Read error: $!\n";
                }

                $self->{client}->{inputbuf} .= $buf;
            }
        };

        alarm(0);

        if ($@) {
            #if ($@ =~ /Timed out/) {
            #}
            return;
        }

        return 1;
    }

    sub _gen_barcode {
        my ($self, $word) = @_;
        my $data = $self->barcode($word);
        for (my $i = 0; $i < scalar @$data; $i += 2) {
            my $a = $data->[$i];
            my $b = $data->[$i + 1];
            if (defined $b) {
                if ($a == 0 && $b == 0) {
                    print "  ";
                } elsif ($a == 1 && $b == 0) {
                    print "\xe2\x96\x8c";
                } elsif ($a == 0 && $b == 1) {
                    print "\xe2\x96\x90";
                } elsif ($a == 1 && $b == 1) {
                    print "\xe2\x96\x88";
                }
            } else {
                if ($a == 0) {
                    print " ";
                } elsif ($a == 1) {
                    print "\xe2\x96\x8c";
                }
            }
        }
    }

    sub barcode {
        my ($self, $text) = @_;
        my @data = $self->_barcode(uc $text);
        return wantarray ? @data : \@data;
    }

    #------------------------------------------------------------------------------
    # barcode (from GD::Barcode::Code93)
    #------------------------------------------------------------------------------
    sub _barcode {
        my $self = shift;
        my $text = shift;

        my $code93bar = {
            0   =>'100010100',
            1   =>'101001000',
            2   =>'101000100',
            3   =>'101000010',
            4   =>'100101000',
            5   =>'100100100',
            6   =>'100100010',
            7   =>'101010000',
            8   =>'100010010',
            9   =>'100001010',
            A   =>'110101000',
            B   =>'110100100',
            C   =>'110100010',
            D   =>'110010100',
            E   =>'110010010',
            F   =>'110001010',
            G   =>'101101000',
            H   =>'101100100',
            I   =>'101100010',
            J   =>'100110100',
            K   =>'100011010',
            L   =>'101011000',
            M   =>'101001100',
            N   =>'101000110',
            O   =>'100101100',
            P   =>'100010110',
            Q   =>'110110100',
            R   =>'110110010',
            S   =>'110101100',
            T   =>'110100110',
            U   =>'110010110',
            V   =>'110011010',
            W   =>'101101100',
            X   =>'101100110',
            Y   =>'100110110',
            Z   =>'100111010',
        ' '  =>'111010010',
        '$'  =>'111001010',
        '%'  =>'110101110',
        '($)'=>'100100110',
        '(%)'=>'111011010',
        '(+)'=>'100110010',
        '(/)'=>'111010110',
        '+'  =>'101110110',
        '-'  =>'100101110',
        '.'  =>'111010100',
        '/'  =>'101101110',
        '*'  =>'101011110',  ##Start/Stop
        };

        my @sum_text = ('*', $self->calculateSums($text), '*');

        my @rv = map { split //, $code93bar->{$_} } @sum_text;
        push @rv, 1;
        return @rv;
    }


    #-----------------------------------------------------------------------------
    # calculateSums (from GD::Barcode::Code93)
    #-----------------------------------------------------------------------------
    sub calculateSums {
        my $self = shift;
        my $text = shift;
        $text = '' unless defined $text;
        my @array = split(//, scalar reverse $text);

        my %code93values = (
            '0'    =>'0',
            '1'    =>'1',
            '2'    =>'2',
            '3'    =>'3',
            '4'    =>'4',
            '5'    =>'5',
            '6'    =>'6',
            '7'    =>'7',
            '8'    =>'8',
            '9'    =>'9',
            'A'    =>'10',
            'B'    =>'11',
            'C'    =>'12',
            'D'    =>'13',
            'E'    =>'14',
            'F'    =>'15',
            'G'    =>'16',
            'H'    =>'17',
            'I'    =>'18',
            'J'    =>'19',
            'K'    =>'20',
            'L'    =>'21',
            'M'    =>'22',
            'N'    =>'23',
            'O'    =>'24',
            'P'    =>'25',
            'Q'    =>'26',
            'R'    =>'27',
            'S'    =>'28',
            'T'    =>'29',
            'U'    =>'30',
            'V'    =>'31',
            'W'    =>'32',
            'X'    =>'33',
            'Y'    =>'34',
            'Z'    =>'35',
            '-'    =>'36',
            '.'    =>'37',
            ' '    =>'38',
            '$'    =>'39',
            '/'    =>'40',
            '+'    =>'41',
            '%'    =>'42',
            '($)'    =>'43',
            '(%)'    =>'44',
            '(/)'    =>'45',
            '(+)'    =>'46',
            '*'        => '',
        );

        my %invCode93Values = reverse %code93values;
        my $weighted_sum;

        foreach my $counter ( qw/4 3/ ) {
            for (my $i = 0, my $x = 1; $i <= $#array; $i++, $x++) {
                my $letter  = $array[$i];

                if ($x > ($counter * 5)) { $x = 1 }
                $weighted_sum += ($code93values{$letter} * $x);
            }

            my $check = $invCode93Values{($weighted_sum % 47)};
            unshift @array, $check;
            $weighted_sum = ();
        }

        return reverse @array;
    }

}

@BarcodeServer::WORDS = map { uc } grep /^[a-z]{8,10}$/, split /\n/, do {
    open my $fh, '<', './words' or die $!;
    local $/; <$fh>;
};
$BarcodeServer::WORDS_NUM = scalar @BarcodeServer::WORDS;

BarcodeServer->run(port => 43010);
