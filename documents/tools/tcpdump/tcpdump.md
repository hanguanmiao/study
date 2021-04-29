sudo tcpdump -i lo '((tcp) and (port 50051) and (dst host 127.0.0.1))' -XXX -vvv > test.txt





