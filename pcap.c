#include <pcap.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
pcap_t *handle;			/* Session handle */
char *dev;			/* The device to sniff on */
char errbuf[PCAP_ERRBUF_SIZE];	/* Error string */
struct bpf_program fp;		/* The compiled filter */
char filter_exp[] = "port 23";	/* The filter expression */
bpf_u_int32 mask;		/* Our netmask */
bpf_u_int32 net;		/* Our IP */
struct pcap_pkthdr header;	/* The header that pcap gives us */
const u_char *packet;		/* The actual packet */

/* Define the device */
dev = pcap_lookupdev(errbuf);
if (dev == NULL) {
	fprintf(stderr, "Couldn't find default device: %s\n", errbuf);
	return(2);
}
/* Find the properties for the device */
if (pcap_lookupnet(dev, &net, &mask, errbuf) == -1) {
	fprintf(stderr, "Couldn't get netmask for device %s: %s\n", dev, errbuf);
	net = 0;
	mask = 0;
}
/* Open the session in promiscuous mode */
handle = pcap_open_live(dev, BUFSIZ, 1, 1000, errbuf);
if (handle == NULL) {
	fprintf(stderr, "Couldn't open device %s: %s\n", dev, errbuf);
	return(2);
}
/* Compile and apply the filter */
if (pcap_compile(handle, &fp, filter_exp, 0, net) == -1) {
	fprintf(stderr, "Couldn't parse filter %s: %s\n", filter_exp, pcap_geterr(handle));
	return(2);
}
if (pcap_setfilter(handle, &fp) == -1) {
	fprintf(stderr, "Couldn't install filter %s: %s\n", filter_exp, pcap_geterr(handle));
	return(2);
}


while(1){
	
	int module=0;
	/* Grab a packet */
	module=pcap_next_ex(handle, &header, &packet);

	/* Print its length */
	printf("Jacked a packet with length of [%d]\n", header.len);
	
	if(module==0)
	{	
		continue;	
	}

	printf("This is [%d] Ethernet Header information space \n",i);
	printf("Destination Mac Address: %02x %02x %02x %02x %02x %02x \n",packet[0],packet[1],packet[2],packet[3],packet[4],packet[5]);
	printf("Source Mac Address: %02x %02x %02x %02x %02x %02x \n",packet[6],packet[7],packet[8],packet[9],packet[10],packet[11]);

	if(packet[12]==0x08 && packet[13]==0x00)
	{
		printf("This is [%d] IP Header information space \n", i);
		printf("Source IP Address: %d.%d.%d.%d \n",packet[26], packet[27], packet[28], packet[29]);
		printf("Destination IP Address: %d.%d.%d.%d \n", packet[30], packet[31], packet[32], packet[33]);
	}
	

	i++;
}
/* And close the session */
pcap_close(handle);
return(0);
}
  
