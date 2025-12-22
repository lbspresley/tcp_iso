#include "simadt.h"
#include "tplib/ulog.h"

char* TCPLIB_VERSION_NUM = "###### TCP Library ver 1.00 (2011/12/09) ######";

int tcp_Open(char *host, int port_no)
{
	int		fd;
	struct	sockaddr_in addr_in;
	struct hostent* hostp ;

	bzero((char *)&addr_in, sizeof(addr_in));

	addr_in.sin_family      = AF_INET;
	addr_in.sin_addr.s_addr = inet_addr(host);
	if( addr_in.sin_addr.s_addr == (unsigned long) 0xffffffff ) {
		hostp = (struct hostent*)gethostbyname( host );

		if( hostp == (struct hostent *)NULL ) {
			// not found hostname
			ulog( 2, "Not found hostname(%s)\n", host );
			addr_in.sin_addr.s_addr = htonl(INADDR_ANY);
		} else {
			addr_in.sin_family = hostp->h_addrtype;
			memcpy( (caddr_t)&addr_in.sin_addr, hostp->h_addr, hostp->h_length );
		}
	}

	addr_in.sin_port = htons((u_short)port_no);

	if ( (fd=socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {
		ulog( 2, "socket Fail errno(%d)\n", errno);
		return(-1);
	}

	if ( connect(fd, (struct sockaddr *)&addr_in, sizeof(addr_in)) < 0 ) {
		ulog( 2, "connect Fail errno(%d)\n", errno);
		close(fd);
		return(-2);
	}

	return(fd);
}

int	tcp_Read(int fd, char *buf, int nbyte)
{
	int		nleft, nread;
	char	*ptr;

	ptr   =  buf;
	nleft = nbyte;

	while ( nleft > 0 ) {
		nread = recv(fd, ptr, nleft, 0);
		if(nread < 0) {
			return(nread);
		} else if (nread == 0 && nleft == nbyte) {
			return 0;
		}

		nleft -= nread;
		ptr   += nread;
	}

	return(nbyte);
}

int	tcp_Write(int fd, char *buf, int nbyte)
{
	int		nleft, nwrite;
	char	*ptr;

	ptr   =  buf;
	nleft = nbyte;

	while (nleft > 0) {
		nwrite = send(fd, ptr, nleft, 0);
		if(nwrite < 0) {
			return nwrite;
		}

		nleft -= nwrite;
		ptr   += nwrite;
	}

	return(nbyte);
}

int	tcp_ReadLen(int fd, char *buf, int nlenbyte)
{
	int		nread;
	char	*ptr;
	char	lenstr[100];
	int		len;

	ptr   =  buf ;
	len = tcp_Read(fd, ptr, nlenbyte );
	if( len != nlenbyte ) {
		ulog( 2, "error to read head length rc(%d)\n", len );
		return -1;
	}

	memset( lenstr, 0, sizeof( lenstr ) );
	memcpy( lenstr, buf, len );

	len = atoi( lenstr );
	if( len <= 0 ) {
		ulog( 2, "error to read head length data(%.*s)\n", nlenbyte, buf );
		return -2;
	}
	ulog( 1, "read data Length(%d)\n", len );

	ptr   =  buf + nlenbyte;
	nread = tcp_Read(fd, ptr, len );
	if( nread != len ) {
		ulog( 2, "error to read data length rc(%d) Length(%d)\n", nread, len );
		return -3;
	}

	return(nread+nlenbyte);
}

int tcp_Listen( char* host, int port )
{
	int rc;
	int sockfd;
	int backlog;

	int on;
	struct sockaddr_in addr;
	struct hostent* hostp ;


	// socket open
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0 ) {
		ulog( 2, "socket create fail errno=%d (%s)",errno, strerror(errno));
		return -1;
	}

	// set sock option
	on = 1;
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on));

	if( ( host == (char*) NULL ) || ( *host == (char) 0 ) ) {
		addr.sin_addr.s_addr = htonl(INADDR_ANY);
	} else {
		addr.sin_addr.s_addr = inet_addr(host);
		if( addr.sin_addr.s_addr == (unsigned long) 0xffffffff ) {
			hostp = (struct hostent*)gethostbyname( host );

			if( hostp == (struct hostent *)NULL ) {
				// not found hostname
				ulog( 1, "Not found hostname(%s)\n", host );
				addr.sin_addr.s_addr = htonl(INADDR_ANY);
			} else {
				addr.sin_family = hostp->h_addrtype;
				memcpy( (caddr_t)&addr.sin_addr, hostp->h_addr, hostp->h_length );
			}
		}
	}

	// bind
	addr.sin_family   = AF_INET;
	addr.sin_port       = htons(port);

	rc = bind(sockfd,(struct sockaddr*)&addr,sizeof(addr));
	if(rc < 0) {
		ulog( 2, "port[%d] bind fail errno=%d (%s)", port , errno, strerror(errno));
		
		/* YYJ 20141028 add for inspection */
		close(sockfd);

		return -2;
	}


	// listen
	backlog = 256;
	rc = listen(sockfd, backlog);
	if(rc < 0) {
		ulog( 2, "port[%d] listen fail errno=%d (%s)\n", port , errno, strerror(errno));

		/* YYJ 20141028 add for inspection */
		close(sockfd);

		return -3;
	}

	ulog( 0, "Port [%d] listening......\n", port );

	return sockfd;
}

int tcp_Accept( int Listenfd )
{
	struct  sockaddr_in addr;
	int fd;
#if defined (_HPUX)
	int len;
#else
	socklen_t len;
#endif

	len = (socklen_t)sizeof(addr);

#if defined (_HPUX)
	fd = accept( Listenfd, (struct sockaddr*)&addr,(int*)&len);
#else
	fd = accept( Listenfd, (struct sockaddr*)&addr,(socklen_t*)&len);
#endif
	if( fd < 0 ) {
		ulog( 2, "Accept Fail rc:%d errno:%d (%s)", fd, errno, strerror(errno));
		return( -1 );
	}

	return( fd );
}
