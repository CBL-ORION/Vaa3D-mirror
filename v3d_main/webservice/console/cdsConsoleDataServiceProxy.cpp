/* cdsConsoleDataServiceProxy.cpp
   Generated by gSOAP 2.8.3 from cdsModHeader.h

Copyright(C) 2000-2011, Robert van Engelen, Genivia Inc. All Rights Reserved.
The generated code is released under one of the following licenses:
1) GPL or 2) Genivia's license for commercial use.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
*/

#include "cdsConsoleDataServiceProxy.h"

namespace cds {

ConsoleDataServiceProxy::ConsoleDataServiceProxy()
{	ConsoleDataServiceProxy_init(SOAP_IO_DEFAULT, SOAP_IO_DEFAULT);
}

ConsoleDataServiceProxy::ConsoleDataServiceProxy(const struct soap &_soap) : soap(_soap)
{ }

ConsoleDataServiceProxy::ConsoleDataServiceProxy(const char *url)
{	ConsoleDataServiceProxy_init(SOAP_IO_DEFAULT, SOAP_IO_DEFAULT);
	soap_endpoint = url;
}

ConsoleDataServiceProxy::ConsoleDataServiceProxy(soap_mode iomode)
{	ConsoleDataServiceProxy_init(iomode, iomode);
}

ConsoleDataServiceProxy::ConsoleDataServiceProxy(const char *url, soap_mode iomode)
{	ConsoleDataServiceProxy_init(iomode, iomode);
	soap_endpoint = url;
}

ConsoleDataServiceProxy::ConsoleDataServiceProxy(soap_mode imode, soap_mode omode)
{	ConsoleDataServiceProxy_init(imode, omode);
}

ConsoleDataServiceProxy::~ConsoleDataServiceProxy()
{ }

void ConsoleDataServiceProxy::ConsoleDataServiceProxy_init(soap_mode imode, soap_mode omode)
{	soap_imode(this, imode);
	soap_omode(this, omode);
	soap_endpoint = NULL;
	static const struct Namespace namespaces[] =
{
	{"SOAP-ENV", "http://schemas.xmlsoap.org/soap/envelope/", "http://www.w3.org/*/soap-envelope", NULL},
	{"SOAP-ENC", "http://schemas.xmlsoap.org/soap/encoding/", "http://www.w3.org/*/soap-encoding", NULL},
	{"xsi", "http://www.w3.org/2001/XMLSchema-instance", "http://www.w3.org/*/XMLSchema-instance", NULL},
	{"xsd", "http://www.w3.org/2001/XMLSchema", "http://www.w3.org/*/XMLSchema", NULL},
	{"ns2", "http://jaxb.dev.java.net/array", NULL, NULL},
	{"fw", "http://ws.FlyWorkstation.it.janelia.org/", NULL, NULL},
	{NULL, NULL, NULL, NULL}
};
	soap_set_namespaces(this, namespaces);
}

void ConsoleDataServiceProxy::destroy()
{	soap_destroy(this);
	soap_end(this);
}

void ConsoleDataServiceProxy::soap_noheader()
{	this->header = NULL;
}

const SOAP_ENV__Header *ConsoleDataServiceProxy::soap_header()
{	return this->header;
}

const SOAP_ENV__Fault *ConsoleDataServiceProxy::soap_fault()
{	return this->fault;
}

const char *ConsoleDataServiceProxy::soap_fault_string()
{	return *soap_faultstring(this);
}

const char *ConsoleDataServiceProxy::soap_fault_detail()
{	return *soap_faultdetail(this);
}

int ConsoleDataServiceProxy::soap_close_socket()
{	return soap_closesock(this);
}

void ConsoleDataServiceProxy::soap_print_fault(FILE *fd)
{	::soap_print_fault(this, fd);
}

#ifndef WITH_LEAN
void ConsoleDataServiceProxy::soap_stream_fault(std::ostream& os)
{	::soap_stream_fault(this, os);
}

char *ConsoleDataServiceProxy::soap_sprint_fault(char *buf, size_t len)
{	return ::soap_sprint_fault(this, buf, len);
}
#endif

int ConsoleDataServiceProxy::removeAnnotation(const char *endpoint, const char *soap_action, LONG64 annotationId, struct fw__removeAnnotationResponse &_param_1)
{	struct soap *soap = this;
	struct fw__removeAnnotation soap_tmp_fw__removeAnnotation;
	if (endpoint)
		soap_endpoint = endpoint;
	if (!soap_endpoint)
		soap_endpoint = "http://localhost:30001/axis2/services/cds";
	if (!soap_action)
		soap_action = "";
	soap->encodingStyle = NULL;
	soap_tmp_fw__removeAnnotation.annotationId = annotationId;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_fw__removeAnnotation(soap, &soap_tmp_fw__removeAnnotation);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_fw__removeAnnotation(soap, &soap_tmp_fw__removeAnnotation, "fw:removeAnnotation", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_fw__removeAnnotation(soap, &soap_tmp_fw__removeAnnotation, "fw:removeAnnotation", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&_param_1)
		return soap_closesock(soap);
	soap_default_fw__removeAnnotationResponse(soap, &_param_1);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	soap_get_fw__removeAnnotationResponse(soap, &_param_1, "fw:removeAnnotationResponse", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int ConsoleDataServiceProxy::getEntityById(const char *endpoint, const char *soap_action, LONG64 entityId, struct fw__getEntityByIdResponse &_param_2)
{	struct soap *soap = this;
	struct fw__getEntityById soap_tmp_fw__getEntityById;
	if (endpoint)
		soap_endpoint = endpoint;
	if (!soap_endpoint)
		soap_endpoint = "http://localhost:30001/axis2/services/cds";
	if (!soap_action)
		soap_action = "";
	soap->encodingStyle = NULL;
	soap_tmp_fw__getEntityById.entityId = entityId;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_fw__getEntityById(soap, &soap_tmp_fw__getEntityById);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_fw__getEntityById(soap, &soap_tmp_fw__getEntityById, "fw:getEntityById", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_fw__getEntityById(soap, &soap_tmp_fw__getEntityById, "fw:getEntityById", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&_param_2)
		return soap_closesock(soap);
	soap_default_fw__getEntityByIdResponse(soap, &_param_2);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	soap_get_fw__getEntityByIdResponse(soap, &_param_2, "fw:getEntityByIdResponse", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int ConsoleDataServiceProxy::getEntityTree(const char *endpoint, const char *soap_action, LONG64 entityId, struct fw__getEntityTreeResponse &_param_3)
{	struct soap *soap = this;
	struct fw__getEntityTree soap_tmp_fw__getEntityTree;
	if (endpoint)
		soap_endpoint = endpoint;
	if (!soap_endpoint)
		soap_endpoint = "http://localhost:30001/axis2/services/cds";
	if (!soap_action)
		soap_action = "";
	soap->encodingStyle = NULL;
	soap_tmp_fw__getEntityTree.entityId = entityId;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_fw__getEntityTree(soap, &soap_tmp_fw__getEntityTree);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_fw__getEntityTree(soap, &soap_tmp_fw__getEntityTree, "fw:getEntityTree", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_fw__getEntityTree(soap, &soap_tmp_fw__getEntityTree, "fw:getEntityTree", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&_param_3)
		return soap_closesock(soap);
	soap_default_fw__getEntityTreeResponse(soap, &_param_3);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	soap_get_fw__getEntityTreeResponse(soap, &_param_3, "fw:getEntityTreeResponse", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int ConsoleDataServiceProxy::getAnnotationsForEntity(const char *endpoint, const char *soap_action, LONG64 entityId, struct fw__getAnnotationsForEntityResponse &_param_4)
{	struct soap *soap = this;
	struct fw__getAnnotationsForEntity soap_tmp_fw__getAnnotationsForEntity;
	if (endpoint)
		soap_endpoint = endpoint;
	if (!soap_endpoint)
		soap_endpoint = "http://localhost:30001/axis2/services/cds";
	if (!soap_action)
		soap_action = "";
	soap->encodingStyle = NULL;
	soap_tmp_fw__getAnnotationsForEntity.entityId = entityId;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_fw__getAnnotationsForEntity(soap, &soap_tmp_fw__getAnnotationsForEntity);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_fw__getAnnotationsForEntity(soap, &soap_tmp_fw__getAnnotationsForEntity, "fw:getAnnotationsForEntity", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_fw__getAnnotationsForEntity(soap, &soap_tmp_fw__getAnnotationsForEntity, "fw:getAnnotationsForEntity", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&_param_4)
		return soap_closesock(soap);
	soap_default_fw__getAnnotationsForEntityResponse(soap, &_param_4);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	soap_get_fw__getAnnotationsForEntityResponse(soap, &_param_4, "fw:getAnnotationsForEntityResponse", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int ConsoleDataServiceProxy::getAnnotationsForEntities(const char *endpoint, const char *soap_action, ns2__longArray *entityIds, struct fw__getAnnotationsForEntitiesResponse &_param_5)
{	struct soap *soap = this;
	struct fw__getAnnotationsForEntities soap_tmp_fw__getAnnotationsForEntities;
	if (endpoint)
		soap_endpoint = endpoint;
	if (!soap_endpoint)
		soap_endpoint = "http://localhost:30001/axis2/services/cds";
	if (!soap_action)
		soap_action = "";
	soap->encodingStyle = NULL;
	soap_tmp_fw__getAnnotationsForEntities.entityIds = entityIds;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_fw__getAnnotationsForEntities(soap, &soap_tmp_fw__getAnnotationsForEntities);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_fw__getAnnotationsForEntities(soap, &soap_tmp_fw__getAnnotationsForEntities, "fw:getAnnotationsForEntities", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_fw__getAnnotationsForEntities(soap, &soap_tmp_fw__getAnnotationsForEntities, "fw:getAnnotationsForEntities", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&_param_5)
		return soap_closesock(soap);
	soap_default_fw__getAnnotationsForEntitiesResponse(soap, &_param_5);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	soap_get_fw__getAnnotationsForEntitiesResponse(soap, &_param_5, "fw:getAnnotationsForEntitiesResponse", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int ConsoleDataServiceProxy::getCurrentOntology(const char *endpoint, const char *soap_action, struct fw__getCurrentOntologyResponse &_param_6)
{	struct soap *soap = this;
	struct fw__getCurrentOntology soap_tmp_fw__getCurrentOntology;
	if (endpoint)
		soap_endpoint = endpoint;
	if (!soap_endpoint)
		soap_endpoint = "http://localhost:30001/axis2/services/cds";
	if (!soap_action)
		soap_action = "";
	soap->encodingStyle = NULL;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_fw__getCurrentOntology(soap, &soap_tmp_fw__getCurrentOntology);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_fw__getCurrentOntology(soap, &soap_tmp_fw__getCurrentOntology, "fw:getCurrentOntology", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_fw__getCurrentOntology(soap, &soap_tmp_fw__getCurrentOntology, "fw:getCurrentOntology", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&_param_6)
		return soap_closesock(soap);
	soap_default_fw__getCurrentOntologyResponse(soap, &_param_6);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	soap_get_fw__getCurrentOntologyResponse(soap, &_param_6, "fw:getCurrentOntologyResponse", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int ConsoleDataServiceProxy::reservePort(const char *endpoint, const char *soap_action, std::string clientName, struct fw__reservePortResponse &_param_7)
{	struct soap *soap = this;
	struct fw__reservePort soap_tmp_fw__reservePort;
	if (endpoint)
		soap_endpoint = endpoint;
	if (!soap_endpoint)
		soap_endpoint = "http://localhost:30001/axis2/services/cds";
	if (!soap_action)
		soap_action = "";
	soap->encodingStyle = NULL;
	soap_tmp_fw__reservePort.clientName = clientName;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_fw__reservePort(soap, &soap_tmp_fw__reservePort);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_fw__reservePort(soap, &soap_tmp_fw__reservePort, "fw:reservePort", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_fw__reservePort(soap, &soap_tmp_fw__reservePort, "fw:reservePort", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&_param_7)
		return soap_closesock(soap);
	soap_default_fw__reservePortResponse(soap, &_param_7);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	soap_get_fw__reservePortResponse(soap, &_param_7, "fw:reservePortResponse", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int ConsoleDataServiceProxy::registerClient(const char *endpoint, const char *soap_action, int _port, std::string _endpointUrl, struct fw__registerClientResponse &_param_8)
{	struct soap *soap = this;
	struct fw__registerClient soap_tmp_fw__registerClient;
	if (endpoint)
		soap_endpoint = endpoint;
	if (!soap_endpoint)
		soap_endpoint = "http://localhost:30001/axis2/services/cds";
	if (!soap_action)
		soap_action = "";
	soap->encodingStyle = NULL;
	soap_tmp_fw__registerClient._port = _port;
	soap_tmp_fw__registerClient._endpointUrl = _endpointUrl;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_fw__registerClient(soap, &soap_tmp_fw__registerClient);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_fw__registerClient(soap, &soap_tmp_fw__registerClient, "fw:registerClient", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_fw__registerClient(soap, &soap_tmp_fw__registerClient, "fw:registerClient", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&_param_8)
		return soap_closesock(soap);
	soap_default_fw__registerClientResponse(soap, &_param_8);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	soap_get_fw__registerClientResponse(soap, &_param_8, "fw:registerClientResponse", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int ConsoleDataServiceProxy::createAnnotation(const char *endpoint, const char *soap_action, fw__ontologyAnnotation *annotation, struct fw__createAnnotationResponse &_param_9)
{	struct soap *soap = this;
	struct fw__createAnnotation soap_tmp_fw__createAnnotation;
	if (endpoint)
		soap_endpoint = endpoint;
	if (!soap_endpoint)
		soap_endpoint = "http://localhost:30001/axis2/services/cds";
	if (!soap_action)
		soap_action = "";
	soap->encodingStyle = NULL;
	soap_tmp_fw__createAnnotation.annotation = annotation;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_fw__createAnnotation(soap, &soap_tmp_fw__createAnnotation);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_fw__createAnnotation(soap, &soap_tmp_fw__createAnnotation, "fw:createAnnotation", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_fw__createAnnotation(soap, &soap_tmp_fw__createAnnotation, "fw:createAnnotation", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&_param_9)
		return soap_closesock(soap);
	soap_default_fw__createAnnotationResponse(soap, &_param_9);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	soap_get_fw__createAnnotationResponse(soap, &_param_9, "fw:createAnnotationResponse", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int ConsoleDataServiceProxy::getKeybindings(const char *endpoint, const char *soap_action, LONG64 ontologyId, struct fw__getKeybindingsResponse &_param_10)
{	struct soap *soap = this;
	struct fw__getKeybindings soap_tmp_fw__getKeybindings;
	if (endpoint)
		soap_endpoint = endpoint;
	if (!soap_endpoint)
		soap_endpoint = "http://localhost:30001/axis2/services/cds";
	if (!soap_action)
		soap_action = "";
	soap->encodingStyle = NULL;
	soap_tmp_fw__getKeybindings.ontologyId = ontologyId;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_fw__getKeybindings(soap, &soap_tmp_fw__getKeybindings);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_fw__getKeybindings(soap, &soap_tmp_fw__getKeybindings, "fw:getKeybindings", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_fw__getKeybindings(soap, &soap_tmp_fw__getKeybindings, "fw:getKeybindings", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&_param_10)
		return soap_closesock(soap);
	soap_default_fw__getKeybindingsResponse(soap, &_param_10);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	soap_get_fw__getKeybindingsResponse(soap, &_param_10, "fw:getKeybindingsResponse", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int ConsoleDataServiceProxy::getParentEntityDataArray(const char *endpoint, const char *soap_action, LONG64 childEntityId, struct fw__getParentEntityDataArrayResponse &_param_11)
{	struct soap *soap = this;
	struct fw__getParentEntityDataArray soap_tmp_fw__getParentEntityDataArray;
	if (endpoint)
		soap_endpoint = endpoint;
	if (!soap_endpoint)
		soap_endpoint = "http://localhost:30001/axis2/services/cds";
	if (!soap_action)
		soap_action = "";
	soap->encodingStyle = NULL;
	soap_tmp_fw__getParentEntityDataArray.childEntityId = childEntityId;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_fw__getParentEntityDataArray(soap, &soap_tmp_fw__getParentEntityDataArray);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_fw__getParentEntityDataArray(soap, &soap_tmp_fw__getParentEntityDataArray, "fw:getParentEntityDataArray", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_fw__getParentEntityDataArray(soap, &soap_tmp_fw__getParentEntityDataArray, "fw:getParentEntityDataArray", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!&_param_11)
		return soap_closesock(soap);
	soap_default_fw__getParentEntityDataArrayResponse(soap, &_param_11);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	soap_get_fw__getParentEntityDataArrayResponse(soap, &_param_11, "fw:getParentEntityDataArrayResponse", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

} // namespace cds

/* End of client proxy code */
