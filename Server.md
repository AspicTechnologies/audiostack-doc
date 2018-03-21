---
title: Server Documentation
permalink: /audiostack/Server/
---

{% icon fa-exclamation-triangle  %} Documentation in progress

Audiostack server features are designed to ease audio server creation.

A basic use-case could be:
- Audiostack server runs on a remote system
- A client app sends orders to the server to driver audio rendering


Introduction
-----

Aspic Audiostack can be used as a server. Here is how it works:
* Client side:
	* Create an app that uses Audiostack
	* Replace the dynamic library by the "client/server" audiostack library (they share the exact same C interface)
	* Fill the blanks in the server_info.json (server ip address, port)
* Server side:
	* Start audiostack_server provided in the package
* Client side: 
	The application that uses the client/server lib will communicate with the server executable to execute all audio processing on server side.



