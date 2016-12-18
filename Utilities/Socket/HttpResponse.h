#if !defined(HttpResponse_H)
#define HttpResponse_H


#include "HttpUtil.h"
#include "HttpRequest.h"
#include "HttpServerInfo.h"
#include "TextFile.h"


#include <string>
#include <iostream>
#include <sstream>
using namespace std;


#pragma warning( disable:4172 )


/////////////////////////////////////////////////////////////////////////////////////
// HttpResponse
//
// Purpose:	represent an http response

class HttpResponse :
	public HttpRequest
{
protected:

	//////////////////////////////////////////////////////////
	// http response format 
	//
	// Response Line Required
	// General Header Optional
	// Response Header Optional
	// Entity Header Optional
	// Entity Body Optional

	// static ref to server
	static HttpServerInfo * _server;

	// handle to file
	HANDLE			_hFile;				// handle to file associated with response
	TextFile		_file;				// file associated with response

public:

	HttpResponse ();
	HttpResponse ( HttpRequest & request );
	virtual ~HttpResponse ();

	// create/release
	bool create  ();
	void release ();

	// set static server ptr
	static setServer ( HttpServerInfo & server )
	{
		_server = &server;
	}


	// content add methods
	bool	startResponse	();
	bool	startServerApp	();
	bool	addHeading		();
	void	addTagetInfo	();
	void	addListing		();
	int		addListingFile	( WIN32_FIND_DATA * pfd, const string& strDir, bool bIcons );
	void	addContentType	();

};



#endif