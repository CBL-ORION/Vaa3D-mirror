#include "DataThread.h"
#include "../entity_model/Entity.h"
#include "../entity_model/Ontology.h"
#include "../entity_model/OntologyAnnotation.h"
#include "../../webservice/impl/EntityAdapter.h"
#include <QMap>

DataThread::DataThread(QObject *parent) :
    QThread(parent),
    results(0),
    errorMessage(0)
{
}

DataThread::~DataThread()
{
    proxy.destroy();
    if (errorMessage != 0) delete errorMessage;
}

void DataThread::run()
{
    fetchData();
    if (errorMessage != 0) {
        qDebug() << "SOAP error:" << *errorMessage;
        emit gotError(*errorMessage);
    }
    else {
        emit gotResults(results);
    }
}

void DataThread::disregard()
{
    disconnect(this, 0, 0, 0);
    connect(this, SIGNAL(finished()), this, SLOT(deleteLater()));
}


// ===========================================================
// Get Current Ontology Tree
// ===========================================================

GetCurrentOntologyThread::GetCurrentOntologyThread(QObject *parent) :
    DataThread(parent)
{
}

void GetCurrentOntologyThread::fetchData()
{

    Entity *root = 0;
    QMap<QKeySequence, qint64> *keyBindMap = 0;

    qDebug() << "Getting current ontology...";
    cds::fw__getCurrentOntologyResponse response;
    if (proxy.getCurrentOntology(response) == SOAP_OK)
    {
        root = EntityAdapter::convert(response.return_);

        qDebug() << "Getting current ontology keybindings...";
        cds::fw__getKeybindingsResponse keybindingsResponse;
        if (proxy.getKeybindings(*root->id, keybindingsResponse) == SOAP_OK)
        {
            cds::fw__ontologyKeyBindings *keyBindings = keybindingsResponse.return_;
            keyBindMap = EntityAdapter::convert(keyBindings);
        }
        else
        {
            errorMessage = new QString(proxy.soap_fault_string());
            delete root;
            return;
        }
    }
    else
    {
        errorMessage = new QString(proxy.soap_fault_string());
        return;
    }

    results = new Ontology(root, keyBindMap);
}

// ===========================================================
// Get AnnotatedBranch
// ===========================================================

GetAnnotatedBranchThread::GetAnnotatedBranchThread(long entityId, QObject *parent) :
    DataThread(parent),
    entityId(entityId)
{
}

void GetAnnotatedBranchThread::fetchAnnotations(Entity *entity)
{
    if (entity == NULL) return;

    cds::fw__getAnnotationsForEntityResponse response;
    if (proxy.getAnnotationsForEntity(*entity->id, response) == SOAP_OK)
    {
        AnnotationList *alist = EntityAdapter::convert(response.return_);
        annotationMap->insert(*entity->id, alist);
    }
    else
    {
        // This overrides the last error message, but the user doesn't need all of them, and they've already been logged.
        errorMessage = new QString(proxy.soap_fault_string());
    }

    QSetIterator<EntityData *> i(entity->entityDataSet);
    while (i.hasNext())
    {
        EntityData *data = i.next();
        fetchAnnotations(data->childEntity);
    }
}

void GetAnnotatedBranchThread::fetchData()
{
    Entity *entity;
    cds::fw__getEntityTreeResponse response;
    if (proxy.getEntityTree(entityId, response) == SOAP_OK)
    {
        // Convert the results into the Entity model
        entity = EntityAdapter::convert(response.return_);
        // Recursively retrieve annotations for every entity in the tree and populate the annotationMap
        annotationMap = new QHash<qint64, AnnotationList*>;
        fetchAnnotations(entity);
    }
    else
    {
        errorMessage = new QString(proxy.soap_fault_string());
        return;
    }

    results = new AnnotatedBranch(entity, annotationMap);
}

// ===========================================================
// Get Entity
// ===========================================================

GetEntityThread::GetEntityThread(long entityId, QObject *parent) :
    DataThread(parent),
    entityId(entityId)
{
}

void GetEntityThread::fetchData()
{
    cds::fw__getEntityByIdResponse response;
    if (proxy.getEntityById(entityId, response) == SOAP_OK)
    {
        results = EntityAdapter::convert(response.return_);        
    }
    else
    {
        errorMessage = new QString(proxy.soap_fault_string());
    }
}

// ===========================================================
// Get Entity Annotations
// ===========================================================

GetEntityAnnotationsThread::GetEntityAnnotationsThread(long entityId, QObject *parent) :
    DataThread(parent),
    entityId(entityId)
{
}

void GetEntityAnnotationsThread::fetchData()
{
    cds::fw__getAnnotationsForEntityResponse response;
    if (proxy.getAnnotationsForEntity(entityId, response) == SOAP_OK)
    {
        results = EntityAdapter::convert(response.return_);
    }
    else
    {
        errorMessage = new QString(proxy.soap_fault_string());
    }
}

// ===========================================================
// Create Annotation
// ===========================================================

CreateAnnotationThread::CreateAnnotationThread(OntologyAnnotation *annotation, QObject *parent) :
    DataThread(parent), annotation(annotation)
{
}

CreateAnnotationThread::~CreateAnnotationThread()
{
    if (annotation!=0) delete annotation;
}

void CreateAnnotationThread::fetchData()
{
    cds::fw__ontologyAnnotation *fwAnnotation = EntityAdapter::convertAnnotation(annotation);
    cds::fw__createAnnotationResponse response;
    if (proxy.createAnnotation(fwAnnotation, response) == SOAP_OK)
    {
        // Assume success
    }
    else
    {
        errorMessage = new QString(proxy.soap_fault_string());
    }

    delete fwAnnotation;
}

qint64* CreateAnnotationThread::getTargetEntityId() const
{
    return annotation->targetEntityId;
}

// ===========================================================
// Remove Annotation
// ===========================================================

RemoveAnnotationThread::RemoveAnnotationThread(qint64 annotationId, QObject *parent) :
    DataThread(parent), annotationId(annotationId)
{
}

void RemoveAnnotationThread::fetchData()
{
    cds::fw__removeAnnotationResponse response;
    if (proxy.removeAnnotation(annotationId, response) == SOAP_OK)
    {
        // Assume success
    }
    else
    {
        errorMessage = new QString(proxy.soap_fault_string());
    }
}
