pcap_test: pcap.o
	gcc -o pcap pcap.o -lpcap

pcap_test.o: pcat.c
	gcc -c pcap.c

clean:
	rm *.o pcap_test
